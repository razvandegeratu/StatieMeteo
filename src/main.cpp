#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void uart_init(uint32_t baud) {
    uint16_t ubrr = F_CPU / 16 / baud - 1;
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << TXEN0); 
    UCSR0C = (3 << UCSZ00); 
}

void uart_print(char* s) {
    while (*s) {
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = *s++;
    }
}

void i2c_init(void) {
    TWSR = 0x00; 
    TWBR = 72;   
}

uint8_t i2c_scan(uint8_t address) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    TWDR = (address << 1);
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    uint8_t status = (TWSR & 0xF8);
    
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    
    return (status == 0x18); // 0x18 = ACK (A raspuns!)
}

int main(void) {
    uart_init(9600);
    i2c_init();
    char buffer[50];

    _delay_ms(2000); 
    uart_print("\r\n--- Incepe Scanarea I2C ---\r\n");

    for (uint8_t addr = 1; addr < 127; addr++) {
        if (i2c_scan(addr)) {
            sprintf(buffer, "Gasit la adresa: 0x%02X\r\n", addr);
            uart_print(buffer);
        }
    }

    uart_print("Scanare terminata.\r\n");

    while (1); 
}