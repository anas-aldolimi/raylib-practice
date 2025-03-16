#include <stdio.h>
#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>



#define PLAYER_BASE_SIZE    20.0f

const int screenWidth = 800;
const int screenHeight = 450;



typedef struct Player {
    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    Vector3 collider;
    Color color;
} Player;



typedef struct Astroid{
    Vector2 position;
    int Radius;
    Vector2 direction;
    Color color;
}Astroid;

Vector2 spawnAstroid();

void sceneDraw();

void update();

void ready();

Astroid Meteor[10] = {0};
Player player;
static float shipHeight = 10.0f;
bool gameOver = false;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    

    // Initialization
    //--------------------------------------------------------------------------------------
    
    int counter;
    
    ready();

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(55);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        
        

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        if(!gameOver)    
            update();    
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            
            sceneDraw();
            
            

     

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}




Vector2 spawnAstroid(){
    srand(time(NULL));
    Vector2 v;
    v.x = rand() % screenWidth;
    v.y = rand() % screenHeight;
    
    return v;
}




void sceneDraw(){
    Vector2 v1 = { player.position.x + sinf(player.rotation*DEG2RAD)*(shipHeight), player.position.y - cosf(player.rotation*DEG2RAD)*(shipHeight) };
    Vector2 v2 = { player.position.x - cosf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE/2), player.position.y - sinf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE/2) };
    Vector2 v3 = { player.position.x + cosf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE/2), player.position.y + sinf(player.rotation*DEG2RAD)*(PLAYER_BASE_SIZE/2) };
    DrawTriangle(v1, v2, v3, MAROON);
    for (int i =0; i<10; i++){
        DrawCircle(Meteor[i].position.x,Meteor[i].position.y,Meteor[i].Radius,Meteor[i].color);
    }

    if(gameOver) DrawText("GAME OVER", screenWidth/2, screenHeight/2, 50, RED);

}

void update(){
    shipHeight = (PLAYER_BASE_SIZE/2)/tanf(20*DEG2RAD);

    player.speed.x = sin(player.rotation*DEG2RAD)*10.0;
    player.speed.y = cos(player.rotation*DEG2RAD)*10.0;


    if (IsKeyDown(KEY_LEFT)) player.rotation -= 3;
    if (IsKeyDown(KEY_RIGHT)) player.rotation += 3;


    if (IsKeyDown(KEY_UP))
    {
        if (player.acceleration < 1) player.acceleration += 0.04f;
    }
    else
    {
        if (player.acceleration > 0) player.acceleration -= 0.02f;
        else if (player.acceleration < 0) player.acceleration = 0;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        if (player.acceleration > 0) player.acceleration -= 0.04f;
        else if (player.acceleration < 0) player.acceleration = 0;
    }


    player.position.x += (player.speed.x * player.acceleration);
    player.position.y -= (player.speed.y * player.acceleration);






    for (int i = 0; i < 10; i++){

        if(Meteor[i].position.x > screenWidth && Meteor[i].direction.x == 1) {
        Meteor[i].direction.x = -1;
    }
        else if(Meteor[i].position.x < 0 && Meteor[i].direction.x == -1) 
        Meteor[i].direction.x = 1;
        
        if(Meteor[i].position.y > screenHeight && Meteor[i].direction.y == 1) {
            Meteor[i].direction.y = -1;
        }
        else if(Meteor[i].position.y < 0 && Meteor[i].direction.y == -1) 
        Meteor[i].direction.y = 1;
            
            
        Meteor[i].position.x += (4 * Meteor[i].direction.x);
        Meteor[i].position.y += (4 * Meteor[i].direction.y);

    }
    for (int i = 0; i < 10; i++)
    {
        if (CheckCollisionCircles((Vector2){player.collider.x, player.collider.y}, player.collider.z, Meteor[i].position, Meteor[i].Radius))
        gameOver = true;
    }
    
}



void ready(){
    srand(time(NULL));
    // meteor spawn random
    for(int i = 0; i < 10; i++){
       
        Meteor[i].position.x = rand() % screenWidth;
        Meteor[i].position.y = rand() % screenHeight;
        Meteor[i].Radius = 10;
        Meteor[i].direction = (Vector2){1,1};
        Meteor[i].color = RED;
    }

    // player values set
    player.position = (Vector2){screenWidth/2, screenHeight/2 - shipHeight/2};
    player.speed = (Vector2){0, 0};
    player.acceleration = 0;
    player.rotation = 0;
    player.collider = (Vector3){player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight/2.5f), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight/2.5f), 12};
    player.color = LIGHTGRAY;


    gameOver = false;

}



