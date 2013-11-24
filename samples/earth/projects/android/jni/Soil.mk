LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

TIGRE					:=	../../../../../tigre
SOILSRC					:=	$(TIGRE)/local/soil/src

LOCAL_MODULE 			:= 	soil

LOCAL_C_INCLUDES 		:= 	$(SOILSRC)

LOCAL_SRC_FILES 		:= 	../$(SOILSRC)/SOIL.c \
							../$(SOILSRC)/stb_image_aug.c \
							../$(SOILSRC)/image_helper.c \
							../$(SOILSRC)/image_DXT.c

include $(BUILD_STATIC_LIBRARY)
