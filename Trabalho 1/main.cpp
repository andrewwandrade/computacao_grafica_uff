#include "Color.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#include <stdlib.h>
#include <time.h>

#define W 960
#define H 720

int main(){
   RGB I[H][W];

   //Fundo da Imagem ------------------------------------------------

   //Define o fundo da imagem como branco
   for(int y = 0; y < H; y++)
      for(int x = 0; x < W; x++)
         I[y][x] = RGB(0xFFFFFF);

   //90 px de altura (Tom de azul 1 - Fundo)
   for(int y = 0; y < 90; y++)
      for(int x = 0; x < W; x++)
         I[y][x] = RGB(0x004A87);
   
   //90 px de altura (Tom de azul 2)
   for(int y = 90; y < 180; y++)
      for(int x = 0; x < W; x++)
         I[y][x] = RGB(0x03467D);
   
   //90 px de altura (Tom de azul 3)
   for(int y = 180; y < 270; y++)
      for(int x = 0; x < W; x++)
         I[y][x] = RGB(0x014174);

   //90 px de altura (Tom de azul 4)
   for(int y = 270; y < 360; y++)
      for(int x = 0; x < W; x++)
         I[y][x] = RGB(0x013967);

   //90 px de altura (Tom de azul 5)
   for(int y = 360; y < 450; y++)
      for(int x = 0; x < W; x++)
         I[y][x] = RGB(0x003560);

   //90 px de altura (Tom de azul 6)
   for(int y = 450; y < 540; y++)
      for(int x = 0; x < W; x++)
         I[y][x] = RGB(0x00345E);

   //90 px de altura (Tom de azul 7)
   for(int y = 540; y < 630; y++)
      for(int x = 0; x < W; x++)
         I[y][x] = RGB(0x003159);
   
   //90 px de altura (Tom de azul 8 - Topo)
   for(int y = 630; y < 720; y++)
      for(int x = 0; x < W; x++)
         I[y][x] = RGB(0x002F56);
   
   //35 estrelas geradas de forma aleatória -----------------------------

   int a = 0;
   srand(time(NULL));

   while(a < 35){
      int numY = rand() % 719;
      int numX = rand() % 959;
      for(int y = numY; y < numY+3; y++){
         for(int x = numX; x < numX+3; x++){
            I[y][x] = RGB(0xFFFFFF);
      }
   }
      a++;
   }
   
   stbi_flip_vertically_on_write(true);
   stbi_write_png("assets/output.png", W, H, 3, I, 0);
}