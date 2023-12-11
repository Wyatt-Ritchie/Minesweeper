#include "GameUI.h"
#include "Game.h"
#include "GameBoard.h"

GameUI::GameUI(Game* game) : UIScreen(game)
							,mResetButton(nullptr)
							,mSettings(nullptr)
							,mGameBoard(nullptr)
							,mHeaderDims(Vector2(0.0f, 0.0f))
							,mState(State::Easy)
{
	game->SetGameBoard(new GameBoard(mGame, 10, Vector2(9.0, 9.0)));
	mGameBoard = game->GetGameBoard();
	mHeaderDims.x = (9 * 32);
	mHeaderDims.y = (2 * 32);
	mGameBoard->SetPosition(Vector2(0.0f, mHeaderDims.y));
	mGame->ResizeWindow(Vector2(9 * 32, (2 * 32) + (9 * 32)));
	
}

GameUI::~GameUI()
{
}

void GameUI::Draw(SDL_Renderer* renderer)
{
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = mHeaderDims.x;
	r.h = mHeaderDims.y;

	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);

	SDL_RenderFillRect(renderer, &r);

}

void GameUI::ButtonResetGame()
{
	// Gets the state of the UI and sets the game board accordingly
	// destroy previous GameBoard, and generate a new one
	delete mGameBoard;

	if (mState == Easy)
	{
		mGameBoard = new GameBoard(mGame, 10, Vector2(9.0, 9.0));
		mHeaderDims.x = (9 * 32);
		mHeaderDims.y = (3 * 32);
		mGameBoard->SetPosition(Vector2(0.0f, 2 * 32.0f));
	}
	if (mState == Medium)
	{
		mGameBoard = new GameBoard(mGame, 20, Vector2(15.0, 15.0));
		mHeaderDims.x = (15 * 32);
		mHeaderDims.y = (3 * 32);
		mGameBoard->SetPosition(Vector2(0.0f, 2 * 32.0f));
	}
	if (mState == Hard)
	{
		mGameBoard = new GameBoard(mGame, 35, Vector2(19.0, 19.0));
		mHeaderDims.x = (19 * 32);
		mHeaderDims.y = (3 * 32);
		mGameBoard->SetPosition(Vector2(0.0f, 2 * 32.0f));
	}
}

void GameUI::ButtonSettings()
{
	// Opens a little dropdown with 3 options (instantiates a UI element):
	// Easy, Medium and Hard
	// each of these sets the state and resets the game
}
