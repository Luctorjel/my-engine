
#include "raylib.h"
#include <stdbool.h>

//#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

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

bool ChecarColisaoTile(Vector2 posicaoPlayer, Scene* cena) {
	int tileX = (int)(posicaoPlayer.x / 8);
	int tileY = (int)(posicaoPlayer.y / 8);

	// Limites do mapa
	if (tileX < 0 || tileX >= 10 || tileY < 0 || tileY >= 10) return true;

	return (cena->colision[tileY][tileX] == 1);
}

void loadscene1(Scene *cena){
    int temp[10][10] ={{2,2,2,2,2,2,2,2,2,2},
                       {2,1,1,1,1,1,1,1,1,2},
                       {2,1,1,1,1,1,1,1,1,2},
                       {2,1,1,1,1,1,1,1,1,2},
                       {2,1,1,1,1,1,1,1,1,2},
                       {2,1,1,1,1,1,1,1,1,2},
                       {2,1,1,1,1,1,1,1,1,2},
                       {2,1,1,1,1,1,1,1,1,2},
                       {2,1,1,1,1,1,1,1,1,2},
                       {2,2,2,2,2,2,2,2,2,2}};

    int temp2[10][10] ={{1,1,1,1,1,1,1,1,1,1},
                       {1,0,0,0,0,0,0,0,0,1},
                       {1,0,0,0,0,0,0,0,0,1},
                       {1,0,0,0,0,0,0,0,0,1},
                       {1,0,0,0,0,0,0,0,0,1},
                       {1,0,0,0,0,0,0,0,0,1},
                       {1,0,0,0,0,0,0,0,0,1},
                       {1,0,0,0,0,0,0,0,0,1},
                       {1,0,0,0,0,0,0,0,0,1},
                       {1,1,1,1,1,1,1,1,1,1}};
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            cena->spriteScene[i][j] = temp[i][j];
	    cena->colision[i][j] = temp2[i][j];
        }
    }
}

int main(void)
{
    // Configuração da resolução interna do jogo (tela virtual)
    const int virtualScreenWidth = 8*10;
    const int virtualScreenHeight = 8*10;
    // Configuração da janela (tela real) 8 x a virtual
    const int screenWidth = virtualScreenWidth*8;
    const int screenHeight = virtualScreenHeight*8;
    
    InitWindow(screenWidth, screenHeight, "Title");
    
    // engine vars
    Texture2D texturas[3];//coloque o tanto que voce quer de texturas
    Scene onScene;
    Player p;
    int textT=0;
    Color ShaderColor=BLUE;
    int velocidade = 1;
    
    // load textures
    texturas[0]=LoadTexture("player.png");
    texturas[1]=LoadTexture("grama.png");
    texturas[2]=LoadTexture("arbusto.png");
    
    //init player
    p.sprite =0;
    p.x=10;
    p.y=10;
    
    //load init scene
    loadscene1(&onScene);

    // Render texture para onde tudo do jogo será desenhado eceto o texto
    RenderTexture2D target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);

    // Retângulos para renderizar a textura interna na tela real
    Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
    Rectangle destRec = { 0.0f, 0.0f, (float)screenWidth, (float)screenHeight };
    Vector2 origin = { 0.0f, 0.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
	//loop
	Player new=p;
	if (IsKeyDown(KEY_RIGHT)) {
		new.x += velocidade;
		// Checa o canto direito superior e inferior do player
		if (!ChecarColisaoTile((Vector2){new.x + 7, new.y}, &onScene) && !ChecarColisaoTile((Vector2){new.x + 7, new.y + 7}, &onScene)) {
			p.x = new.x;
		}
	}

        // Desenha o jogo dentro da Render Texture (Resolução Virtual)
        BeginTextureMode(target);
            ClearBackground(BLACK);
            //draw scene
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    DrawTexture(texturas[onScene.spriteScene[i][j]], j*8, i*8, ShaderColor); 
                }
            }
            // retangulo de teste eu chamo ele de juvenildo
            DrawRectangleV((Vector2){0.0f,0.0f}, (Vector2){8.0f,8.0f}, RED);
            // DRAW player
            DrawTexture(texturas[p.sprite], p.x, p.y, ShaderColor); 

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
    UnloadTexture(texturas[0]);
    UnloadTexture(texturas[1]);
    UnloadTexture(texturas[2]);
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}