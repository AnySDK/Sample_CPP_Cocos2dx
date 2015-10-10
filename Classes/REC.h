//
//  REC.h
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//
#ifndef __MY_REC_H__
#define __MY_REC_H__

#include "AgentManager.h"
#include "cocos2d.h"

using namespace anysdk::framework;

class REC : public RECResultListener
{
public:
    static REC* getInstance();
    static void purge();
    
    //分享系统
    
    void setListener();
    
    void startRecording();
    void stopRecording();
    void share();


    void pauseRecording();
    void resumeRecording();
    bool isAvailable();
    void showToolBar();
    void hideToolBar();
    bool isRecording();
    void showVideoCenter();
    void enterPlatform();
    void setMetaData();
    
    bool isFunctionSupported(string strClassName);

    //分享回调函数
    virtual void onRECResult(RECResultCode ret, const char* msg);
    
    
    
private:
    REC();
    virtual ~REC();
    
    static REC* _pInstance;
    
};

#endif
