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
			c->addBulkReadParam(this->id , Model::modelNumber().address         , 2);
			c->addBulkReadParam(this->id , Model::firmwareVersion().address     , 1);
			c->addBulkReadParam(this->id , Model::id().address                  , 1);
			c->addBulkReadParam(this->id , Model::baudRate().address            , 1);
			c->addBulkReadParam(this->id , Model::returnDelayTime().address     , 1);
			c->addBulkReadParam(this->id , Model::cwAngleLimit().address        , 2);
			c->addBulkReadParam(this->id , Model::ccwAngleLimit().address       , 2);
			c->addBulkReadParam(this->id , Model::controlMode().address         , 1);
			c->addBulkReadParam(this->id , Model::temperatureLimit().address    , 1);
			c->addBulkReadParam(this->id , Model::minVoltageLimit().address     , 1);
			c->addBulkReadParam(this->id , Model::maxVoltageLimit().address     , 1);
			c->addBulkReadParam(this->id , Model::maxTorque().address           , 2);
			c->addBulkReadParam(this->id , Model::statusReturnLevel().address   , 1);
			c->addBulkReadParam(this->id , Model::shutdown().address            , 1);
			c->addBulkReadParam(this->id , Model::torqueEnabled().address        , 1);
			c->addBulkReadParam(this->id , Model::led().address                 , 1);
			c->addBulkReadParam(this->id , Model::dGain().address               , 1);
			c->addBulkReadParam(this->id , Model::iGain().address               , 1);
			c->addBulkReadParam(this->id , Model::pGain().address               , 1);
			c->addBulkReadParam(this->id , Model::goalPosition().address        , 2);
			c->addBulkReadParam(this->id , Model::goalSpeed().address         , 2);
			c->addBulkReadParam(this->id , Model::torqueLimit().address         , 2);
			c->addBulkReadParam(this->id , Model::punch().address               , 2);
			c->addBulkReadParam(this->id , Model::presentPosition().address     , 2);
			c->addBulkReadParam(this->id , Model::presentSpeed().address        , 2);
			c->addBulkReadParam(this->id , Model::presentLoad().address         , 2);
			c->addBulkReadParam(this->id , Model::presentVoltage().address      , 1);
			c->addBulkReadParam(this->id , Model::presentTemperature().address  , 1);
			c->addBulkReadParam(this->id , Model::registered().address          , 1);
			c->addBulkReadParam(this->id , Model::moving().address              , 1);
			c->addBulkReadParam(this->id , Model::hardwareErrorStatus().address , 1);

			c->bulkReadRequest();// esto debiera estar en otro thread!
			
//			uint8_t  data1
			uint16_t data;
			
			
			if(c->getBulkReadData(this->id , Model::modelNumber().address         , 2 , data)){  R_modelNumber = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::firmwareVersion().address     , 1 , data)){  R_firmwareVersion = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::baudRate().address            , 1 , data)){  P_baudRate.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::returnDelayTime().address     , 1 , data)){  P_returnDelayTime.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::cwAngleLimit().address        , 2 , data)){  P_cwAngleLimit.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::ccwAngleLimit().address       , 2 , data)){  P_ccwAngleLimit.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::controlMode().address         , 1 , data)){  P_controlMode.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::temperatureLimit().address    , 1 , data)){  P_temperatureLimit.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::minVoltageLimit().address     , 1 , data)){  P_minVoltageLimit.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::maxVoltageLimit().address     , 1 , data)){  P_maxVoltageLimit.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::maxTorque().address           , 2 , data)){  P_maxTorque.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::statusReturnLevel().address   , 1 , data)){  P_statusReturnLevel.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::shutdown().address            , 1 , data)){  P_shutdown.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::torqueEnabled().address        , 1 , data)){  P_torqueEnabled.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::led().address                 , 1 , data)){  P_ledStatus.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::dGain().address               , 1 , data)){  P_dGain.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::iGain().address               , 1 , data)){  P_iGain.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::pGain().address               , 1 , data)){  P_pGain.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::goalPosition().address        , 2 , data)){  P_goalPosition.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::goalSpeed().address         , 2 , data)){  P_goalSpeed.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::torqueLimit().address         , 2 , data)){  P_torqueLimit.readOnlyParam = data;}
			if(c->getBulkReadData(this->id , Model::punch().address               , 2 , data)){  P_punch.readOnlyParam = data;}		
			if(c->getBulkReadData(this->id , Model::presentPosition().address     , 2 , data)){  R_presentPosition = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::presentSpeed().address        , 2 , data)){  R_presentSpeed = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::presentLoad().address         , 2 , data)){  R_presentLoad = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::presentVoltage().address      , 1 , data)){  R_presentVoltage = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::presentTemperature().address  , 1 , data)){  R_presentTemperature = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::registered().address          , 1 , data)){  R_registered = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::moving().address              , 1 , data)){  R_moving = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::hardwareErrorStatus().address , 1 , data)){  R_hardwareErrorStatus = ofToString(data);}
		}
#endif
	}
//-------------------------------------------------------------------------------------------------------------------		
	
	template class ServoGui<AX12>;
	template class ServoGui<XL320>;
}
