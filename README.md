Pacman_Observer
===============

An exemple of design pattern Observer : Pacman

We will code a simple Pacman game with C++ using the Observer design pattern.
This project is for an assignment for a Software Design course in Tongji University, Shanghai ,China.


--------

How to install
--------------
Clone the repository on your computer.

    git clone https://github.com/mushishi06/Pacman_Observer.git

Compile the project. *You need make and g++ installed*

    make re

Start the program

	./pacman


Options
-------

You can play on two different maps:

    ./pacman --map1
    ./pacman --map2

Disable debug for smoother display:

    ./pacman 2> /dev/null

How to play
-----------
In this Pacman game, you play step by step. You choose your direction (up, down, left, right) and then validate. You and the monsters will then move and the display will update.

Controls
--------

    T       Move up
    G       Move down
    F       Move left
    H       Move right
    Space   Validate your move
    Q	    Exit game
