LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

TIGRE					:=	../../../../../tigre
TIGRESRC				:=	$(TIGRE)/src

LOCAL_MODULE 			:= 	tigre

LOCAL_C_INCLUDES 		:= 	$(TIGRE)/local $(TIGRE)/local/soil/src $(TIGRESRC)

LOCAL_SRC_FILES 		:= 	../$(TIGRESRC)/core/file.cpp \
							../$(TIGRESRC)/core/string.cpp \
							../$(TIGRESRC)/core/Resource.cpp \
							../$(TIGRESRC)/core/Exceptions.cpp \
							../$(TIGRESRC)/core/Timer.cpp \
							../$(TIGRESRC)/core/Logger/AndroidLogger.cpp \
							../$(TIGRESRC)/game/Game.cpp \
							../$(TIGRESRC)/game/Content.cpp \
							../$(TIGRESRC)/game/Sphere.cpp \
							../$(TIGRESRC)/gfx/Display/AndroidDisplay.cpp \
							../$(TIGRESRC)/gfx/Context/OpenGLContext.cpp \
							../$(TIGRESRC)/gfx/Renderer/OpenGLRenderer.cpp \
							../$(TIGRESRC)/gfx/Shader.cpp \
							../$(TIGRESRC)/gfx/ModelMesh.cpp \
							../$(TIGRESRC)/gfx/Mesh.cpp \
							../$(TIGRESRC)/gfx/Color.cpp \
							../$(TIGRESRC)/gfx/Image.cpp \
							../$(TIGRESRC)/gfx/Texture2D.cpp \
							../$(TIGRESRC)/gfx/ImageLoader.cpp \
							../$(TIGRESRC)/gfx/Rectangle.cpp \
							../$(TIGRESRC)/os/android/Activity.cpp \
							../$(TIGRESRC)/os/android/activity.cpp

LOCAL_STATIC_LIBRARIES 	+= 	soil android_native_app_glue

include $(BUILD_STATIC_LIBRARY)

include $(LOCAL_PATH)/Soil.mk

$(call import-module, android/native_app_glue)
