//
//  Ads.h
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

// #import <Foundation/Foundation.h>
#include "AgentManager.h"

using namespace anysdk::framework;

class Ads : public AdsListener
{
    
public:
    static Ads* getInstance();
    static void purge();
    
    //广告系统
    
    //广告回调函数
    virtual void onAdsResult(AdsResultCode code, const char* msg);
    
    //广告系统展示
    void showAds(AdsType type, int idx=1);
    
    //广告系统隐藏
    void hideAds(AdsType type, int idx=1);
    
    //广告系统隐藏
    void preloadAds(AdsType type, int idx=1);
    
    //查询积分
    float queryPoints();
    
    //消费积分
    void spendPoints(int points);
    
private:
    Ads();
    virtual ~Ads();
    
    static Ads* _pInstance;
    
    ProtocolAds* ads_plugin;
    
};
