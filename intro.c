//#include "gamelib.h"

// #define LOGO_PATH "logo.png"
// #define SOUND_PATH "intro.wav"

// int main(int argc, char *argv[])
// {
//     SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
//     IMG_Init(IMG_INIT_PNG);
//     Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);

//     // إعداد الصوت
//     Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
//     Mix_Chunk *sound = Mix_LoadWAV(SOUND_PATH);
//     if (!sound)
//     {
//         printf("خطأ في تحميل الصوت: %s\n", Mix_GetError());
//         return 1;
//     }

//     SDL_Window *window = SDL_CreateWindow(
//         "Splash Screen",
//         SDL_WINDOWPOS_CENTERED,
//         SDL_WINDOWPOS_CENTERED,
//         800, 600,
//         SDL_WINDOW_SHOWN);

//     SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//     // تحميل اللوجو
//     SDL_Surface *logoSurface = IMG_Load(LOGO_PATH);
//     if (!logoSurface)
//     {
//         printf("خطأ في تحميل الصورة: %s\n", IMG_GetError());
//         return 1;
//     }

//     SDL_Texture *logoTexture = SDL_CreateTextureFromSurface(renderer, logoSurface);
//     SDL_FreeSurface(logoSurface);

//     int logo_w, logo_h;
//     SDL_QueryTexture(logoTexture, NULL, NULL, &logo_w, &logo_h);

//     SDL_Rect dst = {(800 - logo_w) / 2, (600 - logo_h) / 2, logo_w, logo_h};

//     SDL_SetTextureBlendMode(logoTexture, SDL_BLENDMODE_BLEND);

//     // 🔊 شغل الصوت
//     int channel = Mix_PlayChannel(-1, sound, 0);
//     if (channel == -1)
//     {
//         printf("خطأ في تشغيل الصوت: %s\n", Mix_GetError());
//     }

//     // 🔹 FADE-IN

//     double alpha = 1;
//     while (alpha <= 255)
//     {
//         SDL_SetTextureAlphaMod(logoTexture, alpha);
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);
//         SDL_RenderCopy(renderer, logoTexture, NULL, &dst);
//         SDL_RenderPresent(renderer);
//         SDL_Delay(10);
//         alpha *= 1.05;
//     }

//     // 🔹 انتظار حتى يكمل الصوت
//     while (Mix_Playing(channel)) // تبقى في اللوب حتى يكمّل الصوت
//     {
//         SDL_SetTextureAlphaMod(logoTexture, 255); // اللوجو ظاهر كامل
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);
//         SDL_RenderCopy(renderer, logoTexture, NULL, &dst);
//         SDL_RenderPresent(renderer);
//         SDL_Delay(10);
//     }

//     // 🔹 FADE-OUT
//     for (int alpha = 255; alpha >= 0; alpha -= 5)
//     {
//         SDL_SetTextureAlphaMod(logoTexture, alpha);
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//         SDL_RenderClear(renderer);
//         SDL_RenderCopy(renderer, logoTexture, NULL, &dst);
//         SDL_RenderPresent(renderer);
//         SDL_Delay(10);
//     }

//     // تنظيف
//     Mix_FreeChunk(sound);
//     Mix_CloseAudio();
//     Mix_Quit();
//     SDL_DestroyTexture(logoTexture);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     IMG_Quit();
//     SDL_Quit();

//     return 0;
// }
