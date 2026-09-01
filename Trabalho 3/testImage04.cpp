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
 ImageRGB img{"background.png"};
 ImageRGBA boy{"flatboy.png"};

 // desenha o menino no cenário
 over(img, boy, 208, 108);

 img.save("output.png");
}

