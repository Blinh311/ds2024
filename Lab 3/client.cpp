#include <iostream>
#include <fstream>
#include <mpi.h>

#define FILENAME "sample_file.txt"

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 1) {
        // Client process
        std::ifstream file(FILENAME, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file for reading" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        MPI_Status status;
        char buffer[1024];
        int bytes_read;

        // Send file to server
        file.seekg(0, std::ios::end);
        int file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        MPI_Send(&file_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        while (!file.eof()) {
            file.read(buffer, 1024);
            bytes_read = file.gcount();
            MPI_Send(buffer, bytes_read, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }

        file.close();
        std::cout << "File sent successfully!" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
