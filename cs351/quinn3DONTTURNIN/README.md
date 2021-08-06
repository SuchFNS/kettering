--------README.md----------

chatServer.py:
Acts as a connection point for 2 clients to connect through.
This server will determine which client sent a message and 
forward that message to the other clients connected at the 
time. In order to start this server, enter:
$ python chatServer.py

chatClient.py:
Allows clients to connect to the chat server, and lets them 
send messages through to each other. Displays which client
sent the message and what the message is. To run this, enter:
$ python chatClient.py <server IP> <port number>

ticTacClient.py:
Allows players to connect to the ticTacServer and play against 
other players. The client side reads input from players and 
sends the information to the server. Upon receiving a message
back from the server, the client will display the state of the 
game such as the current board and whose turn it currently is.
In order to run this client, enter:
$ python ticTacClient.py <server IP> <port number>

ticTacServer.py:
Acts as the server for the tic tac toe game. Uses inputs from 
multiple clients to play the game, where clients are split into
teams X and O. Teams should always be at most one person more than
the other team, and should any player disconnect, the rest of the 
players are notified. If that player was the last one left on their 
respective team, then the other team wins by forfeit. A team wins 
when they have placed 3 of their respective marks on the board first,
otherwise they draw when there are no other places to play left.
Then the server will display the end condition of the game (win or 
draw), and remove all connections to the clients before shutting down.
To run this server, enter:
$ python ticTacServer.py <port number> &