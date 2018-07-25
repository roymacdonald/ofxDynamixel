//
//  ofxGuiGroupMinimal.hpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//

#pragma once

#include "ofxGuiGroup.h"


class ofxGuiGroupMinimal : public ofxGuiGroup{
public:
	ofxGuiGroupMinimal();
	
	ofxGuiGroup * setup(const ofParameterGroup & _parameters, const std::string& _filename, float x, float y) ;
	float getHeader(){return header;}
//	virtual bool mouseMoved(ofMouseEventArgs & args) override{return false;}
//	virtual bool mousePressed(ofMouseEventArgs & args) override{return false;}
//	virtual bool mouseDragged(ofMouseEventArgs & args) override{return false;}
//	virtual bool mouseReleased(ofMouseEventArgs & args) override{return false;}
//	virtual bool mouseScrolled(ofMouseEventArgs & args) override{return false;}

protected:
	virtual void generateDraw() override;
	virtual void render() override;
	
	
}; 
