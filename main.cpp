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
    std::array<std::array<gml::Plate, WIDTH/PL_W>, HEIGHT/PL_H> plates;
    {
        float i = 0, j = 0;
        int t;
        for (auto &row: plates) {
            j = 0;
            for (auto &el: row) {
                el.SetPos({j*PL_W, i*PL_H});
                el.SetPlates(plates);
                t = GetTime()*1000000;
                if(t%2 == 0) el.Invert();
                j++;
            }
            i++;
        }
    }

    while (!done && !WindowShouldClose()) {
        if(IsKeyPressed(KEY_R))
            for (auto& row: plates)
                for (auto& el: row)
                    el.ResetStatus();
        if(IsKeyPressed(KEY_SPACE)) pause = !pause;
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
            DrawText("Pause", 10, 10, 20, GREEN);
        EndDrawing();
    }
    return 0;
}
