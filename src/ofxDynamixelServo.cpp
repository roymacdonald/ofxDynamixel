#include "ofxDynamixelServo.h"
#include "ofxDynamixelControlTables.h"
#include "ofxDynamixelConstants.h"
#include "ofxGuiGroup.h"


namespace ofxDynamixel{


//#define setParamRW(param, group, C, M, X)\
//G_##param.setName(#param);\
//G_##param.add(W_##param.set("W", C, M, X ));\
//grp_##group.add(new ofxGuiRW_<Model>(P_##param));

//R_##param.setName("R");\
//G_##param.add(R_##param);\
//G_##param.add(R_##param.set("R", C,  M, X ));\


	
#define	setParamRW8(param, ref, group, listenerFunc) \
param.set(ref); \
listeners.push(param.writeParam.newListener([this](uint8_t& p){this->listenerFunc(p);})); \
group.add(new ofxGuiRW_<uint8_t>(param));

#define	setParamRW16(param, ref, group, listenerFunc) \
param.set(ref); \
listeners.push(param.writeParam.newListener([this](uint16_t& p){this->listenerFunc(p);})); \
group.add(new ofxGuiRW_<uint16_t>(param));

	
	
//template<typename Model>
//void ServoGui<Model>::setup(){

//-------------------------------------------------------------------------------------------------------------------
void printGuiGroup(ofxGuiGroup * group, std::string prefix = ""){
	std::cout << prefix << group->getName() << std::endl;
	for(int i = 0; i < group->getNumControls(); i++){
		auto control = group->getControl(i);
		if(control != nullptr){
			ofxGuiGroup * subgroup = dynamic_cast <ofxGuiGroup *>(control);
			if(subgroup != nullptr){
				printGuiGroup(subgroup, prefix + "----");
			}else{
				std::cout << prefix + "----"<< control->getName() << std::endl;
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------------------------
template<typename Model>
void ServoGui<Model>::setup(int id,  std::shared_ptr<Connection> connection){
	BaseServo<Model>::setup(id, connection);
//	parameters.setName("ServoGuiParams");
	eepromParams.setup("EEPROM Params");
	ramParams.setup("RAM Params");
	readParams.setup("Read Params");
	
	panel.setup(Model::getModelName()+"_"+ofToString(id), "settings.xml");
	
		
	setParamR("modelNumber"      , R_modelNumber              , eepromParams );
	setParamR("firmwareVersion"  , R_firmwareVersion          , eepromParams);
//	setParamRW8(P_id_param          , Model::id()                , eepromParams, setId);
	setParamRW8(P_baudRate          , Model::baudRate()          , eepromParams, setBaudRate);
	setParamRW16(P_cwAngleLimit      , Model::cwAngleLimit()     , eepromParams, setCwAngleLimit);
	setParamRW8(P_returnDelayTime   , Model::returnDelayTime()   , eepromParams, setReturnDelayTime);
	setParamRW16(P_ccwAngleLimit     , Model::ccwAngleLimit()    , eepromParams, setCcwAngleLimit);
	setParamRW8(P_controlMode       , Model::controlMode()       , eepromParams, setControlMode);
	setParamRW8(P_temperatureLimit  , Model::temperatureLimit()  , eepromParams, setTemperatureLimit);
	setParamRW8(P_minVoltageLimit   , Model::minVoltageLimit()   , eepromParams, setMinVoltageLimit);
	setParamRW8(P_maxVoltageLimit   , Model::maxVoltageLimit()   , eepromParams, setMaxVoltageLimit);
	setParamRW16(P_maxTorque         , Model::maxTorque()        , eepromParams, setMaxTorque);
	setParamRW8(P_statusReturnLevel , Model::statusReturnLevel() , eepromParams, setStatusReturnLevel);
	setParamRW8(P_shutdown          , Model::shutdown()          , eepromParams, setShutdown);
	setParamRW8(P_torqueEnabled     , Model::torqueEnabled()     , ramParams   , setTorqueEnabled);
	setParamRW8(P_ledStatus         , Model::led()               , ramParams   , setLedStatus);
	setParamRW8(P_dGain             , Model::dGain()             , ramParams   , setDGain);
	setParamRW8(P_iGain             , Model::iGain()             , ramParams   , setIGain);
	setParamRW8(P_pGain             , Model::pGain()             , ramParams   , setPGain);
	setParamRW16(P_goalPosition     , Model::goalPosition()      , ramParams   , setGoalPosition);
	setParamRW16(P_goalSpeed        , Model::goalSpeed()         , ramParams   , setGoalSpeed);
	setParamRW16(P_torqueLimit      , Model::torqueLimit()       , ramParams   , setTorqueLimit);
	setParamRW16(P_punch            , Model::punch()             , ramParams   , setPunch);	
//	
	setParamR("presentPosition"     , R_presentPosition     , readParams);
	setParamR("presentSpeed"        , R_presentSpeed        , readParams);
	setParamR("presentLoad"         , R_presentLoad         , readParams);
	setParamR("presentVoltage"      , R_presentVoltage      , readParams);
	setParamR("presentTemperature"  , R_presentTemperature  , readParams);
	setParamR("registered"          , R_registered          , readParams);
	setParamR("moving"              , R_moving              , readParams);
	setParamR("hardwareErrorStatus" , R_hardwareErrorStatus , readParams);

	
	panel.add(&eepromParams);
	panel.add(&ramParams);
	panel.add(&readParams);


	eepromParams.minimize();
//	printGuiGroup(&panel);
	panel.loadFromFile("settings.xml");
	
	setListeners();
}
	
//-------------------------------------------------------------------------------------------------------------------	
	template<typename Model>
	void ServoGui<Model>::setListeners(){
//		listeners.unsubscribeAll();
	//	listeners.push(P_id_param.writeParam.newListener([this](uint8_t&){ this->setId( (uint8_t)P_id_param.writeParam.get() );}));
		
		listeners.push(P_dGain.writeParam.newListener([this](uint8_t&){this->updatePID();}));
		listeners.push(P_iGain.writeParam.newListener([this](uint8_t&){this->updatePID();}));
		listeners.push(P_pGain.writeParam.newListener([this](uint8_t&){this->updatePID();}));
	}
	
	template<typename Model>
	void ServoGui<Model>::update(){
#ifdef ENABLE_GUI_UPDATE
		updateRAM();
				
	#endif
	}
	template<typename Model>
	void ServoGui<Model>::updatePID(){
		P_dGain.readOnlyParam = 	this->getDGain();
		P_iGain.readOnlyParam = 	this->getIGain();
		P_pGain.readOnlyParam = 	this->getPGain();
	}
	template<typename Model>
	void ServoGui<Model>::updateEeprom(){
		R_modelNumber = this->getModelNumber();		
		R_firmwareVersion = this->getFirmwareVersion(); //uint8_t    
		P_baudRate.readOnlyParam = 	this->getBaudRate(); //uint8_t    
		P_returnDelayTime.readOnlyParam = 	this->getReturnDelayTime(); //uint8_t    
		P_cwAngleLimit.readOnlyParam = 	this->getCwAngleLimit(); //uint16_t   
		P_ccwAngleLimit.readOnlyParam = 	this->getCcwAngleLimit(); //uint16_t   
		P_controlMode.readOnlyParam = 	this->getControlMode(); //uint8_t    
		P_temperatureLimit.readOnlyParam = 	this->getTemperatureLimit(); //uint8_t    
		P_minVoltageLimit.readOnlyParam = 	this->getMinVoltageLimit(); //uint8_t    
		P_maxVoltageLimit.readOnlyParam = 	this->getMaxVoltageLimit(); //uint8_t    
		P_maxTorque.readOnlyParam = 	this->getMaxTorque(); //uint16_t   
		P_statusReturnLevel.readOnlyParam = 	this->getStatusReturnLevel(); //uint8_t    
		P_shutdown.readOnlyParam = 	this->getShutdown(); //uint8_t    
	}
	template<typename Model>
	void ServoGui<Model>::updateRAM(){
		
		//P_torqueEnabled.readOnlyParam = 	this->getTorqueEnabled();
		//P_ledStatus.readOnlyParam = 	this->getLedStatus();
		
		//P_goalPosition.readOnlyParam = 	this->getGoalPosition();
		//P_goalSpeed.readOnlyParam = 	this->getGoalSpeed();
		//P_torqueLimit.readOnlyParam = 	this->getTorqueLimit();
		//P_punch.readOnlyParam = 	this->getPunch();
		R_presentPosition = this->getPresentPosition();
		R_presentSpeed = this->getPresentSpeed();
		R_presentLoad = this->getPresentLoad();
		P_goalPosition.readOnlyParam = 	R_presentPosition.get();
		P_goalSpeed.readOnlyParam = 	R_presentSpeed.get();
		
		
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
