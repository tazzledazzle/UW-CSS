
Program 1: Sockets
======================
Professor: Munehiro Fukuda
Due date: See the syllabus

1. Purpose
===

This assignment is intended for two purposes: (1) to exercise use of various socket-related system calls and (2) to evaluate dominant overheads of point-to-point communication over 1Gbps networks.

2. Client-Server Model
===

In all your programming assignments through to the final project, your program will use the client-server model where a client process establishes a connection to a server, sends data or requests, and closes the connection while the server sends back responses or acknowledgments to the client.

3. TCP Communication
=========

HW1 focuses on basic connection-oriented socket (SOCK_STREAM) communication between a client and a server process. To establish such communication, those processes should perform the following sequence of operations:
