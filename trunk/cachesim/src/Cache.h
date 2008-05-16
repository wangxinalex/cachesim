#ifndef CACHE_H_
#define CACHE_H_
#include "Memory.h"
#include <vector>
#include <set>
#include <map>

class Cache
{
public:
	Cache();
	virtual ~Cache();
	char read(uint memAddress);
	bool write(char value, uint memAddress);
	
private:
	int totalSize;
	int associativity;
	int blockSize;
	std::vector<int> content;
	Memory* memPointer;
	std::map<uint,uint> blockMap;
	std::set<uint> dirties;
	void replace(uint memAddress);
	
};

#endif /*CACHE_H_*/
