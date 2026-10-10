#include "sudoku_solver.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define WINDOW_SIZE 600
#define GRID_SIZE 540
#define CELL_SIZE (GRID_SIZE / 9)
#define OFFSET 30

int sudoku_gui(int **sudoku)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow(
        "Sudoku Solver",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600, 600,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    if (renderer == NULL)
    {
        fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    if (TTF_Init() == -1)
{
    fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}

TTF_Font *font = TTF_OpenFont(
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
    32
);

if (font == NULL)
{
    fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}


    int selected_row = -1;
    int selected_col = -1;
    int running = 1;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x - OFFSET;
                int y = event.button.y - OFFSET;

                if (x >= 0 && x < GRID_SIZE &&
                    y >= 0 && y < GRID_SIZE)
                {
                    selected_col = x / CELL_SIZE;
                    selected_row = y / CELL_SIZE;
                }
            }

            if (event.type == SDL_KEYDOWN)
            {
                SDL_Keycode key = event.key.keysym.sym;
		if (key == SDLK_s)
{
    int result = sudoku_solver(sudoku);

    if (result == 0)
        printf("Sudoku solved!\n");
    else
        printf("No solution found.\n");
}

                if (key == SDLK_ESCAPE)
                    running = 0;

                if (selected_row >= 0 && selected_col >= 0)
                {
                    if (key >= SDLK_1 && key <= SDLK_9)
                    {
                        sudoku[selected_row][selected_col] =
                            key - SDLK_0;
                    }

                    if (key == SDLK_BACKSPACE || key == SDLK_DELETE)
                    {
                        sudoku[selected_row][selected_col] = 0;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (selected_row >= 0 && selected_col >= 0)
        {
            SDL_Rect cell = {
                OFFSET + selected_col * CELL_SIZE,
                OFFSET + selected_row * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            };

            SDL_SetRenderDrawColor(renderer, 210, 230, 255, 255);
            SDL_RenderFillRect(renderer, &cell);
        }

        for (int i = 0; i <= 9; i++)
        {
            int thickness = (i % 3 == 0) ? 3 : 1;

            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

            for (int t = 0; t < thickness; t++)
            {
                int pos = OFFSET + i * CELL_SIZE + t;

                SDL_RenderDrawLine(renderer,
                    pos, OFFSET,
                    pos, OFFSET + GRID_SIZE);

                SDL_RenderDrawLine(renderer,
                    OFFSET, pos,
                    OFFSET + GRID_SIZE, pos);
            }
        }
	SDL_Color text_color = {20, 20, 20, 255};

for (int row = 0; row < 9; row++)
{
    for (int col = 0; col < 9; col++)
    {
        int value = sudoku[row][col];

        if (value == 0)
            continue;

        char text[2];
        snprintf(text, sizeof(text), "%d", value);

        SDL_Surface *surface =
            TTF_RenderText_Blended(font, text, text_color);

        if (surface == NULL)
            continue;

        SDL_Texture *texture =
            SDL_CreateTextureFromSurface(renderer, surface);

        if (texture != NULL)
        {
            SDL_Rect dest = {
                OFFSET + col * CELL_SIZE
                    + (CELL_SIZE - surface->w) / 2,
                OFFSET + row * CELL_SIZE
                    + (CELL_SIZE - surface->h) / 2,
                surface->w,
                surface->h
            };

            SDL_RenderCopy(renderer, texture, NULL, &dest);
            SDL_DestroyTexture(texture);
        }

        SDL_FreeSurface(surface);
    }
}
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

