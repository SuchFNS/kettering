--------README.md----------

server.py:
This acts as the connection point for peers to meet through. The 
first peer to connect will be designated as the host peer, and any
sequential connections will be client peers. The host peer will get 
the hostname and port of the server, then end the connection. The client
peer will be sent the host peer's IP and port number and then the 
connection will end. The 2 clients can now communicate through their own 
peer to peer network. 
In order to execute this server, enter:
python server.py <port number> &

clientChristie.py:
This will act as a peer, whether it be the host peer or client peer. 
It will download a book at a given link within the code if it is not 
already found on the system. It will then split the entire book into 
a list of words, and get rid of any words shorter than 5 characters, 
and count the 50 most used words throughout the entire book. It will 
then connect to the server and be designated as either a host peer or 
client peer. If host peer, then it will give the server its chosen
port number and bind to that port number. If client peer, it will 
contact the server and receive the port and connect to the host peer.
After connection between peers, they will exchange greetings and their 
list of the most used words in their respective books. Once that message
is received, each peer will compare the lists and output the words that 
match both lists, and the word counts will be added together.
**There are two seperate programs for these clients:**
I used clientChristie.py as the host peer, and clientMelville.py as client
In order to execute this client, enter:
python clientChristie.py <server hostname> <port of server> <host port number>
and 
python clientMelville.py <server hostname> <port of server>