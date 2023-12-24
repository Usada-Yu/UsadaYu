#include "sample.h"

// 找质数，是质数返回true，否则返回false
bool isPrime(int num) {
	if(num == 2) {
	    return true;
	}

	if(num % 2 == 0 || num < 2) {
	    return false;
	}
	else {
		for(int i = 3; i * i <= num; i += 2) {
			if(num % i == 0) {
				return false;
			}
		}
		return true;
	}
}
