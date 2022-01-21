#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

struct Point {
	double x, y, dist;
};

struct Assumptions {
	double robot_color[3], charger_color[3];
	double max_speed, max_spin;
	double robot_radius;
	double charger_width, charger_height;
};

class Mapper {
public:
	int robotIndex;
	double robotPos[3], chargerPos[2], theGoal[2];
	int ***img, imgwidth, imgheight;
	bool **obst;
	bool readImage;
	long lastCameraRead;
	Assumptions *assumptions;

	double distanceSensor[16];
	
	Mapper() {
		cout << "incomplete Mapper constructor" << endl;
		exit(1);
	}
	
	Mapper(int _ind, Assumptions *_assumptions) {
		robotIndex = _ind;
		assumptions = _assumptions;
		readImage = false;
		imgwidth = imgheight = -1;
		lastCameraRead = 0;
	}
	
	~Mapper() {
		cleanMemory();
	}
	
	void createMap() {
		// read in the current image
		string fname = "../MundoVerdadero/State/cameraimg_" + to_string(robotIndex) + ".txt";
		ifstream input(fname);
		
		int oldimgwidth = imgwidth;
		int oldimgheight = imgheight;
		int newimgwidth, newimgheight;
		
		input >> lastCameraRead;
		input >> robotPos[2];
		input >> theGoal[0];
		input >> theGoal[1];
		input >> newimgwidth;
		input >> newimgheight;
		
		if ((oldimgwidth != newimgwidth) || (oldimgheight != newimgheight)) {
			if (readImage) {
				cleanMemory();
			}

			imgwidth = newimgwidth;
			imgheight = newimgheight;
			
			img = new int**[imgwidth];
			obst = new bool*[imgwidth];
			for (int i = 0; i < imgwidth; i++) {
				img[i] = new int*[imgheight];
				obst[i] = new bool[imgheight];
				for (int j = 0; j < imgheight; j++) {
					img[i][j] = new int[3];
				}
			}
		}
		
		for (int i = 0; i < imgheight; i++) {
			for (int j = 0; j < imgwidth; j++) {
				input >> img[j][i][0];
				input >> img[j][i][1];
				input >> img[j][i][2];
				obst[j][i] = false;
			}
		}
		
		input.close();
		
		readImage = true;
		
		// map out the world
		robotPos[0] = robotPos[1] = 0.0;
		chargerPos[0] = chargerPos[1] = 0.0;
		int robotCount = 0, chargerCount = 0;
		for (int i = 0; i < imgheight; i++) {
			for (int j = 0; j < imgwidth; j++) {
				if (isRobot(img[j][i])) {
					robotCount ++;
					robotPos[0] += j;
					robotPos[1] += i;
				}
				else if (isCharger(img[j][i])) {
					chargerCount ++;
					chargerPos[0] += j;
					chargerPos[1] += i;
				}
				
				if (isObstacle(img[j][i])) {
					fillCircle(obst, imgwidth, imgheight, j, i, 1);//assumptions->robot_radius+0.0);
				}
			}
		}
		
		if (robotCount > 0) {
			robotPos[0] /= robotCount;
			robotPos[1] /= robotCount;
		}
		else {
			robotPos[0] = robotPos[1] = -99999.0;
		}

		if (chargerCount > 0) {
			chargerPos[0] /= chargerCount;
			chargerPos[1] /= chargerCount;
		}
		else {
			chargerPos[0] = chargerPos[1] = -99999.0;
		}
		
		//cout << "Robot Pos: " << robotPos[0] << ", " << robotPos[1] << endl;
		//cout << "Charger Pos: " << chargerPos[0] << ", " << chargerPos[1] << endl;
		
		// print out the "tokens of proficiency"
		fname = "output/mapper_" + to_string(robotIndex) + ".tmp";
		ofstream output(fname);
		
		output << robotPos[0] << endl <<  robotPos[1] << endl;
		output << chargerPos[0] << endl << chargerPos[1] << endl;
		output << imgwidth << endl << imgheight << endl;
		
		for (int i = 0; i < imgheight; i++) {
			for (int j = 0; j < imgwidth; j++) {
				output << obst[j][i];
			}
			output << endl;
		}
		
		output.close();
		
		char mandato[1024];
		sprintf(mandato, "mv output/mapper_%i.tmp output/mapper_%i.txt", robotIndex, robotIndex);
		system(mandato);
	}
	
	void cleanMemory() {
		for (int i = 0; i < imgwidth; i++) {
			for (int j = 0; j < imgheight; j++) {
				delete[] img[i][j];
			}
			delete[] img[i];
			delete[] obst[i];
		}
		delete[] img;
		delete[] obst;
	}

	bool inRange(int val1, int val2, int threshold) {
		if (abs(val1-val2) <= threshold)
			return true;

		return false;
	}
	
	bool isRobot(int pixel[3]) {
		int assumedColor[3];
		assumedColor[0] = (int)(assumptions->robot_color[0] * 255);
		assumedColor[1] = (int)(assumptions->robot_color[1] * 255);
		assumedColor[2] = (int)(assumptions->robot_color[2] * 255);

		if (inRange(pixel[0], assumedColor[0], 20) && inRange(pixel[1], assumedColor[1], 20) && inRange(pixel[2], assumedColor[2], 20))
			return true;
		
		return false;
	}
	
	bool isCharger(int pixel[3]) {
		int assumedColor[3];
		assumedColor[0] = (int)(assumptions->charger_color[0] * 255);
		assumedColor[1] = (int)(assumptions->charger_color[1] * 255);
		assumedColor[2] = (int)(assumptions->charger_color[2] * 255);

		if (inRange(pixel[0], assumedColor[0], 20) && inRange(pixel[1], assumedColor[1], 20) && inRange(pixel[2], assumedColor[2], 20))
			return true;
		
		return false;
	}
	
	bool isObstacle(int pixel[3]) {
		if (isRobot(pixel) || isCharger(pixel))
			return false;

		if ((pixel[0] > 230) && (pixel[1] > 230) && (pixel[2] > 230))
			return false;
		
		return true;
	}
	
	void fillCircle(bool **obst, int imgwidth, int imgheight, int x, int y, double radi) {
		int dx = 0, dy;
		double ry = radi / (200.0 / imgheight);
		double rx = radi / (200.0 / imgwidth);
		
		for (dy = -(int)ry; dy <= (int)ry; dy++) {
			if (((y+dy) < 0) || ((y+dy) >= imgheight))
				continue;
			
			// find left side
			if (dy <= 0) {
				// see if we should move dx to the left
				while (roundedDist(dx-1, dy) <= rx) {
					dx --;
				}
			}
			else {
				while (roundedDist(dx, dy) > rx) {
					dx ++;
				}
			}
			
			//cout << dx << ", " << dy << endl;
			
			for (int xs = x+dx; xs <= x-dx; xs++) {
				if (((xs) < 0) || (xs >= imgwidth))
					continue;
				
				obst[xs][dy+y] = true;
			}
		}
	}
	
	int roundedDist(int dx, int dy) {
		return (int)(sqrt(dx*dx + dy * dy) + 0.5);
	}

	void getDistSensor(double thePos[3]) {
		double inc = 2 * 3.14159 / 16.0;
		int index = 0;
		double heading = (thePos[2] * 3.14159 / 180.0) - (3.14159 / 2.0);
		// cout << "Robot at: " << robotPos[0] << ", " << robotPos[1] << endl;
		for (double theta = 0.0; theta < 2 * 3.14159; theta += inc) {
			// cout << theta << ": " << endl;;
			distanceSensor[index] = readSonar(theta + heading, thePos);
			// cout << distanceSensor[index] << endl;
			index ++;
		}
	}

	double readSonar(double angle, double thePos[3]) {
		double maxDist = 74.0;

		Point p1, p2;
		p1.x = thePos[0];
		p1.y = thePos[1];
		p2.x = cos(angle) * maxDist + p1.x;
		p2.y = sin(angle) * maxDist + p1.y;

		// cout << p2.x << ", " << p2.y << ": ";

		//printf("For edge (%.1lf, %.1lf) to (%.1lf, %.1lf):\n", p1.x, p1.y, p2.x, p2.y); fflush(stdout);
		double dx = p2.x - p1.x;
		double dy = p2.y - p1.y;
		double x, y, t;
		for (t = 0.0; t <= 1.0049; t+=0.005) {
			x = p1.x + dx * t;
			y = p1.y + dy * t;
			// printf("\tcheck (%.1lf, %.1lf) with t = %lf\n", x, y, t); fflush(stdout);
			
			if (obst[(int)(x+0.5)][(int)(y+0.5)]) {
				//cout << "Path blocked" << endl;
				break;
			}
		}

		//cout << "Path clear" << endl;
	
		return maxDist * t;
	}

	void writePerceptions(string str, double thePos[3]) {
		string fnombre = "output/" + str + ".tmp";
		ofstream output(fnombre);

		output << thePos[0] << endl;
		output << thePos[1] << endl;
		output << thePos[2] << endl;
		output << (2*theGoal[0]) << endl;
		output << (2*theGoal[1]) << endl;
		// output << chargerPos[0] << endl;
		// output << chargerPos[1] << endl;
		for (int i = 0; i < 16; i++) {
			output << distanceSensor[i] << endl;
		}

		output.close();

		string mandato = "mv output/" + str + ".tmp output/" + str + ".txt";
		system(mandato.c_str());
	}

	void addGlobalPercept(double thePos[3], ofstream &output) {

		output << thePos[0] << " ";
		output << thePos[1] << " ";
		output << thePos[2] << " ";
		output << (2*theGoal[0]) << " ";
		output << (2*theGoal[1]) << " ";
		for (int i = 0; i < 16; i++) {
			output << distanceSensor[i] << " ";
		}
		output << endl;
	}


};
