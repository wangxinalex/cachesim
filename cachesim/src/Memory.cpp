#include "Memory.h"

using namespace std;

Memory::Memory()
{
}

Memory::~Memory()
{
}

vector<char> Memory::read(uint address, uint blockSize)
{
	vector<char> result;
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


bool Memory::write(uint address, char content)
{
	if(address <= 0xffffffff) {
			contents[address]=content;
			return true;
	}
	else 
		return false;
}