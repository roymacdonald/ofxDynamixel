
#include "ofxDynamixelServoGui.h"
#include "ofxDynamixelControlTables.h"
#include "ofxDynamixelConstants.h"
#include "ofxDynamixelServo.h"
#include "ofxDynamixelServosModels.h"

namespace ofxDynamixel{
	
	template<typename Model>
	void ServoGui<Model>::setup(std::shared_ptr<Servo<Model>> servo, std::shared_ptr<Connection> connection, float guiWidth){
//		std::cout << __PRETTY_FUNCTION__ << std::endl;
		this->servo = servo;
		//	parameters.setName("ServoGuiParams");
//		eepromParams.setup("EEPROM Params");
//		ramParams.setup("RAM Params");
//		readParams.setup("Read Params");
		
		panel.setup(servo->model.getModelName()+"_"+ofToString((int)servo->getId()), "settings.xml");
		panel.add(reboot.set("reboot"));
		
		listeners.push(reboot.newListener([&](){
			servo->reboot();
		}));
		
		panel.setSize(guiWidth, 200);
		panel.setWidthElements(guiWidth);
		panel.setDefaultWidth(guiWidth);
		// agregar parametros desde servo->model;
		//*
		
		
		for(auto p: servo->model.table){
//			auto p8 =  dynamic_cast<Reg8*>(s.second);
			baseDxlParameter * s = p.second; 
			if(s->getType() == typeid(bool).name()){
//				std::cout << "add boolean" << std::endl;
				addParam(dynamic_cast<RegBool* >(s));			
			}else if(s->getLength() == 1){
				addParam(dynamic_cast<Reg8* >(s));
			}else if(s->getLength() == 2){
				addParam(dynamic_cast<Reg16* >(s));
			}else if(s->getLength() == 4){
				addParam(dynamic_cast<Reg32*>(s));
			}
		}
//*/		
//		panel.add(&eepromParams);
//		panel.add(&ramParams);
//		panel.add(&readParams);
		
//		panel.setSize(350, 200);
		
//		eepromParams.minimize();
		//	printGuiGroup(&panel);
		
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
//		std::cout << __PRETTY_FUNCTION__ << std::endl; 
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
//		std::cout << __PRETTY_FUNCTION__ << std::endl;
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
	
	
	//	template class ServoGui<AX12>;
	template class ServoGui<XL320>;
	template class ServoGui<XL430>;
	
	

}
//-------------------------------------------------------------------------------------------------------------------
//void printGuiGroup(ofxGuiGroup * group, std::string prefix = ""){
//	std::cout << prefix << group->getName() << std::endl;
//	for(int i = 0; i < group->getNumControls(); i++){
//		auto control = group->getControl(i);
//		if(control != nullptr){
//			ofxGuiGroup * subgroup = dynamic_cast <ofxGuiGroup *>(control);
//			if(subgroup != nullptr){
//				printGuiGroup(subgroup, prefix + "----");
//			}else{
//				std::cout << prefix + "----"<< control->getName() << std::endl;
//			}
//		}
//	}
//}
//
