#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <vector>
#include <chrono>
#include <math.h>
#include <algorithm>
#include <cstring>

#include "Gen_Mapper.h"

using namespace std;

#define MAX_POINTS		10000

void loadAssumptions(Assumptions *assumptions, int rindex);
bool endSimulation();
bool isCharging();
double getDist(Point p1, Point p2);

double readTrajectory(double v[2]);
void determineActuation(double v[2], double robotTheta, double *rate, int *direction);
void writeActuators(double rate, int direction);
void turnOffSimulation();

bool liningUp = true;
int oldDirection = 0;

// ./robot [pfields/false] [navigate/false]
int main(int argc, char *argv[]) {
	cout << "./robot" << endl;
	if (argc < 3) {
		cout << "Not enough parameters" << endl;
		return -1;
	}
	srand(time(NULL));
	
	Assumptions assumptions0;
	loadAssumptions(&assumptions0, 0);
	Mapper *mapper0 = new Mapper(0, &assumptions0);

	srand(time(NULL));

	// do only if computing potential fields is turned on with the first argument
	if (!strcmp(argv[1], "pfields")) {
		cout << "pfields" << endl;
		mapper0->createMap();
		double pos[3] = {1, 1, 45};
		ofstream output("output/globalpercepts.tmp");
		for (int x = 5; x < 200; x+=5) {
			pos[0] = x;
			for (int y = 5; y < 200; y+=5) {
				pos[1] = y;
				mapper0->getDistSensor(pos);
				mapper0->addGlobalPercept(pos, output);
			}
		}
		output.close();

		system("mv output/globalpercepts.tmp output/globalpercepts.txt");
	}

	// do only if navigate is turned on with the second argument
	if (!strcmp(argv[2], "navigate")) {
		cout << "navigate" << endl;
		int countCharging = 0;
		bool quit = false;
		double v[2], vStable[2] = {0, 1};
		int direction;
		double rate;
		while (!quit) {
			mapper0->createMap();
			mapper0->getDistSensor(mapper0->robotPos);
			mapper0->writePerceptions("percepts", mapper0->robotPos);

			if (!isCharging()) { 			
				rate = readTrajectory(v);
				vStable[0] = 0.8 * vStable[0] + 0.2 * v[0];
				vStable[1] = 0.8 * vStable[1] + 0.2 * v[1];
				determineActuation(vStable, mapper0->robotPos[2], &rate, &direction);
			}
			else {
				rate = 0.0;
				direction = 0;
			}
			oldDirection = direction;

			writeActuators(rate, direction);

			usleep(5000);
			quit = endSimulation();

			if (!quit) {
				if (isCharging()) {
					countCharging ++;
					// perfEstimate->currentPerfEstimate = perfEstimate->timeElapsed;
					if (countCharging > 9)
						quit = true;
				}
				else {
					countCharging = 0;
				}
			}
		}
	}

	delete mapper0;

	turnOffSimulation();

	return 0;
}

void turnOffSimulation() {
	ofstream output("../MundoVerdadero/State/sim.tmp");

	output << "off" << endl;

	output.close();

	system("mv ../MundoVerdadero/State/sim.tmp ../MundoVerdadero/State/sim.txt");
}

double readTrajectory(double v[2]) {
	ifstream input("output/trajectory.txt");

	double speed;

	input >> speed;
	input >> v[0];
	input >> v[1];

	input.close();

	return speed;
}

void determineActuation(double v[2], double robotTheta, double *rate, int *direction) {
	double trajectoryTheta = atan2(v[1], v[0]) * 180.0 / 3.14159;

	// cout << "antes trajectoryTheta: " << trajectoryTheta << endl;
	// cout << "antes robotTheta: " << robotTheta << endl;

	while (trajectoryTheta < (robotTheta - 180)) {
		trajectoryTheta += 360.0;
	}
	while (robotTheta < (trajectoryTheta - 180)) {
		robotTheta += 360.0;
	}

	// cout << "despues trajectoryTheta: " << trajectoryTheta << endl;
	// cout << "despues robotTheta: " << robotTheta << endl;

	if (liningUp) {
		if (fabs(trajectoryTheta - robotTheta) < 10.0) {
			*direction = 0;
			liningUp = false;
		}
		else if ((((trajectoryTheta - robotTheta) > 0) && ((trajectoryTheta - robotTheta) < 180.0)) || (((trajectoryTheta - robotTheta) < 0) && ((trajectoryTheta - robotTheta) < -180.0))) {
			if (oldDirection != -1) {
				*direction = 1;
				*rate = 0.5;
			}
			else {
				*direction = 0;
				liningUp = false;
				*rate = 1.0;
			}
			// if (fabs(trajectoryTheta - robotTheta) < 5.0)
				
		}
		else {
			*direction = -1;
			// if (fabs(trajectoryTheta - robotTheta) < 5.0)
				*rate = 0.5;
		}
	}
	else {
		if (fabs(trajectoryTheta - robotTheta) < 10.0) {
			*direction = 0;
		}
		else if ((((trajectoryTheta - robotTheta) > 0) && ((trajectoryTheta - robotTheta) < 180.0)) || (((trajectoryTheta - robotTheta) < 0) && ((trajectoryTheta - robotTheta) < -180.0))) {
			*direction = 1;
			liningUp = true;
			// if (fabs(trajectoryTheta - robotTheta) < 5.0)
				*rate = 0.5;
		}
		else {
			*direction = -1;
			liningUp = true;
			// if (fabs(trajectoryTheta - robotTheta) < 5.0)
				*rate = 0.5;
		}


	}

}

void writeActuators(double rate, int direction) {
	string fname = "../MundoVerdadero/State/robotactuators_" + to_string(0) + ".tmp";
	ofstream output(fname);
	
	output << "rate " << rate << endl;
	output << "direction " << direction << endl;
	
	output.close();

	char mandato[1024];
	sprintf(mandato, "mv ../MundoVerdadero/State/robotactuators_%i.tmp ../MundoVerdadero/State/robotactuators_%i.txt", 0, 0);
	system(mandato);
}

bool isCharging() {
	ifstream input("../MundoVerdadero/State/charging_0.txt");
	int charge;

	input >> charge;

	input.close();

	if (charge == 1)
		return true;

	return false;
}

bool endSimulation() {
	ifstream input("../MundoVerdadero/State/sim.txt");

	string msg;
	input >> msg;

	input.close();

	if (msg == "off")
		return true;

	return false;
}

void loadAssumptions(Assumptions *assumptions, int rindex) {
	string fnombre = "input/assumptions_" + to_string(rindex) + ".txt";
	//cout << fnombre << endl;
	ifstream input(fnombre);

	if (!input.fail()) {
		string palabra;

		input >> palabra;
		input >> assumptions->robot_color[0];
		input >> assumptions->robot_color[1];
		input >> assumptions->robot_color[2];

		//cout << "Robot color: " << assumptions->robot_color[0] << ", " << assumptions->robot_color[1] << ", " << assumptions->robot_color[2] << endl;

		input >> palabra;
		input >> assumptions->charger_color[0];
		input >> assumptions->charger_color[1];
		input >> assumptions->charger_color[2];

		//cout << "Charger color: " << assumptions->charger_color[0] << ", " << assumptions->charger_color[1] << ", " << assumptions->charger_color[1] << endl;

		input >> palabra;
		input >> assumptions->max_speed;

		input >> palabra;
		input >> assumptions->max_spin;

		input >> palabra;
		input >> assumptions->robot_radius;

		input >> palabra;
		input >> assumptions->charger_width;
		input >> assumptions->charger_height;

		input.close();
	}
	else {
		cout << "assumptions file not found" << endl;
		exit(1);
	}
}

double getDist(Point p1, Point p2) {
	double x = p1.x - p2.x;
	double y = p1.y - p2.y;
	return sqrt(x*x + y*y);
}
