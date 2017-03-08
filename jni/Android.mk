LOCAL_PATH := $(call my-dir)

#include $(CLEAR_VARS)
#LOCAL_MODULE := libosterhoutgroup_ext.a
#LOCAL_SRC_FILES := osterhoutgroup_ext/libosterhoutgroup_ext.a
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/osterhoutgroup_ext/include
#include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE := libosterhoutgroup_ext.so
#LOCAL_SRC_FILES := osterhoutgroup_ext/libosterhoutgroup_ext.so
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/osterhoutgroup_ext/include
#include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := TeapotNativeActivity
LOCAL_SRC_FILES := TeapotNativeActivity.cpp \
		   TeapotRenderer.cpp \

LOCAL_C_INCLUDES :=
LOCAL_CFLAGS :=
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -lGLESv3 -lGLESv1_CM
LOCAL_STATIC_LIBRARIES := cpufeatures android_native_app_glue ndk_helper
#LOCAL_SHARED_LIBRARIES := libosterhoutgroup_ext.so
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/ndk_helper)
$(call import-module,android/native_app_glue)
$(call import-module,android/cpufeatures)
