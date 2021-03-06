//
//  PluginChannel.m
//  sample
//
//  Created by cocos2dx on 14-11-10.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//



#include "PluginChannel.h"
#include <stdlib.h>
#include "Analytics.h"
#include "Push.h"
#include "cocos2d.h"
#include "PluginParam.h"

// #include "PartViews.h"

using namespace anysdk::framework;

#define  LOG_TAG    "PluginChannel"

void CCMessageBox(const char* content, const char* title)
{
    ////
    // [PartViews addDebugView:[[NSString alloc] initWithUTF8String:title] ctx:[[NSString alloc] initWithUTF8String:content]];
}

void CCExit()
{
    ////
    exit(0);
}

PluginChannel* PluginChannel::_pInstance = NULL;
static AllProductsInfo _myProducts;

PluginChannel::PluginChannel()
{
    _pluginsIAPMap = NULL;
    
}

PluginChannel::~PluginChannel()
{
    unloadPlugins();
}

PluginChannel* PluginChannel::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new PluginChannel();
    }
    return _pInstance;
}

void PluginChannel::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

//使用anysdk.com的时候注释掉这个宏就可以
//#define isQudaoInfo 1

void PluginChannel::loadPlugins()
{
    printf("Load plugins invoked\n");
    /**
     * appKey、appSecret、privateKey不能使用Sample中的值，需要从打包工具中游戏管理界面获取，替换
     * oauthLoginServer参数是游戏服务提供的用来做登陆验证转发的接口地址。
     */

    std::string appKey = "D22AB625-CD4C-2167-D35C-C5A03E5896F5";
    std::string appSecret = "8959c650440b6b051d6af588d7f965f3";
    std::string privateKey = "BA26F2670407E0B8664DDA544026FA54";
    std::string oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";
    
    AgentManager::getInstance()->init(appKey,appSecret,privateKey,oauthLoginServer);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //使用框架中代理类进行插件初始化
    //Android建议在onCreate里调用PluginWrapper.loadAllPlugins();来进行插件初始化
    AgentManager::getInstance()->loadAllPlugins();
#endif  
  
    //对用户系统设置监听类
    if(AgentManager::getInstance()->getUserPlugin())
    {
        AgentManager::getInstance()->getUserPlugin()->setActionListener(this);
    }
    
    //对支付系统设置监听类
    printf("Load plugins invoked\n");
    _pluginsIAPMap  = AgentManager::getInstance()->getIAPPlugin();
    std::map<std::string , ProtocolIAP*>::iterator iter;
    for(iter = _pluginsIAPMap->begin(); iter != _pluginsIAPMap->end(); iter++)
    {
        (iter->second)->setResultListener(this);
    }
    
    Analytics::getInstance()->setCaptureUncaughtException(true);
    Analytics::getInstance()->setSessionContinueMillis(15000);
    Analytics::getInstance()->logTimedEventBegin("Load");
    Push::getInstance()->startPush();
    
    _iapAppstore = getIAPAppstore();
}

void PluginChannel::unloadPlugins()
{
    printf("Unload plugins invoked\n");
    AgentManager::getInstance()->unloadAllPlugins();
    Analytics::getInstance()->logTimedEventEnd("Unload");
}

std::string PluginChannel::getPluginId()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        return AgentManager::getInstance()->getUserPlugin()->getPluginId();
    }
    return "";
}

void PluginChannel::login()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        AgentManager::getInstance()->getUserPlugin()->login();
        Analytics::getInstance()->logEvent("login");
    }
}


void PluginChannel::logout()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(isFunctionSupported("logout"))
        {
            
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("logout",NULL);
        }
    }
}

bool PluginChannel::isFunctionSupported(std::string strClassName)
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        return AgentManager::getInstance()->getUserPlugin()->isFunctionSupported(strClassName);
        
    }
    return false;
}

const char* PluginChannel::getResourceId(std::string name)
{
    printf("getResourceId:%s\n", name.c_str());
//     NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"channel" ofType:@"plist"];
//     NSMutableDictionary *data = [[NSMutableDictionary alloc] initWithContentsOfFile:plistPath];
// //    CCLOG("%@", data);
//     NSString* key = [[NSString alloc] initWithUTF8String:name.c_str()];
//     NSString* value = [data objectForKey:key];
    return "";
}

void PluginChannel::ChoosePayMode(std::vector<std::string>& pluginId)
{
    // NSMutableDictionary* _list = [NSMutableDictionary dictionary];
    // ////display interface
    // std::vector<std::string>::iterator iter;
    // for (iter = pluginId.begin(); iter != pluginId.end(); iter++) {
    //     printf("channelID:%s\n", (*iter).c_str());
    //     std::string key = "Channel" + (*iter);
    //     NSString* channelName = [[NSString alloc] initWithUTF8String:getResourceId(key)];
    //     NSString* channelKey = [[NSString alloc] initWithUTF8String:(*iter).c_str()];
    //     [_list setObject:channelName forKey:channelKey];
    // }
    // [PartViews addButtons:_list];
}

void PluginChannel::payMode(std::string id)
{
    std::map<std::string , ProtocolIAP*>::iterator iter;
    iter = _pluginsIAPMap->find(id);
    CCLOG("111");
    if(iter != _pluginsIAPMap->end())
    {
        CCLOG("222");
        (iter->second)->payForProduct(productInfo);
        CCLOG("333");
    }
    CCLOG("444");
}

ProtocolIAP* PluginChannel::getIAPAppstore()
{
    if(_pluginsIAPMap)
    {
        std::map<std::string , ProtocolIAP*>::iterator it = _pluginsIAPMap->begin();
        for (; it != _pluginsIAPMap->end(); it++) {
            printf("it->first: %s----\n", it->first.c_str());
            if (it->first == APPSTORE_PLUGIN_ID) {
                return it->second;
            }
        }
    }
    return NULL;
}

void PluginChannel::requestProducts()
{
    // AppStroe才有的接口，也可以不调用requestProducts直接调用payForProduct 
    printf("payRequest\n");
    if ( NULL!= _iapAppstore ) {
        PluginParam param1("PD_10005");
        PluginParam param2("PD_10004");
        PluginParam param3("PD_10003");
        _iapAppstore->callFuncWithParam("requestProducts", &param1, &param2, &param3, NULL);
    }
    else{
        printf("iap iphone isn't find!\n");
    }
}

void PluginChannel::pay()
{   
    std::map<std::string , ProtocolIAP*>::iterator it = _pluginsIAPMap->begin();
    if(_pluginsIAPMap)
    {
        productInfo["Product_Id"] = "1";
        productInfo["Product_Name"] = "10元宝";
        productInfo["Product_Price"] = "1";
        productInfo["Product_Count"] = "1";
        productInfo["Product_Desc"] = "gold";
        productInfo["Coin_Name"] = "元宝";
        productInfo["Coin_Rate"] = "10";
        productInfo["Role_Id"] = "123456";
        productInfo["Role_Name"] = "test";
        productInfo["Role_Grade"] = "1";
        productInfo["Role_Balance"] = "1";
        productInfo["Vip_Level"] = "1";
        productInfo["Party_Name"] = "test";
        productInfo["Server_Id"] = "1";
        productInfo["Server_Name"] = "test";
        productInfo["EXT"] = "test";
        Analytics::getInstance()->logEvent("pay", productInfo);
        if(_pluginsIAPMap->size() == 1)
        {
            (it->second)->payForProduct(productInfo);
        }
        else if(_pluginsIAPMap->size() > 1)
        {
            std::vector<std::string> pluginId;
            for (;it != _pluginsIAPMap->end();++it)
            {
                pluginId.push_back(it->first);
            }
            ChoosePayMode(pluginId);
        }
    }
    
    
    PluginParam param3("size");
    std::vector<PluginParam*> params;
    params.push_back(&param3);
}

void PluginChannel::resetPayState()
{
    ProtocolIAP::resetPayState();
    pay();
}

std::string PluginChannel::getUserId()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        return AgentManager::getInstance()->getUserPlugin()->getUserID();
    }
    return "";
}

void PluginChannel::enterPlatform()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        //使用isFunctionSupported可先判断该插件是否支持该功能
        if(isFunctionSupported("enterPlatform"))
        {
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("enterPlatform",NULL);
        }
    }
}

void PluginChannel::showToolBar(ToolBarPlace place)
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(isFunctionSupported("showToolBar"))
        {
            PluginParam paramInfo(place);
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("showToolBar",&paramInfo,NULL);
        }
    }
}

void PluginChannel::hideToolBar()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(isFunctionSupported("hideToolBar"))
        {
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("hideToolBar",NULL);
        }
    }
}

void PluginChannel::pause()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(isFunctionSupported("pause"))
        {
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("pause",NULL);
        }
    }
}

void PluginChannel::destroy()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(isFunctionSupported("destroy"))
        {
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("destroy",NULL);
        }
    }
}

void PluginChannel::Exit()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(isFunctionSupported("exit"))
        {
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("exit",NULL);
        }
        
    }
}

void PluginChannel::antiAddictionQuery()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(isFunctionSupported("antiAddictionQuery"))
        {
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("antiAddictionQuery",NULL);
        }
        
    }
}

void PluginChannel::accountSwitch()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(isFunctionSupported("accountSwitch"))
        {
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("accountSwitch",NULL);
        }
        
    }
}

void PluginChannel::realNameRegister()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(isFunctionSupported("realNameRegister"))
        {
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("realNameRegister",NULL);
        }
        
    }
}

void PluginChannel::submitLoginGameRole()
{
    if(AgentManager::getInstance()->getUserPlugin())
    {
        if(PluginChannel::getInstance()->isFunctionSupported("submitLoginGameRole"))
        {
            StringMap userInfo;
            userInfo["dataType"] = "1";
            userInfo["roleId"] = "123456";
            userInfo["roleName"] = "test";
            userInfo["roleLevel"] = "1";
            userInfo["zoneId"] = "1";
            userInfo["zoneName"] = "test";
            userInfo["balance"] = "60";
            userInfo["partyName"] = "test";
            userInfo["vipLevel"] = "1";
            userInfo["roleCTime"] = "1480318110";
            userInfo["roleLevelMTime"] = "-1";
            PluginParam data(userInfo);
            AgentManager::getInstance()->getUserPlugin()->callFuncWithParam("submitLoginGameRole",&data,NULL);
        }
    }
}

void ShowTipDialog()
{
    ////
}

void PluginChannel::onRequestResult(RequestResultCode ret, const char* msg, AllProductsInfo info)
{
    //info: 商品获取到的信息，请在这里进行商品界面的展示。
    printf("get all iap-iphone products info:%lu\n", info.size());
    _myProducts = info;
}

void PluginChannel::onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
{
    printf("onPayResult, %s\n", msg);
    std::string temp = "fail";
    switch(ret)
    {
        case kPaySuccess://支付成功回调
            temp = "Success";
            CCMessageBox(temp.c_str() , temp.c_str() );
            break;
        case kPayFail://支付失败回调
            CCMessageBox(temp.c_str()  , temp.c_str() );
            break;
        case kPayCancel://支付取消回调
            CCMessageBox(temp.c_str()  , "Cancel" );
            break;
        case kPayNetworkError://支付超时回调
            CCMessageBox(temp.c_str()  , "NetworkError");
            break;
        case kPayProductionInforIncomplete://支付超时回调
            CCMessageBox(temp.c_str()  , "ProductionInforIncomplete");
            break;
            /**
             * 新增加:正在进行中回调
             * 支付过程中若SDK没有回调结果，就认为支付正在进行中
             * 游戏开发商可让玩家去判断是否需要等待，若不等待则进行下一次的支付
             */
        case kPayNowPaying:
            ShowTipDialog();
            break;
        default:
            break;
    }
}

void PluginChannel::onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
{
    printf("PluginChannel, onActionResult:%d, msg%s\n",code,msg);
    bool _userLogined = false;
    switch(code)
    {
        case kInitSuccess://初始化SDK成功回调
            break;
        case kInitFail://初始化SDK失败回调
            CCExit();
            break;
        case kLoginSuccess://登陆成功回调
            _userLogined = true;
//            CCMessageBox(msg, "User is  online");
            if (getChannelId() == "000255") {//UC渠道
                printf("开始调用submitLoginGameRole函数\n");
                submitLoginGameRole();
                printf("结束调用submitLoginGameRole函数\n");
            }
            break;
        case kLoginNetworkError://登陆失败回调
        case kLoginCancel://登陆取消回调
        case kLoginFail://登陆失败回调
            CCMessageBox(msg, "fail");
            _userLogined = false;
            Analytics::getInstance()->logError("login","fail");
            break;
        case kLogoutSuccess://登出成功回调
            
            break;
        case kLogoutFail://登出失败回调
            CCMessageBox(msg  , "登出失败");
            break;
        case kPlatformEnter://平台中心进入回调
            break;
        case kPlatformBack://平台中心退出回调
            break;
        case kPausePage://暂停界面回调
            break;
        case kExitPage://退出游戏回调
            CCExit();
            
            break;
        case kAntiAddictionQuery://防沉迷查询回调
            CCMessageBox(msg  , "防沉迷查询回调");
            break;
        case kRealNameRegister://实名注册回调
            CCMessageBox(msg  , "实名注册回调");
            break;
        case kAccountSwitchSuccess://切换账号成功回调
            break;
        case kAccountSwitchFail://切换账号成功回调
            break;
        default:
            break;
    }
}

std::string PluginChannel::getChannelId()
{
    return AgentManager::getInstance()->getChannelId();
}
