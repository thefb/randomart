#include <stdio.h>
#include <stdint.h>
#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 400 
#define HEIGHT 400 

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} RGBA32;

static RGBA32 pixels[WIDTH*HEIGHT];

typedef struct {
    float x, y;
} Vector2;

typedef struct {
    float r, g, b;
} Color;

Color gray_gradient(float x, float y){
    UNUSED(y);
    nob_log(INFO, "Calculando cor para a posição x normalizada: %f", x);
    return (Color) {x, x, x};
};

void render_pixels(Color (*f)(float x, float y)) {
    nob_log(INFO, "iniciando a renderização dos pixels...");
    for (size_t y = 0; y < HEIGHT; y++) {
        float ny = (float)y/HEIGHT * 2.0f - 1;
        for (size_t x = 0; x < WIDTH; x++) {
            float nx = (float)x/WIDTH* 2.0f - 1;
            nob_log(
                INFO, 
                "Posição do pixel: (x: %zu, y: %zu), Normalizado: (nx: %f, ny: %f)", x, y, nx, ny
            );
            Color c = f(nx, ny);
            size_t index = y * WIDTH + x;
            pixels[index].r = (c.r + 1)/2*255;
            pixels[index].g = (c.g + 1)/2*255;
            pixels[index].b = (c.b + 1)/2*255;
            pixels[index].a = 255;

            nob_log(
                INFO, 
                "Pixel [%zu]: Cor calculada (R: %d, G: %d, B: %d, A: %d)", 
                index, pixels[index].r, pixels[index].g, pixels[index].b, pixels[index].a);
        }};
    
    nob_log(INFO, "Renderização dos pixels finalizada.");
};

int main() {
    nob_log(INFO, "Iniciando o programa para gerar imagem de gradiente cinza...");
    render_pixels(gray_gradient);
    const char *output_path = "./output.png";
    nob_log(INFO, "Salvando a imagem em %s...", output_path);
    if (!stbi_write_png(output_path, WIDTH, HEIGHT, 4, pixels, WIDTH*sizeof(RGBA32))){
        nob_log(ERROR, "Could not save image %s", output_path);
        return 1;
    };
    nob_log(INFO, "Imagem salva com sucesso em %s", output_path);
    return 0;
};
