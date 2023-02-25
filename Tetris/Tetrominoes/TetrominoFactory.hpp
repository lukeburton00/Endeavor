#pragma once
#include "I.hpp"
#include "J.hpp"
#include "L.hpp"
#include "O.hpp"
#include "S.hpp"
#include "T.hpp"
#include "Z.hpp"

class TetrominoFactory
{
public:
    std::shared_ptr<Tetromino> getTetromino(Type type, float scale) const
    {
        switch (type)
        {
            case Type::I:
            {
                auto tet = std::make_shared<I>(scale);
                
                return tet;
                break;
            }

            case Type::J:
            {
                auto tet = std::make_shared<J>(scale);

                return tet;
                break;
            }

            case Type::L:
            {
                auto tet = std::make_shared<L>(scale);

                return tet;
                break;
            }

            case Type::O:
            {
                auto tet = std::make_shared<O>(scale);

                return tet;
                break;
            }

            case Type::S:
            {
                auto tet = std::make_shared<S>(scale);

                return tet;
                break;
            }

            case Type::T:
            {
                auto tet = std::make_shared<T>(scale);

                return tet;
                break;
            }

            case Type::Z:
            {
                auto tet = std::make_shared<Z>(scale);

                return tet;
                break;
            }
        }
    }
};