//
//  Share.h
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//
#ifndef __MY_Share_H__
#define __MY_Share_H__

#include "AgentManager.h"

using namespace anysdk::framework;

class Share : public ShareResultListener
{
public:
    static Share* getInstance();
    static void purge();
    
    //分享系统
    
    void setListener();
    
    //分享系统功能
    void share();
    
    //分享回调函数
    virtual void onShareResult(ShareResultCode ret, const char* msg);
    
    
    
private:
    Share();
    virtual ~Share();
    
    static Share* _pInstance;
    
};

#endif
