#include "ofApp.h"
#include <iostream>
#include <fstream>
#include <sstream>
//--------------------------------------------------------------
void ofApp::setup(){
    //first load our image

    
    //img.load(".jpg");
    count = 0;
    countFrame = 0;
    change = 0;
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
     }*/
    
    // load pictures
    //fbo.allocate(img.getWidth(), img.getHeight(), );

    
//    fbo2.allocate(img2.getWidth(), img2.getHeight(),GL_RGBA);
//    fbo2.begin();
//    {
//        ofClear(0,0,0,0);
//    }
//    fbo2.end();
//
//    fbo2.begin();
//    {
//        ofClear(0,0,0,0);
//        //ofBackground(255,255,255);
//        ofSetColor(255);
//        path2.lineTo(100, 100);
//        path2.lineTo(300, 400);
//        path2.lineTo(500, 600);
//        path2.draw();
//    }
//    fbo2.end();
//
//
//    img2.getTexture().setAlphaMask(fbo2.getTexture());

}

void ofApp::loadImg(int num){
    
    // initial the img array, fbos, path
    imgs.clear();
    paths.clear();
    fbos.clear();
    for(int i = 0; i < count; i++) {
        ofImage imgUnit;
        ofFbo fboUnit;
        ofPath pathUnit;
        imgs.push_back(imgUnit);
        fbos.push_back(fboUnit);
        paths.push_back(pathUnit);
    }
    for(int i = 0; i < count; i++){
        
        string loadStr = std::to_string((i + num) % 15) + ".jpg";
        imgs[i].load(loadStr);
        //cout<< "loadstr: " << loadStr <<'\n';
        
        fbos[i].allocate(imgs[i].getWidth(), imgs[i].getHeight(),GL_RGBA);
        
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
        
        //ofTranslate(shapes[i].moveCoordX, shapes[i].moveCoordY);
        imgs[i].getTexture().setAlphaMask(fbos[i].getTexture());
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //now we add lines to our path
    ofBackground(244,234,222);
    
    
    loadImg(countFrame);
    for(int j = 0 ; j < count ; j++) {
        //ofPushMatrix();
        //ofTranslate(shapes[j].moveCoordX, shapes[j].moveCoordY);
        
        imgs[j].draw(0,0);
        //cout<< "!!!!!:" << shapes[j].moveCoordX<< '\n';
        //
    }
    countFrame++;
    //img2.draw(80,60);

//    ofFill();
//    ofSetHexColor(0xe0be21);
//
//    //------(a)--------------------------------------
//    //
//    //         draw a star
//    //
//    //         use poly winding odd, the default rule
//    //
//    //         info about the winding rules is here:
//    //        http://glprogramming.com/red/images/Image128.gif
//    //
//    ofSetPolyMode(OF_POLY_WINDING_ODD);    // this is the normal mode
//    ofBeginShape();
//    ofVertex(200,135);
//    ofVertex(15,135);
//    ofVertex(165,25);
//    ofVertex(105,200);
//    ofVertex(50,25);
//    ofEndShape();

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
