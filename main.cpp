#include <iostream>
#include <raylib.h>
#include <array>
#include "src/common.h"
#include "src/Plate.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "Game Life");
    SetTargetFPS(120);
    bool done = false;
    bool pause = true;
    float time, stopT;
    float offset = 0;
    std::array<std::array<gml::Plate, WIDTH/PL_W>, HEIGHT/PL_H> plates;
    {
        float i = 0, j = 0;
        for (auto &row: plates) {
            j = 0;
            for (auto &el: row) {
                el.SetPos({j*PL_W, i*PL_H});
                el.SetPlates(plates);
                if((int)(i+j)%4 == 0)el.Invert();
                j++;
            }
            i++;
        }
    }

    stopT = GetTime();
    while (!done && !WindowShouldClose()) {
        if(IsKeyPressed(KEY_R))
            for (auto& row: plates)
                for (auto& el: row)
                    el.ResetStatus();
        if(IsKeyPressed(KEY_SPACE)) {
            if(pause)
                offset += GetTime() - stopT;
            else stopT = GetTime();
            pause = !pause;
        }
        if(!pause) {
            for (auto &row: plates)
                for (auto &el: row)
                    el.ResetCheck();
            for (auto &row: plates)
                for (auto &el: row)
                    el.Update();
        }
        for (auto &row: plates)
            for (auto &el: row)
                el.Selection();
        BeginDrawing();
        ClearBackground(GRAY);
        for (auto& row: plates)
            for (auto& el: row)
                el.Draw();
        if(pause)
            DrawText("Paused", WIDTH - 80, 35, 20,  WHITE);
        else time = GetTime() - offset;
        DrawText(TextFormat("%4d:%02d:%02d", (int)time/3600, (int)time/60%60, (int)time%60), WIDTH - 100, 10, 20, WHITE);
        EndDrawing();
    }
    return 0;
}
