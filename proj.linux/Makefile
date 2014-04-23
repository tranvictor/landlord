EXECUTABLE = landlord

USE_BOX2D=1

COCOS_ROOT = ../../..

INCLUDES = -I.. -I../Classes -I. -I../../../extensions -I../../../external -I../../../external/Box2D

TESTS_SRC = tests/StartScene_Test.cpp
CLASSES_SRC = ./Classes/AppDelegate.cpp ../Classes/StartScene.cpp

SOURCES = main.cpp gtest/gtest-all.cpp $(TESTS_SRC) $(CLASSES_SRC) 
#../Classes/AppDelegate.cpp ../Classes/StartScene.cpp

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lbox2d -lextension
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libextension.a

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
