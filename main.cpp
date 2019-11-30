
#include <SDL2/SDL.h>

int main() {
        SDL_Window *win = SDL_CreateWindow("graphic thing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE);
        SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

        SDL_Texture *text = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, 640, 480);

        Uint32 back_buffer[640*480] = {0};

        bool running = 1;
        Uint32 offset = 0;
        while (running) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                                running = 0;
                        }
                }

                for (size_t i = 0; i < 480; ++i) {
                        for (size_t j = 0; j < 640; ++j) {
                                back_buffer[i * 640 + j] = ((i) << 16) | ((j + offset) << 8);
                        }
                }
                ++offset;

                SDL_RenderClear(rend);
                SDL_UpdateTexture(text, 0, back_buffer, 640 * 4);
                SDL_RenderCopy(rend, text, 0, 0);
                SDL_RenderPresent(rend);
        }
}
