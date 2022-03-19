#include "Arduino.h"
#include "Learsim.h"
#include <FastLED.h>
#include <ArduinoJson.h>
DynamicJsonDocument document(512);
LedStrip::LedStrip(int pin, int count, char identfier[])
{
  CRGB strip[count];
  pixelStrip = strip;
  _pin = pin;
  _count = count;
}
void LedStrip::SetPixel(int num, int r, int g, int b)
{
  pixelStrip[num] = CRGB(r, g, b);
}
void LedStrip::Init()
{
  int pin = LedStrip::_pin;
  int count = LedStrip::_count;
  switch (pin)
  {
  case 0:
    FastLED.addLeds<WS2811, 0>(pixelStrip, count);
    break;
  case 1:
    FastLED.addLeds<WS2811, 1>(pixelStrip, count);
    break;
  case 2:
    FastLED.addLeds<WS2811, 2>(pixelStrip, count);
    break;
  case 3:
    FastLED.addLeds<WS2811, 3>(pixelStrip, count);
    break;
  case 4:
    FastLED.addLeds<WS2811, 4>(pixelStrip, count);
    break;
  case 5:
    FastLED.addLeds<WS2811, 5>(pixelStrip, count);
    break;
  case 6:
    FastLED.addLeds<WS2811, 6>(pixelStrip, count);
    break;
  case 7:
    FastLED.addLeds<WS2811, 7>(pixelStrip, count);
    break;
  case 8:
    FastLED.addLeds<WS2811, 8>(pixelStrip, count);
    break;
  case 9:
    FastLED.addLeds<WS2811, 9>(pixelStrip, count);
    break;
  case 10:
    FastLED.addLeds<WS2811, 1>(pixelStrip, count);
    break;
  case 11:
    FastLED.addLeds<WS2811, 11>(pixelStrip, count);
    break;
  case 12:
    FastLED.addLeds<WS2811, 12>(pixelStrip, count);
    break;
  case 13:
    FastLED.addLeds<WS2811, 13>(pixelStrip, count);
    break;
  case 14:
    FastLED.addLeds<WS2811, 14>(pixelStrip, count);
    break;
  case 15:
    FastLED.addLeds<WS2811, 15>(pixelStrip, count);
    break;
  default:
    break;
  }
}
void LedStrip::ShowPixels()
{
  FastLED.show();
}

void Button::Init(int pin, char identfier[])
{
  pinMode(pin, INPUT);
  _pin = pin;
}

void MessangeHandler::Init(int bufferSize)
{

  document = DynamicJsonDocument(bufferSize);
}

bool MessangeHandler::DeserializeJson()
{
  DeserializationError err = deserializeJson(document, Serial);
  if (err == DeserializationError::Ok)
    return true;
  return false;
}
bool MessangeHandler::DeserializeJsonBuffer(const char* input)
{
  DeserializationError err = deserializeJson(document, input);
  if (err == DeserializationError::Ok)
    return true;
  return false;
}
const char *MessangeHandler::GetValue(char *key)
{
  return document[key].as<char*>();
}
const char *MessangeHandler::GetArrayItem(int index, char *key)
{
  return document[index][key].as<const char*>();
}
int MessangeHandler::GetIntValue(char *key)
{
  return document[key].as<int>();
}
int MessangeHandler::GetArraySize()
{
  return document.size();
}
bool MessangeHandler::GetBoolValue(char *key)
{
  return document[key].as<bool>();
}

MessangeHandler::MessangeHandler() {}

bool Button::GetValue()
{
  return digitalRead(_pin);
}
Led::Led() {}

void Led::Init(int pin, char identfier[])
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  ID = identfier;
}

void Led::SetValue(bool value)
{
  digitalWrite(_pin, value);
}