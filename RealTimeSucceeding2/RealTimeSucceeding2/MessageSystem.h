#pragma once
#include <iostream>
#include <vector>
#include "Vec2.h"


class GameObject;
class RTSUnit;

struct message
{
	GameObject* sender;
	RTSUnit* unit_sender;
	std::string mess;
	int I_target;
	std::string S_target;
	int sendvalue;
	CVector2 sendvalue_Vec;
	// Message for sending from a GameObject
	message(GameObject* theSender, std::string message) : sender(theSender), mess(message) {};
	// Sends a vector from a GameObject
	message(GameObject* thesender, std::string message, CVector2 value) : sender(thesender), mess(message), sendvalue_Vec(value) {};
	// Sends a value to a specific ID.
	message(GameObject* thesender, std::string message, CVector2 value, int ID) : sender(thesender), mess(message), sendvalue_Vec(value), I_target(ID) {};
	// Message for sending from a RTSUnit Specifically
	message(RTSUnit* thesender, std::string message) : unit_sender(thesender), mess(message) {};
	// Message for sending from a RTSUnit Specifically. Also sends a value.
	message(RTSUnit* thesender, std::string message, int value) : unit_sender(thesender), mess(message), sendvalue(value) {};
	// sending from a renderable to a another by ID.
	message(GameObject* theSender, std::string message, int I_target) : sender(theSender), mess(message), I_target(I_target) {};
	// Sending a message to another using a string
	message(GameObject* theSender, std::string message, std::string S_target) : sender(theSender), mess(message), S_target(S_target) {};

};

class MessageSystem
{
public:
	static MessageSystem& GetInstance();
	void sendMessage(std::string mes, GameObject* sender);
	void sendMessage(std::string mes, GameObject* sender, int I_target);
	void sendMessage(std::string mes, RTSUnit* sender, int I_target);
	void sendMessage(std::string mes, GameObject* sender, int ID, CVector2 value);

	void sendMessage(std::string mes, GameObject* sender, CVector2 value);
	message* getMessage(int i);
	unsigned int QueSize() { return messageQue.size(); }
	void doneReading() { messageQue.clear(); }
	void Kill();
	std::vector<std::string> split(std::string str, std::string delim);


private:
	MessageSystem();
	~MessageSystem();
	static MessageSystem* _instance;
	std::vector<message*> messageQue;


};

#define MESSAGE MessageSystem::GetInstance()


