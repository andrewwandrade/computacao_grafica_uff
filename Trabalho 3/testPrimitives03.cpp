#include "Primitives.h"
#include "rasterization.h"
#include "Image.h"

int main(){
	ImageRGB Img(500, 400);
	Img.fill(white);

#define N 200
	vec2 P[N];
	for(int i = 0; i < N; i+=2){
		float t = i/(float)N;
		P[i] = vec2{250 + 100*cosf(t*6*M_PI), 300*t + 30};
		P[i+1] = P[i];
		P[i+1][1] += 50;
	}

	TriangleStrip T{N};

	for(Triangle<vec2> triangle: assemble(T, P)){
		vec3 color = is_front_facing(triangle[0], triangle[1], triangle[2])? blue: red;
		
		for(Pixel p: rasterizeTriangle(triangle))
			Img(p.x,p.y) = color;
	}
	
	Img.save("output.png");
}

