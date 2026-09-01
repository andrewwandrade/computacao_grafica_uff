#include "render2d_v1.h"
#include "bezier.h"
#include "polygon_triangulation.h"
#include "rasterization.h"


// Converte uma posição [-1,1] para coordenadas da imagem
vec2 toScreenGradient(vec2 p, int width, int height)
{
    return {
        ((p[0] + 1) * width - 1) / 2,
        ((p[1] + 1) * height - 1) / 2
    };
}

// Desenha o coração preenchido com degradê
void drawGradient(
    const std::vector<vec2>& Q,
    const std::vector<unsigned int>& indices,
    ImageRGB& image
)
{
    int W = image.width();
    int H = image.height();

    vec3 rosa_claro = {
        1.0f,
        0.80f,
        0.90f
    };

    vec3 rosa_escuro = {
        0.90f,
        0.05f,
        0.40f
    };

    Elements<Triangles> T{indices};


    for(auto tri : assemble(T, Q))
    {

        vec2 P[3] = {
            toScreenGradient(tri[0], W, H),
            toScreenGradient(tri[1], W, H),
            toScreenGradient(tri[2], W, H)
        };

        std::vector<Pixel> pixels =
            rasterizeTriangle(P);


        for(Pixel p : pixels)
        {

            // Verifica se está dentro da imagem

            if(
                p.x < 0 ||
                p.x >= W ||
                p.y < 0 ||
                p.y >= H
            )
                continue;


            float dx =
                (float)p.x - W / 2.0f;

            float dy =
                (float)p.y - H / 2.0f;


            float distancia =
                sqrt(dx * dx + dy * dy);


            float maxDist =
                sqrt(
                    (W / 2.0f) * (W / 2.0f) +
                    (H / 2.0f) * (H / 2.0f)
                );


            float t = distancia / maxDist;


            if(t < 0.0f)
                t = 0.0f;

            if(t > 1.0f)
                t = 1.0f;

            vec3 cor =
                lerp(
                    t,
                    rosa_claro,
                    rosa_escuro
                );

            image(p.x, p.y) = cor;
        }
    }
}


int main()
{

    std::vector<vec2> P =
        loadCurve("minha_curva.txt");

    std::vector<vec2> Q =
        sample_bezier_spline<3>(P, 80);

    // DESENHA SOMENTE A CURVA

    ImageRGB G1(600, 600);

    G1.fill(white);

    LineStrip LQ{Q.size()};

    render2d(
        Q,
        LQ,
        red,
        G1
    );

    G1.save("curva.png");

    std::vector<unsigned int> indices =
        triangulate_polygon(Q);

    // CRIA IMAGEM DO CORAÇÃO PREENCHIDO

    ImageRGB G2(600, 600);

    G2.fill(white);

    // DESENHA COM DEGRADÊ

    drawGradient(
        Q,
        indices,
        G2
    );

    G2.save("curva_preenchida.png");


    return 0;
}