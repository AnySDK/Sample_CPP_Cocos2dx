//
//  Share.m
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#include "Share.h"
// #include "PartViews.h"

#define  LOG_TAG    "Share"


Share* Share::_pInstance = NULL;

Share::Share()
{
    setListener();
}

Share::~Share()
{
    
    
}

Share* Share::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Share();
        _pInstance->setListener();
        AgentManager::getInstance()->getSharePlugin()->setDebugMode(true);
    }
    return _pInstance;
}

void Share::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void Share::setListener()
{
    
    if(AgentManager::getInstance()->getSharePlugin())
    {
        AgentManager::getInstance()->getSharePlugin()->setResultListener(this);
    }
    
}

void Share::share()
{
    if(AgentManager::getInstance()->getSharePlugin())
    {
        
        std::map<std::string, std::string> info;
        // title标题，印象笔记、邮箱、信息、微信、人人网和QQ空间使用
        info["title"] = "ShareSDK是一个神奇的SDK";
        // titleUrl是标题的网络链接，仅在人人网和QQ空间使用
        info["titleUrl"] = "http://sharesdk.cn";
        // site是分享此内容的网站名称，仅在QQ空间使用
        info["site"] = "ShareSDK";
        // siteUrl是分享此内容的网站地址，仅在QQ空间使用
        info["siteUrl"] = "http://sharesdk.cn";
        
        // imagePath是图片的本地路径，Linked-In以外的平台都支持此参数
        info["imagePath"] = "/sdcard/test.png";
        // imageUrl是图片的网络路径，新浪微博，人人网，QQ空间支持此字段
        info["imageUrl"] = "http://www.baidu.com/img/bdlogo.png?tn=63090008_1_hao_pg";
        
        // url仅在微信（包括好友和朋友圈）中使用
        info["url"] ="http://sharesdk.cn";
        
        // text是分享文本，所有平台都需要这个字段
        info["text"] = "ShareSDK支持如微信、新浪微博、腾讯微博等社交平台";
        // comment是我对这条分享的评论，仅在人人网和QQ空间使用
        info["comment"] = "无";
        
        
        AgentManager::getInstance()->getSharePlugin()->share(info);
    }
    
}

void Share::onShareResult(ShareResultCode ret, const char* msg)
{
    printf("onShareResult %d\n",ret);
    switch(ret)
    {
        case kShareSuccess://分享成功回调
            printf("onShareResult success\n");
            break;
        case kShareFail://分享失败回调
            printf("onShareResult fail\n");
            break;
        case kShareCancel://分享取消回调
            printf("onShareResult cancel\n");
            break;
        case kShareNetworkError://分享网络出错回调
            printf("onShareResult error\n");
            break;
        default:
            break;
    }
    
}



