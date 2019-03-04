
#include "ofxDynamixelServoGui.h"
#include "ofxDynamixelControlTables.h"
#include "ofxDynamixelConstants.h"
#include "ofxDynamixelServo.h"
#include "ofxDynamixelServosModels.h"
#include <functional>

namespace ofxDynamixel{
	
	template<typename Model>
	void ServoGui<Model>::setup(std::shared_ptr<Servo<Model>> servo, std::shared_ptr<Connection> connection, float guiWidth, const std::vector<std::string>& guiGroups){

		this->servo = servo;
		
		panel.setup(servo->model.getModelName()+"_"+ofToString((int)servo->getId()), "settings.xml");
		panel.add(reboot.set("reboot"));
		listeners.push(reboot.newListener([&](){
			servo->reboot();
		}));
		
		panel.setSize(guiWidth, 200);
		panel.setWidthElements(guiWidth);
		panel.setDefaultWidth(guiWidth);
		
		auto enabled_group = [&](const std::string& group) -> bool  {  
			for(auto&g : guiGroups) {
				if(group == g) return true;
			}
			return false;
		};
		
		for(auto p: servo->model.table){
			baseDxlParameter * s = p.second;
			if(guiGroups.empty() || enabled_group(s->groupHierarchy)){
				if(s->getType() == typeid(bool).name()){
					addParam(dynamic_cast<RegBool* >(s));			
				}else if(s->getLength() == 1){
					addParam(dynamic_cast<Reg8* >(s));
				}else if(s->getLength() == 2){
					addParam(dynamic_cast<Reg16* >(s));
				}else if(s->getLength() == 4){
					addParam(dynamic_cast<Reg32*>(s));
				}
			}
		}
		
		findAndMinimizeGroup(&panel,"info" );
		findAndMinimizeGroup(&panel,"settings", true);
		findAndMinimizeGroup(&panel,"status");
		findAndMinimizeGroup(&panel,"dynamics", true);
		auto d = findGuiGroup(&panel, "dynamics");
		if(d){
			auto p = findGuiGroup(d, "position");
			if(p){
				p->maximize();
			}
		}
		
		panel.loadFromFile("settings.xml");
		
		setListeners();
	}
	
	template<typename Model>
	std::shared_ptr<Servo<Model > > ServoGui<Model>::getServo(){
		if(!servo.expired()){
			return servo.lock();
		}
		return nullptr;
	}
	
	
	//*
	//-------------------------------------------------------------------------------------------------------------------	
	template<typename Model>
	void ServoGui<Model>::setListeners(){
		//		listeners.unsubscribeAll();
		//	listeners.push(P_id_param.writeParam.newListener([this](uint8_t&){ this->setId( (uint8_t)P_id_param.writeParam.get() );}));
		
		//		listeners.push(P_dGain.writeParam.newListener([this](uint8_t&){this->updatePID();}));
		//		listeners.push(P_iGain.writeParam.newListener([this](uint8_t&){this->updatePID();}));
		//		listeners.push(P_pGain.writeParam.newListener([this](uint8_t&){this->updatePID();}));
				
	}
	
	template<typename Model>
	void ServoGui<Model>::update(){
#ifdef ENABLE_GUI_UPDATE
		updateRAM();
		
#endif
	}
	template<typename Model>
	void ServoGui<Model>::updatePID(){
		//	P_dGain.readOnlyParam = 	this->getDGain();
		//	P_iGain.readOnlyParam = 	this->getIGain();
		//	P_pGain.readOnlyParam = 	this->getPGain();
	}
	template<typename Model>
	void ServoGui<Model>::updateEeprom(){ 
		auto s = getServo();
		if(s){
			for( auto param: s->model.table){
				if(param.second->bEeprom){
					s->readDataTo(param.second);
				}
			}
		}
	}
	template<typename Model>
	void ServoGui<Model>::updateRAM(){
		auto s = getServo();
		if(s){
			for( auto param: s->model.table){
				if(!param.second->bEeprom){
					s->readDataTo(param.second);
				}
			}
		}
	}
	//-------------------------------------------------------------------------------------------------------------------		

	template class ServoGui<XL320>;
	template class ServoGui<XL430>;
}
