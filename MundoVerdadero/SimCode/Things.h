#pragma once

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_DIM		1000

class Obstacle {
public:
	Obstacle() {
		cout << "incomplete obstacle constructor" << endl;
		exit(1);
	}
	
	Obstacle(string str) {
		//cout << "Obstacle: " << str << endl;
		stringstream ss(str);
		ss >> ID;
		ss >> sx;
		ss >> sy;
		ss >> ex;
		ss >> ey;
		ss >> rd;
		ss >> gn;
		ss >> bl;
	}
	
	~Obstacle() {
	}

	void modify(string params) {
		stringstream ss(params);
		string aspect;
		ss >> aspect;
		if (aspect == "segment") {
			ss >> sx;
			ss >> sy;
			ss >> ex;
			ss >> ey;
		}
		else if (aspect == "color") {
			ss >> rd;
			ss >> gn;
			ss >> bl;
		}
		else {
			cout << "unknown aspect of obstacle to modify: " << aspect << endl;
		}
	}
	
	void print(ofstream &of) {
		of << "Obstacle " << ID << " " << sx << " " << sy << " " << ex << " " << ey << " "  << rd << " " << gn << " " << bl << endl;
	}
	
	bool collision(double x, double y, double r) {
		if (sx == ex) {
			if (fabs(x - sx) > r) {
				return false;
			}
			else if (fabs(x - sx) == r) {
				if (((y > sy) && (y > ey)) || ((y < sy) && (y < ey))) {
					return false;
				}
				else {
					return true;
				}
			}
			else {
				double answer = r * r - ((sx - x) * (sx - x));
				
				double y1 = y - sqrt(answer);
				double y2 = y + sqrt(answer);
			
				if ((((y1 > sy) && (y1 > ey)) || ((y1 < sy) && (y1 < ey))) &&
					(((y2 > sy) && (y2 > ey)) || ((y2 < sy) && (y2 < ey)))) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else {
			double m = (ey - sy) / (ex - sx);
			double b = sy - (m * sx);
			
			//cout << "m: " << m << endl;
			//cout << "b: " << b << endl;
			
			//cout << "x, y: " << x << ", " << y << endl;
			//cout << "r: " << r << endl;
			
			double qa = 1 + m*m;
			double qb = (2 * (b - y) * m) - 2 * x;
			double qc = x * x + (b - y) * (b - y) - r * r;
			
			double answer = (qb * qb) - 4 * qa * qc;
			
			//cout << "answer: " << answer << endl;
			
			if (answer < 0) {
				return false;
			}
			else if (answer == 0) {
				double root_x = -qb / (2 * qa);
				
				if (((root_x > sx) && (root_x > ex)) || ((root_x < sx) && (root_x < ex))) {
					return false;
				}
				else {
					return true;
				}
			}
			else {
				double root_x1 = (-qb - sqrt(answer)) / (2 * qa);
				double root_x2 = (-qb + sqrt(answer)) / (2 * qa);
			
				if ((((root_x1 > sx) && (root_x1 > ex)) || ((root_x1 < sx) && (root_x1 < ex))) &&
					(((root_x2 > sx) && (root_x2 > ex)) || ((root_x2 < sx) && (root_x2 < ex)))) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		
		return false;
	}

	double sx, sy, ex, ey, rd, gn, bl;
	int ID;
};

class Robot {
public:
	Robot() {
		cout << "incomplete robot constructor" << endl;
		exit(1);
	}
	
	Robot(string str) {
		stringstream ss(str);
		ss >> ID;
		ss >> x;
		ss >> y;
		ss >> theta;
		ss >> w;
		ss >> h;
		ss >> speed;
		ss >> spin;
		ss >> bias;
		ss >> rd;
		ss >> gn;
		ss >> bl;
		ss >> poder;
	}
	
	~Robot() {
	}

	void modify(string params) {
		stringstream ss(params);
		string aspect;
		ss >> aspect;
		if (aspect == "pose") {
			ss >> x;
			ss >> y;
			ss >> theta;
		}
		else if (aspect == "size") {
			ss >> w;
			ss >> h;
		}
		else if (aspect == "color") {
			ss >> rd;
			ss >> gn;
			ss >> bl;
		}
		else if (aspect == "off") {
			//cout << "turning the robot off" << endl;
			poder = 0;
		}
		else if (aspect == "on") {
			//cout << "turning the robot on" << endl;
			poder = 1;
		}
		else if (aspect == "bias") {
			ss >> bias;
		}
		else if (aspect == "speed") {
			ss >> speed;
		}
		else if (aspect == "spin") {
			ss >> spin;
		}
		else {
			cout << "unknown aspect of robot to modify: " << aspect << endl;
		}
	}

	void print(ofstream &of) {
		of << "Robot " << ID << " " << x << " " << y << " " << theta << " " << w << " " << h << " "  << speed << " "  << spin << " "  << bias << " "  << rd << " " << gn << " " << bl << " " << poder << endl;
	}
	
	bool collision(double _x, double _y, double _r) {
		double dist = sqrt((_x - x) * (_x - x) + (_y - y) * (_y - y));
		
		if (dist <= (_r + (w/2)))
			return true;
		else
			return false;
	}

	double x, y, theta, w, h, speed, spin, bias, rd, gn, bl;
	int ID, poder;
};

class Charger {
public:
	Charger() {
		cout << "incomplete Charger constructor" << endl;
		exit(1);
	}
	
	Charger(string str) {
		stringstream ss(str);
		ss >> ID;
		ss >> x;
		ss >> y;
		ss >> w;
		ss >> h;
		ss >> rd;
		ss >> gn;
		ss >> bl;
	}
	
	~Charger() {
	}

	void modify(string params) {
		stringstream ss(params);
		string aspect;
		ss >> aspect;
		if (aspect == "location") {
			ss >> x;
			ss >> y;
		}
		else if (aspect == "size") {
			ss >> w;
			ss >> h;
		}
		else if (aspect == "color") {
			ss >> rd;
			ss >> gn;
			ss >> bl;
		}
		else {
			cout << "unknown aspect of charger to modify: " << aspect << endl;
		}
	}

	void print(ofstream &of) {
		of << "Charger " << ID << " " << x << " " << y << " " << w << " " << h << " " << rd << " " << gn << " " << bl << endl;
	}

	double x, y, w, h, rd, gn, bl;
	int ID;
};

class CameraSensor {
public:
	CameraSensor() {
		cout << "incomplete CameraSensor Constructor" << endl;
		exit(1);
	}
	
	CameraSensor(string str) {
		stringstream ss(str);
		ss >> ID;
		ss >> cpos[0];
		ss >> cpos[1];
		ss >> cpos[2];
		ss >> corient[0];
		ss >> corient[1];
		ss >> corient[2];
		ss >> angx;
		ss >> angy;
		ss >> countx;
		ss >> county;
		ss >> fr;
		ss >> fg;
		ss >> fb;
		ss >> raynoise;
		ss >> distortion;
		ss >> poder;
		
		normalize(corient);
	}
	
	~CameraSensor() {
	}
	
	void modify(string params) {
		stringstream ss(params);
		string aspect;
		ss >> aspect;
		if (aspect == "location") {
			ss >> cpos[0];
			ss >> cpos[1];
			ss >> cpos[2];
		}
		else if (aspect == "orientation") {
			ss >> corient[0];
			ss >> corient[1];
			ss >> corient[2];
			normalize(corient);
		}
		else if (aspect == "viewangle") {
			ss >> angx;
			ss >> angy;
		}
		else if (aspect == "resolution") {
			ss >> countx;
			ss >> county;
		}
		else if (aspect == "filter") {
			ss >> fr;
			ss >> fg;
			ss >> fb;
		}
		else if (aspect == "off") {
			poder = 0;
		}
		else if (aspect == "on") {
			poder = 1;
		}
		else if (aspect == "noise") {
			ss >> raynoise;
		}
		else if (aspect == "distortion") {
			ss >> distortion;
		}
		else {
			cout << "unknown aspect of camera to modify: " << aspect << endl;
		}
	}

	void print(ofstream &of) {
		of << "CameraSensor " << ID << " " << cpos[0] << " " << cpos[1] << " " << cpos[2] << " " << corient[0] << " " << corient[1] << " " << corient[2] << " " << angx << " " << angy << " " << countx << " " << county << " " << fr << " " << fg << " " << fb << " " << raynoise << " " << distortion << " " << poder << endl;
	}
	
	void getImage(vector<Obstacle *> obstacles, vector<Robot *> robots, vector<Charger *> chargers) {
		//cout << "start .... ";
		double ray[3], px, py, t, dist;
		double rise, run, ix, iy;
		for (int ay = 0; ay <= county; ay++) {
			for (int ax = 0; ax <= countx; ax++) {
			//for (int ax = 80; ax < 81; ax++) {
				// get ray
				double noisex = (((rand() % 101) / 50.0) - 1.0) * (raynoise / 10.0);
				double noisey = (((rand() % 101) / 50.0) - 1.0) * (raynoise / 10.0);
				ray[0] = (((ax - (countx/2.0)) / (double)countx) * (angx / 45.0) * 2.0 + corient[0]) + noisex;
				ray[1] = (((ay - (county/2.0)) / (double)county) * (angy / 45.0) * -2.0 + corient[1]) + noisey;
				ray[2] = corient[2];
				distortRay(ray);
				normalize(ray);
				//cout << ray[0] << ", " << ray[1] << ", " << ray[2] << endl;
				
				// if nothing seen, nothing is there
				img[ax][ay][0] = img[ax][ay][1] = img[ax][ay][2] = 255; // set to white for now

				if (ray[2] < 0.0) {
					// find point in plane that the ray intersects
					t = cpos[2] / -ray[2];
					px = cpos[0] + ray[0] * t;
					py = cpos[1] + ray[1] * t;
					
					//cout << px << ", " << py << ": " << endl;
					
					// figure out if the point corresponds to an object
					//  check chargers
					for (int i = 0; i < chargers.size(); i++) {
						double x = fabs(px - chargers[i]->x);
						double y = fabs(py - chargers[i]->y);
						if ((x <= (chargers[i]->w / 2.0)) && (y <= (chargers[i]->h / 2.0))) {
							img[ax][ay][0] = (int)(chargers[i]->rd * 255); 
							img[ax][ay][1] = (int)(chargers[i]->gn * 255); 
							img[ax][ay][2] = (int)(chargers[i]->bl * 255);
							//cout << "charger" << endl;
							continue;
						}
					}

					//  check robots
					for (int i = 0; i < robots.size(); i++) {
						dist = sqrt((px - robots[i]->x) * (px - robots[i]->x) + (py - robots[i]->y) * (py - robots[i]->y));
						if (dist <= (robots[i]->w / 2.0)) {
							img[ax][ay][0] = (int)(robots[i]->rd * 255); 
							img[ax][ay][1] = (int)(robots[i]->gn * 255); 
							img[ax][ay][2] = (int)(robots[i]->bl * 255);
							continue;
						}
					}

					//  check obstacles
					for (int i = 0; i < obstacles.size(); i++) {
						rise = obstacles[i]->sy - obstacles[i]->ey;
						run = obstacles[i]->sx - obstacles[i]->ex;
						if ((rise != 0.0) && (run != 0.0)) {
							double pert_m = -run / rise;
							double pert_b = py - pert_m * px;
							
							//cout << "pert_m: " << pert_m << endl;
							//cout << "pert_b: " << pert_b << endl;
							
							double m = rise / run;
							double b = obstacles[i]->sy - m * obstacles[i]->sx;
							
							//cout << "m: " << m << endl;
							//cout << "b: " << b << endl;
							
							ix = (b - pert_b) / (pert_m - m);
							iy = pert_m * ix + pert_b;

							if ((ix > obstacles[i]->sx) && (ix > obstacles[i]->ex)) {
								if (obstacles[i]->sx > obstacles[i]->ex) {
									ix = obstacles[i]->sx;
									iy = obstacles[i]->sy;
								}
								else {
									ix = obstacles[i]->ex;
									iy = obstacles[i]->ey;
								}
							}
							else if ((ix < obstacles[i]->sx) && (ix < obstacles[i]->ex)) {
								if (obstacles[i]->sx < obstacles[i]->ex) {
									ix = obstacles[i]->sx;
									iy = obstacles[i]->sy;
								}
								else {
									ix = obstacles[i]->ex;
									iy = obstacles[i]->ey;
								}
							}

							//if (i == 4)
							//	cout << "intersection4: " << ix << ", " << iy << endl;
						}
						else if (run == 0) {
							ix = obstacles[i]->sx;
							iy = py;

							if ((iy > obstacles[i]->sy) && (iy > obstacles[i]->ey)) {
								if (obstacles[i]->sy > obstacles[i]->ey) {
									ix = obstacles[i]->sx;
									iy = obstacles[i]->sy;
								}
								else {
									ix = obstacles[i]->ex;
									iy = obstacles[i]->ey;
								}
							}
							else if ((iy < obstacles[i]->sy) && (iy < obstacles[i]->ey)) {
								if (obstacles[i]->sy < obstacles[i]->ey) {
									ix = obstacles[i]->sx;
									iy = obstacles[i]->sy;
								}
								else {
									ix = obstacles[i]->ex;
									iy = obstacles[i]->ey;
								}
							}
						}
						else {
							ix = px;
							iy = obstacles[i]->sy;

							if ((ix > obstacles[i]->sx) && (ix > obstacles[i]->ex)) {
								if (obstacles[i]->sx > obstacles[i]->ex) {
									ix = obstacles[i]->sx;
									iy = obstacles[i]->sy;
								}
								else {
									ix = obstacles[i]->ex;
									iy = obstacles[i]->ey;
								}
							}
							else if ((ix < obstacles[i]->sx) && (ix < obstacles[i]->ex)) {
								if (obstacles[i]->sx < obstacles[i]->ex) {
									ix = obstacles[i]->sx;
									iy = obstacles[i]->sy;
								}
								else {
									ix = obstacles[i]->ex;
									iy = obstacles[i]->ey;
								}
							}
						}
						
						dist = sqrt((px - ix) * (px - ix) + (py - iy) * (py - iy));
					
						if (dist < 0.7) {
							img[ax][ay][0] = (int)(obstacles[i]->rd * 255);
							img[ax][ay][1] = (int)(obstacles[i]->gn * 255);
							img[ax][ay][2] = (int)(obstacles[i]->bl * 255);
							continue;
						}
					}
				}
				
				// apply camera filter
				img[ax][ay][0] = (int)((img[ax][ay][0]+10.0) * fr);
				img[ax][ay][1] = (int)((img[ax][ay][1]+10.0) * fg);
				img[ax][ay][2] = (int)((img[ax][ay][2]+10.0) * fb);

				if (img[ax][ay][0] > 255)
					img[ax][ay][0] = 255;
				else if (img[ax][ay][0] < 0)
					img[ax][ay][0] = 0;

				if (img[ax][ay][1] > 255)
					img[ax][ay][1] = 255;
				else if (img[ax][ay][1] < 0)
					img[ax][ay][1] = 0;

				if (img[ax][ay][2] > 255)
					img[ax][ay][2] = 255;
				else if (img[ax][ay][2] < 0)
					img[ax][ay][2] = 0;
			}
		}
	}

	void distortRay(double ray[3]) {
		double tmpy;
		tmpy = ray[1] - distortion * (1.0 - cos(atan2(ray[0], fabs(ray[2])))) * ray[1];
		ray[0] = ray[0] - distortion * (1.0 - cos(atan2(ray[1], fabs(ray[2])))) * ray[0];
		ray[1] = tmpy;
	}

	void normalize(double ray[3]) {
		double mag = 0;
		for (int i = 0; i < 3; i++) {
			mag += ray[i] * ray[i];
		}
		mag = sqrt(mag);
		for (int i = 0; i < 3; i++) {
			ray[i] /= mag;
		}
	}
	
	double cpos[3], corient[3], angx, angy, fr, fg, fb, raynoise, distortion;
	int ID, countx, county, poder;
	
	int img[MAX_DIM][MAX_DIM][3];
};



