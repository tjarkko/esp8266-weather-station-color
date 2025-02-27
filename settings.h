/**The MIT License (MIT)
Copyright (c) 2015 by Daniel Eichhorn
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
See more at http://blog.squix.ch
*/

#include <simpleDSTadjust.h>

// Setup
#define WIFI_SSID "DNA-Mokkula-3B6466"
#define WIFI_PASS "04326251709"
#define WIFI_HOSTNAME "ThingPulse-weather-station-color"

const int UPDATE_INTERVAL_SECS = 15 * 60; // Update every 10 minutes
const int SLEEP_INTERVAL_SECS = 15;       // Going to Sleep after idle times, set 0 for dont sleep

/* Feather Huzzah + 2.4" TFT wing */
// Pins for the ILI9341
#define TFT_DC 33
#define TFT_CS 15
#define TFT_LED 5
#define BACKLIGHT 21

// #define HAVE_TOUCHPAD
#define TOUCH_CS 32
//  #define TOUCH_IRQ  4

// OpenWeatherMap Settings
// Sign up here to get an API key:
// https://home.openweathermap.org/users/sign_up
const boolean IS_METRIC = true;
// String OPEN_WEATHER_MAP_APP_ID = "ascowijcawjr390r2834q";
String LATITUDE = "61.461521";
String LONGITUDE = "23.891472";
String OPEN_WEATHER_MAP_APP_ID = "0fd14a71f7ee3b94acfa973e5915e3a1";
// String OPEN_WEATHER_MAP_LOCATION = "Manhattan,US";
String OPEN_WEATHER_MAP_LOCATION = "lat=" + LATITUDE + "&lon=" + LONGITUDE;

// Pick a language code from this list:
// Arabic - ar, Bulgarian - bg, Catalan - ca, Czech - cz, German - de, Greek - el,
// English - en, Persian (Farsi) - fa, Finnish - fi, French - fr, Galician - gl,
// Croatian - hr, Hungarian - hu, Italian - it, Japanese - ja, Korean - kr,
// Latvian - la, Lithuanian - lt, Macedonian - mk, Dutch - nl, Polish - pl,
// Portuguese - pt, Romanian - ro, Russian - ru, Swedish - se, Slovak - sk,
// Slovenian - sl, Spanish - es, Turkish - tr, Ukrainian - ua, Vietnamese - vi,
// Chinese Simplified - zh_cn, Chinese Traditional - zh_tw.

String OPEN_WEATHER_MAP_LANGUAGE = "fi";
const uint8_t MAX_FORECASTS = 10;

// Adjust according to your language
const String WDAY_NAMES[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
const String MONTH_NAMES[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
const String MOON_PHASES[] = {"New Moon", "Waxing Crescent", "First Quarter", "Waxing Gibbous",
                              "Full Moon", "Waning Gibbous", "Third quarter", "Waning Crescent"};

#define UTC_OFFSET +2
struct dstRule StartRule = {"EEST", Last, Sun, Mar, 2, 3600}; // Eastern European Summer Time = UTC/GMT +3 hours
struct dstRule EndRule = {"EET", Last, Sun, Oct, 2, 0};       // Eastern European Time = UTC/GMT +2 hour

// Settings for Boston
// #define UTC_OFFSET -5
// struct dstRule StartRule = {"EDT", Second, Sun, Mar, 2, 3600}; // Eastern Daylight time = UTC/GMT -4 hours
// struct dstRule EndRule = {"EST", First, Sun, Nov, 1, 0};       // Eastern Standard time = UTC/GMT -5 hour

// Change for 12 Hour/ 24 hour style clock
bool IS_STYLE_12HR = false;

// change for different ntp (time servers)
// should use some local ntp?
#define NTP_SERVERS "0.ch.pool.ntp.org", "1.ch.pool.ntp.org", "2.ch.pool.ntp.org"
// #define NTP_SERVERS "us.pool.ntp.org", "time.nist.gov", "pool.ntp.org"

/***************************
 * End Settings
 **************************/
