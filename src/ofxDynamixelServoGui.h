
#pragma once

//#include "ofParameter.h"
#include "ofxGui.h"
//#include "ofxDynamixelRWParameter.h"
#include "ofxGuiGroupMinimal.h"
#include "ofxReadOnlySlider.h"
#include "ofxDynamixelConnection.h"
#include "ofxDynamixelControlTables.h"

#include "ofxGuiDXLToggle.h"
#include "ofxGuiUtils.h"

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
		
//		ofxGuiGroup eepromParams, ramParams, readParams;
		
		ofxPanel panel;
		
		void update();
		void updateEeprom();
		void updateRAM();
		void updatePID();
		
		
		std::shared_ptr<Servo<Model>> getServo();
		ofParameter<void> reboot;
		
	protected:
		
		template<typename T>
		typename std::enable_if< !(std::is_same<T, bool>::value), void >::type 
		addOfParam(ofParameter<T>& param, ofxGuiGroup* group, bool showName, bool bIsReadOnly = true){
			if(group){
			auto s = new ofxReadOnlySlider<T>(param, group->getWidth() - 3, showName?16:5);
			s->setShowName(showName);
			group->add(s);
			}
		}
		template<typename T>
		typename std::enable_if<!(std::is_same<T, bool>::value), void >::type 
		addOfParam(ofParameter<T>& param, ofxGuiGroupMinimal* group, bool showName, bool bIsReadOnly = true){
			if(group){
			auto s = new ofxReadOnlySlider<T>(param, group->getWidth() - 3, showName?16:5);
			s->setShowName(showName);
			group->add(s);
			}
			
		}
		void addOfParam(ofParameter<bool>& param, ofxGuiGroup* group, bool bShowName, bool bIsReadOnly){
			if(group){
				group->add(new ofxGuiDXLToggle(param, bShowName, bIsReadOnly, group->getWidth() - 3, (bIsReadOnly && !bShowName)?5:16));
			}
		}
		
		void addOfParam(ofParameter<bool>& param, ofxGuiGroupMinimal* group, bool bShowName, bool bIsReadOnly){
			if(group){
				group->add(new ofxGuiDXLToggle(param, bShowName, bIsReadOnly , group->getWidth() - 3, (bIsReadOnly && !bShowName)?5:16 ));
			}
		}
		
		template<typename T>
		void addParam(dxlParameter<T>* r){
			if(r){
				if(r->bReadOnly){
					addOfParam(r->R_value, getOrCreateGuiGroupHierarchy(&panel, r->groupHierarchy), true, true);
				}else{
//					panel.add(r->W_value);
//					panel.add(r->R_value);
					//*
					auto g = new ofxGuiGroupMinimal();
					g->setup(r->name, "", 0, 0);
					if(!(std::is_same<T, bool>::value)){
						g->add(r->W_value);
						addOfParam(r->R_value, g, false, true);
					}else{
						
						addOfParam(r->W_value, g, true, false);
						addOfParam(r->R_value, g, false, true);
					}
					
					getOrCreateGuiGroupHierarchy(&panel, r->groupHierarchy)->add(g);
					//*/
//					if(r->bEeprom){
//						eepromParams.add(g);
//					}else{
//						ramParams.add(g);
//					}
				}
			}
		}
		
		
			
		
		
	private:
		std::weak_ptr<Servo<Model>> servo;		
		ofEventListeners listeners;
		
		void setListeners();
		
	};
	
	
}
