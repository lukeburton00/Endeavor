#pragma once
#include "Tetromino.hpp"

class J : public Tetromino
{
public:
    using Tetromino::Tetromino;
    void buildTiles() override;
    void resolveRotations() override;
};