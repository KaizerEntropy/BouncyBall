#include <stdio.h>
#include <SDL2/SDL.h>


// Defining the macros

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define ACCLR_GRAVITY 0.2713



// Defining the struct circle

struct Circle {
    double x;
    double y;
    double radius;
    double v_x;
    double v_y;
};



// Rendering a circle

void FillCircle(SDL_Surface *surface, struct Circle circle){
    
    double low_x = circle.x - circle.radius;
    double low_y = circle.y - circle.radius;
    double high_x = circle.x + circle.radius;
    double high_y = circle.y + circle.radius;
    double radius_square = circle.radius*circle.radius;


    for (double i = low_x; i<high_x; i++){
        for (double j = low_y; j<high_y; j++){
            double centre_distance_square = (i-circle.x)*(i-circle.x) + (j-circle.y)*(j-circle.y);
            if (radius_square > centre_distance_square){
                SDL_Rect pixel = (SDL_Rect) {i, j, 1, 1};
                SDL_FillRect (surface, &pixel, COLOR_WHITE);

            }
        }
    }
}


// Designing the movement mechanics of the circle

void step(struct Circle *circle){

        // Calculating new position

        circle->x = circle->x + circle->v_x;
        circle->y = circle->y + circle->v_y;
        circle->v_y += ACCLR_GRAVITY;   
    
        //Accounting for bouncing off

        if (circle->x + circle->radius > WIDTH){
            circle->x = WIDTH - circle->radius;
            circle->v_x = -circle->v_x;
        }

        if (circle->y + circle->radius > HEIGHT){
            circle->y = HEIGHT - circle->radius;
            circle->v_y = -circle->v_y;
        }

        if (circle->x - circle->radius < 0){
            circle->x = circle->radius;
            circle->v_x = -circle->v_x;
        }
        
        if (circle->y - circle->radius < 0){
            circle->y = circle->radius;
            circle->v_y = -circle->v_y;
        }
    }


// Execution of program

int main(){

    printf("Hello Bouncy Ball!\n");


    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window =  SDL_CreateWindow("Bouncy Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    
    

    struct Circle circle = {200, 200, 100, 5, 0};
    SDL_Rect erase_rect = (SDL_Rect) {0, 0, WIDTH, HEIGHT};
    

    SDL_Event event;
    int sim_run = 1;


    while (sim_run){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                sim_run = 0;
            }
        }
        SDL_FillRect (surface, &erase_rect, COLOR_BLACK);
        FillCircle(surface, circle);
        step(&circle);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(20);
    }
    
    SDL_Delay(2713);

    return 0;
}
