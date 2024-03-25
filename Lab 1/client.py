import socket
import os

# Get the IP address of the server
HOST = socket.gethostbyname("192.168.189.131")
# Specify the port number for communication
PORT = 9090


def send_file():
    # Staring a TCP socket.
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    #  Connecting to the server
    client.connect((HOST, PORT))

    # Specify the file to be sent
    file_name = "sample_file.txt"

    if os.path.exists(file_name):
        # Open the file in binary read mode
        with open(file_name, "rb") as file:
            while True:
                # Read data from the file in chunks of 1024 bytes
                data = file.read(1024)
                if not data:
                    break
                # Send the data to the server
                client.sendall(data)

        print(f"File '{file_name}' sent successfully!")
    else:
        print(f"File '{file_name}' not found.")

    client.close()


if __name__ == "__main__":
    send_file()
