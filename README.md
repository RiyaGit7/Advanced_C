# A* Pathfinding Project

## Overview
This project implements the A* algorithm to compute the shortest path between two cities using map data. The program reads the names of the departure and arrival cities from the command line, computes, and displays the shortest path along with the distances for each segment and the total distance.

## Requirements
- GCC Compiler
- Make (optional for using makefile)

## Files Included
- `List.c`, `List.h`: Linked list implementation.
- `Map.c`, `Map.h`: Map data handling.
- `aStar-algo.c`: A* algorithm implementation.
- `status.c`, `status.h`: Error and status handling.
- `FRANCE.MAP`: Default data file containing cities and connections.
- `makefile`: For automating the build process.

## Building the Program
To build the program, you can use the following command:

gcc -o aStarpath List.c Map.c aStar-algo.c status.c

