
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

//-----------------------------------------------------------------------------
// DECLARATIONS

#define GS_TICTACTOE_PLAYERS					2
#define GS_TICTACTOE_BOARD_WIDTH				3
#define GS_TICTACTOE_BOARD_HEIGHT				3

enum gs_tictactoe_space_state
{
	// invalid space state
	gs_tictactoe_space_invalid = -1,

	// states visible to both players
	gs_tictactoe_space_open,	// space is open
	gs_tictactoe_space_o,		// space is taken by O player
	gs_tictactoe_space_x,		// space is taken by X player
};
#ifndef __cplusplus
typedef		enum gs_tictactoe_space_state		gs_tictactoe_space_state;
#endif	// !__cplusplus

// tic-tac-toe game state
typedef		unsigned char						gs_tictactoe_index;
typedef		gs_tictactoe_space_state			gs_tictactoe[GS_TICTACTOE_BOARD_WIDTH][GS_TICTACTOE_BOARD_HEIGHT];


#define	GS_VALIDATE_COORDINATE(x,y,w,h)			(x < w && y < h)
#define GS_TICTACTOE_VALID(x,y)					GS_VALIDATE_COORDINATE(x,y,GS_TICTACTOE_BOARD_WIDTH,GS_TICTACTOE_BOARD_HEIGHT)


inline gs_tictactoe_space_state gs_tictactoe_getSpaceState(gs_tictactoe const game, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos]);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_space_state gs_tictactoe_setSpaceState(gs_tictactoe game, gs_tictactoe_space_state const state, gs_tictactoe_index const xpos, gs_tictactoe_index const ypos)
{
	if (GS_TICTACTOE_VALID(xpos, ypos))
		return (game[xpos][ypos] = state);
	return gs_tictactoe_space_invalid;
}

inline gs_tictactoe_index gs_tictactoe_reset(gs_tictactoe game)
{
	gs_tictactoe_index xpos, ypos, total;
	for (xpos = 0; xpos < GS_TICTACTOE_BOARD_WIDTH; ++xpos)
		for (ypos = 0; ypos < GS_TICTACTOE_BOARD_HEIGHT; ++ypos)
			game[xpos][ypos] = gs_tictactoe_space_open;
	total = (xpos * ypos);
	return total;
}


//-----------------------------------------------------------------------------
// DEFINITIONS

//helps drawBoard(), correctly display X, O, or blank space
char XOPrinter(gs_tictactoe game, int i, int j)
{
	char XorO;
	if (gs_tictactoe_getSpaceState(game, i, j) == 1)
	{
		XorO = 'X';
	}
	else if (gs_tictactoe_getSpaceState(game, i, j) == 2)
	{
		XorO = 'O';
	}
	else
	{
		XorO = ' ';
	}
	return XorO;
}

//couts board, prints by line
void drawBoard(gs_tictactoe game)
{
	int c;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << "  " << XOPrinter(game, i, j) << "  |";
		}
		std::cout << "\n-------------------" << std::endl;
	}
}

//winCondition checks spaces x, y rows if no win check x, y colums, if not checks x,y diagonals, if not checks y, x diagonals, else return flse
bool winCondition(gs_tictactoe game)
{
	for (int i = 0; i < 3; i++)
	{
		//check rows
		if (gs_tictactoe_getSpaceState(game, i, 0) != 0 && gs_tictactoe_getSpaceState(game, i, 0) == gs_tictactoe_getSpaceState(game, i, 1) && gs_tictactoe_getSpaceState(game, i, 1) == gs_tictactoe_getSpaceState(game, i, 2))
		{
			return true;
		}
		//check columns
		else if (gs_tictactoe_getSpaceState(game, 0, i) != 0 && gs_tictactoe_getSpaceState(game, 0, i) == gs_tictactoe_getSpaceState(game, 1, i) && gs_tictactoe_getSpaceState(game, 1, i) == gs_tictactoe_getSpaceState(game, 2, i))
		{
			return true;
		}
	}
	//check diagonals
	if (gs_tictactoe_getSpaceState(game, 0, 0) != 0 && gs_tictactoe_getSpaceState(game, 0, 0) == gs_tictactoe_getSpaceState(game, 1, 1) && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_getSpaceState(game, 2, 2))
	{
		return true;
	}
	else if (gs_tictactoe_getSpaceState(game, 0, 2) != 0 && gs_tictactoe_getSpaceState(game, 0, 2) == gs_tictactoe_getSpaceState(game, 1, 1) && gs_tictactoe_getSpaceState(game, 1, 1) == gs_tictactoe_getSpaceState(game, 2, 0))
	{
		return true;
	}

	return false;
}

int launchTicTacToe()
{
	gs_tictactoe game = { 0 };

	gs_tictactoe_reset(game);

	char turn = 'X';
	int column, row, rounds = 1;

	std::cout << "Round " << rounds << std::endl;
	drawBoard(game);

#ifndef gameLoop

	while (rounds <= 9 && winCondition(game) == false)
	{
		std::cout << "Player " << turn << " turn" << std::endl;

		std::cout << "Enter a row:";
		std::cin >> column;

		std::cout << "Enter a column:";
		std::cin >> row;

		//X turn
		if (turn == 'X' && gs_tictactoe_getSpaceState(game, column, row) == 0)
		{
			gs_tictactoe_setSpaceState(game, gs_tictactoe_space_x, column, row);
			turn = 'O';
			rounds++;
		}
		//O turn
		else if (turn == 'O' && gs_tictactoe_getSpaceState(game, column, row) == 0)
		{
			gs_tictactoe_setSpaceState(game, gs_tictactoe_space_o, column, row);
			turn = 'X';
			rounds++;
		}
		//space taken
		else
		{
			std::cout << "Space taken" << std::endl;
		}
		std::cout << "Round " << rounds << std::endl;
		drawBoard(game);
	}

	//win condition; Player x wins if not, O wins, otherwise tie game
	if (turn == 'X')
	{
		std::cout << "Player X Wins!";
	}
	else if (turn == 'O')
	{
		std::cout << "Player 0  Wins!";
	}
	else
	{
		std::cout << "Tie Game!";
	}

#endif
	gs_tictactoe_setSpaceState(game, gs_tictactoe_space_x, 0, 0);

	return 0;
}


//-----------------------------------------------------------------------------
