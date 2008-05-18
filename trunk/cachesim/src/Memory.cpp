#include "Memory.h"

using namespace std;

Memory::Memory()
{
	for(int i=0;i<= 0x1fffff;i++)
		contents.push_back(0);
}

Memory::~Memory()
{
}

vector<uint> Memory::read(uint address, uint blockSize)
{
	vector<uint> result;
	uint startPos = (address/blockSize);
	startPos *=blockSize;
	if(address <= 0xffffffff) {
		
		for(int i=0;i<blockSize;i++)
		{
			result.push_back(contents[startPos+i]);
		}
	}
	return result;
}


bool Memory::write(uint address, uint content)
{
	if(address <= 0xffffffff) {
			contents[address]=content;
			return true;
	}
	else 
		return false;
}