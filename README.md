# PotentialFields

The goal of this project was to create a reflex agent through potenial fields.
Simply put, we want the robot (our reflexive agent) to make it to the goal by reacting to it's environment.
This is achieved through potential fields.
Each square of the board is given a direction and a weight (think: vector field).
We initialize those weights and directions to be neutral and then apply attractive forces towards the goals and add repellent forces away from obsticles.
This creates a potential field that the robot navigates through.

See [AgentPython/agentPython.py](/AgentPython/agentPython.py) for the implementation.

## Results

For a full breakdown of the implementation and found results, see [Fields Report.pdf](/CS%20470%20Mini%20Project%20-%20Potential%20Fields%20Report.pdf).

Overall, we can see the potential fields attempting to steer clear from obstacles and navigate towards the goal in different scenarios:

![](/Images/PotentialFieldsWorld1.gif)
![](/Images/PotentialFieldsWorld2.gif)
![](/Images/PotentialFieldsWorld3.jpg)
![](/Images/PotentialFieldsWorld4.jpg)

The robot does fail to navigate u shaped valleys however.

## How to Run

See the [spec](Spec.md)

## Interface Controls

The interface allows you to do the following:

- _Load a scenario._ There are four, which you can load by pressing “1”, “2”, “3”, or “4” on the keyboard when the GUI window is active
- _Update the potential fields._ Press “u” to load the potential fields computed by your current algorithm. It only works when the simulator is off.
- _Turn the “potential fields” display on and off._ Press “p”
- _Turn the simulator on_ (to make the robot move according to the potential fields). Press “r”
- _Stop the simulator_ (turn it off). Press “q”
- _Manual move the robot._ Left click on the world to place the robot in a specific place in the world.
- _Change the robot's goal._ Right click in the world to move the goal location of the robot. By default, it is set to be on the charger whenever you load a new scenario.

## Aditional Information

For additional information on this project, see the [spec](Spec.md).

For more information on potential fields, see the [potential fields article](/Pfields.pdf) written by Michael A. Goodrich.
