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


//#define SET_PARAM_R(param, group)\
//R_##param.setName(#param);\
//##group.add(R_##param);\

#define SET_PARAM_R(name, param, group)\
param.setName(#name);\
group.add(param);


	
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
	
		
	SET_PARAM_R("modelNumber"      , R_modelNumber              , eepromParams );
	SET_PARAM_R("firmwareVersion"  , R_firmwareVersion          , eepromParams);
	setParamRW(P_id_param          , Model::id()          , eepromParams);
	setParamRW(P_baudRate          , Model::baudRate()          , eepromParams);
	setParamRW(P_returnDelayTime   , Model::returnDelayTime()   , eepromParams);
	setParamRW(P_cwAngleLimit      , Model::cwAngleLimit()      , eepromParams);
	setParamRW(P_ccwAngleLimit     , Model::ccwAngleLimit()     , eepromParams);
	setParamRW(P_controlMode       , Model::controlMode()       , eepromParams);
	setParamRW(P_temperatureLimit  , Model::temperatureLimit()  , eepromParams);
	setParamRW(P_minVoltageLimit   , Model::minVoltageLimit()   , eepromParams);
	setParamRW(P_maxVoltageLimit   , Model::maxVoltageLimit()   , eepromParams);
	setParamRW(P_maxTorque         , Model::maxTorque()         , eepromParams);
	setParamRW(P_statusReturnLevel , Model::statusReturnLevel() , eepromParams);
	setParamRW(P_shutdown          , Model::shutdown()          , eepromParams);
	setParamRW(P_torqueEnabled     , Model::torqueEnabled()     , ramParams);
	setParamRW(P_ledStatus         , Model::led()         , ramParams);
	setParamRW(P_dGain             , Model::dGain()             , ramParams);
	setParamRW(P_iGain             , Model::iGain()             , ramParams);
	setParamRW(P_pGain             , Model::pGain()             , ramParams);
	setParamRW(P_goalPosition      , Model::goalPosition()      , ramParams);
	setParamRW(P_goalSpeed         , Model::goalSpeed()         , ramParams);
	setParamRW(P_torqueLimit       , Model::torqueLimit()       , ramParams);
	setParamRW(P_punch             , Model::punch()             , ramParams);	
	
	SET_PARAM_R("presentPosition"     , R_presentPosition     , readParams);
	SET_PARAM_R("presentSpeed"        , R_presentSpeed        , readParams);
	SET_PARAM_R("presentLoad"         , R_presentLoad         , readParams);
	SET_PARAM_R("presentVoltage"      , R_presentVoltage      , readParams);
	SET_PARAM_R("presentTemperature"  , R_presentTemperature  , readParams);
	SET_PARAM_R("registered"          , R_registered          , readParams);
	SET_PARAM_R("moving"              , R_moving              , readParams);
	SET_PARAM_R("hardwareErrorStatus" , R_hardwareErrorStatus , readParams);

	
	panel.add(&eepromParams);
	panel.add(&ramParams);
	panel.add(&readParams);


//	printGuiGroup(&panel);
	panel.loadFromFile("settings.xml");
	
	setListeners();
}
	
//-------------------------------------------------------------------------------------------------------------------	
	template<typename Model>
	void ServoGui<Model>::setListeners(){
		listeners.unsubscribeAll();
		listeners.push(P_id_param.writeParam.newListener([this](uint8_t&){ this->setId( (uint8_t)P_id_param.writeParam.get() );}));
	}
	template<typename Model>
	void ServoGui<Model>::update(){
#ifdef ENABLE_GUI_UPDATE
		auto c = this->getConnection();
		if(c){
			c->clearBulkRead();
			c->addBulkReadParam(this->id , Model::MODEL_NUMBER()          , 2);
			c->addBulkReadParam(this->id , Model::FIRMWARE_VERSION()      , 1);
			c->addBulkReadParam(this->id , Model::ID()                    , 1);
			c->addBulkReadParam(this->id , Model::BAUD_RATE()             , 1);
			c->addBulkReadParam(this->id , Model::RETURN_DELAY_TIME()     , 1);
			c->addBulkReadParam(this->id , Model::CW_ANGLE_LIMIT()        , 2);
			c->addBulkReadParam(this->id , Model::CCW_ANGLE_LIMIT()       , 2);
			
			c->addBulkReadParam(this->id, Model::CONTROL_MODE(), 1);
			c->addBulkReadParam(this->id, Model::TEMPERATURE_LIMIT(), 1);
			c->addBulkReadParam(this->id, Model::MIN_VOLTAGE_LIMIT(), 1);
			c->addBulkReadParam(this->id, Model::MAX_VOLTAGE_LIMIT(), 1);
			c->addBulkReadParam(this->id, Model::MAX_TORQUE(), 2);
			c->addBulkReadParam(this->id, Model::STATUS_RETURN_LEVEL(), 1);
			c->addBulkReadParam(this->id, Model::SHUTDOWN(), 1);
			c->addBulkReadParam(this->id, Model::TORQUE_ENABLE(), 1);
			c->addBulkReadParam(this->id, Model::LED(), 1);
			c->addBulkReadParam(this->id, Model::D_GAIN(), 1);
			c->addBulkReadParam(this->id, Model::I_GAIN(), 1);
			c->addBulkReadParam(this->id, Model::P_GAIN(), 1);
			c->addBulkReadParam(this->id, Model::GOAL_POSITION(), 2);
			c->addBulkReadParam(this->id, Model::MOVING_SPEED(), 2);
			c->addBulkReadParam(this->id, Model::TORQUE_LIMIT(), 2);
			c->addBulkReadParam(this->id, Model::PUNCH(), 2);
			c->addBulkReadParam(this->id, Model::PRESENT_POSITION(), 2);
			c->addBulkReadParam(this->id, Model::PRESENT_SPEED(), 2);
			c->addBulkReadParam(this->id, Model::PRESENT_LOAD(), 2);
			c->addBulkReadParam(this->id, Model::PRESENT_VOLTAGE(), 1);
			c->addBulkReadParam(this->id, Model::PRESENT_TEMPERATURE(), 1);
			c->addBulkReadParam(this->id, Model::REGISTERED(), 1);
			c->addBulkReadParam(this->id, Model::MOVING(), 1);
			c->addBulkReadParam(this->id, Model::HARDWARE_ERROR_STATUS(), 1);

			c->bulkReadRequest();// esto debiera estar en otro thread!
			
//			uint8_t  data1
			uint16_t data;
			
			
			if(c->getBulkReadData(this->id , Model::MODEL_NUMBER()          , 2 , data)){  R_modelNumber = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::FIRMWARE_VERSION()      , 1 , data)){  R_firmwareVersion = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::BAUD_RATE()             , 1 , data)){  G_baudRate.setName("baudRate: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::RETURN_DELAY_TIME()     , 1 , data)){  G_returnDelayTime.setName("returnDelayTime: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::CW_ANGLE_LIMIT()        , 2 , data)){  G_cwAngleLimit.setName("cwAngleLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::CCW_ANGLE_LIMIT()       , 2 , data)){  G_ccwAngleLimit.setName("ccwAngleLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::CONTROL_MODE()          , 1 , data)){  G_controlMode.setName("controlMode: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::TEMPERATURE_LIMIT()     , 1 , data)){  G_temperatureLimit.setName("temperatureLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::MIN_VOLTAGE_LIMIT()     , 1 , data)){  G_minVoltageLimit.setName("minVoltageLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::MAX_VOLTAGE_LIMIT()     , 1 , data)){  G_maxVoltageLimit.setName("maxVoltageLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::MAX_TORQUE()            , 2 , data)){  G_maxTorque.setName("maxTorque: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::STATUS_RETURN_LEVEL()   , 1 , data)){  G_statusReturnLevel.setName("statusReturnLevel: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::SHUTDOWN()              , 1 , data)){  G_shutdown.setName("shutdown: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::TORQUE_ENABLE()         , 1 , data)){  G_torqueEnabled.setName("torqueEnabled: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::LED()                   , 1 , data)){  G_ledStatus.setName("ledStatus: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::D_GAIN()                , 1 , data)){  G_dGain.setName("dGain: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::I_GAIN()                , 1 , data)){  G_iGain.setName("iGain: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::P_GAIN()                , 1 , data)){  G_pGain.setName("pGain: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::GOAL_POSITION()         , 2 , data)){  G_goalPosition.setName("goalPosition: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::MOVING_SPEED()          , 2 , data)){  G_goalSpeed.setName("goalSpeed: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::TORQUE_LIMIT()          , 2 , data)){  G_torqueLimit.setName("torqueLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::PUNCH()                 , 2 , data)){  G_punch.setName("punch: "+  ofToString(data));}		
			if(c->getBulkReadData(this->id , Model::PRESENT_POSITION()      , 2 , data)){  R_presentPosition = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::PRESENT_SPEED()         , 2 , data)){  R_presentSpeed = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::PRESENT_LOAD()          , 2 , data)){  R_presentLoad = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::PRESENT_VOLTAGE()       , 1 , data)){  R_presentVoltage = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::PRESENT_TEMPERATURE()   , 1 , data)){  R_presentTemperature = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::REGISTERED()            , 1 , data)){  R_registered = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::MOVING()                , 1 , data)){  R_moving = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::HARDWARE_ERROR_STATUS() , 1 , data)){  R_hardwareErrorStatus = ofToString(data);}
#endif
		}
//-------------------------------------------------------------------------------------------------------------------		
	
	template class ServoGui<AX12>;
	template class ServoGui<XL320>;
}
