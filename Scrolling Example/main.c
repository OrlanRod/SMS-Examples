#include "SMSlib.h"   // we're including the library with the functions we will use
#include "assets.h"   // we're including the assets we created before
#include "stdlib.h"

unsigned char gameScreen=0; // 1 = title, 2 = options, 3 = playfield.
unsigned char il;
unsigned char i;
unsigned char scroll;
unsigned char nextColumn;
unsigned char nextTile;
unsigned int screenIndex;
void loadAssets (void) {

  #define    MOLTAONE_TILES     0

  if (gameScreen == 0){
  SMS_loadPSGaidencompressedTiles(moltaarea1__tiles__psgcompr, MOLTAONE_TILES);
 
  for (il=0;il<25;il++) {

    SMS_loadTileMap(0, il, &moltaarea1__tilemap__bin[il*96*2], 32*2);   //Here is an example to load from further down the map. &moltaarea1__tilemap__bin[(il*96*2)+tiledistance]

  }

  il = 0;
  SMS_loadBGPalette(moltaarea1__palette__bin);
  SMS_loadSpritePalette(sprites__palette__bin);
  }

}

void initGame (void) {

     scroll = 0;
     nextColumn = 32;
     nextTile = 0;
     screenIndex = 0;
     il = 0;
     SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);

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

void main (void) {
   unsigned int ks;
  
    initGame();
    loadAssets();
    

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



     SMS_displayOn();

  }

}
SMS_EMBED_SDSC_HEADER_AUTO_DATE(1, 0, "Orlan Rod", "Example", "Scroll Tilemap Right or Left");
