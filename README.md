# Mini-project: Creating a reflex agent using potential fields

_Note: If you are having a hard time getting the code working properly (my apologies!), please see the 4 announcements for options to bail us all out of our pain._

## Purpose

Experience creating a reflex agent.

## Problem Description

A robot is placed in a world with the task of navigating through its environment to its charger. The robot has sensors that allow it to:

- identify its position in the world
- identify the position of its charger in the world
- identify the distance to an obstacle at 16 angles evenly spaced around it.

The actions available to the robot are:

- rotate in place to the left
- rotate in place to the right
- move forward (straight ahead)

Your task is to use potential fields to tell the robot how to selects actions in a way that allows it to navigate through its world to its charger (ideally in as little time as possible). A simulator is provided. Instructions on how to get the simulator to run and how to modify the code to implement your potential fields algorithm is provided below.

You may do this task with a partner (or even multiple partners). However, you should all be engaged and contribute.

## What to Submit

Submit a brief document that includes the following:

1. List the people in your group
2. A 1-paragraph description (or something like that) of what you implemented in your potential fields. Use math if that helps you create a clearer description. The description should have enough detail that another person should be able to duplicate your exact algorithm in code just by reading this brief description. That said, don’t over do it — it doesn’t have to be polished either.
3. List a thing or two (or three or four) you tried that didn't work (if any -- usually things don't work perfectly the first time). In other words, this step is here to encourage you to experiment just a little bit with making your potential fields better.
4. State how long it takes your algorithm to navigate to its charger in each of the 4 worlds. If your robot fails to get to the goal in a world, just note that.

## Compiling and Running the Code

1. Download the appropriate code for your computer:

   Mac/Linux: PotentialFields_MacLinux2.zip [Download](https://learningsuite.byu.edu/plugins/Upload/fileDownload.php?fileId=23017cae-kKrk-FN5D-S3B9-Fwbd737bebd9)

   Windows Code: PotentialFields_Windows.zip [Download](https://learningsuite.byu.edu/plugins/Upload/fileDownload.php?fileId=b70107a0-3XW4-08Ib-JOwR-H4f1fb7d3f3b)

2. Compile the code. I suggest you use g++, regardless of whether you use Windows, Linux, or a Mac. The simulator consists of four programs.

- Program 1: Compile the java program contained in viewer.java in the folder Viewer. I do this by the command: javac \*.java

- Program 2: Compile the C++ program found in main.cpp in the Folder MundoVerdadero/SimCode. The resulting executable should be named "sim", and this executable should be in the same folder (MundoVerdadero/SimCode). Use: g++ main.cpp -o sim

- Program 3: Compile the C++ program found in main.cpp in the Folder Robot. The resulting executable should be named "robot", and this executable should be in the same folder (Robot). Use:: g++ main.cpp -o robot

- Program 4: For this program, decide whether you want to use C++ or Python in this lab. If you decide on C++, the code is found in main.cpp in the Folder AgentCpp (compile with: g++ main.cpp -o agentCpp). The executable should be in the folder AgentCpp and should be named "agentCpp". If you use python, the code is in the folder AgentPython in the file agentPython.py. You obviously do not need to compile it.

3. Once you have the programs compiled, you now need to configure some scripts. If you choose C++, you need to rename the files pfields_cpp.sh and simulator_on_cpp.sh in the Folder “Viewer” to pfields.sh and simulator_on.sh, respectively. If you choose Python, rename the files the files pfields_python.sh and simulator_on_python.sh in the Folder “Viewer” to pfields.sh and simulator_on.sh, respectively.

4. Once you have the programs compiled for your computer with the executables named correctly and in the appropriate directory, you are ready to run the program. In the command line, type: java viewer

This will launch a GUI through which you can evaluate your algorithms on the robot.

(For WSL, run XLaunch and set your display variable: `export DISPLAY="127.0.0.1:0.0`)

## Interface Controls

The interface allows you to do the following:

- _Load a scenario._ There are four, which you can load by pressing “1”, “2”, “3”, or “4” on the keyboard when the GUI window is active
- _Update the potential fields._ Press “u” to load the potential fields computed by your current algorithm. It only works when the simulator is off.
- _Turn the “potential fields” display on and off._ Press “p”
- _Turn the simulator on_ (to make the robot move according to the potential fields). Press “r”
- _Stop the simulator_ (turn it off). Press “q”
- _Manual move the robot._ Left click on the world to place the robot in a specific place in the world.
- _Change the robot's goal._ Right click in the world to move the goal location of the robot. By default, it is set to be on the charger whenever you load a new scenario.

## Implementing your Algorithm in the Code

You should modify/complete the function “computeTrajectory” in AgentCpp/main.cpp (for C++) or AgentPython/agentPython.py (for Python) to implement your potential fields algorithm. The function takes as input the sensor readings from the robot (robot’s position, goal position, and distance sensors). Your algorithm should compute a directional unit vector (stored in the array trajectory), which specifies the direction the robot should go given the robot’s percepts (sensor readings).
