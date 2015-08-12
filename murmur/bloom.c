#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define DEBUG 0

//Parameters:
//Table size
#define TBSZ 1024
//Number Hash Fns
#define NH 4
//First Seed, Assuming Consecutive, 
#define FS 0

uint32_t murmur3_32(const char *key, uint32_t len, uint32_t seed);


void add(unsigned char * h, unsigned long key){
	//Hashes key with NH hash functions. Sets corresponding bits of h to reflect
	//key's membership in h. 

	uint32_t val;
	//Set bits specified by hash fns. 
	for (int i = FS; i < FS + NH; ++i){
		val = murmur3_32((char *)&key, sizeof(long), i) % TBSZ;
		h[val] = 1;
	}

	if(DEBUG)
		printf("inserted %lu \n", key);
}

int lookup(unsigned char * h, unsigned long key){
	uint32_t val;
	int found = 0;
	for (int i = FS; i < FS + NH; ++i){
		val = murmur3_32((char *)&key, sizeof(long), i) % TBSZ;
		
		//The hash fn says val must be set.
		if(h[val]){
			//If below is true, all bits check out.
			if (i == FS + NH-1){
				found = 1;
				if (DEBUG)
					printf("found %lu\n", key);
			}
			//Check next bit.
			continue;
		//h[val] was not set, key cannot be in h.
		}else {
			if(DEBUG){
				printf("failed to find %lu\n", key);
			}
			return 0;
		}
	}
	return found;
}

int main(){
	unsigned char * h;
	h = calloc (TBSZ, sizeof(unsigned char));

	if(!h){
		printf("failed to allocate h\n");
		exit(1); 
	}

	add(h,5);
	if(lookup(h,5))
		printf("found\n");

	return 0;
}



























