LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/Views.cpp \
                   ../../Classes/Ads.cpp \
                   ../../Classes/Analytics.cpp \
                   ../../Classes/PluginChannel.cpp \
                   ../../Classes/Push.cpp \
                   ../../Classes/Share.cpp \
                   ../../Classes/Social.cpp \
                   ../../Classes/REC.cpp   \
                   ../../Classes/Crash.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					../protocols_c++_static/include \
					../protocols_c++_static/android

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES := PluginProtocolStatic

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,protocols_c++_static/android)
