// TODO: You should write the function computeTrajectory

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <math.h>
#include <algorithm>
#include <cstring>

using namespace std;


double computeTrajectory(double robotPos[3], double chargerPos[2], double distanceSensors[16], double trajectory[2]);
void normalize(double v[2]);
void readPerception(string source, double robotPos[3], double chargerPos[2], double distanceSensors[16]);
void writeTrajectory(string destination, double speed, double v[2]);
bool endSimulation();

// ./agentCpp [pfields/false] [navigate/false]
int main(int argc, char *argv[]) {
	if (argc < 3) {
		cout << "Not enough parameters" << endl;
		exit(1);
	}

	double robotPos[3];
	double chargerPos[2];
	double distanceSensors[16];
	double trajectory[2];

	// do only if computing potential fields is turned on with the first argument
	if (!strcmp(argv[1], "pfields")) {
		ifstream input("../Robot/output/globalpercepts.txt");

		if (!input) {
			cout << "globalpercepts not found" << endl;
		}
		else {
			ofstream output("../Robot/output/globaltrajectory.tmp");

			if (!output) {
				cout << "globaltrajectory not opened" << endl;
			}
			else {
				string str;
				while (getline(input, str)) {
					if (str.length() < 1)
						break;

					stringstream ss(str);
					ss >> robotPos[0];
					ss >> robotPos[1];
					ss >> robotPos[2];
					ss >> chargerPos[0];
					ss >> chargerPos[1];

					for (int i = 0; i < 16; i++)
						ss >> distanceSensors[i];

					double speed = computeTrajectory(robotPos, chargerPos, distanceSensors, trajectory);
					output << robotPos[0] << " " << robotPos[1] << " " << robotPos[2] << " " << speed << " " << trajectory[0] << " " << trajectory[1] << endl;
				}
				output.close();

				system("mv ../Robot/output/globaltrajectory.tmp ../Robot/output/globaltrajectory.txt");
			}

			input.close();
		}
	}
	
	// do only if navigate is turned on with the second argument
	if (!strcmp(argv[2], "navigate")) {
		bool quit = false;
		while (!quit) {
			// read in the percepts
			readPerception("percepts", robotPos, chargerPos, distanceSensors);

			// compute trajectory
			double speed = computeTrajectory(robotPos, chargerPos, distanceSensors, trajectory);

			// write trajectory
			writeTrajectory("trajectory", speed, trajectory);

			quit = endSimulation();

			usleep(50000);
		}
	}

	return 0;
}

// *********************************************************************************************************
// 
// 	TODO: Write the function computeTrajectory
//		robotPos: contains the position (x-coordinate, y-coordinate, direction)  of the robot in the world
// 		goalPos: contains the position (x-coordinate, y-coordinate) of the robot's goal
// 		distanceSensors: contains the distance reading (how far to an object) on each of the robot sensors,
// 						 which are positioned in a ring around the robot at even distances. 
// 						 Examples (for orientation):
// 						   distanceSensors[0] gives the distance reading directly to the robot's right
//						   distanceSensors[4] gives the distance reading direclty in front of the robot
//						   distanceSensors[8] gives the distance reading direclty to the robot's left
//						   distanceSensors[12] gives the distance reading direclty behind the robot
// 		Your code should specify the absolute (in world coordinates) direction the robot should go in the world 
// 			as a two dimension be filling out the array trajectory (0 index is the x coord, 1 index is the y coord)
// 		For example: if you want the robot to go straight to the right, trajectory[0] = 1, trajectory[1] = 0
// 		             if you wan the robot to go straight up in the world, trajectory[0] = 0, trajectory[1] = 1
// 
// *********************************************************************************************************
double computeTrajectory(double robotPos[3], double goalPos[2], double distanceSensors[16], double trajectory[2]) {
	// TODO: tells the robot the robot which direction to go (default: robot goes up)
	trajectory[0] = 0;
	trajectory[1] = 1.0;

	// call this function to normalize the trajectory vector (so that it is a unit vector)
	normalize(trajectory); 

	// always return 1.0
	return 1.0;
}

// normalizes the vector
void normalize(double v[2]) {
	// normalize the vector v
	double mag = sqrt(v[0]*v[0] + v[1]*v[1]);
	if (mag != 0) {
		v[0] /= mag;
		v[1] /= mag;
	}
}

bool endSimulation() {
	ifstream input("../MundoVerdadero/State/sim.txt");

	if (!input) {
		cout << "sim.txt not found" << endl;
		exit(-1);
	}

	string msg;
	input >> msg;

	input.close();

	if (msg == "off")
		return true;

	return false;
}

void writeTrajectory(string destination, double speed, double v[2]) {
	string fnombre = "../Robot/output/" + destination + ".tmp"; 
	ofstream output(fnombre);

	output << speed << endl;
	output << v[0] << endl;
	output << v[1] << endl;

	output.close();

	string mandato = "mv ../Robot/output/" + destination + ".tmp ../Robot/output/" + destination + ".txt";
	system(mandato.c_str());
}

void readPerception(string source, double robotPos[3], double chargerPos[2], double distanceSensors[16]) {
	string fnombre = "../Robot/output/" + source + ".txt";
	ifstream input(fnombre);

	if (!input) {
		cout << "percept.txt not found" << endl;
		exit(1);
	}

	for (int i = 0; i < 3; i++) {
		input >> robotPos[i];
	}

	for (int i = 0; i < 2; i++) {
		input >> chargerPos[i];
	}

	for (int i = 0; i < 16; i++) {
		input >> distanceSensors[i];
	}

	input.close();
}


