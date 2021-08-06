#Bradley Gardner
#bookServer.py
#Assignment 4
#The purpose of this is to act as a server to connect two clients together
#the first client to connect is told that it is to become a server, and 
#the server receives the port number that the client will be listening on
#and keeps track of that client's IP. The second client to connect
#is told that it is still a client and gives it the information that it
#needs to be able to connect to the new server
import socket,sys

#set up a socket
server=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
firstSocket = True
clientPort=""
clientIP=""
host = socket.gethostname()
port = int(sys.argv[1])

#bind the socket to a hostname and port
server.bind((host, port))
server.listen(5)

#continue until the server is stopped
while True:
    #wait for a client to connect
    client, addr = server.accept()

    #say which client connected
    print("Got a connection from " + str(addr))

    #if the client is the first to connect, tell it that
    #it is the server and receive the port number
    #the server keeps track of this client's IP
    if firstSocket:
        client.send("server".encode('UTF-8'))
        clientPort = client.recv(1024).decode('UTF-8') 
        clientIP = addr[0]
        print("The port number received from server peer is " + clientPort)
        firstSocket = not firstSocket

    #if the client is not the first to arrive, inform it that it 
    #is a client and send it the IP and port of the other client
    else:
        clientString = "client:"+clientIP+":"+clientPort
        client.send(clientString.encode('UTF-8'))
        firstSocket = not firstSocket
    client.close()
