
#include "ofxDynamixelServoGui.h"
#include "ofxDynamixelControlTables.h"
#include "ofxDynamixelConstants.h"
#include "ofxDynamixelServo.h"


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
		
		
		// agregar parametros desde servo->model;
		//*
		
		
		for(auto s: servo->model.table){
//			auto p8 =  dynamic_cast<Reg8*>(s.second);
			auto p8 =  dynamic_cast<Reg8*>(s);
			if(p8){
				addParam(p8);
//				panel.add(p8->value);
//				std::cout << p8->value.getName() << std::endl;
			}
			else{
//				auto p16 = dynamic_cast<Reg16*>(s.second);
				auto p16 = dynamic_cast<Reg16*>(s);
				if(p16){
					addParam(p16);
//					panel.add(p16->value);
//					std::cout << p16->value.getName() << std::endl;
				}
			}
		}
//*/		
		panel.add(&eepromParams);
		panel.add(&ramParams);
		panel.add(&readParams);
		
		
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
		//		R_modelNumber = this->getModelNumber();		
		//		R_firmwareVersion = this->getFirmwareVersion(); //uint8_t    
		//		P_baudRate.readOnlyParam = 	this->getBaudRate(); //uint8_t    
		//		P_returnDelayTime.readOnlyParam = 	this->getReturnDelayTime(); //uint8_t    
		//		P_cwAngleLimit.readOnlyParam = 	this->getCwAngleLimit(); //uint16_t   
		//		P_ccwAngleLimit.readOnlyParam = 	this->getCcwAngleLimit(); //uint16_t   
		//		P_controlMode.readOnlyParam = 	this->getControlMode(); //uint8_t    
		//		P_temperatureLimit.readOnlyParam = 	this->getTemperatureLimit(); //uint8_t    
		//		P_minVoltageLimit.readOnlyParam = 	this->getMinVoltageLimit(); //uint8_t    
		//		P_maxVoltageLimit.readOnlyParam = 	this->getMaxVoltageLimit(); //uint8_t    
		//		P_maxTorque.readOnlyParam = 	this->getMaxTorque(); //uint16_t   
		//		P_statusReturnLevel.readOnlyParam = 	this->getStatusReturnLevel(); //uint8_t    
		//		P_shutdown.readOnlyParam = 	this->getShutdown(); //uint8_t    
	}
	template<typename Model>
	void ServoGui<Model>::updateRAM(){
		
		//P_torqueEnabled.readOnlyParam = 	this->getTorqueEnabled();
		//P_ledStatus.readOnlyParam = 	this->getLedStatus();
		
		//P_goalPosition.readOnlyParam = 	this->getGoalPosition();
		//P_goalSpeed.readOnlyParam = 	this->getGoalSpeed();
		//P_torqueLimit.readOnlyParam = 	this->getTorqueLimit();
		//P_punch.readOnlyParam = 	this->getPunch();
		
		
		//		R_presentPosition = this->getPresentPosition();
		//		R_presentSpeed = this->getPresentSpeed();
		//		R_presentLoad = this->getPresentLoad();
		//		P_goalPosition.readOnlyParam = 	R_presentPosition.get();
		//		P_goalSpeed.readOnlyParam = 	R_presentSpeed.get();
		
		
		//R_presentVoltage = this->getPresentVoltage();
		//R_presentTemperature = this->getPresentTemperature();
		//R_registered = this->getRegistered();
		//		R_moving = this->getMoving();
		//		R_hardwareErrorStatus = this->getHardwareErrorStatus();
		
		
	}
	//-------------------------------------------------------------------------------------------------------------------		
	
	
	//	template class ServoGui<AX12>;
	template class ServoGui<XL320>;
	
	
	

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
