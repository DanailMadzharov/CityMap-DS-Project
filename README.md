# CityMap-DS-Project
CLICK ON RAW FOR A BETTER VIEW!!!

A city map implemented with a directed weighted graph. The project includes implementations of some of the more famous digraph algorithms, including Eulerian Path/Circuit, shortest paths from A to B, closing and opening different crossroads, and finding alternative paths.

Before you start the program, make sure you input the crossroads in the input file (input.txt) the right way -

Example file input for each of the lines:

<mainCrossroad> <secondaryCrossroad> <distanceBetweenMainAndSecondary> <secondary2> <distanceBetweenMainAndSecondary2> .... <secondaryN> <distanceBetweenMainAndSecondaryN>

Example input.txt input:

Queens 5thAvenue 2000 Beverly 800 //do not write this! distance between Queens and 5thAvenue is 2000 m, Queens has a LINK with 5thAvenue, same as  Queens-Beverly (800 m distance)
5thAvenue Queens 2000 Beverly 300
randMain randSec 300 randSec2 400

-------------------------------------------------------------------
To start the program simply open main.cpp and follow these steps:

Set the path directory to the current project folder.

Open a new terminal and write down "g++ *.cpp" to compile the program

Start the program with ".\a.exe"

follow the instructions in the terminal!
