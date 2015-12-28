//
//  Crash.h
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//
#ifndef __MY_Crash_H__
#define __MY_Crash_H__

#include "AgentManager.h"

using namespace anysdk::framework;


class Crash
{
public:
    static Crash* getInstance();
    static void purge();
    
    //设置用户唯一标示符
    void setUserIdentifier();
    
    //手动上报Exception
    void reportException();
    
    //设置面包屑
    void leaveBreadcrumb();
    
    
    
private:
    Crash();
    virtual ~Crash();
    
    static Crash* _pInstance;
    
    ProtocolCrash* _Crash;
};

#endif
