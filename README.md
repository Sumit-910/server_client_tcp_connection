# TCP Server-Client Communication

This project consists of two programs, a TCP server (`server`) and a TCP client (`client`), written in C. These programs facilitate communication between a server and a client over TCP/IP.

## Getting Started

### Cloning the Repository

To get started with this project, you can clone the repository from GitHub. Open a terminal and run the following command:

```sh
git clone <repository_url>


## Usage

1. **Compilation**: Compile the server and client programs using the provided Makefile. Open a terminal in the project directory and run the following command:
    ```
    make
    ```
    This will compile the `server.c` and `client.c` files into executables named `server` and `client`, respectively.

2. **Running the Server**: Start the server by executing the following command in the terminal:
    ```
    ./server <port>
    ```
    The server will start listening for incoming connections on a specified port.

3. **Running the Client**: Open another terminal window (or a separate machine) and run the client program using the following command:
    ```
    ./client <ip_address> <port>
    ```
    The client will connect to the server and initiate communication.

4. **Cleaning Up**: After you're done, you can clean up the generated files using the following command:
    ```
    make clean
    ```
    This will remove the executables and object files.

