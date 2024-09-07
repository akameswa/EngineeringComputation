#include <iostream>


void PrintBoard(char board[9])
{
	for(int i=0; i<9; ++i)
	{
		std::cout << board[i];
		if(2==i%3)
		{
			std::cout << "\n";
			if(i<6)
			{
				std::cout << "-+-+-\n";
			}
		}
		else
		{
			std::cout << "|";
		}
	}
}

bool CheckWinner(char board[9],char pl)
{
	return ((board[0]==pl && board[1]==pl && board[2]==pl) ||
	   (board[3]==pl && board[4]==pl && board[5]==pl) ||
	   (board[6]==pl && board[7]==pl && board[8]==pl) ||

	   (board[0]==pl && board[3]==pl && board[6]==pl) ||
	   (board[1]==pl && board[4]==pl && board[7]==pl) ||
	   (board[2]==pl && board[5]==pl && board[8]==pl) ||

	   (board[0]==pl && board[4]==pl && board[8]==pl) ||
	   (board[2]==pl && board[4]==pl && board[6]==pl));
}

bool CheckNoWinner(char board[9])
{
	for(int i=0; i<9; ++i)
	{
		if(' '==board[i])
		{
			return false;
		}
	}
	return true;
}

int main(void)
{
	char board[9];
	for(auto &b : board)
	{
		b=' ';
	}


	char turn='X';
	while(true!=CheckWinner(board,'X') && true!=CheckWinner(board,'O') && true!=CheckNoWinner(board))
	{
		PrintBoard(board);

		unsigned int x,y;
		std::cout << turn << "'s turn.\n";
		std::cout << "Enter X Y:";
		std::cin >> x >> y;

		if(x<3 && y<3)
		{
			if(' '==board[3*y+x])
			{
				board[3*y+x]=turn;
				if('X'==turn)
				{
					turn='O';
				}
				else
				{
					turn='X';
				}
			}
			else
			{
				std::cout << "Column is already used.  Try again.\n";
			}
		}
		else
		{
			std::cout << "Enter 0<=x<=2 and 0<=y<=2.  Try again.\n";
		}
	}

	PrintBoard(board);
	if(true==CheckWinner(board,'X'))
	{
		std::cout << "X wins!\n";
	}
	else if(true==CheckWinner(board,'O'))
	{
		std::cout << "O wins!\n";
	}
	else
	{
		std::cout << "No winner.\n";
	}

	return 0;
}
