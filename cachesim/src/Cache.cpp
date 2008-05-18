#include "Cache.h"
#include "Memory.h"
#include <math.h>
#include <map>
#include <vector>
#include <iostream>

using namespace std;
Cache::Cache(uint tS, uint ass, uint bS, Memory* mP)
{
	totalSize = tS/4;
	associativity = ass;
	blockSize = bS/4;
	memPointer = mP;
	missCounter=0;
	for(int i=0;i<=totalSize;i++)
	{
		content.push_back(0);
	}
}

Cache::~Cache()
{
}

uint Cache::getMissCounter()
{
	return missCounter;
}

uint Cache::read(uint memAddress) 
{
	if(memAddress <= 0x1fffff)
	{
		//cout << " CacheRead1" << endl;
		uint offset = memAddress%blockSize;
		uint memAddNorm = memAddress-offset;
		
		map<uint,uint>::iterator iter = blockMap.find(memAddNorm);
		//cout << " CacheRead2" << endl;
		if(iter != blockMap.end()) {
			uint cacheAdd = iter->second;
			return content[cacheAdd*blockSize + offset];
			
//			cout << "CacheRead IF" << endl;
		}
		else 
		{
//			cout << "CacheRead ELSE" << endl;
			missCounter++;
			replace(memAddNorm);
			iter = blockMap.find(memAddNorm);
			return content[(iter->second)*blockSize + offset];
		}
		//cout << " CacheRead3" << endl;		
	}
}

void Cache::replace(uint memAddress)
{
//	cout << " CacheReplace1" << endl;
	uint blockNum = memAddress/blockSize;
	vector<uint> newBlock = memPointer->read(memAddress,blockSize);
	uint setNum = memAddress % ( totalSize/(associativity*blockSize) );
	srand(time(0));
	uint setPos = rand() % associativity;
	uint cacheAddress = ((setNum*associativity)+setPos);
	map<uint,uint>::iterator iter;
//	cout << " CacheReplace2: setNum: " << setNum << " setPos: " << setPos << endl;
/*	for( iter = blockMap.begin(); iter != blockMap.end();iter++)
	{
		if((*iter).second == cacheAddress)
		{
			uint memOldBlockAddress = iter->first;
			blockMap.erase((*iter).first);
			if(dirties.find(cacheAddress)!= dirties.end())
			{
				for(int i=0;i<blockSize;i++)
				{
					memPointer->write(memOldBlockAddress +i, content[cacheAddress*blockSize + i ]);
					
				}
			}
			break;
		}
	}*/
	
	if((iter = invMap.find(cacheAddress))!=invMap.end())
	{
		blockMap.erase(iter->second);
		uint memOldBlockAddress = iter->second;
		invMap.erase(cacheAddress);
		if(dirties.find(cacheAddress)!= dirties.end())
		{
			for(int i=0;i<blockSize;i++)
			{
				memPointer->write(memOldBlockAddress +i, content[cacheAddress*blockSize + i ]);
				
			}
		}
	}
	
	
//	cout << " CacheReplace3" << endl;
	//	blockMap.insert(memAddress, cacheAddress);
	blockMap[memAddress]=cacheAddress;
	invMap[cacheAddress]=memAddress;
//	cout << " CacheReplace4 + cacheAddress:" << cacheAddress << endl;
	for(int i=0;i< newBlock.size();i++)
	{
		content[cacheAddress*blockSize + i ] = newBlock[i];
	}
	
}

void Cache::write(uint value, uint memAddress)
{
	read(memAddress);
	//cout << "oi 11" << endl;
	uint cacheAddress = blockMap[memAddress];
	//cout << "oi 12" << endl;
	uint offset = memAddress%blockSize;
	//cout << "oi 13" << endl;
	content[cacheAddress*blockSize + offset]=value;
	//cout << "oi 14" << endl;
	dirties.insert(cacheAddress);
	
}

void Cache::clear()
{
	missCounter =0;
	blockMap.clear();
	invMap.clear();
	dirties.clear();
	
}





