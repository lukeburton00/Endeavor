#pragma once
#include "Tetromino.hpp"

class T : public Tetromino
{
public:
    using Tetromino::Tetromino;
    void buildTiles() override;
    void resolveRotations() override;
};