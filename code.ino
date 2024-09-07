/* Program LCD Digital Clock DS1307 with Arduino Uno */
#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"

DateTime now;
//Delkarasi Array Hari
char daysOfTheWeek[7][12] = {"Min", "Sen", "Sel", "Rab", "Kam", "Jum", "Sab"};

RTC_DS3231 rtc; // Pemilihan Pin dan pendeklarasian variabel
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void showDate(void);
void showTime(void);
void showDay(void);

void setup () { //Pengaturan Variabel
    Serial.begin(9600);
    lcd.begin(16, 2);
    Wire.begin();
    if (! rtc.begin())   {
        Serial.println("Couldn't find RTC Module");
        while (1);
    }
    
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, lets set the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () { //Perulangan Program
    now = rtc.now();
    showDate();
    showDay();
    showTime();
}

void showDate() {  //Deklarasi Penampilan Tanggal
    lcd.setCursor(0, 0);
    lcd.print(now.day());
    lcd.print('/');
    lcd.print(now.month());
    lcd.print('/');
    lcd.print(now.year());
}

void showDay() {  //Deklarasi Penampilan Hari
    lcd.setCursor(11, 0);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
}

void showTime() {  //Deklarasi Penampilan Waktu
    lcd.setCursor(0, 1);
    lcd.print("Time:");
    lcd.print(now.hour());
    lcd.print(':');
    lcd.print(now.minute());
    lcd.print(':');
    lcd.print(now.second());
    lcd.print("    ");
    }
