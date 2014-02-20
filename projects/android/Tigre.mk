LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

SRC						:=	../../src

LOCAL_MODULE 			:= 	tigre

LOCAL_C_INCLUDES 		:= 	$(TIGRE)/local $(TIGRE)/local/soil/src $(TIGRESRC)

LOCAL_SRC_FILES 		:= 	$(SRC)/core/file.cpp \
							$(SRC)/core/string.cpp \
							$(SRC)/core/Resource.cpp \
							$(SRC)/core/Exceptions.cpp \
							$(SRC)/core/Timer.cpp \
							$(SRC)/core/Logger/AndroidLogger.cpp \
							$(SRC)/gfx/Display/AndroidDisplay.cpp \
							$(SRC)/gfx/Context/OpenGLContext.cpp \
							$(SRC)/gfx/Renderer/OpenGLRenderer.cpp \
							$(SRC)/gfx/Shader.cpp \
							$(SRC)/gfx/ModelMesh.cpp \
							$(SRC)/gfx/Mesh.cpp \
							$(SRC)/gfx/Color.cpp \
							$(SRC)/gfx/Image.cpp \
							$(SRC)/gfx/Texture2D.cpp \
							$(SRC)/gfx/ImageLoader.cpp \
							$(SRC)/gfx/Rectangle.cpp \
							$(SRC)/gfx/Sphere.cpp \
							$(SRC)/os/android/Activity.cpp \
							$(SRC)/os/android/android.cpp \
							$(SRC)/hl/RenderView.cpp \
							$(SRC)/hl/Content.cpp \

LOCAL_STATIC_LIBRARIES 	+= 	soil android_native_app_glue

include $(BUILD_STATIC_LIBRARY)

include $(LOCAL_PATH)/Soil.mk

$(call import-module, android/native_app_glue)
