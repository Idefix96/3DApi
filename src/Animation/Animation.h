#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "types.h"

struct Channel
{
    std::vector<glm::mat4> vKeyPositions;
    std::vector<glm::mat4> mKeyRotations;    
    std::vector<glm::mat4> vKeyScales;
    std::vector<glm::vec3> v3KeyPositions;
    std::vector<glm::quat> qKeyRotations;    
    std::vector<glm::vec3> v3KeyScales;
    std::vector<double> fTimeStamp;
	glm::mat4 animationTransformation;
};

class Animation
{

private:
    unsigned int m_id;
    std::string m_Name;
    int m_numChannels;
    std::map<std::string, Channel> m_channels;
    double m_duration;
    double m_ticksPerSecond;
	float m_speed;

public:
	Animation();
    glm::mat4 InterpolateKeyFrames(std::string strChannel, float fTime);
	void setId(unsigned int id);
	void setName(std::string name);
	void setNumChannels(int numChannels);
	void addChannel(std::pair<std::string, Channel> channel);
	void setDuration(double duration);
	void setTicksPerSecond(double ticksPerSecond);
	void setSpeed(float speed);
	unsigned int getId();
	std::string getName();
	int getNumChannels();
	double getDuration();
	double getTicksPerSecond();
	float getSpeed();
	Channel getChannel(std::string name);
	std::map<std::string, Channel> getChannels();
};

#endif
