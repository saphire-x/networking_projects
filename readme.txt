concept of big endian and small endian 
htops converts small endian(most intelx86 systems ) to big endia(network byte order)
small endian (0x12345678)
big endian(0x876544321)

accept and recv are blocking calls
accept() is used by the server to accept a connection request from a client. It blocks until a client connects to the server. Once a connection is established, accept() returns a new socket descriptor

multithreading helps to avoid blocking problems 
select() / poll() / epoll() (real scalable solution) other than multithreading to avoid blocking problems

//FUll process of a TCP connection from the client to the server:
Client Application
    connect()
        ↓
TCP adds ports
        ↓
IP adds addresses
        ↓
ARP finds MAC
        ↓
Ethernet/WiFi frame
        ↓
Signals travel
        ↓
Server NIC receives
        ↓
Kernel TCP stack
        ↓
listen queue
        ↓
epoll wakes
        ↓
accept()
        ↓
client socket created
        ↓
recv()
        ↓
your program gets data