LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)





LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/MyNode.h \
				   ../../Classes/Line.h \
				   ../../Classes/City.h \
				   ../../Classes/Guide.h \
				   ../../Classes/GuideLayerScene.cpp \
				   ../../Classes/NewCityScene.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/CreateNodeLayer.cpp \
				   ../../Classes/CreateLineLayer.cpp \
				   ../../Classes/CityMap.cpp \
				   ../../Classes/GuideConfirmLayer.cpp \
				   ../../Classes/LineInfoLayer.cpp \
				   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += libiconv_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
$(call import-module,libiconv)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
