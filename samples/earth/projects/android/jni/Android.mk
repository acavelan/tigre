# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

TIGRE					:=	../../../../../tigre
TIGRESRC				:=	$(TIGRE)/src

ROOT					:=	../..
ROOTSRC					:=	$(ROOT)/src

# Application
LOCAL_MODULE 			:= 	libTigre

LOCAL_C_INCLUDES 		:= 	$(TIGRE)/local $(TIGRESRC) $(ROOTSRC)

LOCAL_SRC_FILES 		:= 	../$(ROOTSRC)/launchers/android/main.cpp \
							../$(ROOTSRC)/launchers/android/EarthActivity.cpp \
							../$(ROOTSRC)/Earth.cpp

LOCAL_LDLIBS 			+= 	-llog -landroid -lEGL -lGLESv2

LOCAL_STATIC_LIBRARIES 	+= 	tigre android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/Tigre.mk

$(call import-module, android/native_app_glue)
