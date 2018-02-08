#include "ofApp.h"
#include <iostream>
#include <fstream>
#include <sstream>
//--------------------------------------------------------------
void ofApp::setup(){
    
    myfont.loadFont("Lovelo Black.otf", 25);
    mytitle.loadFont("Lovelo Black.otf", 70);
    lorem = "LOREM IPSUM";
    countPressed = 0;
    countKey = 0;
    files.push_back("panda.txt");
    files.push_back("el.txt");
    files.push_back("cat.txt");
    files.push_back("ani2.txt");
    files.push_back("sheep.txt");
    //ofPushMatrix();
    loadFile(files[countPressed]); // check loadFile function
    //ofPopMatrix();
    background_files.push_back("video1.mp4");
    background_files.push_back("video5.mp4");
    background_files.push_back("video3.mp4");
    background_files.push_back("video4.mp4");
    background_files.push_back("video5.mp4");
    
    background.load(background_files[countPressed]);
    ofPushMatrix();
    
    //ofEnableAlphaBlending();
    //ofSetColor(255, 255, 255, 100);
    //background.of
    background.play();
    
    ofPopMatrix();
}

void ofApp::loadBackground(string background_name){
    background.load(background_name);
    background.play();
}

void ofApp::loadFile(string fileName){
    
    // -----------------------------------------------------
    // load SVG points file
    // I have already convert them to txt file
    // their format is "x0,y0 x1,y1 x2,y2"
    
    // initial all the variables
    count = 0;
    countFrame = 0;
    change = 0;
    firstLoad = 0;  // if it is first time load image
   
    shapes.clear();
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
            // if encounter "," the string before ',' would be saved to variable number
            while (getline(ss,number, ','))
            {
                if(first == 0){
                    point.x = std::atof(number.c_str());
                    first = 1;
                }
                else {
                    point.y = std::atof(number.c_str());
                    first = 0;
                }
            }
            sCoord.points.push_back(point);
        }
        shapes.push_back(sCoord);
        count ++ ;
    }
    imgs.clear();
    loadImg(0); // check loadImg function
    // It is first time load image, so the variable is 0
}

void ofApp::loadImg(int num){
    
    // ---------------------------------------------------
    // initial the img array, fbos, path
    // fbos is an array used to create mask for images
    // imgs is an array used to put all the images
    // paths is an array used to draw path
    
    // paths and fbos should be cleared and reinitialed everytime I change texture
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
        
        // start to allocate a mask and draw polygon
        fbos[i].allocate(imgs[imgIndex].getWidth(), imgs[imgIndex].getHeight(),GL_RGBA);
        fbos[i].begin();
        {
            ofClear(0,0,0,0);
        }
        fbos[i].end();
        
        fbos[i].begin();
        {
            ofClear(0,0,0,0);
            //ofSetColor(255, 255, 255, 255);
            //ofSetColor(255);
            paths[i].lineTo(shapes[i].points[0].x, shapes[i].points[0].y);
            paths[i].lineTo(shapes[i].points[1].x, shapes[i].points[1].y);
            paths[i].lineTo(shapes[i].points[2].x, shapes[i].points[2].y);
            //paths[i].close();
            paths[i].draw();
            
        }
        fbos[i].end();
        
        imgs[imgIndex].getTexture().setAlphaMask(fbos[i].getTexture());
        // end to allocate a mask and draw polygon
    }
    firstLoad = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    background.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
   // change background
    ofBackground(244,234,222);

    background.draw(0,0);
    
    // change the textures
    int randomNum = ((int)(ofGetElapsedTimef()*5)% 60);
    loadImg(randomNum);
    
    // draw all the shapes
    for(int j = 0 ; j < count ; j++) {
        imgs[j].draw(0,0);
    
    }
    ofPushStyle();
    ofSetColor(0, 0, 0, 200);
    mytitle.drawString(lorem, ofGetWidth()/10,ofGetHeight()/9 * 7);
    myfont.drawString("Become you own collage artist.", ofGetWidth()/10,ofGetHeight()/9 * 8 - 20);
    //ofRotate(9, 0, 0, 1);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // do the screenshot
    if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
        lorem = lorem.substr(0, lorem.length()-1);
    }
    else if(key == OF_KEY_RETURN){
        countKey++;
        imgOut.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        string str1 = "output/screenshot" + std::to_string(countKey) + ".png";
        imgOut.save(str1);
    }
    else {
        ofAppendUTF8(lorem, key);
        mytitle.drawString(lorem, ofGetWidth()/10,ofGetHeight()/9 * 7);
    }
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
    lorem ="Lorem Ipsum";
    // click the canvas and then the SVG file would change;
    countPressed ++;
    if (countPressed == 5) countPressed = 0;
    loadFile(files[countPressed]);
    
    ofVideoPlayer Vid;
    backgrounds.push_back(Vid);
    
    loadBackground(background_files[countPressed]);
    
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
