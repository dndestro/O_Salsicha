#include "displayracao.h"

DisplayRacao::DisplayRacao() : Adafruit_SSD1306 (SCREENWIDTH, SCREENHEIGHT){

}

void DisplayRacao::msgSplash(){
    delay(2000);                      // tempo de atraso para inicialização do display. Tentar diminuir e testar
    clearDisplay();
    delay(100);
    setTextSize(TXTGRD);
    setTextColor(WHITE);
    setTextWrap(false);               //Desliga a função de jogar o texto automaticamente para a próxima linha
    setCursor(0, 0);
    println("Racao e");
    println("Agua do");
    print(  "Salsicha");
    display();
    startscrollright(0x00, 0x05);
    delay(2000);
    startscrollleft(0x00, 0x05);
    delay(2000);
    stopscroll();
}

void DisplayRacao::atualizaLeituras(float racao, float agua){
    clearDisplay();
    delay(10);
    setTextSize(TXTGRD);
    setCursor(0, 0);
    print("Racao:");

    if(racao < 0) {
        print("Erro");
    }
    else{
        print(racao, 0);
        print("%");
    }
    setCursor(0, 40);                // display modo paisagem 
    print("Agua:");

    if(agua < 0){
        print("Erro"); 
    }
    else{  
        print(agua, 0);
        print("%");
    }
    display();
}

void DisplayRacao::msgCustomizada(String msg, uint8_t tamTexto, uint8_t posX, uint8_t posY, bool limpaDisplay){
    
    if(limpaDisplay)
        clearDisplay();

    setTextSize(tamTexto);
    setTextWrap(true);

    setCursor(posX, posY);
    print(msg);
    display();

    setTextWrap(false);
    setTextSize(2); 
}

void DisplayRacao::msgCustomizada(const Printable& msg, uint8_t tamTexto, uint8_t posX, uint8_t posY, bool limpaDisplay){
    
    if(limpaDisplay)
        clearDisplay();

    setTextSize(tamTexto);
    setTextWrap(true);

    setCursor(posX, posY);
    print(msg);
    display();

    setTextWrap(false);
    setTextSize(2); 
}