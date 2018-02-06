#include "ofApp.h"
#include <iostream>
#include <fstream>
#include <sstream>
//--------------------------------------------------------------
void ofApp::setup(){
    
    // initial all the variables
    count = 0;
    countFrame = 0;
    change = 0;
    firstLoad = 0;  // if it is first time load image
    
    loadFile("test.txt"); // check loadFile function
    
     // It is first time load image, so the variable is 0
    loadImg(0); // check loadImg function
    
}

void ofApp::loadFile(string fileName){
    
    // -----------------------------------------------------
    // load SVG points file
    // I have already convert them to txt file
    // their format is "x0,y0 x1,y1 x2,y2"
    // Now I only load it once
    
   
    ifstream infile;
    infile.open (ofToDataPath(fileName).c_str());
    if(!infile) {cout << "Error: File not found or corrupt. "<< endl;}
    string coordStr[3];
    
    // load the strings from txt files
    while(infile >> coordStr[0] && infile >>  coordStr[1] && infile >>  coordStr[2])
    {
        svgShape sCoord;
        
        for(int j = 0; j < 3; j++) {
            string number;
            pointCoordinate point;
            istringstream ss(coordStr[j]);
            
            int first = 0;
            while (getline(ss,number, ','))
            {
                if(first == 0){
                    point.x = std::atof(number.c_str());
                    //std::cout <<"number1: " << number << '\n';
                    first = 1;
                }
                else {
                    point.y = std::atof(number.c_str());
                    //std::cout <<"number2: " << number << '\n';
                    first = 0;
                }
            }
            sCoord.points.push_back(point);
        }
        shapes.push_back(sCoord);
        count ++ ;
    }
    
}

void ofApp::loadImg(int num){
    
    // ---------------------------------------------------
    // initial the img array, fbos, path
    // fbo is an array used to create mask for images
    // imgs is an array used to put all the images
    // path is an array used to draw path
    
    // paths and fbos should be reinitialed everytime I change texture
    // but imgs only need to be loaded once. This could speed up showing images.
    
    paths.clear();
    fbos.clear();
    for(int i = 0; i < count; i++) {
        if(firstLoad == 0){
            ofImage imgUnit;
            imgs.push_back(imgUnit);
        }
        ofFbo fboUnit;
        ofPath pathUnit;
        
        fbos.push_back(fboUnit);
        paths.push_back(pathUnit);
    }
    
    for(int i = 0; i < count; i++){
        
        // load images only once, it reduce the time loading images
        if(firstLoad == 0){
            string loadStr = std::to_string((i + num) % 15) + ".jpg";
            imgs[i].load(loadStr);
        }
        
        // num is a variable changed by time
        int imgIndex = (i + num) % count;
        fbos[i].allocate(imgs[imgIndex].getWidth(), imgs[imgIndex].getHeight(),GL_RGBA);
        fbos[i].begin();
        {
            ofClear(0,0,0,0);
        }
        fbos[i].end();
        
        fbos[i].begin();
        {
            ofClear(0,0,0,0);
            
            ofSetColor(255);
            paths[i].lineTo(shapes[i].points[0].x, shapes[i].points[0].y);
            paths[i].lineTo(shapes[i].points[1].x, shapes[i].points[1].y);
            paths[i].lineTo(shapes[i].points[2].x, shapes[i].points[2].y);
            //paths[i].close();
            paths[i].draw();
            
        }
        fbos[i].end();
        
        imgs[imgIndex].getTexture().setAlphaMask(fbos[i].getTexture());
    }
    firstLoad = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // change background
    ofBackground(244,234,222);
    
    // change the textures
    loadImg( (int)(ofGetElapsedTimef()*5));
    
    // draw all the shapes
    for(int j = 0 ; j < count ; j++) {
        imgs[j].draw(0,0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
