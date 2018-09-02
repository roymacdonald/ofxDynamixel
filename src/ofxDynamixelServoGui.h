
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
			auto s = new ofxReadOnlySlider<T>(param, DXL_GUI_WIDTH, showName?16:5);
			s->setShowName(showName);
			group->add(s);
			
		}
		template<typename T>
		typename std::enable_if<std::is_arithmetic<T>::value, void >::type 
		addOfParam(ofParameter<T>& param, ofxGuiGroupMinimal* group, bool showName){
			auto s = new ofxReadOnlySlider<T>(param, DXL_GUI_WIDTH, showName?16:5);
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
				if(r->bReadOnly){
					addOfParam(r->R_value, &readParams,true);
				}else{
					auto g = new ofxGuiGroupMinimal();
					g->setup(r->name, "", 0, 0);
					if(std::is_arithmetic<T>::value){
						g->add(r->W_value);
					}else{
						addOfParam(r->W_value, g, true);
					}
					addOfParam(r->R_value, g, false);
					
					if(r->bEeprom){
						eepromParams.add(g);
					}else{
						ramParams.add(g);
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
