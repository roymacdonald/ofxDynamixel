
#include "ofxDynamixelServoGui.h"
#include "ofxDynamixelControlTables.h"
#include "ofxDynamixelConstants.h"
#include "ofxDynamixelServo.h"
#include "ofxDynamixelServosModels.h"

namespace ofxDynamixel{
	
	template<typename Model>
	void ServoGui<Model>::setup(std::shared_ptr<Servo<Model>> servo, std::shared_ptr<Connection> connection){
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
		this->servo = servo;
		//	parameters.setName("ServoGuiParams");
		eepromParams.setup("EEPROM Params");
		ramParams.setup("RAM Params");
		readParams.setup("Read Params");
		
		panel.setup(servo->model.getModelName()+"_"+ofToString((int)servo->getId()), "settings.xml");
		panel.setSize(350, 200);
		panel.setWidthElements(350);
		panel.setDefaultWidth(350);
		// agregar parametros desde servo->model;
		//*
		
		
		for(auto s: servo->model.table){
//			auto p8 =  dynamic_cast<Reg8*>(s.second);
		
			if(s->length == 1){
				addParam(dynamic_cast<Reg8* >(s));
			}else if(s->length == 2){
				addParam(dynamic_cast<Reg16* >(s));
			}else if(s->length == 4){
				addParam(dynamic_cast<Reg32*>(s));
			}
		}
//*/		
		panel.add(&eepromParams);
		panel.add(&ramParams);
		panel.add(&readParams);
		
//		panel.setSize(350, 200);
		panel.setWidthElements(350);
		eepromParams.minimize();
		//	printGuiGroup(&panel);
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
				if(param->bEeprom){
					s->readDataTo(param);
				}
			}
		}
	}
	template<typename Model>
	void ServoGui<Model>::updateRAM(){
		
		auto s = getServo();
		if(s){
			for( auto param: s->model.table){
				if(!param->bEeprom){
					s->readDataTo(param);
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
