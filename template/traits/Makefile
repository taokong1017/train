.PHONY : all clean

# 命令
CXX := g++
MKDIR := mkdir
RM := rm -rf

# 库和头文件
INCS := 
LIBS :=

# FLAGS
CXXFLAGS = -g -Wall -std=c++11
LDDFLAGS =

# 目录
DIRS := $(shell find . -maxdepth 3 -type d)
SRCS := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))

OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

EXE := test

all : $(EXE)
	@echo make $(EXE) finished

%.o : %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCS)

%.d : %.cpp
	$(CXX) -MM -c $< -o $@ $(CXXFLAGS) $(INCS)

$(EXE) : $(OBJS)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(LDDFLAGS) $(LIBS)

include $(DEPS)

clean:
	$(RM) $(EXE) $(OBJS) $(DEPS)

























