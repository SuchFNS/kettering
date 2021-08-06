#Colin Quinn
#Cloud Computing Assignemt 2
#This creates an RPC server that adds two numbers given to it by the client.
#The port is received from the command line.
from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler
import sys
class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)
#creates a server using the hostname and a port from command line
server = SimpleXMLRPCServer(("ip-172-31-31-96",int(sys.argv[1])),
                            requestHandler=RequestHandler)
server.register_introspection_functions()
#This is where the adding takes place,
#everything else is the server communication
def adder_function(x,y):
    return x+y
server.register_function(adder_function, 'add')
#run until told to stop
server.serve_forever()
