#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <vector>
#include <chrono>
#include <math.h>
#include <ctime>
#include <algorithm>
#include <cstring>

#include "Things.h"

using namespace std;

#define MAX_ROBOTS		10

#define ADD         	1
#define ALTER       	2
#define REMOVE			3
#define UNKNOWN			0


void simulateWorld();
void moveRobot();
bool collision(int rid, vector<Obstacle *> obstacles, vector<Robot *> robots, double x, double y, double r);
void takePicture();
void detectCharging();
bool endSimulation();
void readStatus();
void cleanMemory();

void implementSaboteursActions();
int getType(string line);
void addObject(string line);
void alterObject(string line);
void removeObject(string line);

chrono::steady_clock::time_point lastTime;

vector<Obstacle *> obstacles;
vector<Robot *> robots;
vector<Charger *> chargers;
vector<CameraSensor *> cameras;

double theGoal[2] = {0.0, 0.0};


int main(int argc, char *argv[]) {
	srand(time(NULL));
	simulateWorld();

	return 0;
}


// *********************************************************************************************************
//
//	Simulates interactions between robot actuators/sensors and the world
//
// *********************************************************************************************************
void simulateWorld() {
	lastTime = chrono::steady_clock::now();
	bool quit = false;

	while (!quit) {
		usleep(10000);
		readStatus();
		moveRobot();
		takePicture();
		detectCharging();
		cleanMemory();
		quit = endSimulation();
	}
}

bool endSimulation() {
	ifstream input("../State/sim.txt");

	string msg;
	input >> msg;

	input.close();

	if (msg == "off")
		return true;

	return false;
}

void readStatus() {
	obstacles.clear();
	robots.clear();
	chargers.clear();
	cameras.clear();

	// read status.txt
	ifstream input("../State/status.txt");
	
	string primero, line;
	if (!input.fail()) {
		while (!input.eof()) {
			
			if (!(input >> primero)) {
				break;
			}
			
			getline(input, line);
			if (primero == "Obstacle") {
				obstacles.push_back(new Obstacle(line));
			}
			else if (primero == "Robot") {
				robots.push_back(new Robot(line));
			}
			else if (primero == "Charger") {
				chargers.push_back(new Charger(line));
			}
			else if (primero == "CameraSensor") {
				cameras.push_back(new CameraSensor(line));
			}
			else if (primero == "Goal") {
				int tmp;

				stringstream ss(line);
				ss >> tmp;
				ss >> theGoal[0];
				ss >> theGoal[1];
			}
			else {
				// ignore everthing else for now
			}
		}
	
		input.close();

		implementSaboteursActions();
	}
	else {
		cout << "status.txt not found" << endl;
		exit(1);
	}
}

void implementSaboteursActions() {
	ifstream input("../State/update.txt");

	if (!input.good())
		return;

	string line;
	while (getline(input, line)) {
		int typecode = getType(line);

		switch (typecode) {
			case ADD:
				addObject(line);
				break;
			case ALTER:
				alterObject(line);
				break;
			case REMOVE:
				removeObject(line);
				break;
			case UNKNOWN:
				cout << "unknown command" << endl;
				break;
        }
	}

	input.close();

	char mandato[1024];
	strcpy(mandato, "rm ../State/update.txt");
	system(mandato);
}

int getType(string line) {
    stringstream ss(line);
    string tipo;

    ss >> tipo;
    if (tipo == "add")
        return ADD;
    else if (tipo == "alter")
        return ALTER;
    else if (tipo == "remove")
        return REMOVE;

    return UNKNOWN;
}

void addObject(string line) {
	string what, params;
	stringstream ss(line);

	ss >> what; // the "add" command
	ss >> what;
	getline(ss, params);
	
	if (what == "robot") {
		params = to_string(robots.size()) + params;
		if (count(params.cbegin(), params.cend(), ' ') == 12)
			robots.push_back(new Robot(params));
		else
			cout << "Not right format to add robot: " << params << endl;
	}
	else if (what == "charger") {
		params = to_string(chargers.size()) + params;
		if (count(params.cbegin(), params.cend(), ' ') == 7)
			chargers.push_back(new Charger(params));
		else 
			cout << "Not right format to add charger: " << params << endl;
	}
	else if (what == "obstacle") {
		params = to_string(obstacles.size()) + params;
		if (count(params.cbegin(), params.cend(), ' ') == 7)
			obstacles.push_back(new Obstacle(params));
		else
			cout << "Not right format to add obstacle: " << params << endl;
	}
}

void alterObject(string line) {
	string what, params;
	int index = 99999;
	stringstream ss(line);

	ss >> what; // the "alter" command
	ss >> what;
	ss >> index;
	getline(ss, params);
	if (what == "robot") {
		if (index < robots.size()) {
			robots[index]->modify(params);
		}
		else {
			cout << "invalid robot index specified" << endl;
		}
	}
	else if (what == "charger") {
		if (index < chargers.size()) {
			chargers[index]->modify(params);
		}
		else {
			cout << "invalid charger index specified" << endl;
		}
	}
	else if (what == "obstacle") {
		if (index < obstacles.size()) {
			obstacles[index]->modify(params);
		}
		else {
			cout << "invalid obstacles index specified" << endl;
		}
	}
	else if (what == "camera") {
		if (index < cameras.size()) {
			cameras[index]->modify(params);
		}
		else {
			cout << "invalid cameras index specified" << endl;
		}
	}
}

void removeObject(string line) {
	string which;
	int index = 99999;
	stringstream ss(line);

	ss >> which; // the "remove" command
	ss >> which;
	ss >> index;
	if (which == "robot") {
		if (index < robots.size()) {
			Robot *goner = robots[index];
			robots.erase(robots.begin()+index);
			delete goner;
			for (int i = 0; i < robots.size(); i++)
				robots[i]->ID = i;
		}
		else {
			cout << "invalid robot index specified" << endl;
		}
	}
	else if (which == "charger") {
		if (index < chargers.size()) {
			Charger *goner = chargers[index];
			chargers.erase(chargers.begin()+index);
			delete goner;
			for (int i = 0; i < chargers.size(); i++)
				chargers[i]->ID = i;
		}
		else {
			cout << "invalid charger index specified" << endl;
		}
	}
	else if (which == "obstacle") {
		if (index < obstacles.size()) {
			Obstacle *goner = obstacles[index];
			obstacles.erase(obstacles.begin()+index);
			delete goner;
			for (int i = 0; i < obstacles.size(); i++)
				obstacles[i]->ID = i;
		}
		else {
			cout << "invalid obstacle index specified" << endl;
		}
	}
}

void cleanMemory() {
	// cleanup
	for (int i = robots.size()-1; i >= 0; i--)
		delete robots[i];

	for (int i = obstacles.size()-1; i >= 0; i--)
		delete obstacles[i];

	for (int i = chargers.size()-1; i >= 0; i--)
		delete chargers[i];

	for (int i = cameras.size()-1; i >= 0; i--)
		delete cameras[i];
}

// *********************************************************************************************************
//
//	Simulates the movement of the robot:
//		Assumes status.txt has been read previously
//		Outputs: updates to status.txt
//
// *********************************************************************************************************
void moveRobot() {	
	// read robotactuators.txt
	int direcciones[MAX_ROBOTS];
	double rate[MAX_ROBOTS];
	string line;
	for (int i = 0; i < robots.size(); i++) {
		string fname = "../State/robotactuators_" + to_string(i) + ".txt";
		ifstream ainput(fname);
		if (!ainput.fail()) {
			while (!ainput.eof()) {
				if (!(ainput >> line)) {
					break;
				}
				if (line == "rate") {
					ainput >> rate[i];
				}
				else if (line == "direction") {
					ainput >> direcciones[i];
				}
			}
		}
		else {
			cout << "robotactuators file not found: " << fname << endl;
		}
	
		ainput.close();
	}
	
	chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

	//cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(currentTime - lastTime).count() << "[µs]" << endl;
	//cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (currentTime - lastTime).count() << "[ns]" << endl;
	
	double timeElapsed = (chrono::duration_cast<chrono::microseconds> (currentTime - lastTime).count()) / 1000000.0;
	
	lastTime = currentTime;
	
	// move the robot accordingly, accounting for obstacles, etc.
	bool robotMoved = false;
	for (int i = 0; i < robots.size(); i++) {
		if (robots[i]->poder == 0) {
			continue;
		}
		robotMoved = true;

		//cout << direcciones[i] << endl;
		if (direcciones[i] == 0) {
			// move robot
			double moveDistance = robots[i]->speed * rate[i] * timeElapsed;
			//cout << "distance traveled: " << moveDistance << endl;
			
			double theta_rads = robots[i]->theta * M_PI / 180.0;
			
			double dx = moveDistance * cos(theta_rads);
			double dy = moveDistance * sin(theta_rads);
			
			if (!collision(i, obstacles, robots, robots[i]->x + dx, robots[i]->y + dy, robots[i]->w / 2.0)) {
				robots[i]->x += dx;
				robots[i]->y += dy;
				robots[i]->theta += robots[i]->bias * rate[i];
			}
		}
		else {
			// rotate robot
			double dRot = robots[i]->spin * rate[i] * timeElapsed * direcciones[i];
			//cout << dRot << endl;
			robots[i]->theta += dRot;
			while (robots[i]->theta > 360.0)
				robots[i]->theta -= 360.0;
			while (robots[i]->theta < 0.0)
				robots[i]->theta += 360.0;
		}
		
		//cout << "new position for robot: " << robots[i]->x << " " << robots[i]->y << " " << robots[i]->theta << endl;
	}

	if (robotMoved) {
	// write new robot positions in status.txt
		ofstream of("../State/statusSim.tmp");
	
		for (int i = 0; i < obstacles.size(); i++) {
			obstacles[i]->print(of);
		}

		for (int i = 0; i < robots.size(); i++) {
			robots[i]->print(of);
		}

		for (int i = 0; i < chargers.size(); i++) {
			chargers[i]->print(of);
		}

		for (int i = 0; i < cameras.size(); i++) {
			cameras[i]->print(of);
		}

		of << "Goal 0 " << theGoal[0] << " " << theGoal[1] << endl;
	
		of.close();

		char mandato[1024];
		strcpy(mandato, "mv ../State/statusSim.tmp ../State/status.txt");
		system(mandato);
	}
}

bool collision(int rid, vector<Obstacle *> obstacles, vector<Robot *> robots, double x, double y, double r) {

	// check to see whether movement puts robot into a wall
	for (int i = 0; i < obstacles.size(); i++) {
		if (obstacles[i]->collision(x, y, r)) {
			return true;
		}
	}
	
	for (int i = 0; i < robots.size(); i++) {
		if (i != rid) {
			if (robots[i]->collision(x, y, r)) {
				return true;
			}
		}
	}
	
	return false;
}

// *********************************************************************************************************
//
//	Simulates a ceiling mounted camera:
//		Assumes status.txt has been read previously
//		Outputs: camera.txt
//
// *********************************************************************************************************
void takePicture() {	
	if ((cameras.size() > 0) && cameras[0]->poder) {
		cameras[0]->getImage(obstacles, robots, chargers);

		// write new CameraSensor images to cameraimg_[i].txt
		ofstream of("../State/cameraimg_0.tmp");

		chrono::milliseconds ms = chrono::duration_cast< chrono::milliseconds >(chrono::steady_clock::now().time_since_epoch());
		of << ms.count() << endl;
		of << robots[0]->theta << endl;
		of << theGoal[0] << endl;
		of << theGoal[1] << endl;
		of << (cameras[0]->countx + 1) << endl;
		of << (cameras[0]->county + 1) << endl;
		for (int yy = cameras[0]->county; yy >= 0; yy--) {
			for (int xx = 0; xx < cameras[0]->countx + 1; xx++) {
				of << cameras[0]->img[xx][yy][0] << " " << cameras[0]->img[xx][yy][1] << " " << cameras[0]->img[xx][yy][2] << endl;
			}
		}
	
		of.close();
	
		char mandato[1024];
		strcpy(mandato, "mv ../State/cameraimg_0.tmp ../State/cameraimg_0.txt");
		system(mandato);
	}	
}

// *********************************************************************************************************
//
//	Simulates the charging sensor on the robot:
//		Assumes status.txt has been read previously
//		Outputs: charging_[i].txt for each robot
//
// *********************************************************************************************************
void detectCharging() {
	for (int i = 0; i < robots.size(); i++) {
		bool ischarging = false;
		for (int j = 0; j < chargers.size(); j++) {
			double dx = fabs(robots[i]->x - chargers[j]->x);
			double dy = fabs(robots[i]->y - chargers[j]->y);
			if ((dx < (chargers[j]->w / 3.0)) && (dy < (chargers[j]->h / 3.0)))
				ischarging = true;
		}
		string fnombre = "../State/charging_" + to_string(i) + ".tmp";
		ofstream of(fnombre);
		of << (int)ischarging << endl;
		of.close();

		char mandato[1024];
		sprintf(mandato, "mv ../State/charging_%i.tmp ../State/charging_%i.txt", i, i);
		system(mandato);
	}
}