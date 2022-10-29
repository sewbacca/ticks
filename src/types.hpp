
#pragma once

#include <cinttypes>

typedef uint_fast16_t bitboard;

enum Player
{
	NO_PLAYER = 0b00,
	PLAYER_HORIZONTAL = 0b01, // Player one
	PLAYER_VERTICAL   = 0b10 // Player two
};

// Swap player
Player operator~(Player player);

enum Square
{
	A1, B1, C1,
	A2, B2, C2,
	A3, B3, C3,
	NO_SQUARE,
};

extern Square squares[9];

bitboard square_as_bb(Square square);

enum State
{
	EMPTY      = 0b00,
	HORIZONTAL = 0b01,
	VERTICAL   = 0b10,
	T          = HORIZONTAL | VERTICAL,
};

class Board
{
public:
	Player turn = PLAYER_HORIZONTAL;
	State at(Square square) const;
	void set(Square square, State state);
	void place(Square square, Player player);
	void unplace(Square square, Player player);
private:
	bitboard m_hpieces = 0;
	bitboard m_vpieces = 0;
};

struct Move
{
	Move();
	Move(Square square);
	Square square;
};

bool operator==(Move a, Move b);

// Assuming a board 3 x 3 and two moves per square, which is impossible to achieve since three ticks must have happened earlier
constexpr int MAX_MOVES = 3 * 3 * 2;

// Stack based move list
class MoveList
{
public:
	const Move* begin() const;
	const Move* end() const;
	void push_back(Move move);
	void pop_back();
	Move back() const;
	size_t size() const;
private:
	Move m_moves[MAX_MOVES];
	size_t m_size {};
};

class Game
{
public:
	const Board& board() const;
	// Returns false if non legal
	bool make(Move move);
	void undo();
	bool can_undo() const;
	size_t depth() const;
private:
	Board m_board {};
	MoveList m_undolist {};
};
