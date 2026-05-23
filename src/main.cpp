#include <avr/io.h>

#include <util/delay.h>

#include <avr/pgmspace.h>

#include <avr/interrupt.h>

#include <stdio.h>

#include <stdlib.h>

// DICTIONAR FONTURI
// https://github.com/PaulStoffregen/LedDisplay/blob/master/font5x7.h
const uint8_t font5x7[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00,// (space)
	0x00, 0x00, 0x5F, 0x00, 0x00,// !
	0x00, 0x07, 0x00, 0x07, 0x00,// "
	0x14, 0x7F, 0x14, 0x7F, 0x14,// #
	0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
	0x23, 0x13, 0x08, 0x64, 0x62,// %
	0x36, 0x49, 0x55, 0x22, 0x50,// &
	0x00, 0x05, 0x03, 0x00, 0x00,// '
	0x00, 0x1C, 0x22, 0x41, 0x00,// (
	0x00, 0x41, 0x22, 0x1C, 0x00,// )
	0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
	0x08, 0x08, 0x3E, 0x08, 0x08,// +
	0x00, 0x50, 0x30, 0x00, 0x00,// ,
	0x08, 0x08, 0x08, 0x08, 0x08,// -
	0x00, 0x60, 0x60, 0x00, 0x00,// .
	0x20, 0x10, 0x08, 0x04, 0x02,// /
	0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
	0x00, 0x42, 0x7F, 0x40, 0x00,// 1
	0x42, 0x61, 0x51, 0x49, 0x46,// 2
	0x21, 0x41, 0x45, 0x4B, 0x31,// 3
	0x18, 0x14, 0x12, 0x7F, 0x10,// 4
	0x27, 0x45, 0x45, 0x45, 0x39,// 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
	0x01, 0x71, 0x09, 0x05, 0x03,// 7
	0x36, 0x49, 0x49, 0x49, 0x36,// 8
	0x06, 0x49, 0x49, 0x29, 0x1E,// 9
	0x00, 0x36, 0x36, 0x00, 0x00,// :
	0x00, 0x56, 0x36, 0x00, 0x00,// ;
	0x00, 0x08, 0x14, 0x22, 0x41,// <
	0x14, 0x14, 0x14, 0x14, 0x14,// =
	0x41, 0x22, 0x14, 0x08, 0x00,// >
	0x02, 0x01, 0x51, 0x09, 0x06,// ?
	0x32, 0x49, 0x79, 0x41, 0x3E,// @
	0x7E, 0x11, 0x11, 0x11, 0x7E,// A
	0x7F, 0x49, 0x49, 0x49, 0x36,// B
	0x3E, 0x41, 0x41, 0x41, 0x22,// C
	0x7F, 0x41, 0x41, 0x22, 0x1C,// D
	0x7F, 0x49, 0x49, 0x49, 0x41,// E
	0x7F, 0x09, 0x09, 0x01, 0x01,// F
	0x3E, 0x41, 0x41, 0x51, 0x32,// G
	0x7F, 0x08, 0x08, 0x08, 0x7F,// H
	0x00, 0x41, 0x7F, 0x41, 0x00,// I
	0x20, 0x40, 0x41, 0x3F, 0x01,// J
	0x7F, 0x08, 0x14, 0x22, 0x41,// K
	0x7F, 0x40, 0x40, 0x40, 0x40,// L
	0x7F, 0x02, 0x04, 0x02, 0x7F,// M
	0x7F, 0x04, 0x08, 0x10, 0x7F,// N
	0x3E, 0x41, 0x41, 0x41, 0x3E,// O
	0x7F, 0x09, 0x09, 0x09, 0x06,// P
	0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
	0x7F, 0x09, 0x19, 0x29, 0x46,// R
	0x46, 0x49, 0x49, 0x49, 0x31,// S
	0x01, 0x01, 0x7F, 0x01, 0x01,// T
	0x3F, 0x40, 0x40, 0x40, 0x3F,// U
	0x1F, 0x20, 0x40, 0x20, 0x1F,// V
	0x7F, 0x20, 0x18, 0x20, 0x7F,// W
	0x63, 0x14, 0x08, 0x14, 0x63,// X
	0x03, 0x04, 0x78, 0x04, 0x03,// Y
	0x61, 0x51, 0x49, 0x45, 0x43,// Z
	0x00, 0x00, 0x7F, 0x41, 0x41,// [
	0x02, 0x04, 0x08, 0x10, 0x20,// "\"
	0x41, 0x41, 0x7F, 0x00, 0x00,// ]
	0x04, 0x02, 0x01, 0x02, 0x04,// ^
	0x40, 0x40, 0x40, 0x40, 0x40,// _
	0x00, 0x01, 0x02, 0x04, 0x00,// `
	0x20, 0x54, 0x54, 0x54, 0x78,// a
	0x7F, 0x48, 0x44, 0x44, 0x38,// b
	0x38, 0x44, 0x44, 0x44, 0x20,// c
	0x38, 0x44, 0x44, 0x48, 0x7F,// d
	0x38, 0x54, 0x54, 0x54, 0x18,// e
	0x08, 0x7E, 0x09, 0x01, 0x02,// f
	0x08, 0x14, 0x54, 0x54, 0x3C,// g
	0x7F, 0x08, 0x04, 0x04, 0x78,// h
	0x00, 0x44, 0x7D, 0x40, 0x00,// i
	0x20, 0x40, 0x44, 0x3D, 0x00,// j
	0x00, 0x7F, 0x10, 0x28, 0x44,// k
	0x00, 0x41, 0x7F, 0x40, 0x00,// l
	0x7C, 0x04, 0x18, 0x04, 0x78,// m
	0x7C, 0x08, 0x04, 0x04, 0x78,// n
	0x38, 0x44, 0x44, 0x44, 0x38,// o
	0x7C, 0x14, 0x14, 0x14, 0x08,// p
	0x08, 0x14, 0x14, 0x18, 0x7C,// q
	0x7C, 0x08, 0x04, 0x04, 0x08,// r
	0x48, 0x54, 0x54, 0x54, 0x20,// s
	0x04, 0x3F, 0x44, 0x40, 0x20,// t
	0x3C, 0x40, 0x40, 0x20, 0x7C,// u
	0x1C, 0x20, 0x40, 0x20, 0x1C,// v
	0x3C, 0x40, 0x30, 0x40, 0x3C,// w
	0x44, 0x28, 0x10, 0x28, 0x44,// x
	0x0C, 0x50, 0x50, 0x50, 0x3C,// y
	0x44, 0x64, 0x54, 0x4C, 0x44,// z
	0x00, 0x08, 0x36, 0x41, 0x00,// {
	0x00, 0x00, 0x7F, 0x00, 0x00,// |
	0x00, 0x41, 0x36, 0x08, 0x00,// }
	0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
	0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};

volatile uint16_t pot_val = 0; // Stocheaza valoarea citita de la potentiometru
uint8_t h_t[128], h_p[128], h_h[128]; // Istoric pentru grafice (temperatura, presiune, umiditate)

// Initializeaza convertorul ADC pentru citirea potentiometrului
void adc_init() {
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Citeste o valoare analogica de pe canalul specificat
uint16_t adc_read(uint8_t ch) {
    ADMUX = (ADMUX & 0xF0) | (ch & 15);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

// Initializeaza Timer1 pentru a citi potentiometrul la intervale regulate
// 1562 = 16MHz / (1024 * 10Hz) pentru a genera o intrerupere la fiecare 100ms
void timer1_init() {
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
    OCR1A = 1562;
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

// Intrerupere generata de Timer1 - citeste continuu valoarea potentiometrului pe canalul 0
ISR(TIMER1_COMPA_vect) {
    pot_val = adc_read(0);
}

// Scrie un byte in memoria EEPROM (pentru a salva recordurile min/max)
void eep_w(uint16_t a, uint8_t d) {
    while (EECR & (1 << EEPE));
    EEAR = a;
    EEDR = d;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
}
// Citeste un byte din memoria EEPROM
uint8_t eep_r(uint16_t a) {
    while (EECR & (1 << EEPE));
    EEAR = a;
    EECR |= (1 << EERE);
    return EEDR;
}

// Initializeaza magistrala I2C (folosita pentru OLED si BME280)
void i2c_init() {
    TWSR = 0;
    TWBR = 72;
}
// Genereaza conditia de START pe bus-ul I2C
void i2c_start() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}
// Genereaza conditia de STOP pe bus-ul I2C
void i2c_stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
// Scrie un byte de date pe bus-ul I2C
void i2c_write(uint8_t d) {
    TWDR = d;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}
// Citeste un byte de pe bus-ul I2C (genereaza ACK daca 'a' e non-zero)
uint8_t i2c_read(uint8_t a) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (a ? (1 << TWEA) : 0);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

// ================= OLED =================
// Trimite o comanda de control catre display-ul OLED (adresa 0x3C)
void oled_cmd(uint8_t c) {
    i2c_start();
    i2c_write(0x3C << 1);
    i2c_write(0);
    i2c_write(c);
    i2c_stop();
}
// Secventa de initializare pentru OLED SSD1306
void oled_init() {
    oled_cmd(0xAE);
    oled_cmd(0x20);
    oled_cmd(0);
    oled_cmd(0xA1);
    oled_cmd(0xC8);
    oled_cmd(0x8D);
    oled_cmd(0x14);
    oled_cmd(0xAF);
}
// Curata ecranul OLED umplandu-l cu zerouri (blank)
void oled_clear() {
    oled_cmd(0x21);
    oled_cmd(0);
    oled_cmd(127);
    oled_cmd(0x22);
    oled_cmd(0);
    oled_cmd(7);
    i2c_start();
    i2c_write(0x3C << 1);
    i2c_write(0x40);
    for (int i = 0; i < 1024; i++) i2c_write(0);
    i2c_stop();
}
// Seteaza cursorul la coloana 'c' (0-127) si pagina 'p' (0-7)
void oled_set_cursor(uint8_t c, uint8_t p) {
    oled_cmd(0xB0 | (p & 7));
    oled_cmd(0 | (c & 15));
    oled_cmd(0x10 | ((c >> 4) & 15));
}

// Printeaza un singur caracter pe OLED folosind dictionarul de fonturi de 5x7 pixeli
void oled_p_char(char c) {
    if (c < 32 || c > 122) c = ' ';
    int idx = (c - 32) * 5;
    i2c_start();
    i2c_write(0x3C << 1);
    i2c_write(0x40);
    for (int i = 0; i < 5; i++) i2c_write(pgm_read_byte( & font5x7[idx + i]));
    i2c_write(0);
    i2c_stop();
}
// Printeaza un sir de caractere (string) pe OLED
void oled_p_str(const char * s) {
    while ( * s) oled_p_char( * s++);
}

// ================= BME280 =================
// Adresa I2C a senzorului BME280 (poate fi 0x76 sau 0x77)
#define BME_A 0x77
// Variabile pentru calibrarea senzorului BME280 citite din memoria ROM a acestuia
uint16_t dT1, dP1;
int16_t dT2, dT3, dP2, dP3, dP4, dP5, dP6, dP7, dP8, dP9, dH2, dH4, dH5;
uint8_t dH1, dH3;
int8_t dH6;
int32_t t_f;

// Citeste un numar 'l' de bytes din registrele incepand de la adresa 'r'
void bme_regs(uint8_t r, uint8_t * d, uint8_t l) {
    i2c_start();
    i2c_write(BME_A << 1);
    i2c_write(r);
    i2c_start();
    i2c_write((BME_A << 1) | 1);
    for (uint8_t i = 0; i < l; i++) d[i] = i2c_read(i < l - 1);
    i2c_stop();
}
// Citeste datele de calibrare BME280 si initializeaza modul normal de citire
void bme_init() {
    uint8_t c[26], c2[7];
    bme_regs(0x88, c, 26);
    dT1 = (c[1] << 8) | c[0];
    dT2 = (c[3] << 8) | c[2];
    dT3 = (c[5] << 8) | c[4];
    dP1 = (c[7] << 8) | c[6];
    dP2 = (c[9] << 8) | c[8];
    dP3 = (c[11] << 8) | c[10];
    dP4 = (c[13] << 8) | c[12];
    dP5 = (c[15] << 8) | c[14];
    dP6 = (c[17] << 8) | c[16];
    dP7 = (c[19] << 8) | c[18];
    dP8 = (c[21] << 8) | c[20];
    dP9 = (c[23] << 8) | c[22];
    dH1 = c[25];
    bme_regs(0xE1, c2, 7);
    dH2 = (c2[1] << 8) | c2[0];
    dH3 = c2[2];
    dH4 = (c2[3] << 4) | (c2[4] & 15);
    dH5 = (c2[5] << 4) | (c2[4] >> 4);
    dH6 = c2[6];
    i2c_start();
    i2c_write(BME_A << 1);
    i2c_write(0xF2);
    i2c_write(1);
    i2c_stop();
    i2c_start();
    i2c_write(BME_A << 1);
    i2c_write(0xF4);
    i2c_write(0x27);
    i2c_stop();
}
// Functia standard de citire presiune, temperatura si umiditate folosind formulele (dubioase) Bosch
// https://www.alldatasheet.com/datasheet-pdf/view/2163284/BOSCH/BME280_V01.html
// pag 25
void bme_read(int32_t * t, uint32_t * p, uint32_t * h) {
    uint8_t r[8];
    bme_regs(0xF7, r, 8);
    int32_t aT = ((int32_t) r[3] << 12) | ((int32_t) r[4] << 4) | (r[5] >> 4);
    int32_t v1 = ((((aT >> 3) - ((int32_t) dT1 << 1))) * (int32_t) dT2) >> 11;
    int32_t v2 = (((((aT >> 4) - (int32_t) dT1)) * ((aT >> 4) - (int32_t) dT1) >> 12) * (int32_t) dT3) >> 14;
    t_f = v1 + v2;* t = (t_f * 5 + 128) >> 8;
    int32_t aP = ((int32_t) r[0] << 12) | ((int32_t) r[1] << 4) | (r[2] >> 4);
    uint32_t pr;
    v1 = (t_f >> 1) - 64000;
    v2 = (((v1 >> 2) * (v1 >> 2)) >> 11) * dP6;
    v2 += (v1 * dP5) << 1;
    v2 = (v2 >> 2) + ((int32_t) dP4 << 16);
    v1 = (((dP3 * (v1 >> 2) * (v1 >> 2) >> 13) >> 3) + (dP2 * v1 >> 1)) >> 18;
    v1 = ((32768 + v1) * dP1) >> 15;
    if (v1 == 0) pr = 0;
    else {
        pr = (((uint32_t)(1048576 - aP) - (v2 >> 12))) * 3125;
        if (pr < 0x80000000) pr = (pr << 1) / v1;
        else pr = (pr / v1) * 2;
        v1 = (dP9 * ((int32_t)(pr >> 3) * (pr >> 3) >> 13)) >> 12;
        v2 = ((int32_t)(pr >> 2) * dP8) >> 13;
        pr = (uint32_t)(pr + ((v1 + v2 + dP7) >> 4));
    }* p = pr;
    int32_t aH = ((int32_t) r[6] << 8) | r[7];
    int32_t vx = (t_f - 76800);
    vx = (((((aH << 14) - ((int32_t) dH4 << 20) - (dH5 * vx)) + 16384) >> 15) * (((((((vx * dH6) >> 10) * ((vx * dH3 >> 11) + 32768)) >> 10) + 2097152) * dH2 + 8192) >> 14));
    vx -= ((((vx >> 15) * (vx >> 15)) >> 7) * dH1) >> 4;
    vx = (vx < 0 ? 0 : vx);
    vx = (vx > 419430400 ? 419430400 : vx);* h = (vx >> 12);
}

// ================= LOGICA RECORDURI RECALIBRATA =================
// Actualizeaza valorile minime/maxime in EEPROM daca o citire depaseste limitele salvate anterior
void upd_rec(int16_t t, uint16_t p, uint8_t h) {
    // TEMP (Adresa 10-13) - Stocare int16_t pe 2 octeti (High si Low byte)
    int16_t tX = (eep_r(10) << 8) | eep_r(11), tN = (eep_r(12) << 8) | eep_r(13);
    if (tX == 0xFFFF || tX > 6000 || tX < -4000) {
        eep_w(10, t >> 8);
        eep_w(11, t & 255);
    } else if (t > tX) {
        eep_w(10, t >> 8);
        eep_w(11, t & 255);
    }
    if (tN == 0xFFFF || tN > 6000 || tN < -4000) {
        eep_w(12, t >> 8);
        eep_w(13, t & 255);
    } else if (t < tN) {
        eep_w(12, t >> 8);
        eep_w(13, t & 255);
    }

    // PRES (Adresa 14-17) - Stocare uint16_t pe 2 octeti
    uint16_t pX = (eep_r(14) << 8) | eep_r(15), pN = (eep_r(16) << 8) | eep_r(17);
    if (pX == 0xFFFF || pX < 500) {
        eep_w(14, p >> 8);
        eep_w(15, p & 255);
    } else if (p > pX) {
        eep_w(14, p >> 8);
        eep_w(15, p & 255);
    }
    if (pN == 0xFFFF || pN < 500) {
        eep_w(16, p >> 8);
        eep_w(17, p & 255);
    } else if (p < pN) {
        eep_w(16, p >> 8);
        eep_w(17, p & 255);
    }

    // UMID (Adresa 18-19) - Stocare uint8_t
    uint8_t hX = eep_r(18), hN = eep_r(19);
    if (hX == 0xFF || hX > 100) {
        eep_w(18, h);
    } else if (h > hX) eep_w(18, h);
    if (hN == 0xFF || hN > 100) {
        eep_w(19, h);
    } else if (h < hN) eep_w(19, h);
}

// GRAFICA
// Deseneaza pe ecran axele, textul si graficele in functie de istoricul array-ului (temperature, pressure, sau humidity)
void draw_g(const char * t1,
    const char * rec, uint8_t * h) {
    // Randul 0 - titlu, Randul 1 - text cu recorduri
    oled_set_cursor(0, 0);
    oled_p_str(t1);
    oled_set_cursor(0, 1);
    oled_p_str(rec);
    // Randurile 2-7 de pe OLED sunt folosite pentru plotarea graficului de 48 de pixeli in inaltime (6x8 pixeli)
    for (uint8_t pg = 2; pg < 8; pg++) {
        oled_set_cursor(0, pg);
        i2c_start();
        i2c_write(0x3C << 1);
        i2c_write(0x40);
        for (uint8_t col = 0; col < 128; col++) {
            uint8_t px = (col == 0) ? 0xFF : 0; // Axa Y de la stanga
            // Axa X de jos si marcajele pe verticala/orizontala
            if (col > 0) {
                if (pg == 2 && col % 4 == 0) px |= 1;
                if (pg == 5 && col % 4 == 0) px |= 1;
                if (pg == 7 && col % 2 == 0) px |= 0x80;
                uint8_t v = h[col], l = 47 - v, g_pg = pg - 2, pt = g_pg * 8, pb = pt + 7;
                // Umple graficul cu pixeli acolo unde intra valoarea din istoric
                if (l <= pt) px = 0xFF;
                else if (l <= pb) px |= (0xFF << (l % 8));
            }
            i2c_write(px);
        }
        i2c_stop();
    }
}

// MAIN 
int main() {
    // Initializarea diverselor periferice Hardware si ale modulelor
    i2c_init();
    adc_init();
    bme_init();
    oled_init();
    oled_clear();
    timer1_init();

    // Variabile folosite pentru a retine ecranul curent si buffer-uri pentru texte
    uint8_t e_c = 255;
    char b[32], tx[32];
    int32_t tv;
    uint32_t pv, hv;

    // Contor folosit pentru masurarea timpului de apasare/mentinere a potentiometrului la maxim pentru reset
    uint16_t contor_reset = 0;

    while (1) {
        // Citeste tensiunea potentiometrului (0-1023) si imparte plaja pt. 5 ecrane distincte
        uint8_t e_n = (pot_val < 205) ? 0 : (pot_val < 410) ? 1 : (pot_val < 615) ? 2 : (pot_val < 820) ? 3 : 4;

        // Verifica daca am tranzitat catre alt ecran fata de ciclul anterior pentru a sterge fosta imagine desenata peoled
        if (e_n != e_c) {
            e_c = e_n;
            oled_clear();
        }

        // --- HARDWARE RESET EEPROM LOGIC (3 SECUNDE LA MAXIM DREAPTA) ---
        // Daca potentiometrul este rotit complet spre dreapta (valoare maxima de control)
        if (pot_val > 1010) {
            contor_reset++;
            // Daca pozitia este mentinuta timp de 3 secunde (50ms per ciclu * 60 repetari = 3000ms)
            if (contor_reset >= 60) {
                // Se suprascrie toata zona de recorduri din EEPROM cu valoarea de curatare 0xFF
                eep_w(10, 0xFF);
                eep_w(11, 0xFF);
                eep_w(12, 0xFF);
                eep_w(13, 0xFF);
                eep_w(14, 0xFF);
                eep_w(15, 0xFF);
                eep_w(16, 0xFF);
                eep_w(17, 0xFF);
                eep_w(18, 0xFF);
                eep_w(19, 0xFF);

                // Feedback vizual instantaneu pe OLED pentru confirmarea stergerii memoriei
                oled_clear();
                oled_set_cursor(20, 3);
                oled_p_str("RECORDS RESET!");
                _delay_ms(1500);
                oled_clear();

                e_c = 255; // Fortam redesenarea ecranelor curente dupa stergere
                contor_reset = 0; // Resetam contorul hardware
            }
        } else {
            contor_reset = 0; // Resetam contorul daca utilizatorul schimba ecranul din potentiometru
        }

        // Variabile transmise prin referinta pt incarcarea cu val. masurate brut
        bme_read( & tv, & pv, & hv);
        // Se aplica scala /100 pentru presiune, /1024 pentru umiditate potrivite senzorului folosit
        uint16_t cur_p = pv / 100;
        uint8_t cur_h = hv / 1024;
        upd_rec((int16_t) tv, cur_p, cur_h);

        // Impartirea pt. afisare a temperaturii la zecimale
        int32_t ti = tv / 100, tz = abs(tv % 100);

        // Mapping - Calculeaza inaltimea liniei de pe grafic pt valorile prezente (0 pânǎ la un maxim de 47 de puncte in inaltime)
        int32_t mt = (tv - 1500) * 47 / 2000;
        if (mt < 0) mt = 0;
        if (mt > 47) mt = 47;
        int32_t mp = (int32_t)(cur_p - 980) * 47 / 60;
        if (mp < 0) mp = 0;
        if (mp > 47) mp = 47;
        int32_t mh = cur_h * 47 / 100;
        if (mh > 47) mh = 47;

        // Shiftarea array-ului memoriei istorice pentru efectul vizual de deplasare la stanga a intregului grafic (scrolling)
        for (int i = 0; i < 127; i++) {
            h_t[i] = h_t[i + 1];
            h_p[i] = h_p[i + 1];
            h_h[i] = h_h[i + 1];
        }
        // Se adauga valoarea nou in capat
        h_t[127] = mt;
        h_p[127] = mp;
        h_h[127] = mh;

        // Randarea ecranului curent - Meniu (0), Live(1), Grafic Temp(2), Grafic Presiune(3), Grafic Umiditate(4)
        if (e_c == 0) {
            oled_set_cursor(25, 1);
            oled_p_str("PROIECT 2026");
            oled_set_cursor(15, 3);
            oled_p_str("Degeratu Razvan");
            oled_set_cursor(5, 6);
            oled_p_str("Roteste rotita");
        } else if (e_c == 1) {
            oled_set_cursor(30, 0);
            oled_p_str("DATE LIVE");
            sprintf(b, "Temp: %ld.%02ld C", ti, tz);
            oled_set_cursor(0, 3);
            oled_p_str(b);
            sprintf(b, "Pres: %u hPa", cur_p);
            oled_set_cursor(0, 5);
            oled_p_str(b);
            sprintf(b, "Umid: %u %%", cur_h);
            oled_set_cursor(0, 7);
            oled_p_str(b);
        } else if (e_c == 2) { // TEMP
            int16_t rX = (eep_r(10) << 8) | eep_r(11), rN = (eep_r(12) << 8) | eep_r(13);
            sprintf(tx, "T:%ld.%02ld C", ti, tz);
            sprintf(b, "Max:%d.%02d Min:%d.%02d", rX / 100, abs(rX % 100), rN / 100, abs(rN % 100));
            draw_g(tx, b, h_t);
        } else if (e_c == 3) { // PRES
            uint16_t rX = (eep_r(14) << 8) | eep_r(15), rN = (eep_r(16) << 8) | eep_r(17);
            sprintf(tx, "P:%u hPa", cur_p);
            sprintf(b, "Max:%u Min:%u", rX, rN);
            draw_g(tx, b, h_p);
        } else if (e_c == 4) { // UMID
            uint8_t rX = eep_r(18), rN = eep_r(19);
            sprintf(tx, "H:%u %%", cur_h);
            sprintf(b, "Max:%u%% Min:%u%%", rX, rN);
            draw_g(tx, b, h_h);
        }
        _delay_ms(50); // Mentine refresh rate-ul la maxim ~20 FPS.
    }
}