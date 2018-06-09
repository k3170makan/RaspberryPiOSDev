#include <stdint.h>
#define STDLIB_H

#define MIN(x,y) ((x < y ? x : y))
#define MAX(x,y) ((x > y ? x : y))

typedef struct divmod_result{
	uint32_t div;
	uint32_t mod;
} divmod_t;

divmod_t divmod(uint32_t divident, uint32_t divisor); //divide returning a divmod_t result with modulus
uint32_t div(uint32_t divident, uint32_t divisor);

char * itoa(int num,int base);
int atoi(char num);

divmod_t divmod(uint32_t divident, uint32_t divisor){
	divmod_t dm;
	dm.div = divident / divisor;
	dm.mod = divident % divisor;
	return dm;
}
char *itoa(int num, int base){
	char intbuf[33];

	uint32_t j = 0,i = 0,isneg = 0;
	divmod_t _divmod;

	if (num == 0){
		intbuf[0] = '0';
		intbuf[1] = '\0';
		return intbuf;
	}		
	/**first divide the number by its base and at every 
		stage of the division we do something with remainder
		mark the buffer with the inflection of the remainder in the ascii value
	*/
	if (base == 10 && num < 0){
		isneg = 1;
		num = -num;
	}	
	
	i = (uint32_t)	num;
	
	while (i != 0){
		_divmod = divmod(i,base);
		if (_divmod.mod < 10){
			intbuf[j++] = '0' + (_divmod.mod);
		}
		else{ 
			intbuf[j++] = 'a' + (_divmod.mod) - 10;
		}
		i = (uint32_t) _divmod.div;
	}
	if (isneg){
		intbuf[j++] = '-';
	}	
	if (base == 16){
		intbuf[j++] = 'x';
		intbuf[j++] = '0';
		
	}
	if (base == 8){
		intbuf[j++] = '0';
	}
	if (base == 2){
		intbuf[j++] = 'b';
		intbuf[j++] = '0';
		
	}
	intbuf[j] = '\0';
	j--;
	i = 0;
	while (i < j){
		isneg = intbuf[i];
		intbuf[i] = intbuf[j];
		intbuf[j] = isneg;
		i++;
		j--;
	}
	return intbuf;
}
/**
uint32_t div(uint32_t divident, uint32_t divisor){
	return divident / divisor;
}*/
