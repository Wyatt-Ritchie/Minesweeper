#include "GameUI.h"
#include "Game.h"
#include "GameBoard.h"
#include "Button.h"

GameUI::GameUI(Game* game) : UIScreen(game)
							,mResetButton(nullptr)
							,mSettings(nullptr)
							,mGameBoard(nullptr)
							,mHeaderDims(Vector2(0.0f, 0.0f))
							,mState(Easy)
{
	game->SetGameBoard(new GameBoard(mGame, 10, Vector2(9.0, 9.0)));
	mGameBoard = game->GetGameBoard();
	mHeaderDims.x = (9 * 32);
	mHeaderDims.y = (2 * 32);
	mGameBoard->SetPosition(Vector2(0.0f, mHeaderDims.y));
	mGame->ResizeWindow(Vector2(mHeaderDims.x, (2 * 32) + (9 * 32)));
	mNextButtonPos = (Vector2(mHeaderDims.x/2, mHeaderDims.y - 32));
	GenerateButtons();
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

	if (!mButtons.empty())
	{
		for (auto const& b : mButtons)
		{
			if (b->GetHighlighted())
			{
				b->Draw(mButtonSelected, renderer);
			}
			else
			{
				b->Draw(mButtonUnSelected, renderer);
			}
		}
	}
}

void GameUI::ButtonResetGame()
{
	// Gets the state of the UI and sets the game board accordingly
	// destroy previous GameBoard, and generate a new one
	
	

	if (mState == Easy)
	{
		mGameBoard->ResetGame(10, Vector2(9.0, 9.0));
		mHeaderDims.x = (9 * 32);
		mHeaderDims.y = (2 * 32);
	}
	if (mState == Medium)
	{
		mGameBoard = new GameBoard(mGame, 20, Vector2(15.0, 15.0));
		mHeaderDims.x = (15 * 32);
		mHeaderDims.y = (2 * 32);
		mGameBoard->SetPosition(Vector2(0.0f, 2 * 32.0f));
	}
	if (mState == Hard)
	{
		mGameBoard = new GameBoard(mGame, 35, Vector2(19.0, 19.0));
		mHeaderDims.x = (19 * 32);
		mHeaderDims.y = (2 * 32);
		mGameBoard->SetPosition(Vector2(0.0f, 2 * 32.0f));
	}
}

void GameUI::ButtonSettings()
{
	// Opens a little dropdown with 3 options (instantiates a UI element):
	// Easy, Medium and Hard
	// each of these sets the state and resets the game
}

void GameUI::GenerateButtons()
{
	// Reset Button
	mFont = mGame->GetFont("Assets/Caviar_Dreams_Bold.ttf");
	mButtonSelected = mGame->GetTexture("Assets/Sad_face.png");
	mButtonUnSelected = mGame->GetTexture("Assets/Happy_face.png");
	AddButton("", [this]() {return this->ButtonResetGame(); });
	
}
