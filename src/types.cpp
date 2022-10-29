
#include <types.hpp>

#include <cassert>

Square squares[9]
{
	A1, B1, C1,
	A2, B2, C2,
	A3, B3, C3
};

State Board::at(Square square) const
{
	// If first player (HORIZONTAL_PLAYER) has placed a piece on given sqare, add state HORIZONTAL
	// Same goes for second player, but add VERTICAL
	return (State) (
			(square_as_bb(square) & m_hpieces ? HORIZONTAL : EMPTY) |
			(square_as_bb(square) & m_vpieces ? VERTICAL : EMPTY)
		);
}

void Board::set(Square square, State state)
{
	bitboard bb = square_as_bb(square);
	m_hpieces &= ~bb;
	m_vpieces &= ~bb;

	if(state & HORIZONTAL)
		m_hpieces |= bb;
	if(state & VERTICAL)
		m_vpieces |= bb;
}

void Board::place(Square square, Player player)
{
	set(square, (State) (at(square) | player));
};

void Board::unplace(Square square, Player player)
{
	set(square, (State) (at(square) & ~player));
};

const Move* MoveList::begin() const
{
	return m_moves;
}

const Move* MoveList::end() const
{
	return m_moves + m_size;
}

void MoveList::push_back(Move move)
{
	assert(m_size < MAX_MOVES);
	m_moves[m_size++] = move;
}

void MoveList::pop_back()
{
	m_size--;
}

Move MoveList::back() const
{
	return m_moves[m_size-1];
}

size_t MoveList::size() const
{
	return m_size;
}

const Board& Game::board() const
{
	return m_board;
}

bool Game::make(Move move)
{
	if(m_undolist.size() > 0 && m_undolist.back() == move) return false;

	State state = m_board.at(move.square);
	if (state & m_board.turn) return false;

	m_board.place(move.square, m_board.turn);
	m_board.turn = ~m_board.turn;
	m_undolist.push_back(move);

	return true;
}

void Game::undo()
{
	assert(can_undo());

	Move move = m_undolist.back();
	m_board.turn = ~m_board.turn;

	m_board.unplace(move.square, m_board.turn);
	m_undolist.pop_back();
}

bool Game::can_undo() const
{
	return depth() > 0;
};

size_t Game::depth() const
{
	return m_undolist.size();
}

Player operator~(Player player)
{
	if(player == NO_PLAYER)
		return NO_PLAYER;

	return player == PLAYER_HORIZONTAL ? PLAYER_VERTICAL : PLAYER_HORIZONTAL;
}

bitboard square_as_bb(Square square)
{
	return 1ULL << square;
}

bool operator==(Move a, Move b)
{
	return a.square == b.square;
}

Move::Move() : Move{ NO_SQUARE } { }

Move::Move(Square square) { this->square = square; };

