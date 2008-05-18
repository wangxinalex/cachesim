#ifndef MEMORY_H_
#define MEMORY_H_
#include <vector>

class Memory
{
public:
	Memory();
	virtual ~Memory();
	std::vector<uint> read(uint address, uint blockSize);
	bool write(uint address, uint content);
	
	
private:
	std::vector<int> contents;
};

#endif /*MEMORY_H_*/
