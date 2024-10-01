#include <assert.h>
#include "str2int.h"
#include <printf.h>
#include <stdlib.h>
#include <stdio.h>
#include "stdbool.h"


int str2int(const char *str) {
    if (*str == '-') {
        assert(1 == 0);
    }
    return 0;
}

bool space(char c) {
    return (c == ' ');
}
bool digit(char c) {    
    return (c >= '0' & c <= '9');
}
int otvet(const char *str) {
    int result = 0;
    int sign = 1;
    while (space(*str)) {
        str++;    
    }
    if (*str == '-' || *str == '+') {
        sign = (*str == '-') ? -1 : 1;        
        str++;
    }
    while (digit(*str)) {      
        int digit = *str - 0x30;
        result = result * 10 + digit;        
        str++;
    }

    return result * sign;
}
int main(void){
    printf("%d", otvet("235"));
    return 0;
}