#include <iostream>
#include "Cache.h"
#include "Memory.h"
#include <math.h>
#define N 500

using namespace std;

int main() {
//	cout << "oi A" << endl;
//  Memory mem;
//	cout << "oi B0" << endl;
	Cache cache(16*1024,1,128); // Mudar
/*	
	// LOOP INTERCHANGE 
//	cout << "oi B" << endl;

	for(int j=0; j< 100; j++)	
	{
		cout << "oi j=" << j << endl;
		for(int i=0;i<5000;i++)	
		{
//			cout << "oi 1" << endl;
			uint val = cache.read(i*100+j);
//			cout << "oi 2" << endl;
			cache.write(val, i*100+j);
//			cout << "no Address: " << i*100+j << endl;
		}
	}
*//*
	//LOOP FUSION B4
	
	for (int i = 0; i < 500; i = i+1) {
		cout << "i1 = " << i << endl;
		for (int j = 0; j < 500; j = j+1)
		{
			uint val = cache.read(i*500+j +300000);
			uint val1 = cache.read(i*500+j+600000);
			cache.write(val1+val, i*500+j);
		}

	}
	for (int i = 0; i < 500; i = i+1) {
		cout << "i2 = " << i << endl;
		for (int j = 0; j < 500; j = j+1){
			uint val = cache.read(i*500+j);
			uint val1 = cache.read(i*500+j+600000);
			cache.write(val1+val, i*500+j+900000);
		}
	
	}
*/
/*	
	//LOOP FUSION AFTER
	for (int i = 0; i < 500; i = i+1) {
			cout << "i1 = " << i << endl;
			for (int j = 0; j < 500; j = j+1)
			{
				uint val = cache.read(i*500+j +300000);
				uint val1 = cache.read(i*500+j+600000);
				cache.write(val1+val, i*500+j);
				val = cache.read(i*500+j);
				val1 = cache.read(i*500+j+600000);
				cache.write(val1+val, i*500+j+900000);
			}
	}
*/
	
/*	//BLOCKING BEFORE
	for (int i = 0; i < 100; i = i+1) {
		cout << "i1 = " << i << endl;
	for (int j = 0; j < 100; j = j+1)
	{	cache.write(0,270000);
		for (int k = 0; k < 100; k = k+1){
			uint val = cache.read(i*100+k+300000);
			val += cache.read(k*100+j+600000);
			val += cache.read(270000);
			cache.write(val,270000);
		}
		uint val1 = cache.read(270000);
		cache.write(val1,100*i+j);
	}
	} */
	
	//BLOCKING AFTER
	
	for(int B=8;B<=8;B++){
		for (int jj = 0; jj < N; jj = jj+B) {
			cout << "jj = " << jj << endl;
			for (int kk = 0; kk < N; kk = kk+B)
				for (int i = 0; i < N; i = i+1)
					for (int j = jj; j < min(jj+B,N); j = j+1)
					{
						cache.write(0,270000);
						for (int k = kk; k < min(kk+B,N); k = k+1) 
						{
							uint val = cache.read(i*N+k+300000);
							val += cache.read(k*N+j+600000);
							val += cache.read(270000);
							cache.write(val,270000);
						}
						uint val1 = cache.read(270000);
						val1+= cache.read(N*i+j);
						cache.write(val1,N*i+j);
					} }
		cout << "B = "<< B << " missRate = " << cache.getMissCounter() << endl;
		cache.clear();
	}
	
	
	
	
	
	
	//cout << "Total Miss Rates: " << cache.getMissCounter() << endl;
	
	
}
