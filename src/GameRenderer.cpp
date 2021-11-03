#include "../headers/GameRenderer.hpp"
#include "../headers/Tictactoe.hpp"
#include "../headers/TictactoeOnline.hpp"
template <typename T>
GameRenderer<T>::GameRenderer(sf::RenderWindow& window, sf::Event& event, T& game){
	_is_host = 1;
	_current_state = TURN_CHOOSER;
	_game = &game;
	prepareData(window, event);
}

template <typename T>
void GameRenderer<T>::prepareData(sf::RenderWindow& window, sf::Event& event){
	_window = &window;
	_events = &event;

	_turn_chooser = new Chooser(_window,_events);
	_turn_chooser->setMode(_current_state);

	_WIDTH = _window->getSize().x;
	_HEIGHT = _window->getSize().y;

	_background_texture.loadFromFile("assets/pictures/background_play.jpg");
	_txt_font.loadFromFile("assets/fonts/japanese.ttf");

	//Defining constants
	_item[CONNECTION].stat1 = "CONNECTED";
	_item[CONNECTION].stat2 = "NOT CONNECTED";

	_item[gOPPONENT].stat1 = "CONSPIRING";
	_item[gOPPONENT].stat2 = "WAITING";
	_item[gOPPONENT].label = "OPPONENT";

	_item[gYOU].stat1 = "CONSPIRING";
	_item[gYOU].stat2 = "WAITING";
	_item[gYOU].label = "YOU";
}

template <typename T>
GameState GameRenderer<T>::handleInput(){
	switch (_current_state){
		case TURN_CHOOSER:
			// 0 indicates accepted to play first
			_turn_chosen = _turn_chooser->handleInput();
			if(_turn_chosen > -1){
				_game->turn = _turn_chosen ? _game->OPPONENT : _game->YOU;
				_game->clearGrid();
				_current_state = GAME;
			}
			break;
		case GAME:
			{
				_window->waitEvent(*_events);
				if(_events->type == sf::Event::MouseButtonReleased){
					short position = _getGridPosition(sf::Mouse::getPosition(*_window));
					if(position>-1){
						if(_game->placeMove(_game->MOVE_MAP[position])){
							_winner = _game->checkWinner();
							if(_winner < 0)	_game->toggleTurn();
							else _current_state = WINNER;
						}
					}
				}
			}
			break;
		case WINNER:
			_window->waitEvent(*_events);
			if(_events->type == sf::Event::MouseButtonReleased)
				_current_state = PLAY_AGAIN;
			break;
		case PLAY_AGAIN:
			_turn_chosen = _turn_chooser->handleInput();
			if(!_turn_chosen){
				_game->clearGrid();
				_current_state = TURN_CHOOSER;
			}
			else if(_turn_chosen == 1){
				_game->clearGrid();
				return Menu;
			}
			break;

		}
	return Offline;
	}

template <typename T>
void GameRenderer<T>::render(){
	_updateDimensions();
	_renderBackground();
	_renderGrid();
	_renderStatus();
	_renderConnection(false);
	switch(_current_state){
		case TURN_CHOOSER:
			_turn_chooser->setMode((unsigned int)TURN_CHOOSER);
			_turn_chooser->render();
			break;		
		case PLAY_AGAIN:
			_turn_chooser->setMode((unsigned int)PLAY_AGAIN);
			_turn_chooser->render();
			break;
		case WINNER:
			_renderWinner();
			break;
		default:
			std::cout << "No valid state" << std::endl;
			break;
	}
}

template <typename T>
short GameRenderer<T>::_getGridPosition(sf::Vector2i position){
	int x1,y1,x2,y2,count=0;
	for (int i=0;i<3;i++){
		for (int j=0;j<3;j++){
			x1 = _item[GRID].posX+j*(_tileProperties.grid_sizeX+_tileProperties.line_sizeX),
			y1 = _item[GRID].posY+i*(_tileProperties.grid_sizeY+_tileProperties.line_sizeY);
			x2 = x1+_tileProperties.grid_sizeX;
			y2 = y1+_tileProperties.grid_sizeY;

			if(position.x > x1 and position.x < x2 and position.y > y1 and position.y < y2)
				return count;
			count++;
		}
	}
	return -1;
}

template <typename T>
void GameRenderer<T>::_renderWinner(){
	_rect.setPosition(0,(_HEIGHT-_HEIGHT/2.0f)/2.0f);
	_rect.setSize(sf::Vector2f(_WIDTH,_HEIGHT/2.0f));
	_rect.setFillColor(sf::Color(100,100,100,100));
	_window->draw(_rect);

	std::string winning_label = "You  ";
	if(_game->turn == _game->YOU)
		winning_label.insert(4,"Won");
	else
		winning_label.insert(4,"Lost");

	unsigned short character_size = _HEIGHT/5.0f;
	float x = (_WIDTH - character_size*winning_label.size())*2.0f;
	float y = _rect.getGlobalBounds().top+(_rect.getSize().y-character_size)/2.0f;
	_text.setFont(_txt_font);
	_text.setString(winning_label);
	_text.setPosition(x,y);
	_text.setCharacterSize(character_size);
	_window->draw(_text);
}

template <typename T>
void GameRenderer<T>::_renderGrid(){
	for(int i=0;i<3;i++){
		for (int j=0;j<3;j++){
			if (i>0 && j>0)
				_renderLine(i,j);
			_renderMove(i,j, _game->_grid[i][j]);
		}
	}
}

template <typename T>
void GameRenderer<T>::_updateDimensions(){
	_WIDTH = _window->getSize().x;
	_HEIGHT = _window->getSize().y;

	_item[GRID].sizeX = 0.55f*_WIDTH;
	_item[GRID].sizeY = 0.8f*_HEIGHT;
	_item[GRID].posX = (_WIDTH-_item[GRID].sizeX)/2.0f;
	_item[GRID].posY = (_HEIGHT-_item[GRID].sizeY)/2.0f;

	_item[CONNECTION].sizeY = 0.04f*_HEIGHT;
	_item[CONNECTION].sizeX = _item[CONNECTION].sizeY*_item[CONNECTION].stat2.size();
	_item[CONNECTION].posX = (_WIDTH-_item[CONNECTION].sizeX)/2.0f;
	_item[CONNECTION].posY = (_HEIGHT-_item[CONNECTION].sizeY);

	_item[gOPPONENT].sizeX = (_WIDTH-_item[GRID].sizeX)/3.0f;
	_item[gOPPONENT].sizeY = _item[GRID].sizeY/5.0f;
	_item[gOPPONENT].posX = (_WIDTH-2*_item[gOPPONENT].sizeX-_item[GRID].sizeX)/4.0f;
	_item[gOPPONENT].posY = _item[GRID].posY+_item[GRID].sizeY/2.7f;

	_item[gYOU].sizeX = _item[gOPPONENT].sizeX;
	_item[gYOU].sizeY = _item[gOPPONENT].sizeY;
	_item[gYOU].posX = _WIDTH - _item[gOPPONENT].posX - _item[gOPPONENT].sizeX;
	_item[gYOU].posY = _item[gOPPONENT].posY;

	_tileProperties.hypotenuse=sqrt(pow(0.2f*_item[GRID].sizeX,2)+pow(0.2f*_item[GRID].sizeY,2));
	_tileProperties.x_offset = _item[GRID].sizeX*0.05f;
	_tileProperties.y_offset = _item[GRID].sizeY*0.05f;
	_tileProperties.grid_sizeX = _item[GRID].sizeX/3.0f;
	_tileProperties.grid_sizeY = _item[GRID].sizeY/3.0f;
	_tileProperties.line_sizeX = 0.01f*_item[GRID].sizeX;
	_tileProperties.line_sizeY = 0.01f*_item[GRID].sizeY;
}

template <typename T>
void GameRenderer<T>::_renderBackground(){
	_background_sprite.setTexture(_background_texture);
	_window->draw(_background_sprite);
}

template <typename T>
void GameRenderer<T>::_renderStatus(){
	unsigned short character_size = _item[gOPPONENT].sizeX/(_item[gOPPONENT].label.size()+5);
	//Background Base Rectangles and labels
	for(int i=gOPPONENT;i<=gYOU;i++){
		bool green=false;
		
		green = ((_game->turn == _game->OPPONENT and i==gOPPONENT) or (_game->turn == _game->YOU and i==gYOU));
		
		_rect.setPosition(_item[i].posX, _item[i].posY);
		_rect.setSize(sf::Vector2f(_item[i].sizeX, _item[i].sizeY));
		_rect.setFillColor(sf::Color(20*(!green),255*green,255*green,100));
		_window->draw(_rect);

		float txtX = _item[i].posX+(_item[i].sizeX-_item[i].label.size()*character_size)/2.0f;
		float txtY = _item[i].posY+character_size/2.0f;
		_text.setCharacterSize(_item[CONNECTION].sizeY);
		_text.setPosition(txtX,txtY);
		_text.setString(_item[i].label);
		_window->draw(_text);

		std::string stat = green ? _item[i].stat1 : _item[i].stat2;
		txtX = _item[i].posX+(_item[i].sizeX-stat.size()*character_size)/2.0f;
		txtY += character_size*3;
		_text.setPosition(txtX,txtY);
		_text.setString(stat);
		_window->draw(_text);
	}
}

template <typename T>
void GameRenderer<T>::_renderConnection(bool connected /*= false*/){
	_rect.setPosition(_item[CONNECTION].posX, _item[CONNECTION].posY);
	_rect.setSize(sf::Vector2f(_item[CONNECTION].sizeX, _item[CONNECTION].sizeY));
	_rect.setFillColor(sf::Color(0,200,200,100));
	_window->draw(_rect);

	float character_size = _item[CONNECTION].sizeY;
	float textPositionX = _item[CONNECTION].posX+3*character_size;
	float textPositionY = _item[CONNECTION].posY-character_size/10.0f;
	if(connected){
		_text.setFillColor(sf::Color(0,200,100));
		_text.setString(_item[CONNECTION].stat1);
	}
	else{
		_text.setFillColor(sf::Color(200,50,50));
		_text.setString(_item[CONNECTION].stat2);
	}
	_text.setFont(_txt_font);
	_text.setCharacterSize(character_size);
	_text.setPosition(textPositionX,textPositionY);
	_window->draw(_text);
}

template <typename T>
void GameRenderer<T>::_renderMove(unsigned int i, unsigned int j, char symbol){
	if(symbol == 'X'){
		_rect.setPosition(_item[GRID].posX+j*(_tileProperties.grid_sizeX+_tileProperties.line_sizeX)+_tileProperties.x_offset,
							_item[GRID].posY+i*(_tileProperties.grid_sizeY+_tileProperties.line_sizeY)+_tileProperties.y_offset);
		_rect.setSize(sf::Vector2f(0.3f*0.01f*_item[GRID].sizeX, _tileProperties.hypotenuse));
		_rect.setRotation(-55);
		_rect.setFillColor(sf::Color::White);
		_window->draw(_rect);


		_rect.setPosition(_item[GRID].posX+j*(_tileProperties.grid_sizeX+_tileProperties.line_sizeX)+_tileProperties.x_offset+0.2*_item[GRID].sizeX,
							_item[GRID].posY+i*(_tileProperties.grid_sizeY+_tileProperties.line_sizeY)+_tileProperties.y_offset);
		_rect.setRotation(55);
		_window->draw(_rect);
		_rect.setRotation(0);
	}else if(symbol == 'O'){
		_circle.setRadius(_item[GRID].sizeX*0.3/4);
		_circle.setFillColor(sf::Color(0,0,0,1));
		_circle.setOutlineThickness(6);

		_circle.setPosition(_item[GRID].posX+(j*0.35+0.07)*_item[GRID].sizeX, _item[GRID].posY+(i*0.35+0.05)*_item[GRID].sizeY);
		_window->draw(_circle);
	}
}

template <typename T>
void GameRenderer<T>::_renderLine(unsigned int i, unsigned int j){
	//Vertical
	_rect.setPosition(_item[GRID].posX+i*_item[GRID].sizeX/3.0f,_item[GRID].posY);
	_rect.setSize(sf::Vector2f(_item[GRID].sizeX*0.01f,_item[GRID].sizeY));
	_rect.setFillColor(sf::Color::White);
	_window->draw(_rect);

	//Horizontal
	_rect.setPosition(_item[GRID].posX,_item[GRID].posY+j*_item[GRID].sizeY/3.0f);
	_rect.setSize(sf::Vector2f(_item[GRID].sizeX,_item[GRID].sizeY*0.01f));
	_rect.setFillColor(sf::Color::White);
	_window->draw(_rect);
}

template class GameRenderer<TicTacToe>;
template class GameRenderer<TicTacToeOnline>;