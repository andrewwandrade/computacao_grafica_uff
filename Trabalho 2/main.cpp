#include "Color.h"
#include "Image.h"
#include "vec.h"
#include <cmath>

float G(vec2 P, vec2 C, float s){
   vec2 d = P- C;
   float r2 = dot(d, d);
   return 100.0f * std::exp(-r2/(s*s));
}

float dist2(vec2 P, vec2 C){
   vec2 d = P - C;
   return dot(d, d);
}

int main(){
   int W = 400, H = 500;
   ImageRGB Img(W, H);
   Img.fill(white);

   // Esqueleto do boneco
   
   vec2 cabeca      = {200, 420};
   vec2 pescoco     = {200, 380};
   vec2 peito       = {200, 330};
   vec2 cintura     = {200, 260};

   vec2 ombroE      = {160, 360};
   vec2 cotoveloE   = {100, 330};
   vec2 maoE        = { 50, 300};
   vec2 braco_meioE = lerp(0.5f, ombroE, cotoveloE);
   vec2 abraco_meioE= lerp(0.5f, cotoveloE, maoE);

   vec2 ombroD      = {240, 360};
   vec2 cotoveloD   = {300, 330};
   vec2 maoD        = {350, 300};
   vec2 braco_meioD = lerp(0.5f, ombroD, cotoveloD);
   vec2 abraco_meioD= lerp(0.5f, cotoveloD, maoD);

   vec2 quadrilE    = {160, 230};
   vec2 joelhoE     = {145, 150};
   vec2 peE         = {135,  70};
   vec2 coxa_meioE  = lerp(0.5f, quadrilE, joelhoE);
   vec2 canela_meioE= lerp(0.5f, joelhoE, peE);

   vec2 quadrilD    = {240, 230};
   vec2 joelhoD     = {255, 150};
   vec2 peD         = {265,  70};
   vec2 coxa_meioD  = lerp(0.5f, quadrilD, joelhoD);
   vec2 canela_meioD= lerp(0.5f, joelhoD, peD);


   // Raio de cada parte do corpo
   float s_cabeca = 52;
   float s_tronco = 50;
   float s_pescoco = 30;
   float s_braco  = 24;
   float s_perna  = 28;
   float s_mao = 18;
   float s_pe = 20;

   // Limiar
   float T = 45;

   // Percorre todos os pixels e testa se pertencem ao corpo
   for (int x = 0; x < W; x++){
      for (int y = 0; y < H; y++){
         vec2 P = {(float)x, (float)y};
         float soma = 
            G(P, cabeca,    s_cabeca)
            + G(P, pescoco,   s_pescoco)
            + G(P, peito,     s_tronco)
            + G(P, cintura,   s_tronco)

            + G(P, ombroE,     s_braco)
            + G(P, braco_meioE,s_braco)
            + G(P, cotoveloE,  s_braco)
            + G(P, abraco_meioE,s_braco)
            + G(P, maoE,       s_mao)

            + G(P, ombroD,     s_braco)
            + G(P, braco_meioD,s_braco)
            + G(P, cotoveloD,  s_braco)
            + G(P, abraco_meioD,s_braco)
            + G(P, maoD,       s_mao)

            + G(P, quadrilE,     s_perna)
            + G(P, coxa_meioE,   s_perna)
            + G(P, joelhoE,      s_perna)
            + G(P, canela_meioE, s_perna)
            + G(P, peE,          s_pe)

            + G(P, quadrilD,     s_perna)
            + G(P, coxa_meioD,   s_perna)
            + G(P, joelhoD,      s_perna)
            + G(P, canela_meioD, s_perna)
            + G(P, peD,          s_pe);
         float F = T - soma;

         if (F <= 0)
            Img(x, y) = red;
      }
   }

   // Rosto
   vec2 olhoE = {180, 428};
   vec2 olhoD = {220, 428};
   float r_olho2 = 7*7;

   vec2 bochechaE = {170, 415};
   vec2 bochechaD = {230, 415};
   float r_bochecha2 = 9*9;

   vec2 centroBoca = {200, 405};
   float larguraBoca2 = 18*18;
   float alturaBoca2  = 8*8;

   for (int x = 0; x < W; x++){
      for (int y = 0; y < H; y++){
         vec2 P = {(float)x, (float)y};

         if (dist2(P, bochechaE) <= r_bochecha2) Img(x,y) = RGB(0xff8080); // rosa clarinho
         if (dist2(P, bochechaD) <= r_bochecha2) Img(x,y) = RGB(0xff8080);

         if (dist2(P, olhoE) <= r_olho2) Img(x,y) = black;
         if (dist2(P, olhoD) <= r_olho2) Img(x,y) = black;

         vec2 d = P - centroBoca;
         float boca = (d[0]*d[0])/larguraBoca2 + (d[1]*d[1])/alturaBoca2;
         if (boca <= 1.0f) Img(x,y) = black;
      }
   }

   Img.save("output/boneco.png");
    return 0;
}