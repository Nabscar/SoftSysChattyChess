# Chatty Chess &#9812;
### Nabih Estefan & Oscar De La Garza

This project is an implementation of TCP server to play chess across two terminals on the same network. This is done by running a server to which two clients connect to. Then, the server shows the board to the clients and they input their moves. The server takes cares of all the checking and logic related to the game, and the users only have to input the pieces they want to move.

## Getting Started
To compile the server executable file
`make server`
To run this server file
`./server`


To compile the client executable file
`make client`
To run this client file and connect to the server
`./cleint [ip-address-of-server-computer]`

## Images
Below is an image of two clients side-by-side playing:
![Image of Players](/imgs/players.png)

And this other image if what the server will print in this same game 
(there is a commented line in code for if the server wants to also see the board move)
![Image of Server](/imgs/server.png)
 
## Acknowledgements
We used outside resources to understand and implement a lot of the server and chess code. These are those resources that helped us the most.

Resources on networking using sockets:  
- For starting we created a one server-one client network, which was mostly done using [this GeeksandGeeks link](https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/).  
- After getting this one working, we moved on to working with [this other GeeksandGeeks link](https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/) to implement multiple clients.  
- Finally, over the whole process, [this third GeeksandGeeks link](https://www.geeksforgeeks.org/socket-programming-cc/) helped a lot for conceptual understanding and debugging.  

Basically, for the networking with sockets, GeeksandGeeks was extremely useful.

Resources for chess implementation:
- For the Board implementation, some inspiration was taken from [this ASCII implementation of a Chess Game](https://github.com/Parigyan/ASCII-Chess).
- To do move checking and the actual updating and movement of the pieces, we did this implementation ourselves.
