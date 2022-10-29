
#include <rules.hpp>

static Square winning[][3] {
	// Rows
	{ A1, B1, C1 },
	{ A2, B2, C2 },
	{ A3, B3, C3 },
	// Columns
	{ A1, A2, A3 },
	{ B1, B2, B3 },
	{ C1, C2, C3 },
	// Diagonals
	{ A1, B2, C3 },
	{ A3, B2, C1 }
};

bool is_finished(const Board& board)
{
	// If there is any full sequence, it is a finished game

	for (auto&& sequence : winning)
	{
		State total_state = T;
		for(Square pos : sequence)
			total_state = (State) (total_state & board.at(pos));

		if(total_state == T)
			return true;
	}

	return false;
}

Player winner(const Board& board)
{
	return ~board.turn;
}

void generate_pseudo_legal_moves(const Board& board, MoveList& out)
{
	for(Square square : squares)
	{
		if (!(board.at(square) & board.turn))
			out.push_back(Move(square));
	}
}
