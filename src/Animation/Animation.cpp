#include "stdafx.h"
#include "Animation.h"

Animation::Animation()
{
	this->m_speed = 1.0f;
}

void Animation::setId(unsigned int id)
{
	this->m_id = id;
}

void Animation::setName(std::string name)
{
	this->m_Name = name;
}

void Animation::setNumChannels(int numChannels)
{
	this->m_numChannels = numChannels;
}

void Animation::addChannel(std::pair<std::string, Channel> channel)
{
	std::pair<std::string, Channel> pair = { channel.first, channel.second };
	this->m_channels.insert(pair);
}

void Animation::setDuration(double duration) 
{
	this->m_duration = duration;
}

void Animation::setTicksPerSecond(double ticksPerSecond)
{
	this->m_ticksPerSecond = ticksPerSecond;
}

void Animation::setSpeed(float speed)
{
	this->m_speed = speed;
}

unsigned int  Animation::getId()
{
	return this->m_id;
}

std::string  Animation::getName()
{
	return this->m_Name;
}

int  Animation::getNumChannels()
{
	return this->m_numChannels;
}

double  Animation::getDuration()
{
	return this->m_duration;
}

double  Animation::getTicksPerSecond()
{
	return this->m_ticksPerSecond;
}

float  Animation::getSpeed()
{
	return this->m_speed;
}

Channel  Animation::getChannel(std::string name)
{
	return this->m_channels[name];
}

std::map<std::string, Channel> Animation::getChannels()
{
	return this->m_channels;
}


glm::mat4 Animation::InterpolateKeyFrames(std::string strChannel, float fTime)
{
    glm::vec3 vInterPos;
	glm::vec3 vInterScale;
	glm::quat qInterRot;
	float fTicksInFloat =  (this->m_ticksPerSecond/1000000.0)*fTime;
	
	
		//check if time for animation is over then interpolate between last and first frame
		if (fTicksInFloat > this->m_channels[strChannel].fTimeStamp[this->m_channels[strChannel].v3KeyPositions.size() - 1])
		{

			float fDelta = fTicksInFloat - this->m_channels[strChannel].fTimeStamp[this->m_channels[strChannel].v3KeyPositions.size() - 1];
			float fFactor = fDelta / (float(this->m_channels[strChannel].fTimeStamp[0] - this->m_channels[strChannel].fTimeStamp[this->m_channels[strChannel].v3KeyPositions.size() - 1]));
			vInterPos = fFactor * this->m_channels[strChannel].v3KeyPositions[0] + (1 - fFactor)*this->m_channels[strChannel].v3KeyPositions[this->m_channels[strChannel].v3KeyPositions.size() - 1];
			vInterScale = fFactor * this->m_channels[strChannel].v3KeyScales[0] + (1 - fFactor)*this->m_channels[strChannel].v3KeyScales[this->m_channels[strChannel].v3KeyPositions.size() - 1];
			qInterRot = glm::slerp(this->m_channels[strChannel].qKeyRotations[this->m_channels[strChannel].v3KeyPositions.size() - 1], this->m_channels[strChannel].qKeyRotations[0], fFactor);
		}
		//else interpolate between last and next frame
		else
			for (unsigned int i = 1; i <= this->m_channels[strChannel].v3KeyPositions.size() - 1; i++)
			{

				if (this->m_channels[strChannel].fTimeStamp[i] > fTicksInFloat)
				{


					float fDelta = fTicksInFloat - this->m_channels[strChannel].fTimeStamp[i - 1];
					float fFactor = fDelta / (float(this->m_channels[strChannel].fTimeStamp[i] - this->m_channels[strChannel].fTimeStamp[i - 1]));

					vInterPos = fFactor * this->m_channels[strChannel].v3KeyPositions[i] + (1 - fFactor)*this->m_channels[strChannel].v3KeyPositions[i - 1];
					vInterScale = fFactor * this->m_channels[strChannel].v3KeyScales[i] + (1 - fFactor)*this->m_channels[strChannel].v3KeyScales[i - 1];
					qInterRot = glm::slerp(this->m_channels[strChannel].qKeyRotations[i - 1], this->m_channels[strChannel].qKeyRotations[i], fFactor);
					break;
				}

			}
	
    return glm::translate(glm::mat4(1.0f),vInterPos)*glm::toMat4(qInterRot)*glm::scale(vInterScale);
}