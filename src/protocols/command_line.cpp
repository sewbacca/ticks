
#include <engine.hpp>
#include <iostream>
#include <string>

static void print_board(const Board& board)
{
	for(Square square : squares)
	{
		std::cout << ' ';
		switch (board.at(square))
		{
		case EMPTY: std::cout << ' '; break;
		case HORIZONTAL: std::cout << '-'; break;
		case VERTICAL: std::cout << '|'; break;
		case T: std::cout << 't'; break;
		default:
			std::cout << '?';
		}
		std::cout << ' ';

		if(square % 3 == 2) std::cout << std::endl;
	}
	std::cout << std::endl;
}

enum Action
{
	UNDO,
	ENGINE,
	PLAY_MOVE,
	UNDEFINED
};

static Action parses_move(std::istream& in, Move& move)
{
	std::string encoded = "";
	in >> encoded;
	if(encoded == "undo" || encoded == "u") return UNDO;
	else if(encoded == "engine" || encoded == "e") return ENGINE;
	else if (encoded.size() == 1)
	{
		Square num_key_map[] {
			A3, B3, C3,
			A2, B2, C2,
			A1, B1, C1
		};

		move.square = num_key_map[encoded[0] - '1'];
		bool ok = A1 <= move.square && move.square <= C3;
		return ok ? PLAY_MOVE : UNDEFINED;
	}
	else return UNDEFINED;
}

void command_line()
{
	Game game {};

	static const char* players[] { "No one", "Player 1 (-)", "Player 2 (|)" };
	std::cout << "Playing TickoaTTwo" << std::endl;

	while(!is_finished(game.board()))
	{
restart:
		print_board(game.board());
		std::cout << players[game.board().turn] << std::endl;

		std::cout << "Move: ";
		Move move;
		switch (parses_move(std::cin, move))
		{
		case PLAY_MOVE:
			if(!game.make(move))
				std::cout << "Move is illegal" << std::endl;
			else
				std::cout << "Played move!" << std::endl;
			break;
		case UNDO:
			if(!game.can_undo())
				std::cout << "Cannot perform undo" << std::endl;
			else
				game.undo();
			break;
		case ENGINE:
		{
			Move move = best_move(game);

			// Square -> keypad
			int key_num_map[] {
				7, 8, 9,
				4, 6, 6,
				1, 2, 3
			};

			if(game.make(move))
				std::cout << "Engine made move " << key_num_map[move.square] << std::endl;
			else
				std::cout << "Engine made invalid move" << std::endl;
			break;
		}
		default:
		case UNDEFINED:
			std::cout << "Couldn't parse move" << std::endl;
			break;
		}
	}
	std::cout << "Winner is " << players[winner(game.board())] << std::endl << "Undo? 1 == ";
	int undo = 0;
	std::cin >> undo;
	if (undo)
		goto restart;
}
