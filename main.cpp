
#include <SDL2/SDL.h>

int main() {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_Window *win = SDL_CreateWindow("graphic thing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
        SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

        SDL_Texture *text = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, 640, 480);

        Uint32 back_buffer[640*480] = {};

        bool running = 1;
        Uint32 x_offset = 0;
        Uint32 y_offset = 0;
        while (running) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                                running = 0;
                        }
                }

                Uint32 *pixel = back_buffer;
                for (size_t i = 0; i < 480; ++i) {
                        for (size_t j = 0; j < 640; ++j) {
                                *pixel = ((i + y_offset) << 16) | ((j + x_offset) << 8);
                                ++pixel;
                        }
                }
                ++x_offset;
                y_offset += 2;

                SDL_RenderClear(rend);
                SDL_UpdateTexture(text, 0, back_buffer, 640 * 4);
                SDL_RenderCopy(rend, text, 0, 0);
                SDL_RenderPresent(rend);
        }

        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
}
