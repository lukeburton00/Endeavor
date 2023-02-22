#pragma once
#include "Tetromino.hpp"

class I : public Tetromino
{
public:
    using Tetromino::Tetromino;
    void buildTiles() override;
    void resolveRotations() override;
};