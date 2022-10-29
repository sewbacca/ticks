
#include <engine.hpp>

#include <cmath>

#include <iostream>

constexpr int INF = 2;

class Search
{
public:
	int evaluate(const Board& board)
	{
		visited_leafs++;
		auto player = winner(board);
		if(player == PLAYER_HORIZONTAL)
			winning_h++;
		else
			winning_v++;
		return player == PLAYER_HORIZONTAL ? 1 : -1;
	}

	int alphabeta(Game& game, size_t depth, int alpha, int beta)
	{
		auto self = game.board().turn;
		if(is_finished(game.board()))
		{
			if(visited_leafs % 10000000 == 0)
				checkup();
			return (self == PLAYER_HORIZONTAL ? 1 : -1) * evaluate(game.board());
		}
		else if(depth == 0)
		{
			return 0;
		}

		MoveList moves {};
		generate_pseudo_legal_moves(game.board(), moves);

		int i = 0;
		int value = -INF;
		for(Move move : moves)
		{
			if(!game.make(move)) continue;

			calculated_max_depth = std::max(calculated_max_depth, game.depth());
			i++;
			max_branching = std::max(max_branching, i);

			value = std::max(value, -alphabeta(game, depth - 1, -beta, -alpha));
			alpha = std::max(alpha, value);

			game.undo();

			if (alpha >= beta)
				break;
		}
		max_branching = std::max(max_branching, i);

		return value;
	}

	void checkup()
	{
		std::cout << "Visited: " << visited_leafs << " leafs "
			"max depth: " << calculated_max_depth << " "
			"max  branching: " << max_branching << " "
			"winning horizontal: " << (100 * winning_h / (double) visited_leafs) << "% "
			"winning vertical: " << (100 * winning_v / (double) visited_leafs) << "%" << std::endl;
	};

	void setup()
	{
		visited_leafs = 0;
	}

	// Info
	int visited_leafs = 0;
private:

	// Pruning
	size_t calculated_max_depth = 0;

	int max_branching = 0;
	size_t winning_h = 0;
	size_t winning_v = 0;
};

Move best_move(Game game)
{
	MoveList moves {};
	Search search {};
	generate_pseudo_legal_moves(game.board(), moves);
	Move lastMove;
	int bestValue = -INF;
	Player self = game.board().turn;
	for(int depth = 0; search.visited_leafs < 10'000'000; depth++)
	{
		for(Move move : moves)
		{
			if(!game.make(move)) continue;

			lastMove = move;

			int value = -search.alphabeta(game, depth, -INF, +INF);
			bestValue = value;
			if (value > 0)
				goto finish;

			game.undo();
		}
	}

finish:
	search.checkup();

	std::cout << "Confidence: " << bestValue << std::endl;
	return lastMove;
}
