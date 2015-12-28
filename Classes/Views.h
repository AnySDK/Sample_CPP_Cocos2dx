#ifndef __VIEWS_LAYER_H__
#define __VIEWS_LAYER_H__

#include "cocos2d.h"
#include "const.h"

USING_NS_CC;

class Views : public Layer
{
public:
	static Views* getInstance();

    CREATE_FUNC(Views);
    
	bool init();
private:
    void onClick(Ref* nd);
    void switchView(int idx);
    void addCurrentView(int count, int lv, std::string arr[]);
    void hideCurItems();
    
    void onRECOperation(int idx);
    void onCrashOperation(int idx);
    void onAnalyticsOperation(int idx);
    void onPushOperation(int idx);
    void onSocialOperation(int idx);
    void onAdsOperation(int idx);
    void onShareOperation(int idx);
    void onIAPOperation(int idx);
    void onUserOperation(int idx);
    
    void onBannerViews(int idx);
    void onFullscreenViews(int idx);
    void onMoreappViews(int idx);
    void onOfferwallViews(int idx);
};

#endif //__VIEWS_LAYER_H__
