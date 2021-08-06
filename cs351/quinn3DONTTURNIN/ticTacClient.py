#Colin Quinn
#Cloud Assignment 3
#The client program for ticTacToe.
#This program will get user input and send it to the ticTacServer,
#then listens for a repsonse from the server and prints the data to console
import sys
import socket
import select

def tic_tac_client():
    #stop client connection if there are incorrect arguments
    if(len(sys.argv) < 3) :
        print("To play the game, please enter\n$python ticTacClient.py <hostname> <port>")
        sys.exit()
    host = sys.argv[1]
    port = int(sys.argv[2])

    #create connection socket to server
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(2)

    #search for hostname and port given in command line
    try :
        s.connect((host, port))
    except:
        print("Please check the hostname and port entered\nUnable to connect to desired server")
        sys.exit()
    print("Connected! Get ready to play!")

    #force stdout to print to console
    sys.stdout.flush()

    #main game loop on the client side
    while 1:
        #create a list of stdin and server communication
        socket_list = [sys.stdin, s]
        ready_to_read, ready_to_write,in_error = select.select(socket_list, [], [])

        for sock in ready_to_read:
            #check what data is received from the server, print message if it is data
            if sock == s:
                data = sock.recv(4096)
		#disconnect if the server sends something that is not proper data
                if not data :
                    print("\nThe server has disconnected")
                    sys.exit()
		#otherwise decode and flush (print) the message
                else :
                    sys.stdout.write(data.decode("UTF-8"))
                    sys.stdout.flush()
	    #if data is from stdin, send data to the server
            else :
                msg = sys.stdin.readline()
                s.send(bytes(msg,'UTF-8'))
                sys.stdout.flush()
                sys.stdin.flush()

#acts as the starting point for the script
if __name__=="__main__":
    sys.exit(tic_tac_client())
