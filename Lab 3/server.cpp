#include <iostream>
#include <fstream>
#include <mpi.h>

#define FILENAME "received_file.txt"

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) {
        // Server process
        std::ofstream file(FILENAME, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file for writing" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        MPI_Status status;
        char buffer[1024];
        int bytes_received;

        // Receive file from client
        MPI_Recv(&bytes_received, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        while (bytes_received > 0) {
            MPI_Recv(buffer, 1024, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
            file.write(buffer, bytes_received);
            MPI_Recv(&bytes_received, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        }

        file.close();
        std::cout << "File received successfully!" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
