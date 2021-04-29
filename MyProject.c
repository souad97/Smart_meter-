// LCD module connections
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module connections

unsigned int ADCResult=0;
float pressure;
unsigned char txt[15];
 #define LEDG PORTD.RD0
 #define LEDR PORTD.RD1

void main() {

 TRISA.RA0 = 1; // Configure RA0 pin as input
  TRISD.RD0 = 0;
   TRISD.RD1 = 0;
ADC_Init(); // Initialize ADC

Lcd_Init(); // Initialize LCD
 Lcd_Cmd(_LCD_CLEAR); // Clear display
 Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off

Lcd_Out(1, 1, "s m a r t"); // Display "StudentCompanion"
 Lcd_Out(2, 1, "m e t e r"); // Display "Thermometer"
 Delay_ms(2000); // 2 Second delay
 Lcd_Cmd(_LCD_CLEAR); // Clear display

do {
 ADCResult = ADC_Read(0);
 pressure = (ADCResult*5.0)/1023;
 pressure = (pressure + 0.475)/0.0475;
 FloatToStr(pressure, txt);
 Lcd_Out(1, 1, "P = ");
 Lcd_Out_Cp(txt);
 Lcd_Out_Cp("KPa");
 LEDG=1;  // alllumer led vert
 LEDR=0 ; // fermer led rouge

 
      Sound_Init(&PORTA, 1);
    if (pressure>=102) {
                   LEDG=0;  // fermer led vert
                   LEDR=1 ; //allumer led rouge
               Sound_play(880,300);
               Lcd_Cmd(_LCD_CLEAR);
                Lcd_Out(1, 1, "f u i te"); // Display "StudentCompanion"
               Lcd_Out(2, 1, "d' e a u");
               Delay_ms(2000); // Display "Thermometer"
               Lcd_Cmd(_LCD_CLEAR); // 2 Second delay
          }

} while(1);

}