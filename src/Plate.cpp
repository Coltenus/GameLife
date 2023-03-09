//
// Created by colte on 09.03.2023.
//

#include "Plate.h"

namespace gml {
    Plate::Plate(Vector2 pos) : _active(false), _pPlates(nullptr), _time(0), _check(false) {
        _pos = {(float)(((int)pos.x)/PL_W)*PL_W, (float)(((int)pos.y)/PL_H)*PL_H};
        _posArray = {_pos.x/PL_W, _pos.y/PL_H};
    }

    void Plate::Update() {
        static float time = GetTime();
        static float delta;
        static int neighbors;
        if(_posArray.x == 0 && _posArray.y == 0) {
            delta = GetTime() - time;
            time = GetTime();
        }
        _time += delta;
        if(_pPlates && _time >= DELTA_TIME) {
            _time = 0;
            neighbors = CheckNeighbors();
            if(_active) {
                if (neighbors < 2 || neighbors > 3) {
                    Invert(true);
                }
            }
            else if(neighbors == 3) {
                Invert(true);
            }
        }
    }

    void Plate::Selection() {
        static Vector2 mouse;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouse = GetMousePosition();
            if(mouse.x >= _pos.x && mouse.x < _pos.x + PL_W
               && mouse.y >= _pos.y && mouse.y < _pos.y + PL_H)
                Invert();
        }
    }

    void Plate::Draw() {
        if(_active)
            DrawRectangleV(_pos, {PL_W, PL_H}, GREEN);
        else DrawRectangleV(_pos, {PL_W, PL_H}, BLACK);
    }

    Plate::Plate() : Plate({0, 0}) {}

    void Plate::SetPos(Vector2 pos) {
        _pos = {(float)(((int)pos.x)/PL_W)*PL_W, (float)(((int)pos.y)/PL_H)*PL_H};
        _posArray = {_pos.x/PL_W, _pos.y/PL_H};
    }

    void Plate::SetPlates(std::array<std::array<gml::Plate, WIDTH/PL_W>, HEIGHT/PL_H>& plates) {
        _pPlates = &plates;
    }

    void Plate::Invert(bool check) {
        _active = !_active;
        if(check) _check = true;
    }

    bool Plate::GetStatus() {
        return _active;
    }

    void Plate::ResetCheck() {
        _check = false;
    }

    void Plate::ResetStatus() {
        _active = false;
        ResetCheck();
    }

    int Plate::CheckNeighbors() {
        int result = 0;

        if(_posArray.x > 0) {
            if((*_pPlates)[_posArray.y][_posArray.x-1]._active && !(*_pPlates)[_posArray.y][_posArray.x-1]._check
            || !(*_pPlates)[_posArray.y][_posArray.x-1]._active && (*_pPlates)[_posArray.y][_posArray.x-1]._check)
                result++;
            if(_posArray.y > 0) {
                if((*_pPlates)[_posArray.y-1][_posArray.x-1]._active && !(*_pPlates)[_posArray.y-1][_posArray.x-1]._check
                   || !(*_pPlates)[_posArray.y-1][_posArray.x-1]._active && (*_pPlates)[_posArray.y-1][_posArray.x-1]._check)
                    result++;
            }
        }
        if(_posArray.x < WIDTH/PL_W-1) {
            if((*_pPlates)[_posArray.y][_posArray.x+1]._active && !(*_pPlates)[_posArray.y][_posArray.x+1]._check
               || !(*_pPlates)[_posArray.y][_posArray.x+1]._active && (*_pPlates)[_posArray.y][_posArray.x+1]._check)
                result++;
            if(_posArray.y < HEIGHT/PL_H-1) {
                if((*_pPlates)[_posArray.y+1][_posArray.x+1]._active && !(*_pPlates)[_posArray.y+1][_posArray.x+1]._check
                   || !(*_pPlates)[_posArray.y+1][_posArray.x+1]._active && (*_pPlates)[_posArray.y+1][_posArray.x+1]._check)
                    result++;
            }
        }
        if(_posArray.y > 0) {
            if((*_pPlates)[_posArray.y-1][_posArray.x]._active && !(*_pPlates)[_posArray.y-1][_posArray.x]._check
               || !(*_pPlates)[_posArray.y-1][_posArray.x]._active && (*_pPlates)[_posArray.y-1][_posArray.x]._check)
                result++;
            if(_posArray.x < WIDTH/PL_W-1) {
                if((*_pPlates)[_posArray.y-1][_posArray.x+1]._active && !(*_pPlates)[_posArray.y-1][_posArray.x+1]._check
                   || !(*_pPlates)[_posArray.y-1][_posArray.x+1]._active && (*_pPlates)[_posArray.y-1][_posArray.x+1]._check)
                    result++;
            }
        }
        if(_posArray.y < HEIGHT/PL_H-1) {
            if((*_pPlates)[_posArray.y+1][_posArray.x]._active && !(*_pPlates)[_posArray.y+1][_posArray.x]._check
               || !(*_pPlates)[_posArray.y+1][_posArray.x]._active && (*_pPlates)[_posArray.y+1][_posArray.x]._check)
                result++;
            if(_posArray.x > 0) {
                if ((*_pPlates)[_posArray.y+1][_posArray.x-1]._active && !(*_pPlates)[_posArray.y+1][_posArray.x-1]._check
                    || !(*_pPlates)[_posArray.y+1][_posArray.x-1]._active && (*_pPlates)[_posArray.y+1][_posArray.x-1]._check)
                    result++;
            }
        }

        return result;
    }
} // gml