sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D7 at RB5_bit;
sbit LCD_D6 at RB4_bit;
sbit LCD_D5 at RB3_bit;
sbit LCD_D4 at RB2_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D7_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB2_bit;

char S1, S2, M1, M2, H1, H2, J;
char display[16] = "";

void morchid() {
    lcd_out(1, 3, ":");
    lcd_out(1, 6, ":");
    delay_ms(500);
    lcd_out(1, 3, " ");
    lcd_out(1, 6, " ");
    delay_ms(500);
}

void updateClock() {
    S1++;
    if (S1 == 58) { S1 = 48; S2++; }  //57.....9   ,   48.....0
    if (S2 == 54) { S1 = S2 = 48; M1++; }
    if (M1 == 58) { M1 = 48; M2++; }
    if (M2 == 54) { M1 = M2 = 48; H1++; }
    if (H1 == 58) { H1 = 48; H2++; }
    if (H2 == 50 && H1 == 52) { H1 = H2 = 48; J++; }   //50...2 ,52....4
    if (J == 1) { Lcd_out(1, 10, "sat"); }
    if (J == 2) { Lcd_out(1, 10, "sun"); }
    if (J == 3) { Lcd_out(1, 10, "mon"); }
    if (J == 4) { Lcd_out(1, 10, "tus"); }
    if (J == 5) { Lcd_out(1, 10, "wed"); }
    if (J == 6) { Lcd_out(1, 10, "thur"); }
    if (J == 7) { Lcd_out(1, 10, "fri"); }
    if (J == 8) { J = 1; }

    Lcd_Chr(1, 8, S1);
    Lcd_Chr(1, 7, S2);
    Lcd_Chr(1, 5, M1);
    Lcd_Chr(1, 4, M2);
    Lcd_Chr(1, 2, H1);
    Lcd_Chr(1, 1, H2);
}

void updateTemperature() {
    unsigned int result = adc_read(0);
    float volt = result * 4.88;
    float temp = volt / 10;
    lcd_out(2, 1, "Temp=");
    floattostr(temp, display);
    lcd_out_cp(display);
    lcd_chr(2, 14, 223); // Display degree symbol
    lcd_out_cp("C");
}

void main() {
    trisb = 0;
    trisa = 0xff;
    adcon1 = 0x80;
    S1 = S2 = M1 = M2 = H1 = H2 = 48;
    J = 1;

    Lcd_Init();
    Lcd_Cmd(_Lcd_CLEAR);
    Lcd_Cmd(_Lcd_CURSOR_OFF);

    while (1) {
        morchid();
        updateClock();
        updateTemperature();
        delay_ms(1000); // Update every second
    }
}