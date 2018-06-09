#include <stdint.h>
#define STDLIB_H

#define MIN(x,y) ((x < y ? x : y))
#define MAX(x,y) ((x > y ? x : y))

typedef struct divmod_result{
	uint32_t div;
	uint32_t mod;
} divmod_t;

divmod_t divmod(uint32_t divident, uint32_t divisor); //divide returning a divmod_t result with modulus
char * itoa(int num,int base);
int atoi(char num);
