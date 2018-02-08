#pragma once

#include "ofMain.h"
#include <iostream>
#include <fstream>
#include <sstream>

class pointCoordinate : public ofImage {
public:
    double x, y;
};

class svgShape : public ofImage {
public:
    vector <pointCoordinate> points;
    double moveCoordX, moveCoordY;
};
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void loadImg(int num);
        void loadFile(string fileName);
        void loadBackground(string background_name);
        ofPath path, path2;
        ofImage img, img2, imgOut;
        vector <float> coordinates;
        vector <ofFbo> fbos;
        vector <ofPath> paths;
        vector <ofImage> imgs;
        vector <svgShape> shapes;
        vector <string> files;
        ofFbo fbo, fbo2;
        int count;
        int countFrame;
        int change;
        int firstLoad;
        int countPressed;
        int countKey;
    
        vector <ofVideoPlayer> backgrounds;
        vector <string> background_files;
        ofVideoPlayer background;
};
