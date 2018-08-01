#include "MessageSystem.h"


MessageSystem *MessageSystem::_instance{ nullptr };

MessageSystem &MessageSystem::GetInstance()
{
	if (_instance == nullptr)
		_instance = new MessageSystem;
	return *_instance;
}


MessageSystem::MessageSystem()
{
}


MessageSystem::~MessageSystem()
{
}

std::vector<std::string> MessageSystem::split(std::string str, std::string delim)
{
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	char* delim_c = const_cast<char*>(delim.c_str());
	std::vector<std::string> list;
	char* context = NULL;
	
	current = strtok_s(cstr, delim.c_str(),&context);
	while (current != NULL)
	{
		list.push_back(current);
		current = strtok_s(NULL, delim.c_str(),&context);
	}
	
	return list;
}

void MessageSystem::sendMessage(std::string mes, GameObject* sender)
{
	message* newMessage = new message(sender, mes);
	messageQue.push_back(newMessage);

}

void MessageSystem::sendMessage(std::string mes, GameObject* sender, int ID)
{
	message* newMessage = new message(sender, mes, ID);
	messageQue.push_back(newMessage);

}

void MessageSystem::sendMessage(std::string mes, RTSUnit* sender, int ID)
{
	message* newMessage = new message(sender, mes, ID);
	messageQue.push_back(newMessage);
}

void MessageSystem::sendMessage(std::string mes, GameObject* sender, CVector2 value)
{
	message* newMessage = new message(sender, mes, value);
	messageQue.push_back(newMessage);
}

void MessageSystem::sendMessage(std::string mes, GameObject* sender, int ID, CVector2 value)
{
	message* newMessage = new message(sender, mes, value, ID);
	messageQue.push_back(newMessage);
}


message* MessageSystem::getMessage(int i)
{
	return messageQue[i];
}


void MessageSystem::Kill()
{
	delete this;
}
