Important concept,big endian and small endian 
htops converts small endian(most intelx86 systems) to big endian(network byte order)

Value: 0x12345678
BIG ENDIAN(Low → High Address)
+----+----+----+----+
| 12 | 34 | 56 | 78 |
+----+----+----+----+
MSB              LSB

Value: 0x12345678
SMALL ENDIAN(Low → High Address)
+----+----+----+----+
| 78 | 56 | 34 | 12 |
+----+----+----+----+
LSB              MSB

accept and recv are blocking calls
accept() is used by the server to accept a connection request from a client.It blocks until a client connects to the server. Once a connection is established, accept() returns a new socket descriptor

multithreading helps to avoid blocking problems 
select() / poll() / epoll() (real scalable solution) other than multithreading to avoid blocking problems

//The overall process of a TCP connection from the client to the server:

<Client Application>>
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

TCP - Tranmission Control Protocol
NIC - Network Interface Card
ARP - Address Resolution Protocol
MAC - Media Access Control