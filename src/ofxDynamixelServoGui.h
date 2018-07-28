
#pragma once

//#include "ofParameter.h"
#include "ofxGui.h"
//#include "ofxDynamixelRWParameter.h"
#include "ofxGuiGroupMinimal.h"
#include "ofxReadOnlySlider.h"
#include "ofxDynamixelConnection.h"
#include "ofxDynamixelControlTables.h"


namespace ofxDynamixel {
template<typename Model>
class Servo;


///--------------------------------------------------------------------------

template<typename Model>
class ServoGui{
public:
	ServoGui(){}
	ServoGui(std::shared_ptr<Servo<Model>> servo, std::shared_ptr<Connection> connection){
		setup(servo, connection);
	}
	
	void setup( std::shared_ptr<Servo<Model>> servo, std::shared_ptr<Connection> connection);
	
	ofxGuiGroup eepromParams, ramParams, readParams;
	
	ofxPanel panel;
	
	void update();
	void updateEeprom();
	void updateRAM();
	void updatePID();
	
	
	std::shared_ptr<Servo<Model>> getServo();
	
	
protected:
	template<typename T>
	void addParam(dxlParameter<T>* r){
		if(r){
			if(r->bReadOnly){
				auto s = new ofxReadOnlySlider<T>(r->R_value, 350, 16);
				s->showName();
				readParams.add(s);
			}else{
				auto g = new ofxGuiGroupMinimal();
				g->setup(r->name, "", 0, 0);
				
				if(std::is_arithmetic<T>::value){
					g->add(r->W_value);
					g->add(new ofxReadOnlySlider<T>(r->R_value, 350));
					if(r->bEeprom){
						eepromParams.add(g);
					}else{
						ramParams.add(g);
					}
				}else{
					std::cout << "cant add non arithmetic param" << std::endl; 
				}
			}
		}
	}

private:
	std::weak_ptr<Servo<Model>> servo;		
	ofEventListeners listeners;
		
	void setListeners();

};


}
