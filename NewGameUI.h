#pragma once
#include "UIScreen.h"
class NewGameUI : public UIScreen
{
public:
	NewGameUI(class Game* game);
	~NewGameUI();

	void Draw(SDL_Renderer* renderer);

	void GenerateButtons();

private:

	class GameBoard* mGameBoard;
	class GameUI* mUI;



	void SetEasy();
	void SetMedium();
	void SetHard();
};

