# DijkstraContest
Contest to see who has the best dijkstra algo

Dependancies : Please install *libsfml-dev* or execute *sudo make configure* __before__ executing make

The goal of this repository is to have a *nice* and *fast* path-finder algo which would allow our robot to pown ennemies.
In order to get that, this is a little contest, anyone can participate.

This repository is composed of 2 parts :

####1.The first one is setup :

README.md (hope you'll read it until the end), LICENSE
	
A directory __testInputs__ which contains (as it's named) inputs for your program. Basically, the format is :
	
	*v1 v2 -> size of table : objects will be drawn in the area (0-v1) (0-v2)
		
	*v3 -> radius of the robot (robot is represented as a circle)
		
	*v4 v5 -> start position of robot center (v4 = xPos, v5 = yPos)
		
	*v6 v7 -> end position of robot center (v6 = xPos, v7 = yPos)
		
	*v8+5*i v9+5*i v10+5*i v11+5*i v12+5*i -> positions of center of obstacles and half sizes (v8 = xPosCenter, v9 = half width, v10 = yPosCenter, v11 = half height, v12 = angle in degrees)
		
A directory __results__ which contains the result of timed tests (your program will be run the maximum number of times during 10 seconds)
	
2 directories which contain the code used to draw the result of your program for the wanted input and to compute the speed of your program, you can look at them if you are interested by the code, but please don't modify them or I'll be compelled to hate you. You can use **make run-graphical**, **make run-graphical-withEnvironment**, **make run-timed** or **make run-timed-withEnvironment** in order to easily run the 2 programs.

####2.The second one is yours : anyone can create his directory (please name it with *something that can identify you*).

This directory can contain anything you want, but must contain one executable which will receive *on standard input* the data from desired test (see the format above). Your program musts output, *on standard output*, the result of your computation of path as follows :

xPos1 yPos1 xPos2 yPos2 ... xPos_n yPos_n (so it's basically a list of coordinates of robot centers)



###Example

Your name is petitAgneauDu35.

You decide to participate this high level contest.

You clone this repository : **git clone https://github.com/Alkanoor/DijkstraContest.git**, and install libsfml : **sudo make configure** in the repo.

You create a directory petitAgneauDu35 in the folder which contains this wonderful README (you may estimate the chance you have, it's my first Readme) : **mkdir petitAgneauDu35**

You put all your stuff (I'm so kind I let you program in javascript), where you want in your directory.
You create an executable file (it obviously can be a scripted file if your langage can't be compiled, even if it is a shame) and put it in a random place, for example *petitAgneauDu35/bin/obviouslyTheBestAlgorithm*.

You decide to test it on the first basic situation so you type **make run-graphical** and you enter following information :
>Your name (or dir) : 

>petitAgneauDu35

>Your algorithm path from your name (or dir) : 

>bin/obviouslyTheBestAlgorithm

>Situation chosen : 

>1

You should observe a beautiful straight line between the starting point and the ending point, if your algo is not too bad.

You decide to compare your parts to other's, so you type **make run-timed** and you enter the same information as previously, or you decide to test program from another dude. Result of the test is in folder results.

If you're bored to enter the same information everytime, you can export variables *NAME*, *ALGO_PATH*, *SITUATION_INDEX* and *DELAY*, and run **make run-graphical-withEnvironment** or **make run-timed-withEnvironment**.

