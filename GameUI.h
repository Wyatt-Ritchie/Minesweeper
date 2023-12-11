#pragma once
#include "UIScreen.h"
class GameUI : public UIScreen
{
public:
	enum State {
		Easy,
		Medium,
		Hard
	};
	GameUI(class Game* game);
	~GameUI();
	void Draw(SDL_Renderer* renderer);

	void ButtonResetGame();

	void ButtonSettings();

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

private:
	State mState;
	class Button* mResetButton;

	class Button* mSettings;

	Vector2 mHeaderDims;

	class GameBoard* mGameBoard;
};

