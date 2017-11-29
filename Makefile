#
# Makefile for prosody
#

CXX = g++

prosody: main.cpp ProsodyClassifier.cpp ProsodyClassifier.h
	${CXX} `pkg-config --cflags --libs opencv` -o main main.cpp ProsodyClassifier.cpp
