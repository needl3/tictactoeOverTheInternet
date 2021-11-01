#pragma once 
class TicTacToe
{
	private:
		static const unsigned short _GRID_SIZE = 3;

	protected:
		char _grid[_GRID_SIZE][_GRID_SIZE] = {0};
		//Game Variables
		enum {YOU=(unsigned short)('X'), OPPONENT=(unsigned short)('O')};
		unsigned short MOVE_MAP[_GRID_SIZE*_GRID_SIZE][2];
		char turn;
		bool is_host = false;
		int is_connected = false;	//0 --> Not connected
									//1`--> Connected
									//-1 -> Offline

		//Game Methods
		void clearGrid();
		bool placeMove(const unsigned short*, bool check = false);
		virtual unsigned short getMove();
		virtual void askTurn();
		int checkWinner();	//YOU indicates you,
							//OPPONENT indicates opponent,
							//-1 indicates no win till now
		void displayWinner(int);
		void displayTurn();
		void toggleTurn();
		void displayGrid();

	public:
		void start();
		TicTacToe();
};
