import socket

# Define the port number for communication
PORT = 9090


def receive_file():
    # Create a TCP socket
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to an address (empty string means all available interfaces) and the specified port
    server.bind(("", PORT))

    # Listen for incoming connections
    server.listen()

    print("Server is listening for incoming connections...")

    # Accept a connection from a client
    communication_socket, address = server.accept()
    print(f"Connected to {address}")

    # Specify the file name to save the received data
    file_name = "received_file.txt"

    # Receive data from the client and write it to the file
    with open(file_name, "wb") as file:
        while True:
            data = communication_socket.recv(1024)
            if not data:
                break
            file.write(data)

    print(f"File '{file_name}' received successfully!")

    # Close the communication socket and the server socket
    communication_socket.close()
    server.close()


if __name__ == "__main__":
    receive_file()
