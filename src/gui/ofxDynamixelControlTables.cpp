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
//	std::cout << __PRETTY_FUNCTION__ << std::endl;
	add<uint16_t>(modelNumber         ,  0 , "modelNumber"                            , true  , true);
	
}

}
