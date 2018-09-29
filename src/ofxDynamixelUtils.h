//
//  ofxDynamixelUtils.h
//  test_autoDistribucion
//
//  Created by Roy Macdonald on 9/29/18.
//
//

#pragma once
namespace ofxDynamixel{
	//-----------------------------------------------------------------------------------------
	static inline float wrapAngle(float angle){
		if(angle >180){
			angle = angle - 360;
		}else if(angle < -180){
			angle = angle + 360;
		}
		//			ss << "av1 x: " << ofToString(angle)<< endl;
		angle += 180;
		return angle;
	}
	//-----------------------------------------------------------------------------------------
	static inline uint16_t degreesToServoPos(float angle, uint16_t servoMax){
		
		return (uint16_t)round(ofMap(wrapAngle(angle), 0, 360, servoMax, 0));
	}
}
