#pragma once
#include "Tetromino.hpp"

class O : public Tetromino
{
public:
    using Tetromino::Tetromino;
    void buildTiles() override;
    void resolveRotations() override;
};