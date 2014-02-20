LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

SRC						:=	../../local/soil/src

LOCAL_MODULE 			:= 	soil

LOCAL_C_INCLUDES 		:= 	$(TIGRE)/local/soil/src

LOCAL_SRC_FILES 		:= 	$(SRC)/SOIL.c \
							$(SRC)/stb_image_aug.c \
							$(SRC)/image_helper.c \
							$(SRC)/image_DXT.c

include $(BUILD_STATIC_LIBRARY)
