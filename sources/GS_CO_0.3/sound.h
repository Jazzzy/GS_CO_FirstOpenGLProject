#ifndef SOUND_H
#define SOUND_H
#include <iostream>
#include <al\al.h>
#include <al\alc.h>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "vec3f.h"

class sound{
	struct data{
		unsigned int sourceid;
		unsigned int bufferid;
		char* buffer;
		data(unsigned int si,unsigned int bi,char* buff) : sourceid(si),bufferid(bi),buffer(buff) {}
	};
	std::vector<data> datas;
	ALCcontext* context;
	ALCdevice* device;
	bool bigEndian;
	char* loadWAV(const char* filename,int& ochannels,int& osampleRate,int& osamplesPerSecond,int& osize);
	int convertToInt(const char* data,int len);
	bool isBigEndian();
	public:
		sound();
		~sound();
		unsigned int loadSound(const char* filename,float minGain=0,float maxGain=1.0);
		void deleteSound(unsigned int id);
		void playSound(unsigned int id);
		void playSound(unsigned int id,bool loop);
		void playSound(unsigned int id,const Vec3f& position);
		void playSound(unsigned int id, const Vec3f& position, const Vec3f& velocity);
		void playSound(unsigned int id, const Vec3f& position, const Vec3f& velocity, float gain, bool loop);
		void stopSound(unsigned int id);
		void setListener(const Vec3f& position, const Vec3f& orientation);
		
};

#endif
