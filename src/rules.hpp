
#pragma once

#include <types.hpp>

bool is_finished(const Board& board);
// Undefined if is_finished returns false
Player winner(const Board& board);
void generate_pseudo_legal_moves(const Board& board, MoveList& out);
