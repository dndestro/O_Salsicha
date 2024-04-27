#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <spi.h>

#define TXTPEQ 1    // Texto tamanho pequeno no display;
#define TXTGRD 2    // Text tamanhao grande no display

#define SCREENWIDTH 128 // OLED display width, in pixels
#define SCREENHEIGHT 64 // OLED display height, in pixels
  

class DisplayRacao : public Adafruit_SSD1306{
    public:

        DisplayRacao();
        void msgSplash();
        void atualizaLeituras(float racao, float agua);
        void msgCustomizada(String msg, uint8_t tamTexto = TXTPEQ, uint8_t posX = 0, uint8_t posY = 0, bool limpaDisplay = true);
        void msgCustomizada(const Printable& msg, uint8_t tamTexto = TXTPEQ, uint8_t posX = 0, uint8_t posY = 0, bool limpaDisplay = true);
};