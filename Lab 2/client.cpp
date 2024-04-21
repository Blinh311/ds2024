#include <iostream>
#include <fstream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "file_transfer.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using filetransfer::FileTransfer;
using filetransfer::FileRequest;
using filetransfer::FileResponse;
using filetransfer::FileChunk;
using filetransfer::Empty;

// Client class for file transfer
class FileTransferClient {
public:
    // Constructor to initialize gRPC stub
    FileTransferClient(std::shared_ptr<Channel> channel)
            : stub_(FileTransfer::NewStub(channel)) {}

    // Method to send file to server
    bool SendFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file for reading" << std::endl;
            return false;
        }

        // Read file content
        FileRequest request;
        request.set_filename(filename);
        std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        request.set_content(content);

        // Call SendFile RPC
        FileResponse response;
        ClientContext context;
        Status status = stub_->SendFile(&context, request, &response);
        if (status.ok() && response.success()) {
            std::cout << "File sent successfully!" << std::endl;
            return true;
        } else {
            std::cerr << "Error sending file: " << status.error_message() << std::endl;
            return false;
        }
    }

    // Method to receive file from server
    void ReceiveFile() {
        FileTransfer::Stub stub(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
        Empty request;
        FileChunk chunk;
        ClientContext context;

        // Open file for writing
        std::ofstream file("received_file.txt", std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file for reading" << std::endl;
            return;
        }
        // Receive file chunks and write to disk
        while (!file.eof()) {
            chunk.set_content(std::string((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>())));
            Status status = stub.ReceiveFile(&context, chunk, &request);
            if (!status.ok()) {
                std::cerr << "Error receiving file: " << status.error_message() << std::endl;
                return;
            }
        }
        std::cout << "File received successfully!" << std::endl;
    }

private:
    std::unique_ptr<FileTransfer::Stub> stub_;
};

// Main function
int main(int argc, char** argv) {
    FileTransferClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    client.SendFile("sample_file.txt");
    client.ReceiveFile();
    return 0;
}
