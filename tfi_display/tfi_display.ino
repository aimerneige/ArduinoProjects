#include <TFT_eSPI.h>
#include <SPI.h>

#include "hutao.h"

#define ROTATION_PROTRAIT 0
#define ROTATION_LANDSCAPE 1

#define WIDTH  120
#define HEIGHT 120

#define GIF_DELAY 20

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

uint16_t cmap[16];

void setup() {
  Serial.begin(115200);
  tft.init();
  spr.setColorDepth(4);
}

void loop() {
  for (int f = 0; f < 36; f++) {
    spr.createSprite(WIDTH, HEIGHT);
    tft.fillScreen(TFT_BLACK);
    spr.pushImage(4, 4, 100, 100, (uint16_t *)hutao[f]);
  
    for (int i = 0; i < 16; i++) {
      cmap[i] = hutao_palette[f][i];
    }
    spr.createPalette(cmap, 16);
    spr.pushSprite(tft.width() / 2 - WIDTH / 2, tft.height() / 2 - HEIGHT / 2);
  
    delay(GIF_DELAY);
  }
}
