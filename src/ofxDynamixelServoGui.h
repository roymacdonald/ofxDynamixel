
#pragma once

//#include "ofParameter.h"
#include "ofxGui.h"
//#include "ofxDynamixelRWParameter.h"
#include "ofxGuiGroupMinimal.h"
#include "ofxReadOnlySlider.h"
#include "ofxDynamixelConnection.h"
#include "ofxDynamixelControlTables.h"

#include "ofxGuiDXLToggle.h"


namespace ofxDynamixel {
template<typename Model>
class Servo;

#define DXL_GUI_WIDTH 350
	
	
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
	typename std::enable_if<std::is_arithmetic<T>::value, void >::type 
	addOfParam(ofParameter<T>& param, ofxGuiGroup* group, bool showName){
		auto s = new ofxReadOnlySlider<T>(param, DXL_GUI_WIDTH, 16);
		s->setShowName(showName);
		group->add(s);
		
	}
	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, void >::type 
	addOfParam(ofParameter<T>& param, ofxGuiGroupMinimal* group, bool showName){
		auto s = new ofxReadOnlySlider<T>(param, DXL_GUI_WIDTH, 16);
		s->setShowName(showName);
		group->add(s);
		
	}
	void addOfParam(ofParameter<bool>& param, ofxGuiGroup* group, bool showName){
		group->add(new ofxGuiDXLToggle(param, DXL_GUI_WIDTH));
	}
	
	void addOfParam(ofParameter<bool>& param, ofxGuiGroupMinimal* group, bool showName){
		group->add(new ofxGuiDXLToggle(param, DXL_GUI_WIDTH));
	}
	
	template<typename T>
	void addParam(dxlParameter<T>* r){
		if(r){
			
//			std::cout << r->getType() << std::endl;
//			
//			std::cout << typeid(dxlParameter<bool>).name() << std::endl;
//			
			if(r->bReadOnly){
				
//				auto b = dynamic_cast<ofParameter<bool>* >(&r->R_value);
				addOfParam(r->R_value, &readParams,true);
//				if(r->getType() == "b"){
////					std::cout << "bool R" << std::endl;
//					auto R = dynamic_cast<ofParameter<bool>*>(&r->R_value);
//					if(R) readParams.add(new ofxGuiDXLToggle(*R, DXL_GUI_WIDTH));
////					g->add(new ofxGuiDXLToggle(*dynamic_cast<ofParameter<bool>* >(&r->R_value), DXL_GUI_WIDTH));						
//				}else if(std::is_arithmetic<T>::value){
////					std::cout << "non bool R" << std::endl;
////					g->add(r->W_value);
//					auto s = new ofxReadOnlySlider<T>(r->R_value, DXL_GUI_WIDTH, 16);
//					s->showName();
//					readParams.add(s);
//				}
			}else{
				auto g = new ofxGuiGroupMinimal();
				g->setup(r->name, "", 0, 0);
				
//					if(r->W_value.getMin()==0 && r->W_value.getMax()==1){
//					auto b = dynamic_cast<ofParameter<bool>*>(&r->W_value);
//					if(r->getType() == "b"){
////					if(r->getType() == typeid(bool).name()){
////						std::cout << "bool RW" << std::endl;
////						auto R = dynamic_cast<ofParameter<bool>*>(&r->R_value);
////						auto W = dynamic_cast<ofParameter<bool>*>(&r->W_value);
//						if(W)g->add(new ofxGuiDXLToggle(*W, DXL_GUI_WIDTH));
//						if(R)g->add(new ofxGuiDXLToggle(*R, DXL_GUI_WIDTH));						
//					}else 
					if(std::is_arithmetic<T>::value){
//						std::cout << "non bool RW" << std::endl;
						g->add(r->W_value);
//						addOfParam(r->R_value, *g, false);
//						g->add(new ofxReadOnlySlider<T>(r->R_value, DXL_GUI_WIDTH));
					}else{
						addOfParam(r->W_value, g, true);
					}
					addOfParam(r->R_value, g, false);
					
					if(r->bEeprom){
						eepromParams.add(g);
					}else{
						ramParams.add(g);
					}
//				}else{
//					std::cout << "cant add non arithmetic param" << std::endl; 
//				}
			}
		}
	}




private:
	std::weak_ptr<Servo<Model>> servo;		
	ofEventListeners listeners;
		
	void setListeners();

};


}
