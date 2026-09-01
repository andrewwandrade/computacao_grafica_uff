#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image.h"
#include "rasterization.h"

#define W 800
#define H 600

int main() {
    //Cria o elemento base para a imagem
    ImageRGB img(W, H);

    //Preenche o fundo com uma cor branca
    img.fill(RGB(0xFFFFFF));

    //Define os vértices do triângulo
    std::vector<vec2> triangle = {
       {400.0f, 100.0f},
       {200.0f, 500.0f}, 
       {600.0f, 500.0f} 
    };

    //Chama a função de rasterização do triângulo
    std::vector<Pixel> pixels = rasterizeTriangle(triangle);

    //Define a cor que será utilizada para pintar o triângulo
    RGB triangleColor = RGB(0x09BAF0);

    for (const auto& p : pixels) {
        //Garante que o pixel está dentro dos limites da imagem antes de pintar
        if (p.x >= 0 && p.x < W && p.y >= 0 && p.y < H) {
            img(p.x, p.y) = triangleColor; 
        }
    }
    
    //Salva a imagem
    img.save("triangulorast.png");

    return 0;
}