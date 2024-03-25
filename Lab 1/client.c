#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.189.131"
#define PORT 12345

int main()
{
    int client_fd;
    struct sockaddr_in server_address;

    // Create socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0)
    {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Send file to server
    FILE *file_to_send = fopen("sample_file.txt", "rb");
    if (file_to_send)
    {
        char buffer[1024];
        while (1)
        {
            int bytes_read = fread(buffer, 1, sizeof(buffer), file_to_send);
            if (bytes_read <= 0)
                break;
            send(client_fd, buffer, bytes_read, 0);
        }
        fclose(file_to_send);
        printf("File sent successfully!\n");
    }
    else
    {
        printf("File not found.\n");
    }

    close(client_fd);
    return 0;
}
