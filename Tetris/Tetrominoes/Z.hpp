#pragma once
#include "Tetromino.hpp"

class Z : public Tetromino
{
public:
    using Tetromino::Tetromino;
    void buildTiles() override;
    void resolveRotations() override;
};