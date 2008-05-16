#include "Cache.h"
#include "Memory.h"
#include <math.h>
#include <map>
#include <vector>
#include <iostream>

using namespace std;
Cache::Cache()
{
}

Cache::~Cache()
{
}

char Cache::read(uint memAddress) 
{
	if(memAddress <= 0xffffffff)
	{
		uint blockNum = memAddress/blockSize;
		uint offset;
		map<uint,uint>::iterator iter = blockMap.find(blockNum);
		if(iter != blockMap.end())
			offset = (*iter).second;
		else 
		{
			replace(memAddress);
		}
				
	}
}

void Cache::replace(uint memAddress)
{
	uint blockNum = memAddress/blockSize;
	vector<char> newBlock = memPointer->read(memAddress,blockSize);
	uint setNum = memAddress % ( totalSize/associativity );
	uint setPos = rand() % associativity;
	uint cacheAddress = ((setNum*associativity)+setPos);
	map<uint,uint>::iterator iter;
	for( iter = blockMap.begin(); iter != blockMap.end();iter++)
	{
		if((*iter).second == cacheAddress)
		{
			blockMap.erase((*iter).first);
			if(dirties.find(cacheAddress)!= dirties.end())
			{
				for(int i=0;i<blockSize;i++)
				{
					//TODO: PARAMOS AQUI xD
					
				}
			}
			break;
		}
	}
	blockMap.insert(memAddress, cacheAddress);
	for(int i=0;i< newBlock.size();i++)
	{
		contents[((setNum*associativity)+setPos)*blockSize + i ] = newBlock[i];
	}
	
}

void Cache::write(char value, uint memAddress)
{
	read(memAddress);
	
}







