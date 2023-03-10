//
// Created by colte on 09.03.2023.
//

#ifndef GAMELIFE_PLATE_H
#define GAMELIFE_PLATE_H

#include <raylib.h>
#include <array>
#include "common.h"

namespace gml {
#define PL_W 5
#define PL_H 5
#define DELTA_TIME 0.2
    class Plate {
    private:
        std::array<std::array<gml::Plate, WIDTH/PL_W>, HEIGHT/PL_H>* _pPlates;
        bool _active, _check;
        Vector2 _pos, _posArray;
        float _time;

    public:
        Plate();
        Plate(Vector2 pos);
        ~Plate() = default;
        void Update();
        void Selection();
        void Draw();
        void SetPos(Vector2 pos);
        void SetPlates(std::array<std::array<gml::Plate, WIDTH/PL_W>, HEIGHT/PL_H>& plates);
        void Invert(bool check = false);
        bool GetStatus();
        void ResetCheck();
        void ResetStatus(float& offset);
        int CheckNeighbors();
    };

} // gml

#endif //GAMELIFE_PLATE_H
