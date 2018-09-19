//
//  ofxGuiUtils.h
//  test_ofxModule
//
//  Created by Roy Macdonald on 9/3/18.
//
//

#pragma once

#include "ofxGui.h"
#include "ofxGuiGroupMinimal.h"
//-------------------------------------------------------------------------------------------------------------------
static ofxGuiGroup * findGuiGroup( ofxGuiGroup * parentgroup, const std::string& groupname){
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
	return nullptr;
	
}
//-------------------------------------------------------------------------------------------------------------------
static ofxGuiGroup * getOrCreateGuiGroup( ofxGuiGroup * parentgroup, const std::string& groupname){
	
	ofxGuiGroup * g = findGuiGroup(parentgroup, groupname);
	if(!g){
		g = new ofxGuiGroup();
		g->setup(groupname);
		parentgroup->add(g);
	}
	return g;
	
}
//-------------------------------------------------------------------------------------------------------------------
static void findAndMinimizeGroup( ofxGuiGroup * parentgroup, const std::string& groupname, bool bMinimizeChildrenOnly = false){
	auto g = findGuiGroup(parentgroup, groupname);
	if(g){
		if(bMinimizeChildrenOnly){
			g->minimizeAll();
		}else{
			g->minimize();
		}
	}else{
		std::cout << "findAndMinimizeGroup::  ofxGuiGroup " << groupname << " not found!" << std::endl;
	}
}
//-------------------------------------------------------------------------------------------------------------------
template<typename T>
static void setWidthElementsRecursive(T* group, float w){
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
