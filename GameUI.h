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

	void SetEasy();

	void GenerateButtons();

	State GetState() const { return mState; }
	void SetMedium();
	void SetHard();
	void SetState(State state);

	void SetHeaderDims(Vector2 dims) { mHeaderDims = dims; }
	void SetFlaggedCountPos();

private:
	State mState;
	Vector2 mHeaderDims;
	Vector2 mNumberPos;
	SDL_Texture* mFlaggedCount;

	class GameBoard* mGameBoard;
};