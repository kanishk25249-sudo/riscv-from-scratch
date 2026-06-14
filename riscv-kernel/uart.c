#include "uart.h"
#define UART_BASE 0x10000000

void uart_putc(char c) {
    volatile char* uart = (volatile char*)UART_BASE;
    *uart = c;
}

void uart_puts(const char* s) {
    while (*s != '\0') {
        uart_putc(*s);
        s++;
    }
}   

void uart_putint(int n) {
    if (n == 0) {
        uart_putc('0');
        return;
    }
    int temp;
    char buff[12];
    int i = 11;
    while (n > 0) {
        temp = n % 10;
        buff[i] = '0' + temp;
        i--;
        n = n / 10;
    }
    for (int j = i + 1; j < 12; j++) {
        uart_putc(buff[j]);
    }
}

void uart_puthex(unsigned int n) {
    uart_puts("0x");
    if (n == 0) {
        uart_putc('0');
        return;
    }
    int temp;
    char buff[12];
    int i = 11;
    while (n > 0) {
        temp = n % 16;
        if (temp < 10) {
            buff[i] = '0' + temp;
        } else {
            buff[i] = 'a' + (temp - 10);
        }
        i--;
        n = n / 16; 
    }
    for (int j = i + 1; j < 12; j++) {
        uart_putc(buff[j]);
    }
}