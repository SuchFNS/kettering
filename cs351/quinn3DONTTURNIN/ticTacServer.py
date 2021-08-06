#Colin Quinn
#Cloud Assignment 3
#Acts as the server for users to play tic tac toe.
#The server assigns each user to a team (X or O).
#after receiving a message with the desired move from the
#first user of the currently selected team, the server
#makes sure that the spot is valid and send the updated
#board to each client. The game ends when either team gets
#three consecutive pieces, or there are no valid spots left,
#the server displays reason for end of game, and disconnects
#clients before shutting itself down
import sys
import socket
import select
import time

#globals for server
HOST = socket.gethostname()
SOCKET_LIST=[]
TEAM_X_LIST=[]
TEAM_O_LIST=[]
RECV_BUFFER = 4096
PORT = int(sys.argv[1])

def tic_tac_server():
    players=0
    started = False
    teamXTurn=True
    turnTaken = False
    lock = False
    win = False
    draw = False

    #create server and reserve/bind hostname and port
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((HOST, PORT))
    server_socket.listen(10)

    #selected team variable
    team = "\nTeam X"

    error = "\nInput is not valid, please enter a previously unselected position\n" +\
		"of the form (x,y) to choose a spot to play."
    #add this socket to the list of used sockets
    SOCKET_LIST.append(server_socket)

    #make blank game board, and list of points that are used
    board=createboard()
    usedPoints =[]
    print("Game starting! The connection port is: " + str(PORT))

    #main game loop, end condition is within this loop
    while 1:

        #if game is over, remove all connections and close server
        if win or draw:
            boot(server_socket)
            sys.exit(0)

        #end game if either team loses all of their players or disconnects
        if started and (len(TEAM_X_LIST)==0 or len(TEAM_O_LIST)==0):
            boot(server_socket)
            sys.exit(0)

        #get lists of players and their status as ready or in error
        ready_to_read,ready_to_write,in_error=select.select(SOCKET_LIST,[],[],0)

        #check every socket (player) that is ready to read data from server
        for sock in ready_to_read:
            #if a new player joins, add them to the list of sockets
            if sock==server_socket:
                sockfd, addr=server_socket.accept()
                SOCKET_LIST.append(sockfd)
                temp=""

                #assign the new player to either team based on sizes
                if players%2==0:
                    TEAM_X_LIST.append(sockfd)
                    temp="X"
                else:
                    TEAM_O_LIST.append(sockfd)
                    temp="O"
                #confirm that new player has connected
                print("Client connected from " + addr)

                #announce that a new player has joined, send them the board and their team assignment
                broadcast(server_socket, sockfd, "\nNew player connected!\n")
                sockfd.send(bytes(team+"'s turn\n" + printBoard(board) + "\nYou've joined team" +\
                            temp+"! Best of luck!\n", 'UTF-8'))
                
                #add one to the amount of players
                players+=1

                #check if there are at least 2 players to start the game
                if players >= 2 and not started:
                    started = True
                    broadcast(server_socket, server_socket, "\nEach team has players, we can start now!  " +\
                                                            "Team X enter your location: (x,y)\n")
            #if a client is not trying to be added
            else:
                #needed in case of failure of any of the following steps
                try:

                    if players>=2 and started:
                        #attempt to retrieve data from a client
                        data = sock.recv(RECV_BUFFER).decode('UTF-8')

                        #check for which team's turn and if data is available
                        if teamXTurn and data:
                            #check if any team X player has selected a location
                            if sock in TEAM_X_LIST and not lock:
                                #lock reading so other team members cannot submit data
                                lock=True
                                #check for data validity and if it causes an ending collision
                                if inputValid(data,usedPoints):
                                    usedPoints.append(data)
                                    board=makeMove(data, teamXTurn, board)
                                    win,draw=detectWinOrDraw(board)
                                    turnTaken=True

                                #if data is invalid, broadcast to all team members to submit a location
                                else:
                                    sock.send(bytes(error,'UTF-8'))
                                    lock=False
                                    broadcastTeamX("\nInvalid data entered, please try again\n")

                            #if player submits data second, notify that they were not fast enough
                            elif sock in TEAM_X_LIST:
                                sock.send(bytes("\nYour submission was not fast enough, using a team member's submission\n",'UTF-8'))

                            #notify player if they are not on the currently selected team, tell them to wait
                            else:
                                sock.send(bytes("\nPlease wait for your team's turn.\n" +\
                                                "You will be notified when you can submit",'UTF-8'))

                        #case if it is team O's turn
                        elif not teamXTurn and data:
                            #the same logic as used above, but for team O
                            if sock in TEAM_O_LIST and not lock:
                                lock=True

                                if inputValid(data, usedPoints):
                                    usedPoints.append(data)
                                    board=makeMove(data, teamXTurn, board)
                                    win,draw=detectWinOrDraw(board)
                                    turnTaken = True

                                else:
                                    sock.send(bytes(error,'UTF-8'))
                                    lock=False
                                    broadcastTeamO("\nInvalid data entered, please try again\n")

                            elif sock in TEAM_O_LIST:
                                sock.send(bytes("\nYour submission was not fast enough, using a team member's submission\n",'UTF-8'))

                            else:
                                sock.send(bytes("\nPlease wait for your team's turn.\n" +\
                                                "You will be notified when you can submit",'UTF-8'))

                        #if the data is invalid, remove the client who sent it
                        #from the socket list and their respective team
                        else:

                            if sock in SOCKET_LIST:
                                SOCKET_LIST.remove(sock)

                            if sock in TEAM_X_LIST:
                                TEAM_X_LIST.remove(sock)

                            elif sock in TEAM_O_LIST:
                                TEAM_O_LIST.remove(sock)
                            #broadcast to the other players that someone left
                            #decrement the number of players and lift the lock if
                            #needed
                            broadcast(server_socket, sock, "\nA player disconnected\n")
                            players -=1
                            lock = False

                        #if a win or draw is detected, stop the game
                        if win or draw:
                            turnTaken = False
                            started = False
                            message = ""
                            #tell the players who the winning team is
                            if win:
                                if teamXTurn:
                                    message = "\nTeam X is the winner! Congrats!\n"
                                else:
                                    message = "\nTeam O is the winner! Congrats!\n"
                            else:
                                message = "\nThe board is full, that means its a draw! Good Game!\n"

                            #broadcast game over message and end the game
                            broadcast(server_socket,server_socket,message + printBoard(board))
                            gameOver(server_socket)
                            #end the game loop, quitting the game
                            break

                        #Swap selected teams after a successful turn
                        if turnTaken:
                            if teamXTurn:
                                team = "Team O"
                            else:
                                team = "Team X"

                            #reinitialize used flags for next turn
                            teamXTurn = not teamXTurn
                            lock = False
                            turnTaken = False

                            #broadcast the game board to the players and update whose turn it is
                            broadcast(server_socket, server_socket,"\n\n\n\n"+  team +"'s turn\n" +\
                            printBoard(board) +"\n"+ team +  " enter your pick\n")

                        #end game if either team has all of their players disconnected
                        if started and (len(TEAM_X_LIST)==0 or len(TEAM_O_LIST)==0):
                            if len(TEAM_X_LIST)==0:
                                broadcastTeamO("\nYour opponents have forfeited\n")
                            else:
                                 broadcastTeamX("\nYour opponents have forfeited\n")
                            gameOver(server_socket)
                            break

                except:
                    #if any exception, remove culprit client and broadcast message
                    if sock in TEAM_X_LIST:
                        TEAM_X_LIST.remove(sock)
                    elif sock in TEAM_O_LIST:
                        TEAM_O_LIST.remove(sock)

                    #remove the client that caused the error
                    SOCKET_LIST.remove(sock)
                    broadcast(server_socket, sock, "\nA player has lost connection\n")
                    sock.close()
                    players = len(SOCKET_LIST)-1
                    lock = False
                    continue
    server_socket.close()


#function to send a message to all clients connected to the server
def broadcast(server_socket, sockfd, message):
    #check all clients in socket list
    for socket in SOCKET_LIST:
        if socket != server_socket and socket!=sockfd:
            try :
                socket.send(bytes(message, 'UTF-8'))
            #if message cannot be sent, close the connection with the socket
            except:
                socket.close()
                if socket in SOCKET_LIST:
                    SOCKET_LIST.remove(socket)
                if socket in TEAM_X_LIST:
                    TEAM_X_LIST.remove(socket)
                elif socket in TEAM_O_LIST:
                    TEAM_O_LIST.remove(socket)

#same as previous broadcast, but specifically to teamX
def broadcastTeamX(message):

    for socket in TEAM_X_LIST:
        try:
            socket.send(bytes(message, 'UTF-8'))
        except:
            socket.close()
            if socket in TEAM_X_LIST and socket in SOCKET_LIST:
                SOCKET_LIST.remove(socket)
                TEAM_X_LIST.remove(socket)


#same as previous broadcast, but specifically to teamO
def broadcastTeamO(message):
    for socket in TEAM_O_LIST:
        try:
            socket.send(bytes(message,'UTF-8'))
        except:
            socket.close()
            if socket in TEAM_O_LIST and socket in SOCKET_LIST:
                SOCKET_LIST.remove(socket)
                TEAM_O_LIST.remove(socket)

#determine if the input is of valid syntax/dimensions
def inputValid(user, used):
    #default value is false
    valid = False
    
    #only set valid = true if all syntax is followed and 
    #the coordinates have not been used yet
    if ("(" in user and ")" in user and "," in user and
    "." not in user and user not in used):
        #remove unneeded chars
        user = user.replace("(","")
        user = user.replace(")","")
        user = user.replace("\n","")
        #split the coordinates into x and y values
        points=user.split(",")

        #verify that x and y values are between 1-9
        if len(points) == 2 and  points[0].isdigit() and points[1].isdigit():
            x = int(points[0])
            y = int(points[1])
            valid = x > 0 and x <10 and y > 0 and y <10

    #return whether data is valid or not
    return valid

#initialize the playing board, must be 9x9
def createboard():
    board=[]
    x = 0
    while (x < 9):
        y = 0
        line = []
        #initialize all spaces as a '_'
        while(y < 9):
            line.append('_')
            y+=1
        board.append(line)
        x+=1
    return board

#print the board as a 2D grid, with dimensions included for easier reading
def printBoard(board):
    rowCount = 1
    output=""
    for line in board:
        output+=str(rowCount)+" "
        for char in line:
            output += char + " "
        output+="\n"
        rowCount+=1
    #append column values to end of board
    output+="  1 2 3 4 5 6 7 8 9\n"
    return output

#function to update the board with the provided coords and previous board
def makeMove(point, player,board):
    #default to team X's turn
    symbol="X"
    #check whose turn it is
    if not player:
        symbol="O"
    #extract x and y values from the input
    point = point.replace("(","")
    point = point.replace(")","")
    point = point.replace("\n","")
    points = point.split(",")
    
    #update the board with the team's guess
    x = int(points[0])
    y = int(points[1])
    board[y-1][x-1]=symbol

    #return the new board
    return board

#check board for a win condition / 3 in a row, or a draw / full board
def detectWinOrDraw(board):
    win = False
    draw = True
    x = 0

    #check rows of the board
    while (x<9):
        y=0

        while (y<9):
            #if any '_'s are found, the board is not yet full
            if board[x][y]=="_":
                draw = False

            #check all possible win conditions, without leaving the bounds of the board
            #only need to check one diagonal because of the way the board is checked
            else:
                #check left spaces
                if y < 7 and not win:
                    win = (board[x][y]==board[x][y+1] and board[x][y+1]==board[x][y+2])
                #check lower spaces
                if x < 7 and not win:
                    win = (board[x][y]==board[x+1][y] and board[x+1][y]==board[x+2][y])
                #check lower right diagonal spaces
                if x < 7 and y < 7 and not win:
                    win = (board[x][y]==board[x+1][y+1] and board[x+1][y+1]==board[x+2][y+2])
                #check lower left diagonal spaces
                if x < 7 and y > 1 and not win:
                    win = (board[x][y]==board[x+1][y-1] and board[x+1][y-1]==board[x+2][y-2])
            y+=1
        x+=1
    
    #return the game ending conditions
    return(win, draw)

#function to end the game once a conclusion has been reached
def gameOver(server):
    count = 3
    broadcast(server,server,"\nGame over! Server will quit in 3 seconds...\n")

    while count > 0:
        broadcast(server,server,str(count)+"..\n")
        count-=1
        time.sleep(1)

    broadcast(server,server,"\nServer closed\n")

#removes all connected clients
def boot(server):
    #remove team X players
    for sock1 in TEAM_X_LIST:
        sock1.close()
        TEAM_X_LIST.remove(sock1)
    #remove team O players
    for sock2 in TEAM_O_LIST:
        sock2.close()
        TEAM_O_LIST.remove(sock2)
    #remove any remaining connections
    for sock3 in SOCKET_LIST:
        if sock3!=server:
            SOCKET_LIST.remove(sock3)

#main for server script
if __name__=="__main__":
    sys.exit(tic_tac_server())
