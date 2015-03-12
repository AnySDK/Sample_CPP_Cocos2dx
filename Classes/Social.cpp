//
//  Social.m
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#include "Social.h"

using namespace anysdk::framework;

#define  LOG_TAG    "Social"

Social* Social::_pInstance = NULL;

Social::Social()
{
    setListener();
    
}

Social::~Social()
{
    
}

Social* Social::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Social();
        _pInstance->setListener();
        AgentManager::getInstance()->getSocialPlugin()->setDebugMode(true);
    }
    return _pInstance;
}

void Social::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void Social::setListener()
{
    
    if(AgentManager::getInstance()->getSocialPlugin())
    {
        AgentManager::getInstance()->getSocialPlugin()->setListener(this);
    }
}

void Social::submitScore()
{
    if(AgentManager::getInstance()->getSocialPlugin())
    {
        AgentManager::getInstance()->getSocialPlugin()->submitScore("friend",1);
    }
    
}
void Social::showLeaderboard()
{
    if(AgentManager::getInstance()->getSocialPlugin())
    {
        AgentManager::getInstance()->getSocialPlugin()->showLeaderboard("friends");
    }
    
}

void Social::unlockAchievement()
{
    if(AgentManager::getInstance()->getSocialPlugin())
    {
        TAchievementInfo achInfo;
        achInfo["rank"] = "friends";
        AgentManager::getInstance()->getSocialPlugin()->unlockAchievement(achInfo);
    }
    
}

void Social::showAchievements()
{
    if(AgentManager::getInstance()->getSocialPlugin())
    {
        AgentManager::getInstance()->getSocialPlugin()->showAchievements();
    }
}


//社交回调函数
void Social::onSocialResult(SocialRetCode code, const char* msg)
{
    switch(code)
    {
        case kScoreSubmitSucceed://提交分数成功回调
            
            break;
        case kScoreSubmitfail://提交分数失败回调
            
            break;
        case kAchUnlockSucceed://解锁成F就成功回调
            
            break;
        case kAchUnlockFail://解锁成就失败回调
            
            break;
        default:
            break;
    }
}


