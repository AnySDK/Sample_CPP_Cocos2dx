//
//  Social.h
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#ifndef __MY_SOCIAL_H__
#define __MY_SOCIAL_H__

#include "AgentManager.h"

using namespace anysdk::framework;

class Social:public SocialListener
{
public:
    static Social* getInstance();
    static void purge();
    
    //社交系统
    
    void setListener();
    
    
    void submitScore();
    void showLeaderboard();
    
    void unlockAchievement();
    
    void showAchievements();
    
    
    //社交回调函数
    virtual void onSocialResult(SocialRetCode code, const char* msg);
    
    
    
private:
    Social();
    virtual ~Social();
    
    static Social* _pInstance;
    
};

#endif

