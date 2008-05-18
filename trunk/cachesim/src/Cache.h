#ifndef CACHE_H_
#define CACHE_H_
#include "Memory.h"
#include <vector>
#include <set>
#include <map>

class Cache
{
public:
	Cache(uint tS, uint ass, uint bS);
	virtual ~Cache();
	uint read(uint memAddress);
	void write(uint value, uint memAddress);
	uint getMissCounter();
	void clear();
	
private:
	uint totalSize;
	uint associativity;
	uint blockSize;
	//std::vector<uint> content;
	//Memory* memPointer;
	std::map<uint,uint> blockMap;
	std::map<uint,uint> invMap;
	//std::set<uint> dirties;
	void replace(uint memAddress);
	uint missCounter;
	
};

#endif /*CACHE_H_*/
