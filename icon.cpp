#include "icon.h"
#include<iostream>
int ICON::GRID_SIZE = 32;


pair<string,ICON> pairArray[] =
{
    make_pair("soldier",ICON("soldier",5,0, 1, 2)),
    make_pair("ruins",ICON("ruins",11,12,2,2)),
    make_pair("tower",ICON("tower",4,0,1, 2)),
    make_pair("enemy",ICON("enemy",1,1,1,1)),
    make_pair("base",ICON("base",4,2,1,2))
    /*make_pair("fruit",ICON("fruit",3,6, 1, 1)),
    make_pair("tree",ICON("tree",3,13,2,3)),
    make_pair("monster",ICON("monster",1,1,1,1))*/
};

//这下面的代码不用管，反正没问题
map<string,ICON> ICON::GAME_ICON_SET(pairArray,pairArray+sizeof(pairArray)/sizeof(pairArray[0]));


ICON::ICON(string name, int x, int y, int w, int h){
    this->typeName = name;
    this->srcX = x;
    this->srcY = y;
    this->width = w;
    this->height = h;
}

ICON ICON::findICON(string type){
    map<string,ICON>::iterator kv;
    kv = ICON::GAME_ICON_SET.find(type);
    if (kv==ICON::GAME_ICON_SET.end()){

       cout<<"Error: cannot find ICON"<<endl;
       return ICON();
    }
    else{
        return kv->second;
    }
}
