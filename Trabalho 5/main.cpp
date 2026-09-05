#include "Render2D_v1.h"
#include "bezier.h"
#include "transforms2d.h"

int main(){
   std::vector<vec2> CP = loadCurve("minha_curva.txt"); //Carrega os pontos de controle
   std::vector<vec2> P = sample_bezier_spline<3>(CP, 50); //Processo de poliganização da curva
   
   ImageRGB G(1200, 800);
   G.fill(white);
   
   //Matrizes para realizar as combinações de transformações 
   mat3 S = scale(0.45, 0.45);
   mat3 W = window(0, 3, 0, 2); 
   mat3 T = translate(1.5, 1); 
   
   LineStrip L{P.size()};
   render2d(W*T*S*P, L, red, G);

   int num_coracoes = 20;
   float largura_total = 3;
   float espaco = largura_total / num_coracoes;

   //Faixa superior de corações
   for(int i=0; i<num_coracoes; i++){
      mat3 S = scale(0.08, 0.08);

      //Cálculo da translação para distribuir os corações horizontalmente
      float x_pos = (i*espaco) + (espaco/2);
      float y_pos = 1.92f;
      mat3 T = translate(x_pos, y_pos);

      //Renderiza o coração
      render2d(W*T*S*P, L, blue, G);
   }

   //Faixa inferior de corações
   for(int i=0; i<num_coracoes; i++){
      mat3 S = scale(0.08, 0.08);

      float x_pos = (i*espaco) + (espaco/2);
      float y_pos = 0.08f;
      mat3 T = translate(x_pos, y_pos);

      render2d(W*T*S*P, L, blue, G);
   }

   int num_coracoes_v = 13;
   float altura_total = 2;
   float espaco_v = altura_total / num_coracoes_v;

   //Faixa esquerda de corações
   //Começando em 1 e terminando em -1 pois irá deixar de desenhar o primeiro e o último coração da margem
   for(int i=1; i<num_coracoes_v-1; i++){ 
      mat3 S = scale(0.08, 0.08);

      float x_pos = 0.075;
      float y_pos = (i*espaco_v) + (espaco_v/2);
      mat3 T = translate(x_pos, y_pos);

      render2d(W*T*S*P, L, blue, G);
   }

   //Faixa direita de corações
   for(int i=1; i<num_coracoes_v-1; i++){
      mat3 S = scale(0.08, 0.08);

      float x_pos = 2.925;
      float y_pos = (i*espaco_v) + (espaco_v/2);
      mat3 T = translate(x_pos, y_pos);

      render2d(W*T*S*P, L, blue, G);
   }

   //Círculo de corações no centro
   int num_coracoes_c = 26; 
   float raio = 0.7;
   
   mat3 Sc = scale(0.12, 0.12);
   mat3 Tr = translate(raio, 0); //Afasta o coração da origem
   mat3 Tc = translate(1.5, 1); //Move o círculo completo para o centro
   
   for(int i=0; i<num_coracoes_c; i++){
      //Calcula o ângulo em radianos para cada um dos corações distribuídos uniformemente
      float angulo = i*2.0f*M_PI/num_coracoes_c;

      mat3 R = rotate_2d(angulo); //Gira os corações
      mat3 M1 = Tc*R*Tr*Sc;

      render2d(W*M1*P, L, green, G);
   }

   G.save("output.png");

}
