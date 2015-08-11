#include <stdio.h>
#include <stdint.h>

uint32_t murmur3_32(const char *key, uint32_t len, uint32_t seed);

int main(){
	long key;
	for (int i = 0; i < 10; ++i)
	{
		uint32_t hash = murmur3_32((char *)&key, sizeof(long), i);
		printf("%u\n",hash);
	}
  return 0;
}
