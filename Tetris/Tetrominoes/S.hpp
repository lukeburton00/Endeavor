#pragma once
#include "Tetromino.hpp"

class S : public Tetromino
{
public:
    using Tetromino::Tetromino;
    void buildTiles() override;
    void resolveRotations() override;
};