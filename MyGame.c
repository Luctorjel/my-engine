#include "raylib.h"

typedef struct Entiny Entiny;
typedef struct Event Event;
typedef struct Scene Scene;

typedef struct Player{
    int sprite, x, y;
}Player;

typedef struct Entiny{
    int sprite, x, y;
    void (*eFun)(Scene*,Player);
}Entiny;

typedef struct Event{
    int x, y;
    void (*eFun)(Scene*,Player);
}Event;

typedef enum {
    INVISIBLE,
    ONSCREEN
}TextState;

typedef struct Scene{
    Entiny *entinys;
    Event *events;
    int spriteScene[10][10];
    int colision[10][10];
    char text[21];
    TextState t;
}Scene;

int main(void)
{
    // Configuração da janela (tela real) 8 x a virtual
    const int screenWidth = 768;
    const int screenHeight = 640;

    // Configuração da resolução interna do jogo (tela virtual)
    const int virtualScreenWidth = 96;
    const int virtualScreenHeight = 80;
    
    InitWindow(screenWidth, screenHeight, "Title");
    
    // engine vars
    Texture2D texturas[1];//coloque o tanto que voce quer de texturas
    Scene onScene;
    Player p;
    int textT=0;
    
    // load textures
    texturas[0]=LoadTexture("player.png");
    
    //init player
    p.sprite =0;
    p.x=10;
    p.y=0;

    // Render texture para onde tudo do jogo será desenhado eceto o texto
    RenderTexture2D target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);

    // Retângulos para renderizar a textura interna na tela real
    Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
    Rectangle destRec = { 0.0f, 0.0f, (float)screenWidth, (float)screenHeight };
    Vector2 origin = { 0.0f, 0.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Desenha o jogo dentro da Render Texture (Resolução Virtual)
        BeginTextureMode(target);
            ClearBackground(BLACK);
            // retangulo de teste eu chamo ele de juvenildo
            DrawRectangleV((Vector2){0.0f,0.0f}, (Vector2){8.0f,8.0f}, RED);
            // DRAW player
            DrawTexture(texturas[p.sprite], p.x, p.y, WHITE); 

        EndTextureMode();

        // Desenha a Render Texture no tamanho real da tela
        BeginDrawing();
            ClearBackground(BLACK);

            DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
            // draw text isso adiciona um texto por tempo limitado
            if(onScene.t==ONSCREEN && textT < 120){
                DrawText(onScene.text, 30, 500, 30, BLUE);
                textT++;
            }else{
                textT=0;
                onScene.t = INVISIBLE;
            }
        EndDrawing();
    }
    
    // Limpeza de memória
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}