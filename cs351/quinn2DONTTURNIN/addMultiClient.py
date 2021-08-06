#Colin Quinn
#Cloud Computing Assignment 2
#Client to connect to two different RPC servers, one for addition and one for 
#multiplication. This then reads a file, and depending on the first character
#in each line, will send the following 2 numbers to the corresponding server.
#The addresses for the servers and the filename is provided by the command
#prompt
import xmlrpc.client
import string
import sys

addServer = xmlrpc.client.ServerProxy(sys.argv[2])
multiServer = xmlrpc.client.ServerProxy(sys.argv[3])

with open(sys.argv[1], "r") as read:
    for line in read:
        values = line.split()
        #If the first character is an A, pass the integer value of the next 2
        #characters to the add server. If it starts with an M, send it to the
        #multiply server.
        if(values[0].upper()=="A"):
            print (values[1]+" + "+values[2]+" = "+str(addServer.add(int(values[1]),
                     int(values[2]))))
        elif(values[0].upper()=="M"):
            print (values[1]+" * "+values[2]+" = "+str(multiServer.multi(
                    int(values[1]),int(values[2]))))

