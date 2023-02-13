#include "GarbageCollector.h"
#include <iostream>
#include <sstream>


GarbageCollector::GarbageCollector()
{
}

void GarbageCollector::AddToGarbage(const std::string& garbage)
{
	int id = std::stoi(garbage.substr(4));
	m_Garbage[id] = garbage;
}

void GarbageCollector::PrintGarbage()
{
	std::cout << "List of deleted objects:\n";
	for (auto g : m_Garbage)
		std::cout << g.second << std::endl;
}
