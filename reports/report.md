# Chatty Chess &#9812;
## Through a server and two client terminals
### Nabih Estefan & Oscar De La Garza

[//]: <> (Reflect on the outcome of the project in terms of your learning goals.  Between the lower and upper bounds you identified in the proposal, where did your project end up?  Did you achieve your learning goals?)

[//]: <> (What is the goal of your project; for example, what do you plan to make, and what should it do?)
#### Goal
For our Project we wished to make chess rooms for people to log on and play. However with the twist that people would be able to join over the Olin network in their linux terminal and choose a room that they can then play either another person or a computer. For a lower bound we’d hope to at least have the rooms setup for anyone to join into and play against someone in a chess game. For stretch we would enjoy being able to implement these functions as well as add the possibility of implementing an AI, which would be the only major part we don’t write directly, but do write the implementation to get the moves and represent them against the opponent. As well as allow for spectating and chat functions for all attending parties.

At the end, we were able to implement a server that accepts two clients and runs the whole logic and rule-checking behind the chess game. The clients are then able to send their moves and have the board update for the other play in response to a valid move. Even though we weren't able to implement our stretch goals, we created a very fun, and usable, chess game to play with friends on our same network, which makes us very happy.

[//]: <> (What are your learning goals; that is, what do you intend to achieve by working on this project?)
#### Learning Goals
We wished to learn about network programming and how client/server side access is achieved and set up to bring users an interface that they can then use. We also wish to learn how programming a game works in c and how we can then attach that to our client chat rooms that we will be making in tandem. All in all, it sounds like a big task but we are excited and ready.

We were able to complete both of these goals! We created a standalone chess implementation in chess.c (which was mostly used for testing the chess game itself). We also create a a client-server network communication program  in server.c and client.c (for server and client respectively). Finally, we were able to combine these two to create this chatroom for chess!

[//]: <> (What resources did you find that were useful to you.  If you found any resources you think I should add to the list on the class web page, please email them to me.)
#### Resources
Resources on networking using sockets:  
- For starting we created a one server-one client network, which was mostly done using [this GeeksandGeeks link](https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/).  
- After getting this one working, we moved on to working with [this other GeeksandGeeks link](https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/) to implement multiple clients.  
- Finally, over the whole process, [this third GeeksandGeeks link](https://www.geeksforgeeks.org/socket-programming-cc/) helped a lot for conceptual understanding and debugging.  

Basically, for the networking with sockets, GeeksandGeeks was extremely useful.

Resources for chess implementation:
- For the Board implementation, some inspiration was taken from [this ASCII implementation of a Chess Game](https://github.com/Parigyan/ASCII-Chess).
- To do move checking and the actual updating and movement of the pieces, Oscar did this implementation himself.

[//]: <> (What were you able to get done?  Include in the report whatever evidence is appropriate to demonstrate the outcome of the project.  Consider including snippets of code with explanation. do not paste in large chunks of unexplained code.  Consider including links to relevant files.  And do include output from the program you wrote.)
#### What we got Done
For our project we were able to achieve a working local server that could accept two separate clients two communicate through string input. This was done through "SECTION ABOUT HOW SERVER STUFF WORKS"
  When it comes to the Chess part of this assignment. We were able to accomplish what we felt like is a functional Chess Game. Currently however the checking for checkmate is not finished, but all the pieces move in accordance to the rules by which they should. 


[//]: <> (Explain at least one design decision you made.  Were there several ways to do something?  Which did you choose and why?)
#### Design Decisions
There weren't many design decisions to do in this project, but there were two big decisions that defined how the whole project would look for the clients playing, how to print the chess board. This decision in and of itself depends on other design decision so we will mention a few. The first decision was whether we were going to run the chess logic in both clients or on the server. The clients might be easier in a sense, because then the server only has to take care of sending which move was done, but if there was an error in sending, then the game splits in two and it becomes a nightmare. Thus we decided to run the chess implementation on the server. This means that the clients actually only get a string representation of the board, and then use functions to print it nicely.  
This brings us to our second decision, how to print the board. To do this, we created an array of integers that symbolizes the pieces, and then used a (very long) printBoard() function to get this into a more visually easier to read board with black and white squares.

[//]: <> (You will probably want to present a few code snippets that present the most important parts of your implementation.  You should not paste in large chunks of code or put them in the Appendix.  You can provide a link to a code file, but the report should stand alone; I should not have to read your code files to understand what you did.)
#### Code

[//]: <> (Audience: Target an external audience that wants to know what you did and why.  More specifically, think about students in future versions of SoftSys who might want to work on a related project.  Also think about people who might look at your online portfolio to see what you know, what you can do, and how well you can communicate.)
