import java.awt.*;
import java.util.*;
import java.awt.event.*;
import java.lang.*;
import java.io.*;
import java.net.*;
import javax.swing.*;
import java.math.*;
import java.text.*;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import javax.swing.JComponent;
import javax.swing.JFrame;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;


class Obstacle {
	double sx, sy, ex, ey;
	double rd, gn, bl;
	int ID;
	boolean updated;

	public Obstacle(String str) {
		//System.out.println("new Obstacle: " + str);
		StringTokenizer st = new StringTokenizer(str, " ");
		ID = Integer.parseInt(st.nextToken());
		sx = Double.parseDouble(st.nextToken());
		sy = Double.parseDouble(st.nextToken());
		ex = Double.parseDouble(st.nextToken());
		ey = Double.parseDouble(st.nextToken());
		rd = Double.parseDouble(st.nextToken());
		gn = Double.parseDouble(st.nextToken());
		bl = Double.parseDouble(st.nextToken());
		updated = true;
	}
	
	public void updateIt(String str) {
		StringTokenizer st = new StringTokenizer(str, " ");
		ID = Integer.parseInt(st.nextToken());
		sx = Double.parseDouble(st.nextToken());
		sy = Double.parseDouble(st.nextToken());
		ex = Double.parseDouble(st.nextToken());
		ey = Double.parseDouble(st.nextToken());
		rd = Double.parseDouble(st.nextToken());
		gn = Double.parseDouble(st.nextToken());
		bl = Double.parseDouble(st.nextToken());
		updated = true;
	}
}

class Robot {
	double x, y;
	double theta;
	double width, height;
	double rd, gn, bl;
	double speed, spin, bias;
	int ID, poder;
	boolean updated;
	boolean isCharging;
	
	public Robot(String str) {
		//System.out.println("new Robot: " + str);
		StringTokenizer st = new StringTokenizer(str, " ");
		ID = Integer.parseInt(st.nextToken());
		x = Double.parseDouble(st.nextToken());
		y = Double.parseDouble(st.nextToken());
		theta = Double.parseDouble(st.nextToken());
		width = Double.parseDouble(st.nextToken());
		height = Double.parseDouble(st.nextToken());
		speed = Double.parseDouble(st.nextToken());
		spin = Double.parseDouble(st.nextToken());
		bias = Double.parseDouble(st.nextToken());
		rd = Double.parseDouble(st.nextToken());
		gn = Double.parseDouble(st.nextToken());
		bl = Double.parseDouble(st.nextToken());
		poder = Integer.parseInt(st.nextToken());
		updated = true;

		isCharging = false;
	}
	
	public void updateIt(String str) {
		StringTokenizer st = new StringTokenizer(str, " ");
		ID = Integer.parseInt(st.nextToken());
		x = Double.parseDouble(st.nextToken());
		y = Double.parseDouble(st.nextToken());
		theta = Double.parseDouble(st.nextToken());
		width = Double.parseDouble(st.nextToken());
		height = Double.parseDouble(st.nextToken());
		speed = Double.parseDouble(st.nextToken());
		spin = Double.parseDouble(st.nextToken());
		bias = Double.parseDouble(st.nextToken());
		rd = Double.parseDouble(st.nextToken());
		gn = Double.parseDouble(st.nextToken());
		bl = Double.parseDouble(st.nextToken());
		poder = Integer.parseInt(st.nextToken());
		updated = true;
	}
}

class Charger {
	double x, y;
	double width, height;
	double rd, gn, bl;
	int ID;
	boolean updated;
	
	public Charger(String str) {
		//System.out.println("new Charger: " + str);
		StringTokenizer st = new StringTokenizer(str, " ");
		ID = Integer.parseInt(st.nextToken());
		x = Double.parseDouble(st.nextToken());
		y = Double.parseDouble(st.nextToken());
		width = Double.parseDouble(st.nextToken());
		height = Double.parseDouble(st.nextToken());
		rd = Double.parseDouble(st.nextToken());
		gn = Double.parseDouble(st.nextToken());
		bl = Double.parseDouble(st.nextToken());
		updated = true;
	}
	
	public void updateIt(String str) {
		StringTokenizer st = new StringTokenizer(str, " ");
		ID = Integer.parseInt(st.nextToken());
		x = Double.parseDouble(st.nextToken());
		y = Double.parseDouble(st.nextToken());
		width = Double.parseDouble(st.nextToken());
		height = Double.parseDouble(st.nextToken());
		rd = Double.parseDouble(st.nextToken());
		gn = Double.parseDouble(st.nextToken());
		bl = Double.parseDouble(st.nextToken());
		updated = true;
	}
}

// CameraSensor 0 50 50 50 0 0 -1 45 45 200 200 1 1 1 1
class CameraSpecs {
	double x, y, z;
	double ox, oy, oz;
	double viewx, viewy;
	int resx, resy;
	double fr, fg, fb;
	int ID, poder;
	double raynoise, distortion;
	boolean updated;
	
	public CameraSpecs(String str) {
		//System.out.println("new Charger: " + str);
		StringTokenizer st = new StringTokenizer(str, " ");
		ID = Integer.parseInt(st.nextToken());
		x = Double.parseDouble(st.nextToken());
		y = Double.parseDouble(st.nextToken());
		z = Double.parseDouble(st.nextToken());
		ox = Double.parseDouble(st.nextToken());
		oy = Double.parseDouble(st.nextToken());
		oz = Double.parseDouble(st.nextToken());
		viewx = Double.parseDouble(st.nextToken());
		viewy = Double.parseDouble(st.nextToken());
		resx = Integer.parseInt(st.nextToken());
		resy = Integer.parseInt(st.nextToken());
		fr = Double.parseDouble(st.nextToken());
		fg = Double.parseDouble(st.nextToken());
		fb = Double.parseDouble(st.nextToken());
		raynoise = Double.parseDouble(st.nextToken());
		distortion = Double.parseDouble(st.nextToken());
		poder = Integer.parseInt(st.nextToken());
		updated = true;
	}
	
	public void updateIt(String str) {
		StringTokenizer st = new StringTokenizer(str, " ");
		ID = Integer.parseInt(st.nextToken());
		x = Double.parseDouble(st.nextToken());
		y = Double.parseDouble(st.nextToken());
		z = Double.parseDouble(st.nextToken());
		ox = Double.parseDouble(st.nextToken());
		oy = Double.parseDouble(st.nextToken());
		oz = Double.parseDouble(st.nextToken());
		viewx = Double.parseDouble(st.nextToken());
		viewy = Double.parseDouble(st.nextToken());
		resx = Integer.parseInt(st.nextToken());
		resy = Integer.parseInt(st.nextToken());
		fr = Double.parseDouble(st.nextToken());
		fg = Double.parseDouble(st.nextToken());
		fb = Double.parseDouble(st.nextToken());
		raynoise = Double.parseDouble(st.nextToken());
		distortion = Double.parseDouble(st.nextToken());
		poder = Integer.parseInt(st.nextToken());
		updated = true;
	}
}

class Trajectory {
	double posX, posY, trajX, trajY;

	public Trajectory(double _posX, double _posY, double _trajX, double _trajY) {
		posX = _posX;
		posY = _posY;
		trajX = _trajX;
		trajY = _trajY;
	}
};


class distSensorStuff {
	double robotPos[] = new double[3];
	double chargerPos[] = new double[2];
	double distSensors[] = new double[16];
	double chosenSpeed;
	double chosenTrajectory[] = new double[2];

	Vector<Trajectory> globalTrajectories = new Vector<Trajectory>();

	public distSensorStuff() {
		String file = "../Robot/output/percepts.txt";
		String file2 = "../Robot/output/trajectory.txt";
		String str, str2;
		
		try {
			BufferedReader reader = new BufferedReader(new FileReader(file));
			
			robotPos[0] = Double.parseDouble(reader.readLine());
			robotPos[1] = Double.parseDouble(reader.readLine());
			robotPos[2] = Double.parseDouble(reader.readLine());
			chargerPos[0] = Double.parseDouble(reader.readLine());
			chargerPos[1] = Double.parseDouble(reader.readLine());
			for (int i = 0; i < 16; i++) {
				distSensors[i] = Double.parseDouble(reader.readLine());
			}

			reader.close();

			BufferedReader reader2 = new BufferedReader(new FileReader(file2));
			
			chosenSpeed = Double.parseDouble(reader2.readLine());
			chosenTrajectory[0] = Double.parseDouble(reader2.readLine());
			chosenTrajectory[1] = Double.parseDouble(reader2.readLine());

			reader2.close();
		}
		catch (IOException e) {
			System.out.println(e);
		}

		readGlobalTrajectories();
	}

	public void readGlobalTrajectories() {
		try {
			globalTrajectories.clear();

			String file = "../Robot/output/globaltrajectory.txt";
			BufferedReader reader = new BufferedReader(new FileReader(file));

			String str;
			while (((str=reader.readLine()) != null) && (str.length() != 0)) {
				// System.out.println(str);
				StringTokenizer st = new StringTokenizer(str, " ");
				double posx = Double.parseDouble(st.nextToken());
				double posy = Double.parseDouble(st.nextToken());
				st.nextToken();
				st.nextToken();
				double trajx = Double.parseDouble(st.nextToken());
				double trajy = Double.parseDouble(st.nextToken());

				// System.out.println(trajx + ", " + trajy);

				// if (Math.abs((trajx * trajx + trajy * trajy) - 1.0) > 0.001) {
					// System.out.println(posx + ", " + posy + ": " + trajx + ", " + trajy + " = " + (trajx * trajx + trajy * trajy));
				// }
				Trajectory traj = new Trajectory(posx, posy, trajx, trajy);
				globalTrajectories.addElement(traj);
			}

			reader.close();
		}
		catch (IOException e) {
			System.out.println(e);
		}
	}

	public double getMag(int index) {
		double mag = globalTrajectories.get(index).trajX*globalTrajectories.get(index).trajX;
		mag += globalTrajectories.get(index).trajY*globalTrajectories.get(index).trajY;

		return Math.sqrt(mag);
	}
}


class myCanvas extends JComponent implements MouseListener {
	Vector<Obstacle> obstacles = new Vector<Obstacle>();
	Vector<Robot> robots = new Vector<Robot>();
	Vector<Charger> chargers = new Vector<Charger>();
	Vector<CameraSpecs> cameraspecs = new Vector<CameraSpecs>();
	double goalPos[] = new double[2];

	boolean simulationOn = false;
	int keyFocusIndex = -1;
	Point mousePunto;
	String popMsg;
	int showPFields = 1;

    public static final Color myRed = new Color(200, 0, 0);
	public static final Color myOrange = new Color(255, 140, 0);
    public static final Color myBlue = new Color(0, 0, 200);
	public static final Color myBlack = new Color(0, 0, 0);
	public static final Color myGreen = new Color(0, 200, 0);

	int paintCount = 0;

	int screenX = 0, screenY = 0;
	int windowWidth = 800, windowHeight = 510;

    public myCanvas() {
		addMouseListener(this);

        MyThread thread = new MyThread();
        thread.start();

        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }

	public void mousePressed(MouseEvent e) {}

    public void mouseReleased(MouseEvent e) {}

    public void mouseEntered(MouseEvent e) {}

    public void mouseExited(MouseEvent e) {}

    public void mouseClicked(MouseEvent e) {
    	// System.out.println("Mouse clicked; # of clicks: " + e.getX() + ", " + e.getY());

		double vx = (windowWidth - 10) / 100.0;
		double vy = (windowHeight - 10) / 100.0;
		double scaleVal = vx;
		if (vy < vx)
			scaleVal = vy;	   

		// System.out.println("Fringe = " + scaleVal * 100);
		double X = (e.getX() - 5) / scaleVal;
		double Y = 100.0 - ((e.getY() - 5) / scaleVal);


		if (SwingUtilities.isLeftMouseButton(e)) {
			if ((X > 2.0) && (X < 98.0) && (Y > 2.0) && (Y < 98.0)) {
				// System.out.println("normalized coords: " + X + ", " + Y);

				try {
					// first, find out which robot is being controlled
					// open up ../MundoVerdadero/State/status.txt for reading
					String file = "../MundoVerdadero/State/status.txt";
					BufferedReader reader = new BufferedReader(new FileReader(file));				

					// open up ..//MundoVerdadero/State/status.tmpr for writing
					String fnombre = "../MundoVerdadero/State/status.tmpr";
					BufferedWriter writer = new BufferedWriter(new FileWriter(fnombre));		

					// read each line and write to status.tmpr, except modify robot 0 line
					String str;
					while (((str=reader.readLine()) != null) && (str.length() != 0)) {
						StringTokenizer st = new StringTokenizer(str, " ");
						if (st.nextToken().equals("Robot")) {
							writer.write("Robot ");
							writer.write(st.nextToken() + " ");
							st.nextToken();
							st.nextToken();
							writer.write(X + " " + Y);
							for (int i = 0; i < 10; i++) {
								writer.write(" " + st.nextToken());
							}
							writer.write("\n");
						}
						else
							writer.write(str + "\n");
					}

					reader.close();
					writer.close();

					// move contents to ..//MundoVerdadero/State/status.txt
					String command = "mv ../MundoVerdadero/State/status.tmpr ../MundoVerdadero/State/status.txt";
					Process process = Runtime.getRuntime().exec(command);
				}
				catch (IOException er) {
					System.out.println(er);
				}		
			}
		}
		else if (SwingUtilities.isRightMouseButton(e)) {
			// System.out.println("right click");
			if ((X > 2.0) && (X < 98.0) && (Y > 2.0) && (Y < 98.0)) {
				// System.out.println("normalized coords: " + X + ", " + Y);

				try {
					// first, find out which robot is being controlled
					// open up ../MundoVerdadero/State/status.txt for reading
					String file = "../MundoVerdadero/State/status.txt";
					BufferedReader reader = new BufferedReader(new FileReader(file));				

					// open up ..//MundoVerdadero/State/status.tmpr for writing
					String fnombre = "../MundoVerdadero/State/status.tmpr";
					BufferedWriter writer = new BufferedWriter(new FileWriter(fnombre));		

					// read each line and write to status.tmpr, except modify robot 0 line
					String str;
					while (((str=reader.readLine()) != null) && (str.length() != 0)) {
						StringTokenizer st = new StringTokenizer(str, " ");
						if (st.nextToken().equals("Goal")) {
							writer.write("Goal ");
							writer.write(st.nextToken() + " ");
							writer.write(X + " " + Y);
							writer.write("\n");
						}
						else
							writer.write(str + "\n");
					}

					reader.close();
					writer.close();

					// move contents to ..//MundoVerdadero/State/status.txt
					String command = "mv ../MundoVerdadero/State/status.tmpr ../MundoVerdadero/State/status.txt";
					Process process = Runtime.getRuntime().exec(command);
				}
				catch (IOException er) {
					System.out.println(er);
				}		
			}
		}
	}


	public void updateScreenPosition(int x, int y) {
		screenX = x;
		screenY = y;
		//System.out.println("Screen: " + screenX + ", " + screenY);
	}

	public void updateTheWindowSize(int w, int h) {
		// System.out.print(w + ", " + h + "     ");
		windowWidth = w-300;
		windowHeight = h-30;
	}

    public class MyThread extends Thread {

		public void updateRobots(String str) {
			// see if this robot already exists
			boolean found = false;
		
			StringTokenizer st = new StringTokenizer(str, " ");
			int id = Integer.parseInt(st.nextToken());
			//System.out.println("Robot ID: " + id);
			for (int i = 0; i < robots.size(); i++) {
				if (id == robots.get(i).ID) {
					robots.get(i).updateIt(str);
					found = true;
					break;
				}
			}
		
			if (!found) {
				// System.out.println("We have a new robot");
				robots.add(new Robot(str));
			}
		}
		
		public void updateObstacles(String str) {
			// see if this obstacle already exists
			boolean found = false;
		
			StringTokenizer st = new StringTokenizer(str, " ");
			int id = Integer.parseInt(st.nextToken());
			//System.out.println("Obstacle ID: " + id);
			for (int i = 0; i < obstacles.size(); i++) {
				if (id == obstacles.get(i).ID) {
					obstacles.get(i).updateIt(str);
					found = true;
					break;
				}
			}
		
			if (!found) {
				// System.out.println("We have a new obstacle");
				obstacles.add(new Obstacle(str));
			}
		}
		
		public void updateChargers(String str) {
			// see if this charger already exists
			boolean found = false;
		
			StringTokenizer st = new StringTokenizer(str, " ");
			int id = Integer.parseInt(st.nextToken());
			//System.out.println("Charger ID: " + id);
			for (int i = 0; i < chargers.size(); i++) {
				if (id == chargers.get(i).ID) {
					chargers.get(i).updateIt(str);
					found = true;
					break;
				}
			}
		
			if (!found) {
				// System.out.println("We have a new charger");
				chargers.add(new Charger(str));
			}
		}

		public void updateCameras(String str) {
			// see if this camera already exists
			boolean found = false;
		
			StringTokenizer st = new StringTokenizer(str, " ");
			int id = Integer.parseInt(st.nextToken());
			//System.out.println("Charger ID: " + id);
			for (int i = 0; i < cameraspecs.size(); i++) {
				if (id == cameraspecs.get(i).ID) {
					cameraspecs.get(i).updateIt(str);
					found = true;
					break;
				}
			}
		
			if (!found) {
				// System.out.println("We have a new charger");
				cameraspecs.add(new CameraSpecs(str));
			}
		}

		public void updateGoal(String str) {
			StringTokenizer st = new StringTokenizer(str, " ");
			int id = Integer.parseInt(st.nextToken());
			goalPos[0] = Double.parseDouble(st.nextToken());
			goalPos[1] = Double.parseDouble(st.nextToken());
		}
	
		public void updateThings() {
			// Set each object to not having been updated
			for (int i = 0; i < robots.size(); i++) {
				robots.get(i).updated = false;
			}
			for (int i = 0; i < obstacles.size(); i++) {
				obstacles.get(i).updated = false;
			}
			for (int i = 0; i < chargers.size(); i++) {
				chargers.get(i).updated = false;
			}
		
			try {
				// update objects by reading status.txt
				String file = "../MundoVerdadero/State/status.txt";
				String str;
				BufferedReader reader = new BufferedReader(new FileReader(file));
				
				while (((str=reader.readLine()) != null) && (str.length()!=0)) {
					// see what kind of object it is
					StringTokenizer st = new StringTokenizer(str, " ");
					String str2 = st.nextToken();
					switch (str2) {
						case "Robot": updateRobots(st.nextToken("")); break;
						case "Obstacle": updateObstacles(st.nextToken("")); break;
						case "Charger": updateChargers(st.nextToken("")); break;
						case "CameraSensor": updateCameras(st.nextToken("")); break;
						case "Goal": updateGoal(st.nextToken("")); break;
						default: System.out.println("Don't recognize object " + str2); break;
					}
				}
				
				reader.close();
			}
			catch (IOException e) {
				System.out.println(e);
			}
			
			// remove objects that have not been updated
			for (int i = 0; i < robots.size(); i++) {
				if (!(robots.get(i).updated)) {
					System.out.println("removing robot " + robots.get(i).ID);
					robots.remove(i);
					i--;
				}
			}
			for (int i = 0; i < obstacles.size(); i++) {
				if (!(obstacles.get(i).updated)) {
					System.out.println("removing obstacle " + obstacles.get(i).ID);
					obstacles.remove(i);
					i--;
				}
			}
			for (int i = 0; i < chargers.size(); i++) {
				if (!(chargers.get(i).updated)) {
					System.out.println("removing charger " + chargers.get(i).ID);
					chargers.remove(i);
					i--;
				}
			}
			
			// see if the simulation is on or off
			try {
				// update objects by reading status.txt
				String file = "../MundoVerdadero/State/sim.txt";
				String str;
				BufferedReader reader = new BufferedReader(new FileReader(file));
				
				str = reader.readLine();
				//System.out.println("the simulation is " + str);
				if (str.equals("on"))
					simulationOn = true;
				else
					simulationOn = false;
				
				reader.close();
			}
			catch (IOException e) {
				System.out.println(e);
			}

			try {
				// find out which robot is being controlled
				String file = "../MundoVerdadero/State/keyFocusIndex.txt";
				String str;
				BufferedReader reader = new BufferedReader(new FileReader(file));
				str = reader.readLine();
				keyFocusIndex = Integer.parseInt(str);
				reader.close();
			}
			catch (IOException e) {
				System.out.println(e);
			}

			// get an update on charging
			try {
				for (int i = 0; i < robots.size(); i++) {
					String file = "../MundoVerdadero/State/charging_" + i + ".txt";
					BufferedReader reader = new BufferedReader(new FileReader(file));
					if (reader.readLine().equals("0")) {
						robots.get(i).isCharging = false;
					}
					else {
						robots.get(i).isCharging = true;
					}

					reader.close();
				}
			}
			catch (IOException e) {
				System.out.println(e);
			}
		
		}
	
        public void run() {
            try {
                // repeatedly read status.txt and display
				while (true) {
					updateThings();
                    repaint();
                    Thread.sleep(100);
                }
            }
            catch (InterruptedException e) {
                System.out.println(e);
            }
        }
    }

    public void paint(Graphics g) {
		double vx = (windowWidth - 10) / 100.0;
		double vy = (windowHeight - 10) / 100.0;
		double scaleVal = vx;
		if (vy < vx)
			scaleVal = vy;
		paintWorldFrame(g, 0, 0);
		paintDistSensor(g, (int)(100 * scaleVal) + 10, 30);
    }

	public void paintDistSensor(Graphics g, int cx, int cy) {
		int componentWidth = 300, componentHeight = 300;
		g.setColor(new Color(200, 200, 200));
		g.drawRect(cx, cy, componentWidth, componentHeight);

		double w = robots.get(0).width * 3.5;
		double h = robots.get(0).height * 3.5;
		double x = 150+cx;
		double y = 150+cy;

		int Xvals[] = new int[16];
		int Yvals[] = new int[16];
		distSensorStuff sensors = new distSensorStuff();
		double inc = (2.0 * 3.14159) / 16;
		double theta = 0.0;//(sensors.robotPos[2] * 3.14159 / 180.0) - (3.14159 / 2.0);
		// System.out.println(theta * 180.0 / 3.14159);
		for (int i = 0; i < 16; i++) {
			Xvals[i] = (int)(x + Math.cos(theta) * 2.0 * sensors.distSensors[i]);
			Yvals[i] = (int)(y - Math.sin(theta) * 2.0 * sensors.distSensors[i]);
			theta += inc;
		}

		g.setColor(new Color(220, 220, 220));
		g.fillPolygon(Xvals, Yvals, 16);

		g.setColor(new Color(180, 180, 180));
		for (int i = 0; i < 16; i++) {
			g.drawLine((int)x, (int)y, Xvals[i], Yvals[i]);
		}

		// display the vector from the robot to the charger
		double dx = sensors.chargerPos[0] - sensors.robotPos[0];
		double dy = sensors.chargerPos[1] - sensors.robotPos[1];
		double chargerTheta = Math.atan2(dy, dx) - (sensors.robotPos[2] * 3.14159 / 180.0) + (3.14159 / 2.0);
		// System.out.println("chargerTheta: " + chargerTheta * 180.0 / 3.14159);
		// System.out.println("robotTheta: " + sensors.robotPos[2]);
		g.setColor(new Color((float)chargers.get(0).rd, (float)chargers.get(0).gn, (float)chargers.get(0).bl));
		g.drawLine((int)x, (int)y, (int)(x + 150.0 * Math.cos(-chargerTheta)), (int)(y + 150.0 * Math.sin(-chargerTheta)));

		// display the chosen trajectory
		double chosenTheta = Math.atan2(sensors.chosenTrajectory[1], sensors.chosenTrajectory[0]) - (sensors.robotPos[2] * 3.14159 / 180.0) + (3.14159 / 2.0);;
		g.setColor(new Color(0, 200, 0));
		g.drawLine((int)x, (int)y, (int)(x + 75.0 * Math.cos(-chosenTheta)), (int)(y + 75.0 * Math.sin(-chosenTheta)));

		g.setColor(new Color((float)robots.get(0).rd, (float)robots.get(0).gn, (float)robots.get(0).bl));
		g.fillOval((int)(x - (w / 2.0) + 0.5), (int)(y - (h / 2.0) + 0.5), (int)(w + 0.5), (int)(h + 0.5));

		g.setColor(new Color(220, 20, 20));
		g.drawLine((int)x, (int)y, (int)x, (int)(y - h/2));

	}

	public void paintWorldFrame(Graphics g, int cx, int cy) {
		double vx = (windowWidth - 10) / 100.0;
		double vy = (windowHeight - 10) / 100.0;
		double scaleVal = vx;
		if (vy < vx)
			scaleVal = vy;
		int componentWidth = (int)(100 * scaleVal) + 10, componentHeight = (int)(100 * scaleVal) + 10;

        g.setColor(new Color(200, 200, 200));
        g.fillRect(cx, cy, componentWidth, componentHeight);

        g.setColor(new Color(230, 230, 230));
        g.fillRect(cx + 5, cy + 5, componentWidth-10, componentHeight-10);

		if (showPFields == 1) {
			// draw the potential fields
			distSensorStuff sensors = new distSensorStuff();
			// System.out.println(sensors.globalTrajectories.size());
			g.setColor(new Color(0, 200, 0));
			for (int i = 0; i < sensors.globalTrajectories.size(); i++) {
				// System.out.println(sensors.globalTrajectories.get(i).trajX + ", " + sensors.globalTrajectories.get(i).trajY);
				int x = cx + 5 + (int)((sensors.globalTrajectories.get(i).posX / 200.0) * (componentWidth-10));
				int y = cy + 5 + (int)(((200 - sensors.globalTrajectories.get(i).posY) / 200.0) * (componentHeight-10));
				
				// System.out.println(sensors.getMag(i));
				if (sensors.getMag(i) < 0.01) {
					g.drawLine(x, y, x+1, y+1);
				}
				else {
					double theta = Math.atan2(sensors.globalTrajectories.get(i).trajY, sensors.globalTrajectories.get(i).trajX);
					double xp = x + scaleVal * Math.cos(theta);
					double yp = y - scaleVal * Math.sin(theta);
					double x1 = xp + scaleVal * Math.cos(theta - Math.PI * 0.75);
					double y1 = yp - scaleVal * Math.sin(theta - Math.PI * 0.75);
					g.drawLine((int)xp, (int)yp, (int)x1, (int)y1);
					double x2 = xp + scaleVal * Math.cos(theta + Math.PI * 0.75);
					double y2 = yp - scaleVal * Math.sin(theta + Math.PI * 0.75);
					g.drawLine((int)xp, (int)yp, (int)x2, (int)y2);
					double x3 = xp - 2*scaleVal * Math.cos(theta);
					double y3 = yp + 2*scaleVal * Math.sin(theta);
					g.drawLine((int)xp, (int)yp, (int)x3, (int)y3);
				}
			}
		}

		// draw the chargers
		for (int i = 0; i < chargers.size(); i++) {
			double w = chargers.get(i).width * scaleVal;
			double h = chargers.get(i).height * scaleVal;
			double x = chargers.get(i).x * scaleVal + 5.0;
			double y = (100.0 - chargers.get(i).y) * scaleVal + 5.0;
			g.setColor(new Color((float)chargers.get(i).rd, (float)chargers.get(i).gn, (float)chargers.get(i).bl));
			g.fillRect((int)(x - (w / 2.0) + 0.5) + cx, (int)(y - (h / 2.0) + 0.5) + cy, (int)(w + 0.5), (int)(h + 0.5));
		}
		
		// draw the robots
		for (int i = 0; i < robots.size(); i++) {
			double w = robots.get(i).width * scaleVal;
			double h = robots.get(i).height * scaleVal;
			double x = robots.get(i).x * scaleVal + 5.0;
			double y = (100.0 - robots.get(i).y) * scaleVal + 5.0;
			g.setColor(new Color((float)robots.get(i).rd, (float)robots.get(i).gn, (float)robots.get(i).bl));
			g.fillOval((int)(x - (w / 2.0) + 0.5) + cx, (int)(y - (h / 2.0) + 0.5) + cy, (int)(w + 0.5), (int)(h + 0.5));

			double theta = robots.get(i).theta * Math.PI / 180.0;
			double dx = Math.cos(theta) * w / 2.0;
			double dy = Math.sin(theta) * w / 2.0;
			g.setColor(myOrange);
			g.drawLine((int)(x + 0.5) + cx, (int)(y + 0.5) + cy, (int)(x + dx), (int)(y - dy));
		}
		
		// draw the obstacles
		for (int i = 0; i < obstacles.size(); i++) {
			double sx = obstacles.get(i).sx * scaleVal + 5.0;
			double sy = (100.0 - obstacles.get(i).sy) * scaleVal + 5.0;
			double ex = obstacles.get(i).ex * scaleVal + 5.0;
			double ey = (100.0 - obstacles.get(i).ey) * scaleVal + 5.0;
			g.setColor(new Color((float)obstacles.get(i).rd, (float)obstacles.get(i).gn, (float)obstacles.get(i).bl));
			g.drawLine((int)(sx + 0.5) + cx, (int)(sy + 0.5) + cy, (int)(ex + 0.5), (int)(ey + 0.5));
		}

		// draw the goal
		g.setColor(new Color(0, 200, 0, 50));
		g.fillOval((int)((goalPos[0]-3.1)*scaleVal) + cx, (int)((100-(goalPos[1]+3.1))*scaleVal) + cy, (int)(8*scaleVal), (int)(8*scaleVal));

		// see whether the simulation is on or off
		if (!simulationOn) {
			g.setFont(new Font("Courier", Font.PLAIN, 21));
			g.setColor(myOrange);
			g.drawString("Simulation Off", componentWidth / 2 + cx - 91, (componentHeight / 3) + cy);
		}
	}
}

class viewer extends JFrame implements KeyListener, ComponentListener {
    myCanvas canvas;
    Color bkgroundColor = new Color(0, 0, 0);
	boolean shown = false;

    viewer(int _screenWidth, int _screenHeight) {
        setSize(_screenWidth, _screenHeight + 22);
        getContentPane().setBackground(bkgroundColor);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(500, 0, _screenWidth, _screenHeight + 22);
        canvas = new myCanvas();
		addKeyListener(this);
		addComponentListener(this);
        getContentPane().add(canvas);
        setVisible(true);
        setTitle("The Viewer");

		shown = true;

		// call this when the window is closed down
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				quitSimulation();
				System.exit(0);
			}
		});		
    }

	public void componentHidden(ComponentEvent e) {}

    public void componentMoved(ComponentEvent e) {
		if (!shown)
			return;

		Point p = getContentPane().getLocationOnScreen();
		canvas.updateScreenPosition(p.x, p.y);
    }

    public void componentResized(ComponentEvent e) {
		canvas.updateTheWindowSize(e.getComponent().getWidth(), e.getComponent().getHeight());
	}

    public void componentShown(ComponentEvent e) {}

	public void keyReleased(KeyEvent e) {}
	public void keyTyped(KeyEvent e) {}

	public void keyPressed(KeyEvent e) {
		int keyCode = e.getKeyCode();
    	switch (keyCode) { 
        	case KeyEvent.VK_UP:
            	//System.out.println("up arrow");
				writeControl(0, 1);
            	break;
        	case KeyEvent.VK_DOWN:
				//System.out.println("down arrow");
				writeControl(0, 0);
            	break;
        	case KeyEvent.VK_LEFT:
				//System.out.println("left arrow");
				writeControl(1, 1);
            	break;
        	case KeyEvent.VK_RIGHT:
				//System.out.println("right arrow");
				writeControl(-1, 1);
            	break;
			case KeyEvent.VK_Q:
				quitSimulation();
				break;
			case KeyEvent.VK_1:
				loadMaze(1);
				break;
			case KeyEvent.VK_2:
				loadMaze(2);
				break;
			case KeyEvent.VK_3:
				loadMaze(3);
				break;
			case KeyEvent.VK_4:
				loadMaze(4);
				break;
			case KeyEvent.VK_R:
				startSimulation();
				break;
			case KeyEvent.VK_U:
				updatePFields();
				break;
			case KeyEvent.VK_P:
				canvas.showPFields = 1 - canvas.showPFields;
				break;
     	}
	}

	public void updatePFields() {
		try {
			// now write the information to the appropriate robotactuators file
			// String fnombre = "../MundoVerdadero/State/sim.txt";
			// BufferedWriter writer = new BufferedWriter(new FileWriter(fnombre));		

			// writer.write("on\n");

			// writer.close();

			System.out.println("Update potential fields");

			// start the sim program
			String command = "./pfields.sh";
			Process process = Runtime.getRuntime().exec(command);
		}
		catch (IOException e) {
			System.out.println(e);
		}
	}

	public void startSimulation() {
		try {
			// now write the information to the appropriate robotactuators file
			String fnombre = "../MundoVerdadero/State/sim.txt";
			BufferedWriter writer = new BufferedWriter(new FileWriter(fnombre));		

			writer.write("on\n");

			writer.close();

			// start the sim program
			String command = "./simulator_on.sh";
			Process process = Runtime.getRuntime().exec(command);
		}
		catch (IOException e) {
			System.out.println(e);
		}
	}

	public void quitSimulation() {
		try {
			// now write the information to the appropriate robotactuators file
			String fnombre = "../MundoVerdadero/State/sim.txt";
			BufferedWriter writer = new BufferedWriter(new FileWriter(fnombre));		

			writer.write("off\n");

			writer.close();
		}
		catch (IOException e) {
			System.out.println(e);
		}		
	}

	public void loadMaze(int num) {
		try {
			Process process = Runtime.getRuntime().exec("cp ../MundoVerdadero/Presets/MazePreset" + num + ".txt ../MundoVerdadero/State/status.txt");
		}
		catch (IOException e) {
			System.out.println(e);
		}
	}

	public void writeControl(int direction, double rate) {
		try {
			// first, find out which robot is being controlled
			String file = "../MundoVerdadero/State/keyFocusIndex.txt";
			String str;
			BufferedReader reader = new BufferedReader(new FileReader(file));				
			str = reader.readLine();
			int rindex = Integer.parseInt(str);
			reader.close();
	
			// now write the information to the appropriate robotactuators file
			String fnombre = "../MundoVerdadero/State/robotactuators_" + rindex + ".txt";
			BufferedWriter writer = new BufferedWriter(new FileWriter(fnombre));		

			writer.write("rate " + rate + "\ndirection " + direction + "\n");

			writer.close();
		}
		catch (IOException e) {
			System.out.println(e);
		}		
	}

    public static void main(String args[]) {
        new viewer(800, 510);
    }
}
