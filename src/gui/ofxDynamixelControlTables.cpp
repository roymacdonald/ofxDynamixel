//
//  ofxDynamixelControlTables.cpp
//  example
//
//  Created by Roy Macdonald on 7/26/18.
//
//

#include "ofxDynamixelControlTables.h"
namespace ofxDynamixel {
	
	
	DXLBaseControlTable::DXLBaseControlTable(){
		add<uint16_t>(modelNumber         ,  0 , "modelNumber"                            , true  , true, "info/");
		
	}	
}
