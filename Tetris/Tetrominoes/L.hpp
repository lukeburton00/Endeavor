#pragma once
#include "Tetromino.hpp"

class L : public Tetromino
{
public:
    using Tetromino::Tetromino;
    void buildTiles() override;
    void resolveRotations() override;
};