#Bradley Gardner
#bookClient.py
#Assignment 4
#Reads an entire book and picks out the 50 most common words
#This then connects to the server and receives either a
#server or a client designation. This will either then
#connect to the new server or listen for a connection, at
#which point it will exchange messages. After the exchange, it
#will send the book it had read, along with receive the other book
#and find the most commonly used words in both books, and print out
#the total number of times they are used in both books combined
import socket
import os
import sys
import os.path
import pickle
from collections import Counter

def compareBooks(dataList):
    outputList = []
    #split the received book into two lists
    words, count = zip(*dataList)


    for word in mostCommon.most_common(50):
#if a word is shared between both book, add word
#and their combined total to the list
        if word[0] in words:
            #since words and count are one to one,
            #retreive the item at the index of the 
            #matched word in the words list
            amount = count[words.index(word[0])]
            outputList.append((word[0], word[1]+amount))

    #sort outputList based on the count values
    outputList = sorted(outputList, key=lambda x: x[1])
    
    #reverse outputList to display the larger values first
    outputList.reverse()

    print ("Word          count")
    for pair in outputList:
        print(pair[0].ljust(16)+str(pair[1]))
        

def becomeServer(port):
    #create a server using a specified port and the local
    #host name
    cs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = socket.gethostname()
    cs.bind((host, port))
    cs.listen(5)

    #receive a new client
    oc, addr = cs.accept()
    print("Got connection from client peer")

    #exchange friendly messages between client and server
    oc.send("Nice to meet you!".encode('UTF-8'))
    print("Sent a message to client peer, Nice to meet you!")

    message = oc.recv(1024).decode('UTF-8')
    print("I received a message from client peer " + message)

    #receive a pcikled book from the client and unpack it
    data = oc.recv(4096)
    dataList = pickle.loads(data)

    #pickle your own book and send it to the client
    ownBook = pickle.dumps(mostCommon.most_common(50))
    oc.send(ownBook)
    print("I sent my book data")

    #compare the two books and close the connection
    compareBooks(dataList)
    oc.close()

def becomeClient(port, IP):
    #if either the port or the IP was not received
    #stop
    if port=='' or IP =='':
        print("An error occurred")
        sys.exit(0)

    #retrieve the hostname
    serverName = socket.gethostbyaddr(IP)
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    #make a connection and exchange friendly banter
    print("Making connection to server peer")
    server.connect((serverName[0], int(port)))
    print("My connection was accepted")

    message = server.recv(1024).decode('UTF-8')
    print("I received a message from peer server " + message)

    server.send("Nice to meet you too!".encode('UTF-8'))
    print("Sent a message to server peer")

    #pickle the list of the most common words in the book
    data = pickle.dumps(mostCommon.most_common(50))
    server.send(data)
    print("I sent my book")
    
    #receive the list from the server and unpack it
    sBook = server.recv(4096)
    bookList = pickle.loads(sBook)
    compareBooks(bookList)
    server.close()


#BEGIN MAIN CODE
#in an effort to save space, if the book isn't already on the local
#machine, retrieve it
if not os.path.exists("84-0.txt"):
    fileBook = os.system('wget http://www.gutenberg.org/files/84/84-0.txt')
book = open("84-0.txt", mode="r")

#convert the book into lowercase, to prevent duplicate words
contents = book.read().lower()
correctedContents =""

#remove any and all nonalphabetic characters from the book
for letter in contents:
    if letter.isalpha():
        correctedContents+=letter
    else:
        correctedContents+=" "

#cut the book up into a list of string that are seperated by 
#a space
words = correctedContents.split(" ")

#ignore all words that are less than length 5
fiveLetterWords = []
for word in words:
    if len(word) >=5:
        fiveLetterWords.append(word)
mostCommon = Counter(fiveLetterWords)

#connect to the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = sys.argv[1]
port = int(sys.argv[2])

s.connect((host, port))

print("Thank you for connecting from Torrent Server")
name = s.recv(1024).decode('UTF-8')

#if the client receives word that it is a server
#send the port number to the server, close the 
#socket and launch a new server
if name == "server":
    print("Got message that I am a peer server")
    s.send((sys.argv[3]).encode('UTF-8'))
    s.close()
    becomeServer(int(sys.argv[3]))

#if the client receives word that it is still a client
#extract the ip and port number from the designation sent
elif "client" in name:

    items = name.split(":")

    print("Got message that I am a peer client")

    print("Requesting ip address of server peer")
    IPClient = items[1]
    print("Received ip address " + IPClient)

    print("Requested port of server peer")
    portClient = items[2]
    print("Received port " + portClient)

    #close the socket and become a client again
    s.close()
    becomeClient(portClient, IPClient)

