#include "SMSlib.h"   // we're including the library with the functions we will use
#include "assets.h"   // we're including the assets we created before
#include "stdlib.h"
#include "PSGlib.h"

unsigned char gameScreen=0; // 1 = title, 2 = options, 3 = playfield.
unsigned char gamePoints[2];
unsigned char il;
unsigned char incr;
unsigned char i;
unsigned char scroll;
unsigned char nextColumn;
unsigned char nextColumnTwo;
unsigned char nextTile;
unsigned char nextTileTwo;
unsigned int screenIndex;
unsigned char converToArray[5];

void loadAssets (void) {

  #define    GAMEFONT_TILES    74
  #define    MOLTAONE_TILES     0
  if (gameScreen == 0){
  SMS_loadPSGaidencompressedTiles(moltaarea1__tiles__psgcompr, MOLTAONE_TILES);
  SMS_loadPSGaidencompressedTiles(smallgfont__tiles__psgcompr, GAMEFONT_TILES);
  for (il=0;il<25;il++) {
    //SMS_loadTileMap(1, il, &moltaarea1__tilemap__bin[il*96*2], 30*2);   //Example to load from further down the map. &moltaarea1__tilemap__bin[(il*96*2)+tiledistance]
    SMS_loadTileMap(0, il, &moltaarea1__tilemap__bin[il*96*2], 32*2);   //Example to load from further down the map. &moltaarea1__tilemap__bin[(il*96*2)+tiledistance]

  }

  il = 0;
  SMS_loadBGPalette(moltaarea1__palette__bin);
  SMS_loadSpritePalette(sprites__palette__bin);
  }

}

void initGame (void) {

     scroll = 0;
     nextColumn = 32;
     nextColumnTwo = 0;
     nextTile = 0;
     converToArray[0] = 42;
     screenIndex = 0;
     il = 0;
     incr = 2;
     SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);

}

//Thanks for contributing the drawString function Calindro! ;)
void drawString(unsigned char x, unsigned char y, char* message) {
unsigned char cnt;
SMS_setNextTileatXY (x,y); for(cnt=0;cnt<29 && message[cnt];++cnt) { SMS_setTile(GAMEFONT_TILES + smallgfont__tilemap__bin[(message[cnt]- ' ')*2] ); }

}


void scrollLeft(void){

     for (i=0; i < 24; i++){

     SMS_setNextTileatXY(nextTile, i);
     SMS_setTile(*(unsigned int *)(&moltaarea1__tilemap__bin[(i*96+nextColumn)*2])); //next column is after the first 32 tiles of the next screen. i is the row to pick. 96 is width of the tilemap in tiles. We cast to int, to have tile mirror flogs.

     }
     i = 0;
     nextColumn++;
     if (nextTile < 31) { nextTile++; } else {  nextTile = 0;  }

}

void scrollRight(void){

     for (i=0; i < 24; i++){

     SMS_setNextTileatXY(nextTile, i);
     SMS_setTile(*(unsigned int *)(&moltaarea1__tilemap__bin[(i*96+(nextColumn-32))*2])); //next column is after the first 32 tiles of the next screen. i is the row to pick. 96 is width of the tilemap in tiles. We cast to int, to have tile mirror flogs.

     }
     i = 0;
     nextColumn--;
     if (nextTile > 0) { nextTile--; } else {  nextTile = 31;  }

}

//Draws a char number at x,y, using a array index value and setting the amount of digits in the number, indicated by pvalues.
void drawNum(unsigned char x, unsigned char y, unsigned char* num, unsigned char aindex, unsigned char pvalues) {

unsigned char cn; //used in incrementing the for loop.
unsigned char tenth[2] = {num[0] / 10, num[0] % 10};      //math for seperating the digits.  function can do up to 100ths, currently.
unsigned char hundr[3] = {num[0] / 100, (num[0] % 100)/10, num[0] % 10};
if (pvalues == 1) { SMS_setNextTileatXY (x,y); SMS_setTile(GAMEFONT_TILES + smallgfont__tilemap__bin[(16+num[aindex])*2]); }
if (pvalues == 2) {
  for(cn=0;cn<pvalues;++cn) { SMS_setNextTileatXY (x+cn,y); SMS_setTile(GAMEFONT_TILES + smallgfont__tilemap__bin[(16+tenth[cn])*2]); }
}
if (pvalues == 3) {
  for(cn=0;cn<pvalues;++cn) { SMS_setNextTileatXY (x+cn,y); SMS_setTile(GAMEFONT_TILES + smallgfont__tilemap__bin[(16+hundr[cn])*2]); }
}

}

void resetVars(void){

  //Resets all gameplay related vars.

}

void main (void) {
   unsigned int ks;
   unsigned int kbrel;
    initGame();
    loadAssets();
    //drawString(3,0, "SHIT");

    for (;;) {

     ks=SMS_getKeysStatus();
     kbrel=SMS_getKeysReleased();

    if ((ks & PORT_A_KEY_RIGHT) && (screenIndex < 65)) {

    SMS_waitForVBlank();
    if ((scroll % 8)==0) {
      scrollLeft();
      screenIndex+= 1;

    }

    if (screenIndex < 65){
    scroll++;
    SMS_setBGScrollX(-(scroll));

    } else {
        scroll = 0;
        nextTile = 0;
      }
    }


    if ((ks & PORT_A_KEY_LEFT) && (screenIndex > 0)) {

    SMS_waitForVBlank();

    if ((scroll % 8)==0) {
      scrollRight();
      screenIndex-= 1;
      }

    if (screenIndex > 0) {
      scroll--;
      SMS_setBGScrollX(-(scroll));
      } else {
        scroll = 0;
        nextTile = 0;
      }

    }



    converToArray[0] = scroll;
    drawNum(5, 0, converToArray, 0, 3);



     SMS_displayOn();

  }

}
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "Orlan Rod", "Sentient Seed", "Aventure Game");
