#pragma once
#include <map>
#include <string>


class GarbageCollector
{
public:
	GarbageCollector();
	void AddToGarbage(const std::string& garbage);
	void PrintGarbage();

private:
	std::map<int, std::string> m_Garbage;
};