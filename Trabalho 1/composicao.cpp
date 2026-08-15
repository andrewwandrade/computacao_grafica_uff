#include "Image.h"

void over(ImageRGB& bg, ImageRGBA& img, int x0, int y0){
  int x1 = x0 + img.width();
  int y1 = y0 + img.height();  

  for(int y = std::max(y0, 0); y < y1 && y < bg.height(); y++)
     for(int x = std::max(x0, 0); x < x1 && x < bg.width(); x++){
          RGB& Bg = bg(x, y);
          vec4 C = img(x-x0, y-y0);
          float alpha = C[3];
          Bg = lerp(alpha, (vec3)Bg, toVec3(C));
     }
}

int main(){

    //Importa os elementos do cenário
    ImageRGB img{"assets/output.png"};
    ImageRGBA island1{"assets/island1.png"};
    ImageRGBA island2{"assets/island2.png"};
    ImageRGBA island3{"assets/island3.png"};
    ImageRGBA tree{"assets/tree.png"};
    ImageRGBA bush{"assets/bush.png"};
    ImageRGBA character1{"assets/adventurer.png"};
    ImageRGBA character2{"assets/soldier.png"};
    ImageRGBA character3{"assets/female.png"};
    ImageRGBA stone{"assets/stone.png"};

    //Desenha os elementos no cenário

    //Ilha 1
    over(img, island1, 60, 94);
    over(img, island2, 188, 94);
    over(img, island3, 316, 94);

    //Ilha 2
    over(img, island1, 296, 500);
    over(img, island2, 424, 500);
    over(img, island3, 552, 500);

    //Ilha 3 
    over(img, island1, 654, 160);
    over(img, island3, 782, 160);

    //Outros elementos
    over(img, tree, 45, 187);
    over(img, bush, 500, 593);
    over(img, stone, 340, 593);
    over(img, tree, 612, 253);
    over(img, character1, 260, 187);
    over(img, character2, 790, 253);
    over(img, character3, 450, 593);

    img.save("assets/trabalhofinal.png");
}