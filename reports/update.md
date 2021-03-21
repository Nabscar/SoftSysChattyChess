Chatty Chess
### Nabih Estefan & Oscar De La Garza


#### Goal
For our Project we wish to make chess rooms for people to log on and play. However with the twist that people would be able to join over the Olin network in their linux terminal and choose a room that they can then play either another person or a computer. For a lower bound we’d hope to at least have the rooms setup for anyone to join into and play against someone in a chess game. For stretch we would enjoy being able to implement these functions as well as add the possibility of implementing an AI, which would be the only major part we don’t write directly, but do write the implementation to get the moves and represent them against the opponent. As well as allow for spectating and chat functions for all attending parties.

#### Learning Goals
We wish to learn about network programming and how client/server side access is achieved and set up to bring users an interface that they can then use. We also wish to learn how programming a game works in c and how we can then attach that to our client chat rooms that we will be making in tandem. All in all, it sounds like a big task but we are excited and ready.

#### What's Been Done
Currently Nabih has taken lead on achieving the server-based client chatroom.This has taken shape with us achieving a working server that can then host 2 separate clients. In this setup the users are able to currently chat between each other through the terminals. We were able to achieve this through a resource of a prior project that was very similar, but we have had to adapt it our needs of course and still have more implementation and changes we'd like to make. As for the chess game, Oscar currently has a printed Chess Board that takes inputs of what move a player would like to make, but lacks any of the actual computation to moves the pieces. For this we have found one other implementation of a Chess terminal game in C that has helped with give us some guidance, but are not fans of how they implemented their game so are going through it on our own some.


#### What's next
- Finalize the Server client. This is very close to being done. We currently are able to send communications to another client through the server but need to works out some bugs and assure we can connect between two different computers on the same wifi. This is something we can determine as accomplished once we can connect to a server by using both of our laptops and communicate - Nabih / Oscar
- Finalize the Chess Game. Currently the chess game is taking an input from the user for the moves and printing the full board with all the pieces being identifiable. For full implementation the main part missing a computation function to determine if a move is valid and then one to update the board. For this to be complete we would be looking for a person off of one laptop to be able to play Chess. - Oscar / Nabih
- Implement combined server application with a chess game. With both other tasks being completed we would like to then achieve this task through what we expect will be quite a bit of debugging since we wish for the serve to print the new board only to the corresponding players whose turn it is. This will be measured as complete once we have two computers being able to log onto a server through their terminal and play each other in a chess game. - Nabih & Oscar
