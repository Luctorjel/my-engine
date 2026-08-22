#include "raylib.h"
#include <stdlib.h>

typedef struct Entiny Entiny;
typedef struct Event Event;

typedef struct Player{
    int sprite, x, y;
}Player;

typedef struct Entiny{
    int sprite, x, y;
    void (*eFun)(Scene,Player);
}Entiny;

typedef struct Event{
    int x, y;
    void (*eFun)(Scene,Player);
}Event;

typedef struct Scene{
    Entiny *entinys;
    Event *events;
    int spriteScene[10][10];
    int colision[10][10];
}Scene;

int main(void)
{
    // Configuração da janela (tela real)
    const int screenWidth = 768;
    const int screenHeight = 640;

    // Configuração da resolução interna do jogo (tela virtual)
    const int virtualScreenWidth = 96;
    const int virtualScreenHeight = 80;
    
    // engine vars
    Texture2D *texturas = malloc(3*sizeof(Texture2D)); 
    Scene onScene;
    Player p;
    

    InitWindow(screenWidth, screenHeight, "Resolução do Jogo");

    // Render texture para onde tudo do jogo será desenhado
    RenderTexture2D target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);

    // Retângulos para renderizar a textura interna na tela final
    // (A altura é negativa devido ao sistema de coordenadas do OpenGL)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
    Rectangle destRec = { 0.0f, 0.0f, (float)screenWidth, (float)screenHeight };
    Vector2 origin = { 0.0f, 0.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // 1. Desenha o jogo dentro da Render Texture (Resolução Virtual)
        BeginTextureMode(target);
            ClearBackground(BLACK);
            
            DrawRectangleV((Vector2){0.0f,0.0f}, (Vector2){8.0f,8.0f}, RED);
            // <-- Adicione a lógica de renderização do seu jogo aqui

        EndTextureMode();

        // 2. Desenha a Render Texture esticada na tela final
        BeginDrawing();
            ClearBackground(BLACK);

            DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);

        EndDrawing();
    }
    
    // Limpeza de memória
    free(texturas);
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}