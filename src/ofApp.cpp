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
    firstLoad = 0;  // if first load image
    
    ifstream infile;
    infile.open (ofToDataPath("ani.txt").c_str());
    if(!infile) {cout << "Error: File not found or corrupt. "<< endl;}
    string coordStr[3];
    while(infile >> coordStr[0] && infile >>  coordStr[1] && infile >>  coordStr[2])
    {
        //cout << coordStr[0] << " " << coordStr[1] << " " << coordStr[2] << endl;
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
    cout << "count" << count << '\n';
    //count ++ ;
  
    loadImg(0);
    //min move
    /*
     for(int i = 0; i < count; i++) {
         double minX, minY;
         minX = shapes[i].points[0].x;
         minY = shapes[i].points[0].y;
         for(int j = 0; j < 3; j++) {
         if (shapes[i].points[j].x<= minX){
         minX = shapes[i].points[j].x;
         }
         if (shapes[i].points[j].y<= minY){
         minY = shapes[i].points[j].y;
         }
         }
         shapes[i].moveCoordX = minX;
         shapes[i].moveCoordY = minY;
     }
    */
}

void ofApp::loadImg(int num){
    
    // initial the img array, fbos, path
    
    //imgs.clear();
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

        if(firstLoad == 0){
            string loadStr = std::to_string((i + num) % 15) + ".jpg";
            imgs[i].load(loadStr);
        //cout<< "loadstr: " << loadStr <<'\n';
        }
        
    
        int imgIndex = (i + num) % count;
        
        fbos[i].allocate(imgs[imgIndex].getWidth(), imgs[imgIndex].getHeight(),GL_RGBA);
        
        fbos[i].begin();
        {
            ofClear(0,0,0,0);
            //ofBackground(255,255,255);
        }
        fbos[i].end();
        
        fbos[i].begin();
        {
            ofClear(0,0,0,0);
            //ofBackground(255,255,255);
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
    //now we add lines to our path
    ofBackground(244,234,222);
    
    loadImg( (int)(ofGetElapsedTimef()*5));
    
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
