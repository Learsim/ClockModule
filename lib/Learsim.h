#ifndef Learsim_h
#define Learsim_h
#include <FastLED.h>
#include <ArduinoJson.h>
#include "Arduino.h"

class Button
{
  public:
    Button();
    void Init(int pin, char identfier[]);
    bool GetValue();
  private:
    int _pin;
    char _identifier[];
};
class LedStrip
{
  public:
    CRGB* pixelStrip;
    LedStrip(int pin,int count);
    void Init();
    void SetPixel(int num, int r, int g, int b);
    void ShowPixels();
  private:
     int _pin;
     int _count;
    char _identifier[];
};
class Led
{
  public:
    Led();
    void Init(int pin, char identfier[]);
    void SetValue(bool value);
    char* ID;
  private:
    int _pin;
    char* _identifier;
};
class MessangeHandler
{
  public:
    MessangeHandler();
    void Init(int bufferSize);
    const char* GetValue(char* key);
    int GetIntValue(char* key);
    bool GetBoolValue(char* key);
    const char* GetArrayItem(int index,char* key);
    bool DeserializeJson();
    bool DeserializeJsonBuffer(const char* input);
    int GetArraySize();
    void SendID();
  private:
};
#endif