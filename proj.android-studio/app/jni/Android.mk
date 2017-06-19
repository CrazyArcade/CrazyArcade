LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/Controller/GameController.cpp \
                   ../../../Classes/Controller/RoomController.cpp \
                   ../../../Classes/Manager/BubbleManager.cpp \
                   ../../../Classes/Manager/PlayerManager.cpp \
                   ../../../Classes/Manager/PropManager.cpp \
                   ../../../Classes/Model/Bubble.cpp \
                   ../../../Classes/Model/Entity.cpp \
                   ../../../Classes/Model/Player.cpp \
                   ../../../Classes/Model/Prop.cpp \
                   ../../../Classes/Network/Client.cpp \
                   ../../../Classes/Operator/Rocker.cpp \
                   ../../../Classes/Operator/KeyBoard.cpp \
                   ../../../Classes/Operator/Operator.cpp \
                   ../../../Classes/Scene/GameScene.cpp \
                   ../../../Classes/Scene/HelloWorldScene.cpp \
                   ../../../Classes/Scene/HelpScene.cpp \
                   ../../../Classes/Scene/LoadingScene.cpp \
                   ../../../Classes/Scene/LoginScene.cpp \
                   ../../../Classes/Scene/RoomScene.cpp \
                   ../../../Classes/Scene/SettingsScene.cpp \
                   ../../../Classes/Scene/StartScene.cpp \
                   ../../../Classes/Scene/UI/ChatBox.cpp \
                   ../../../Classes/Scene/UI/CheckBox.cpp \
                   ../../../Classes/Scene/UI/GameMap.cpp \
                   ../../../Classes/Scene/UI/ResultBox.cpp \
                   ../../../Classes/Scene/UI/RoleBox.cpp \
                   ../../../Classes/Scene/UI/UserBox.cpp \
                   ../../../Classes/Util/AnimationLoader.cpp \
                   ../../../Classes/Util/GameAudio.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
