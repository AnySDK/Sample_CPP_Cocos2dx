//
//  Push.m
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#include "Push.h"


Push* Push::_pInstance = NULL;

Push::Push()
{
//    setListener();
}

Push::~Push()
{
    
}

Push* Push::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Push();
        _pInstance->_push = AgentManager::getInstance()->getPushPlugin();
        _pInstance->setListener();
    }
    return _pInstance;
}

void Push::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void Push::setListener()
{
    if(_push)
    {
        _push->setActionListener(this);
    }
}

//开启推送
void Push::startPush()
{
    if(_push)
    {
        _push->startPush();
    }
}

//开启推送
void Push::closePush()
{
    if(_push)
    {
        _push->closePush();
    }
    
}

//设置别名
void Push::setAlias()
{
    if(_push)
    {
        _push->setAlias("AnySDK");
    }
    
    
}



//删除别名
void Push::delAlias()
{
    if(_push)
    {
        _push->delAlias("AnySDK");
    }
    
}

//设置标签
void Push::setTags()
{
    if(_push)
    {
        list<string> tags;
        tags.push_back("easy");
        tags.push_back("fast");
        tags.push_back("strong");
        _push->setTags(tags);
    }
}

//删除标签
void Push::delTags()
{
    if(_push)
    {
        list<string> tags;
        tags.push_back("easy");
        tags.push_back("fast");
        _push->delTags(tags);
    }
}

//Push回调函数
void Push::onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg)
{
    printf("Push::onActionResult\n");
    switch(code)
    {
        case kPushReceiveMessage://Push接受到消息回调
            printf("%s\n",msg);
            break;
        default:
            break;
    }
    
}



