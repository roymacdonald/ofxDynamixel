//
//  ofxGuiUtils.h
//  test_ofxModule
//
//  Created by Roy Macdonald on 9/3/18.
//
//

#pragma once

#include "ofxGui.h"
//-------------------------------------------------------------------------------------------------------------------
static ofxGuiGroup * getOrCreateGuiGroup( ofxGuiGroup * parentgroup, const std::string& groupname){
	
	//			auto paths = ofSplitString(path, "/");
	for(int i = 0; i < parentgroup->getNumControls(); i++){
		auto control = parentgroup->getControl(i);
		if(control != nullptr){
			ofxGuiGroup * subgroup = dynamic_cast <ofxGuiGroup *>(control);
			if(subgroup != nullptr){
				if(subgroup->getName() == groupname){
					return subgroup; 
				}
			}
		}
	}
	ofxGuiGroup * g = new ofxGuiGroup();
	g->setup(groupname);
	parentgroup->add(g);
	return g;
	
}
//-------------------------------------------------------------------------------------------------------------------
static void setWidthElementsRecursive(ofxGuiGroup* group, float w){
for(int i = 0; i < group->getNumControls(); i++){
	auto control = group->getControl(i);
	if(control != nullptr){
		ofxGuiGroup * subgroup = dynamic_cast <ofxGuiGroup *>(control);
		if(subgroup != nullptr){
			
		}
	}
}
}
//-------------------------------------------------------------------------------------------------------------------
static ofxGuiGroup * getOrCreateGuiGroupHierarchy(ofxGuiGroup* panel, const std::string& path){
	ofxGuiGroup * parent = panel;
	ofxGuiGroup * child;
	auto groups = ofSplitString(path, "/");
//	for(auto& g: groups){
//		cout << g << endl;
//	}
//	
	//			cout << "//////////" << endl;
//	if(groups.size() == 0) return parent;
	for(auto& g: groups){
		if(!g.empty()){
			child = getOrCreateGuiGroup(parent, g);
			parent = child;
		}
	}
	return parent;
}

//-------------------------------------------------------------------------------------------------------------------
static void printGuiGroup(ofxGuiGroup * group, std::string prefix = ""){
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
