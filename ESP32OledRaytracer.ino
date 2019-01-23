
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

//OLED pins to ESP32 GPIOs via this connecthin:
//OLED_SDA -- GPIO4
//OLED_SCL -- GPIO15
//OLED_RST -- GPIO16

#define DISPLAY_HEIGHT 64
#define DISPLAY_WIDTH  128

SSD1306  display(0x3c, 4, 15);

#include "tinyraytracer.h" // a modified version of https://github.com/ssloy/tinyraytracer


void raytrace() {
  Material      ivory(1.0, Vec4f(0.6,  0.3, 0.1, 0.0), Vec3f(0.4, 0.4, 0.3),   50.);
  Material      glass(1.5, Vec4f(0.0,  0.5, 0.1, 0.8), Vec3f(0.6, 0.7, 0.8),  125.);
  Material red_rubber(1.0, Vec4f(0.9,  0.1, 0.0, 0.0), Vec3f(0.3, 0.1, 0.1),   10.);
  Material     mirror(1.0, Vec4f(0.0, 10.0, 0.8, 0.0), Vec3f(1.0, 1.0, 1.0), 1425.);

  std::vector<Sphere> spheres;
  spheres.push_back(Sphere(Vec3f(-3,    0,   -16), 2,      ivory));
  spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2,      glass));
  spheres.push_back(Sphere(Vec3f( 1.5, -0.5, -18), 3, red_rubber));
  spheres.push_back(Sphere(Vec3f( 7,    5,   -18), 4,     mirror));

  std::vector<Light>  lights;
  lights.push_back(Light(Vec3f(-20, 20,  20), 1.5));
  lights.push_back(Light(Vec3f( 30, 50, -25), 1.8));
  lights.push_back(Light(Vec3f( 30, 20,  30), 1.7));

  render(spheres, lights);
}


void setup() {
  Serial.begin(115200);

  Serial.println("Setup start");

  pinMode(16,OUTPUT);
  digitalWrite(16, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(16, HIGH);    // turn the LED off by making the voltage LOW

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  display.clear();

  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "Raytrace start");
  display.display();

  delay(1000);

  Serial.println("Raytrace start ...");

  display.clear();
  display.display();

  Serial.print("Start time: "); 
  Serial.println(String(millis())); 
  
  raytrace();

  Serial.print("Stop time: "); 
  Serial.println(String(millis())); 
  Serial.println("Setup done");
}

void loop() {
  //  
}
