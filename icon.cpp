#include "icon.h"
#include<iostream>
int ICON::GRID_SIZE = 32;


pair<string,ICON> pairArray[] =
{
    make_pair("soldier1",ICON("soldier1",0,0, 2, 2)),
    make_pair("soldier2",ICON("soldier2",0,2, 2, 2)),
    make_pair("soldier3",ICON("soldier3",0,4, 2, 2)),
    make_pair("tower",ICON("tower",8,0,3, 3)),
    make_pair("enemy1",ICON("enemy1",2,0,2,2)),
    make_pair("enemy2",ICON("enemy1",2,2,2,2)),
    make_pair("enemy3",ICON("enemy1",2,4,2,2)),
    make_pair("base",ICON("base",8,3,3,3)),
    make_pair("bullet",ICON("bullet",11,0,1,1))
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
