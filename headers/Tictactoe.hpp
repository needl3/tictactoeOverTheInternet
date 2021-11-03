#pragma once 
class TicTacToe
{
	private:
		static const unsigned short _GRID_SIZE = 3;

	protected:
		//Game Methods
		virtual unsigned short getMove();
		virtual void askTurn();
		void displayWinner(int);
		void displayTurn();
		void displayGrid();

	public:
		//Game Variables
		char _grid[_GRID_SIZE][_GRID_SIZE] = {0};
		enum {YOU=(unsigned short)('X'), OPPONENT=(unsigned short)('O')};
		unsigned short MOVE_MAP[_GRID_SIZE*_GRID_SIZE][2];
		char turn;
		bool is_host = false;
		int is_connected = false;	//0 --> Not connected
									//1`--> Connected
									//-1 -> Offline
		void clearGrid();
		int checkWinner();	//YOU indicates you,
							//OPPONENT indicates opponent,
							//-1 indicates no win till now
		void toggleTurn();
		bool placeMove(const unsigned short*, bool check = false);
		void start();
		TicTacToe();
};
