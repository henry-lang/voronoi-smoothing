#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Pixel {
    uint8_t r, g, b;
} Pixel;

typedef struct Seed {
    int x;
    int y;
    Pixel color;
} Seed;

const int WIDTH = 600;
const int HEIGHT = 400;

const int NUM_SEEDS = 100;
Seed seeds[NUM_SEEDS];

Pixel frame[HEIGHT][WIDTH];

void seeds_init() {
    for(int i = 0; i < NUM_SEEDS; i++) {
        seeds[i] = (Seed) {
            .x = rand() % WIDTH,
            .y = rand() % HEIGHT,
            .color = (Pixel) {.r = rand() % 255, .g = rand() % 255, .b = rand() % 255}
        };
    }
}

void frame_write() {
    printf("P3\n%d %d\n255\n", WIDTH, HEIGHT);
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            printf("%d %d %d\n", frame[y][x].r, frame[y][x].g, frame[y][x].b);
        }
    }
}

int main() {
    srand(time(NULL));
    seeds_init();

    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            double r = 0;
            double g = 0;
            double b = 0;
            double total = 0;
            for(int s = 0; s < NUM_SEEDS; s++) {
                double dx = seeds[s].x - x;
                double dy = seeds[s].y - y;
                double distance = sqrt(dx*dx+dy*dy);
                total += distance;
            }
            for(int s = 0; s < NUM_SEEDS; s++) {
                double dx = seeds[s].x - x;
                double dy = seeds[s].y - y;
                double distance = sqrt(dx*dx+dy*dy);
                r += sqrt(distance / total) * seeds[s].color.r;
                g += sqrt(distance / total) * seeds[s].color.g;
                b += sqrt(distance / total) * seeds[s].color.b;
            }
            frame[y][x] = (Pixel) {.r = r, .g = g, .b = b};
        }
    }
    frame_write();
 }
