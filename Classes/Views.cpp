
#include "Views.h"


#include "Ads.h"
#include "Push.h"
#include "Share.h"
#include "Social.h"
#include "Analytics.h"
#include "PluginChannel.h"


static std::string base_menu[] = {"User System", "IAP System", "Share System", "Ads System", "Social System", "Push System", "Analytics System"};
static int g_testCount = sizeof(base_menu) / sizeof(base_menu[0]);

static std::string user_menu[] = {"login", "logout", "enterPlatform", "showToolbar", "hideToolbar", "accountSwitch", "realNameRegister", "antiAddictionQuery", "submitLoginGameRole"};
static int user_count = sizeof(user_menu) / sizeof(user_menu[0]);

static std::string ads_menu[] = {"banner", "fullscreen", "moreapp", "offerwall"};
static int ads_count = sizeof(ads_menu) / sizeof(ads_menu[0]);

static std::string banner_menu[] = {"show banner 1", "hide banner 1", "show banner 2", "hide banner 2", "show banner 3", "hide banner 3", "show banner 4", "hide banner 4", "show banner 5", "hide banner 5"};
static int banner_count = sizeof(banner_menu) / sizeof(banner_menu[0]);

static std::string fullscreen_menu[] = {"show screen 1", "hide screen 1", "show screen 2", "hide screen 2", "show screen 3", "hide screen 3"};
static int fullscreen_count = sizeof(fullscreen_menu) / sizeof(fullscreen_menu[0]);

static std::string moreapp_menu[] = {"show moreapp 1", "hide moreapp 1", "show moreapp 2", "hide moreapp 2", "show moreapp 3", "hide moreapp 3"};
static int moreapp_count = sizeof(moreapp_menu) / sizeof(moreapp_menu[0]);

static std::string offerwall_menu[] = {"show offerwall 1", "hide offerwall 1", "show offerwall 2", "hide offerwall 2", "show offerwall 3", "hide offerwall 3"};
static int offerwall_count = sizeof(offerwall_menu) / sizeof(offerwall_menu[0]);

static std::string analytics_menu[]= {"log event", "log error"};
static int analytics_count = sizeof(analytics_menu) / sizeof(analytics_menu[0]);

static std::string share_menu[]= {"share"};
static int share_count = sizeof(share_menu) / sizeof(share_menu[0]);

static std::string iap_menu[]= {"iap pay", "iap request"};
static int iap_count = sizeof(iap_menu) / sizeof(iap_menu[0]);

static std::string push_menu[]= {"start push", "stop push", "set alias", "del alias", "set tags", "del tags"};
static int push_count = sizeof(push_menu) / sizeof(push_menu[0]);

static std::string social_menu[]= {"submit score", "show leaderboard", "unlock achievement", "show achievements"};
static int social_count = sizeof(social_menu) / sizeof(social_menu[0]);

static Views* _instance = NULL;

static Menu* _secMenu = NULL;

Views* Views::getInstance()
{
	if (_instance == NULL)
	{
		_instance = Views::create();
	}
	return _instance;
}

bool Views::init()
{
    Size vSize = Director::getInstance()->getVisibleSize();
    
	CCLOG("views init");
    auto menu = Menu::create();
    float _x = 120;
    float _y = vSize.height - 60;
    float _h = 50;
    for (int i=0; i<g_testCount; i++) {
        Label* lb = Label::createWithSystemFont(base_menu[i], "", 26);
        auto item = MenuItemLabel::create(lb, CC_CALLBACK_1(Views::onClick, this));
        item->setTag(i);
        item->setPosition(_x, _y - i * _h);
        menu->addChild(item);
    }
    this->addChild(menu);
    menu->setPosition(0, 0);
    
    _secMenu = Menu::create();
    _secMenu->setPosition(0, 0);
    addChild(_secMenu);

    //init anysdk
    PluginChannel::getInstance()->loadPlugins();
    
	return true;
}

void Views::onClick(Ref* nd)
{
    int idx = ((Node*)nd)->getTag();
    CCLOG("click:%d", idx);
    
    if (idx>=ANALYTICS_LEVEL) {
        onAnalyticsOperation(idx-ANALYTICS_LEVEL);
    }
    else if (idx>=PUSH_LEVEL) {
        onPushOperation(idx-PUSH_LEVEL);
    }
    else if (idx>=SOCIAL_LEVEL){
        onSocialOperation(idx-SOCIAL_LEVEL);
    }
    else if (idx>=ADS_LEVEL){
        onAdsOperation(idx-ADS_LEVEL);
    }
    else if (idx>=SHARE_LEVEL){
        onShareOperation(idx-SHARE_LEVEL);
    }
    else if (idx>=IAP_LEVEL){
        onIAPOperation(idx-IAP_LEVEL);
    }
    else if (idx>=USER_LEVEL){
        onUserOperation(idx-USER_LEVEL);
    }
    else{
        switchView(idx);
    }
}

void Views::switchView(int idx)
{
    hideCurItems();
    
    switch (idx) {
        case USER_SYSTEM:
            addCurrentView(user_count, USER_LEVEL, user_menu);
            break;
        case IAP_SYSTEM:
            addCurrentView(iap_count,IAP_LEVEL,iap_menu);
            break;
        case SHARE_SYSTEM:
            addCurrentView(share_count,SHARE_LEVEL,share_menu);
            break;
        case ADS_SYSTEM:
            addCurrentView(ads_count,ADS_LEVEL,ads_menu);
            break;
        case PUSH_SYSTEM:
            addCurrentView(push_count,PUSH_LEVEL,push_menu);
            break;
        case SOCIAL_SYSTEM:
            addCurrentView(social_count,SOCIAL_LEVEL,social_menu);
            break;
        case ANALYTICS_SYSTEM:
            addCurrentView(analytics_count,ANALYTICS_LEVEL,analytics_menu);
            break;
    }
}

void Views::addCurrentView(int count, int lv, std::string arr[])
{
    float _x = Director::getInstance()->getVisibleSize().width/2;
    float _y = Director::getInstance()->getVisibleSize().height - 60;
    float _h = Director::getInstance()->getVisibleSize().height / 12;
    if (_h > 45) {
        _h = 45;
    }
    for (int i=0; i<count; i++) {
        Label* lb = Label::createWithSystemFont(arr[i], "", 26);
        auto item = MenuItemLabel::create(lb, CC_CALLBACK_1(Views::onClick, this));
        item->setPosition(_x, _y - i*_h);
        _secMenu->addChild(item);
        item->setTag(lv + i);
    }
}

void Views::hideCurItems()
{
    int count = _secMenu->getChildrenCount();
    if (count > 0) {
        _secMenu->removeAllChildren();
    }
}


void Views::onAnalyticsOperation(int idx)
{
    CCLOG("onAnalyticsOperation");
    Analytics* _analytics = Analytics::getInstance();
    switch (idx) {
        case LOG_EVENT:
           _analytics->logEvent("1001");
           _analytics->startSession();
           _analytics->stopSession();
           _analytics->logTimedEventBegin("1003");
           _analytics->logTimedEventEnd("1004");
           _analytics->isFunctionSupported("stopSession");
           _analytics->setSessionContinueMillis(100);
           _analytics->setCaptureUncaughtException(true);
            break;
        case LOG_ERROR:
           _analytics->logError("1003", "err msg!");
            break;
            
        default:
            break;
    }
}

void Views::onPushOperation(int idx)
{
    CCLOG("onPushOperation");
    Push* _push = Push::getInstance();
    switch (idx) {
        case START_PUSH:{
           _push->startPush();
        }
            break;
        case CLOSE_PUSH:
           _push->closePush();
            break;
        case SET_ALIAS:
           _push->setAlias();
            break;
        case DEL_ALIAS:
           _push->delAlias();
            break;
        case SET_TAGS:{
           _push->setTags();
        }
            break;
        case DEL_TAGS:{
           _push->delTags();
        }
            break;
    }
}

void Views::onSocialOperation(int idx)
{
    CCLOG("onSocialOperation");
   Social* _social = Social::getInstance();
    switch (idx) {
        case SUBMIT_SCORE:
           _social->submitScore();
            break;
        case SHOW_LEADERBOARD:
           _social->showLeaderboard();
            break;
        case UNLOCK_ACHIEVEMENT:{
           _social->unlockAchievement();
        }
            break;
        case SHOW_ACHIEVEMENTS:
           _social->showAchievements();
            break;
    }
}

void Views::onAdsOperation(int idx)
{
    CCLOG("onAdsOperation:%d", idx);
    if (idx >= ADS_OFFERWALL_LEVEL) {
        onOfferwallViews(idx-ADS_OFFERWALL_LEVEL);
        return;
    }
    if (idx >= ADS_MOREAPP_LEVEL) {
        onMoreappViews(idx-ADS_MOREAPP_LEVEL);
        return;
    }
    if (idx >= ADS_FULLSCREEN_LEVEL) {
        onFullscreenViews(idx-ADS_FULLSCREEN_LEVEL);
        return;
    }
    if (idx >= ADS_BANNER_LEVEL) {
        onBannerViews(idx-ADS_BANNER_LEVEL);
        return;
    }
    
    hideCurItems();
    
    switch (idx) {
        case ADS_BANNER:
            addCurrentView(banner_count,ADS_LEVEL+ADS_BANNER_LEVEL,banner_menu);
            break;
        case ADS_FULLSCREEN:
            addCurrentView(fullscreen_count,ADS_LEVEL+ADS_FULLSCREEN_LEVEL,fullscreen_menu);
            break;
        case ADS_MOREAPP:
            addCurrentView(moreapp_count,ADS_LEVEL+ADS_MOREAPP_LEVEL,moreapp_menu);
            break;
        case ADS_OFFERWALL:
            addCurrentView(offerwall_count,ADS_LEVEL+ADS_OFFERWALL_LEVEL,offerwall_menu);
            break;
    }
}

void Views::onShareOperation(int idx)
{
    CCLOG("onShareOperation");
   Share::getInstance()->share();
}

void Views::onIAPOperation(int idx)
{
    CCLOG("onIAPOperation");
    switch (idx) {
        case IAP_PAY:{
           PluginChannel::getInstance()->pay();
            break;
        }
        case IAP_REQUEST:{
            CCLOG("request iap product info.");
            
           PluginChannel::getInstance()->requestProducts();
        }
            break;
    }
}

void Views::onUserOperation(int idx)
{
    CCLOG("onUserOperation");
   PluginChannel* _user = PluginChannel::getInstance();
    switch (idx) {
        case USER_LOGIN:
           _user->login();
            break;
        case USER_LOGOUT:
           _user->logout();
            break;
        case USER_ENTERPLATFORM:
           _user->enterPlatform();
            break;
        case USER_SHOWTOOLBAR:
           _user->showToolBar(kToolBarBottomLeft);
            break;
        case USER_HIDETOOLBAR:
           _user->hideToolBar();
            break;
        case USER_ACCOUNTSWITCH:
           _user->accountSwitch();
            break;
        case USER_REALNAMEREGISTER:
           _user->realNameRegister();
            break;
        case USER_ANTIADDICTIONQUERY:
           _user->antiAddictionQuery();
            break;
        case USER_SUBMITLOGINGAMEROLE:{
           _user->submitLoginGameRole();
           std::string uid = _user->getUserId();
           CCLOG("userID is:%s", uid.c_str());
           std::string pid = _user->getPluginId();
           CCLOG("plugin ID is:%s", pid.c_str());
           std::string cid = _user->getChannelId();
           CCLOG("ChannelID is:%s", cid.c_str());
           std::string cparam = AgentManager::getInstance()->getCustomParam();
           CCLOG("CustomParam is:%s", cparam.c_str());
        }
            break;
    }
}


void Views::onBannerViews(int idx)
{
    CCLOG("onBannerViews:%d", idx);
    Ads* _ads = Ads::getInstance();
    CCLOG("check ads---");
    if (_ads == NULL) {
        return;
    }
    switch (idx) {
        case SHOW_BANNER_1:
            _ads->showAds(AD_TYPE_BANNER, 1);
            break;
        case HIDE_BANNER_1:
            _ads->hideAds(AD_TYPE_BANNER, 1);
            break;
        case SHOW_BANNER_2:
            _ads->showAds(AD_TYPE_BANNER, 2);
            break;
        case HIDE_BANNER_2:
            _ads->hideAds(AD_TYPE_BANNER, 2);
            break;
        case SHOW_BANNER_3:
            _ads->showAds(AD_TYPE_BANNER, 3);
            break;
        case HIDE_BANNER_3:
            _ads->hideAds(AD_TYPE_BANNER, 3);
            break;
        case SHOW_BANNER_4:
            _ads->showAds(AD_TYPE_BANNER, 4);
            break;
        case HIDE_BANNER_4:
            _ads->hideAds(AD_TYPE_BANNER, 4);
            break;
        case SHOW_BANNER_5:
            _ads->showAds(AD_TYPE_BANNER, 5);
            break;
        case HIDE_BANNER_5:
            _ads->hideAds(AD_TYPE_BANNER, 5);
            break;
    }
}

void Views::onFullscreenViews(int idx)
{
    CCLOG("onFullscreenViews:%d", idx);
    Ads* _ads = Ads::getInstance();
    if (_ads == NULL) {
        return;
    }
    switch (idx) {
        case SHOW_FULLSCREEN_1:
            _ads->showAds(AD_TYPE_FULLSCREEN, 1);
            break;
        case HIDE_FULLSCREEN_1:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 1);
            break;
        case SHOW_FULLSCREEN_2:
            _ads->showAds(AD_TYPE_FULLSCREEN, 2);
            break;
        case HIDE_FULLSCREEN_2:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 2);
            break;
        case SHOW_FULLSCREEN_3:
            _ads->showAds(AD_TYPE_FULLSCREEN, 3);
            break;
        case HIDE_FULLSCREEN_3:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 3);
            break;
    }
}

void Views::onMoreappViews(int idx)
{
    CCLOG("onMoreappViews:%d", idx);
    Ads* _ads = Ads::getInstance();
    if (_ads == NULL) {
        return;
    }
    switch (idx) {
        case SHOW_FULLSCREEN_1:
            _ads->showAds(AD_TYPE_FULLSCREEN, 1);
            break;
        case HIDE_FULLSCREEN_1:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 1);
            break;
        case SHOW_FULLSCREEN_2:
            _ads->showAds(AD_TYPE_FULLSCREEN, 2);
            break;
        case HIDE_FULLSCREEN_2:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 2);
            break;
        case SHOW_FULLSCREEN_3:
            _ads->showAds(AD_TYPE_FULLSCREEN, 3);
            break;
        case HIDE_FULLSCREEN_3:
            _ads->hideAds(AD_TYPE_FULLSCREEN, 3);
            break;
    }
}

void Views::onOfferwallViews(int idx)
{
    CCLOG("onOfferwallViews:%d", idx);
    Ads* _ads = Ads::getInstance();
    if (_ads == NULL) {
        return;
    }
    switch (idx) {
        case SHOW_OFFERWALL_1:
            _ads->showAds(AD_TYPE_OFFERWALL, 1);
            break;
        case HIDE_OFFERWALL_1:
            _ads->hideAds(AD_TYPE_OFFERWALL, 1);
            break;
        case SHOW_OFFERWALL_2:
            _ads->showAds(AD_TYPE_OFFERWALL, 2);
            break;
        case HIDE_OFFERWALL_2:
            _ads->hideAds(AD_TYPE_OFFERWALL, 2);
            break;
        case SHOW_OFFERWALL_3:
            _ads->showAds(AD_TYPE_OFFERWALL, 3);
            break;
        case HIDE_OFFERWALL_3:
            _ads->hideAds(AD_TYPE_OFFERWALL, 3);
            break;
    }
}

