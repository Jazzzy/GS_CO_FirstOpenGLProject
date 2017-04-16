#include "sound.h"

char* sound::loadWAV(const char* filename,int& ochannels,int& osampleRate,int& osamplesPerSecond,int& osize)
{
	std::ifstream in(filename,std::ios::binary);
	char tmpBuffer[4];
	in.read(tmpBuffer,4);
	if(strncmp(tmpBuffer,"RIFF",4)!=0)
	{
		std::cout << "This is not a valid WAV file (1) " << tmpBuffer[0] << tmpBuffer[1] << tmpBuffer[2] << tmpBuffer[3] << tmpBuffer[4] << '\n'; 
		return 0;
	}
	in.read(tmpBuffer,4);
	int sizeInBytes=convertToInt(tmpBuffer,4);
	in.read(tmpBuffer,4);
	if(strncmp(tmpBuffer,"WAVE",4)!=0)
	{
		std::cout << "This is not a valid WAV file (2) " << tmpBuffer[0] << tmpBuffer[1] << tmpBuffer[2] << tmpBuffer[3] << tmpBuffer[4] << '\n'; 
		return 0;
	}
	in.read(tmpBuffer,4);
	if(strncmp(tmpBuffer,"fmt ",4)!=0)
	{
		std::cout << "This is not a valid WAV file (3) " << tmpBuffer[0] << tmpBuffer[1] << tmpBuffer[2] << tmpBuffer[3] << tmpBuffer[4] << '\n'; 
		return 0;
	}	
	in.read(tmpBuffer,4);
	int fmtSize=convertToInt(tmpBuffer,4);
	if(fmtSize!=16)
	{
		std::cout << "Sorry only PCM (not compressed WAV)" << fmtSize << '\n'; 
		return 0;		
	}
	in.read(tmpBuffer,2);
	int PCM=convertToInt(tmpBuffer,2);
	if(PCM!=1)
	{
		std::cout << "Sorry only PCM (not compressed WAV)\n"; 
		return 0;	
	}
	in.read(tmpBuffer,2);
	int channels=convertToInt(tmpBuffer,2);
	in.read(tmpBuffer,4);
	int samples=convertToInt(tmpBuffer,4);
	in.read(tmpBuffer,4);
	int byteRate=convertToInt(tmpBuffer,4);
	in.read(tmpBuffer,2);
	int blockAlign=convertToInt(tmpBuffer,2);
	in.read(tmpBuffer,2);
	int bitsPerSample=convertToInt(tmpBuffer,2);
	in.read(tmpBuffer,4);
	if(strncmp(tmpBuffer,"data",4)!=0)
	{
		std::cout << "This is not a valid WAV file (4) " << tmpBuffer[0] << tmpBuffer[1] << tmpBuffer[2] << tmpBuffer[3] << '\n'; 
	//	return 0;
	}		
	in.read(tmpBuffer,4);
	int dataSize=convertToInt(tmpBuffer,4);
	if(dataSize<=0)
	{
		std::cout << "This is not a valid WAV file (4) " << dataSize << '\n'; 
		return 0;	
	}	
	char* data=new char[dataSize];
	in.read(data,dataSize);
	//std::cout << sizeInBytes << ' ' << fmtSize << ' ' << channels << ' ' << samples << ' ' << byteRate << ' ' << blockAlign << ' ' << bitsPerSample << ' ' << dataSize << std::endl;
	ochannels=channels;
	osampleRate=bitsPerSample;
	osamplesPerSecond=samples;
	osize=dataSize;
	
	return data;	
}

int sound::convertToInt(const char* data,int len)
{
	int a=0;
	if(!bigEndian)
		for(int i=0;i<len;i++)
			((char*)&a)[i]=data[i];
	else
		for(int i=0;i<len;i++)
			((char*)&a)[sizeof(int)-i-1]=data[i];		
	return a;
}

bool sound::isBigEndian()
{
	int a=1;
	return (((unsigned char*)&a)[0]==0);
}

sound::sound()
{
	bigEndian=isBigEndian();
	device=alcOpenDevice(NULL);
	if(device==NULL)
	{
		std::cout << "couldn't open device" << std::endl;
		context=NULL;
		return;
	}
	context=alcCreateContext(device,NULL);
	if(context==NULL)
	{
		std::cout << "couldn't open context" << std::endl;
		return;
	}
	alcMakeContextCurrent(context);
}

sound::~sound()
{
	for(int i=0;i<datas.size();i++)
	{
			alDeleteSources(1,&datas[i].sourceid);
			alDeleteBuffers(1,&datas[i].bufferid);
			delete[] datas[i].buffer;
	}
	alcDestroyContext(context);
	alcCloseDevice(device);
}

unsigned int sound::loadSound(const char* filename,float minGain,float maxGain)
{
	unsigned int sourceid;
	int channel,sampleRate,samplesPerSecond,size;
	alGenSources(1,&sourceid);
	char* bufferdata=loadWAV(filename,channel,sampleRate,samplesPerSecond,size);
	unsigned int bufferid;
	alGenBuffers(1,&bufferid);
	int format;
	if(channel==1)
	{
		if(sampleRate==8)
			format=AL_FORMAT_MONO8;
		else
			format=AL_FORMAT_MONO16;
	}else{
		if(sampleRate==8)
			format=AL_FORMAT_STEREO8;
		else
			format=AL_FORMAT_STEREO16;		
	}
	alBufferData(bufferid,format,bufferdata,size,samplesPerSecond);
	alSourcei(sourceid,AL_BUFFER,bufferid);
	alSourcef(sourceid,AL_MIN_GAIN,minGain);
	alSourcef(sourceid,AL_MAX_GAIN,maxGain);
	alSourcei(sourceid,AL_SOURCE_RELATIVE,AL_TRUE);
	datas.push_back(data(sourceid,bufferid,bufferdata));
	return sourceid;
}

void sound::deleteSound(unsigned int id)
{
	for(int i=0;i<datas.size();i++)
		if(datas[i].sourceid==id)
		{
			alSourcei(datas[i].sourceid,AL_BUFFER,NULL);
			alDeleteBuffers(1,&datas[i].bufferid);
			delete[] datas[i].buffer;
			alDeleteSources(1,&datas[i].sourceid);
			datas.erase(datas.begin()+i);
			return;
		}
}

void sound::playSound(unsigned int id)
{
	alSourcePlay(id);
}

void sound::playSound(unsigned int id, const Vec3f& position)
{
	alSource3f(id,AL_POSITION,position[0],position[1],position[2]);
	alSourcePlay(id);

}

void sound::playSound(unsigned int id, const Vec3f& position, const Vec3f& velocity)
{
	alSource3f(id,AL_POSITION,position[0],position[1],position[2]);
	alSource3f(id,AL_VELOCITY,velocity[0],velocity[1],velocity[2]);
	alSourcePlay(id);
}

void sound::playSound(unsigned int id, const Vec3f& position, const Vec3f& velocity, float gain, bool loop)
{
	alSource3f(id,AL_POSITION,position[0],position[1],position[2]);
	alSource3f(id,AL_VELOCITY,velocity[0],velocity[1],velocity[2]);
	alSourcef(id,AL_GAIN,gain);
	alSourcePlay(id);
}

void sound::playSound(unsigned int id,bool loop)
{
	alSourcei(id, AL_LOOPING, loop);
	alSourcePlay(id);
}


void sound::stopSound(unsigned int id)
{
	alSourceStop(id);
}

void sound::setListener(const Vec3f& position, const Vec3f& orientation)
{
	alListener3f(AL_POSITION,position[0],position[1],position[2]);
	float f[]={orientation[0],orientation[1],orientation[2],0,1,0};
	alListenerfv(AL_ORIENTATION,f);
}
