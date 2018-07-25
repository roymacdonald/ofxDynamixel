
#pragma once
#include "ofxDynamixelBaseServo.h"
#include "ofParameter.h"
#include "ofxGui.h"
#include "ofxDynamixelRWParameter.h"
#include "ofxGuiRW.h"


//#define DECL_PARAM_RW_8(param) ofParameter<uint8_t> R_##param; ofParameter<uint8_t> W_##param; ofParameterGroup  G_##param;
//#define DECL_PARAM_RW_16(param) ofParameter<uint16_t> R_##param; ofParameter<uint16_t> W_##param; ofParameterGroup  G_##param;


//#define DECL_PARAM_RW_8(param) ofReadOnlyParameter<std::string, ServoGui> R_##param; ofParameter<uint8_t> W_##param; ofParameterGroup  G_##param;
//#define DECL_PARAM_RW_16(param) ofReadOnlyParameter<std::string, ServoGui> R_##param; ofParameter<uint16_t> W_##param; ofParameterGroup  G_##param;
 
//#define DECL_PARAM_RW_8(param)  ofParameter<uint8_t> W_##param; ofParameterGroup  G_##param;
//#define DECL_PARAM_RW_16(param) ofParameter<uint16_t> W_##param; ofParameterGroup  G_##param;
//#define DECL_PARAM_RW_B(param)  ofParameter<bool> W_##param; ofParameterGroup  G_##param;


namespace ofxDynamixel {
#define DECL_PARAM_RW_8(param)  RWParameter<uint8_t> P_##param;// ofParameterGroup  G_##param;
#define DECL_PARAM_RW_16(param) RWParameter<uint16_t> P_##param;// ofParameterGroup  G_##param;
#define DECL_PARAM_RW_B(param)  RWParameter<bool> P_##param; //ofParameterGroup  G_##param;

	template<typename Model>
	class ServoGui: public BaseServo<Model>{
public:
		
	virtual void setup(int id,  std::shared_ptr<Connection> connection) override;
	
	
//		ofParameterGroup parameters;
				
		//epprom
		ofReadOnlyParameter<std::string, ServoGui<Model>>  R_modelNumber;
		ofReadOnlyParameter<std::string, ServoGui<Model>>  R_firmwareVersion;
		
		DECL_PARAM_RW_8 (id_param)
		DECL_PARAM_RW_8 (baudRate)          
		DECL_PARAM_RW_8 (returnDelayTime)   
		DECL_PARAM_RW_16(cwAngleLimit)      
		DECL_PARAM_RW_16(ccwAngleLimit)     
		DECL_PARAM_RW_8 (controlMode)       
		DECL_PARAM_RW_8 (temperatureLimit)  
		DECL_PARAM_RW_8 (minVoltageLimit)   
		DECL_PARAM_RW_8 (maxVoltageLimit)   
		DECL_PARAM_RW_16(maxTorque)         
		DECL_PARAM_RW_8 (statusReturnLevel) 
		DECL_PARAM_RW_8 (shutdown)      
		//ram
		DECL_PARAM_RW_8(torqueEnabled);
		DECL_PARAM_RW_8(ledStatus);
		DECL_PARAM_RW_8(dGain);
		DECL_PARAM_RW_8(iGain);
		DECL_PARAM_RW_8(pGain);
		DECL_PARAM_RW_16(goalPosition);
		DECL_PARAM_RW_16(goalSpeed);
		DECL_PARAM_RW_16(torqueLimit);
		DECL_PARAM_RW_16(punch);

		
//		ofParameter<uint16_t> R_presentPosition;
//		ofParameter<uint16_t> R_presentSpeed;
//		ofParameter<uint16_t> R_presentLoad;
//		ofParameter<uint8_t>  R_presentVoltage;
//		ofParameter<uint8_t>  R_presentTemperature;
//		ofParameter<uint8_t>  R_registered;
//		ofParameter<uint8_t>  R_moving;
//		ofParameter<uint8_t>  R_hardwareErrorStatus;

		ofReadOnlyParameter<std::string, ServoGui<Model>> R_presentPosition;
		ofReadOnlyParameter<std::string, ServoGui<Model>> R_presentSpeed;
		ofReadOnlyParameter<std::string, ServoGui<Model>> R_presentLoad;
		ofReadOnlyParameter<std::string, ServoGui<Model>>  R_presentVoltage;
		ofReadOnlyParameter<std::string, ServoGui<Model>>  R_presentTemperature;
		ofReadOnlyParameter<std::string, ServoGui<Model>>  R_registered;
		ofReadOnlyParameter<std::string, ServoGui<Model>>  R_moving;
		ofReadOnlyParameter<std::string, ServoGui<Model>>  R_hardwareErrorStatus;
		
		
		ofxGuiGroup eepromParams, ramParams, readParams;
		
		ofxPanel panel;
		
		void update();
		
	private:
		template<typename T>
		void setParamRW(RWParameter<T>& param, const regStruct<T>& ref, ofxGuiGroup& group){	
		//		param.setName(#param);\
		//		G_##param.add(W_##param.set("W", C, M, X ));
		//		param.setup(
			param.set(ref);
			group.add(new ofxGuiRW_<T>(param));
		}

		
		
	ofEventListeners listeners;
	
	void setListeners();
	
		
//		void disableMouseInput(std::string groupName, std::string paramName);
};
	typedef ServoGui<XL320> ServoGuiXL320;
	typedef ServoGui<AX12> ServoGuiAX12;
}
