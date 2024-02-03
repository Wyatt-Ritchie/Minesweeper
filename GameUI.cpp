#include "GameUI.h"
#include "Game.h"
#include "GameBoard.h"
#include "Button.h"
#include "Font.h"
#include <functional>

GameUI::GameUI(Game* game) : UIScreen(game)
							,mGameBoard(nullptr)
							,mHeaderDims(Vector2(0.0f, 0.0f))
							,mState(Easy)
							,mNumberPos(Vector2(0.0f, 0.0f))
							,mFlaggedCount(nullptr)
{
	game->SetGameBoard(new GameBoard(mGame, 13, Vector2(9.0, 9.0)));
	mGameBoard = game->GetGameBoard();
	mHeaderDims.x = (9 * 32);
	mHeaderDims.y = (2 * 32);

	SetFlaggedCountPos();

	mGameBoard->SetPosition(Vector2(0.0f, mHeaderDims.y));
	mGame->ResizeWindow(Vector2(mHeaderDims.x, (2 * 32) + (9 * 32)));
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
	r.w = static_cast<int>(mHeaderDims.x);
	r.h = static_cast<int>(mHeaderDims.y);

	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);

	SDL_RenderFillRect(renderer, &r);

	SDL_Rect numRegion;
	numRegion.x = static_cast<int>(mNumberPos.x);
	numRegion.y = static_cast<int>(mNumberPos.y);
	numRegion.w = 40;
	numRegion.h = 40;

	// background for flag counter
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderFillRect(renderer, &numRegion);

	// Set and render flag counter texture
	int num = mGameBoard->GetFlaggedCount();
	int size = 30;
	int offset = 0;
	if (num < 10) offset = 20;
	std::string numToRender = std::to_string(num);
	if (mGameBoard->RequiresUpdate())
	{
		if(mFlaggedCount) SDL_DestroyTexture(mFlaggedCount);
		mGameBoard->SetFlagChange(false);
		mFlaggedCount = mFont->RenderText(numToRender, Color::Red, size);
	}
	
	SDL_Rect textDest{ numRegion.x + offset, numRegion.y, 1, 1 };
	SDL_QueryTexture(mFlaggedCount, NULL, NULL, &textDest.w, &textDest.h);
	SDL_RenderCopyEx(renderer,
		mFlaggedCount,
		nullptr,
		&textDest,
		0.0,
		nullptr,
		SDL_FLIP_NONE);

	if (!mButtons.empty())
	{
		for (auto const& b : mButtons)
		{
			if (b->GetHighlighted())
			{
				b->Draw(b->GetSelected(), renderer);
			}
			else
			{
				b->Draw(b->GetUnSelected(), renderer);
			}
		}
	}
}

void GameUI::GenerateButtons()
{
	// Reset Button
	mFont = mGame->GetFont("Assets/Caviar_Dreams_Bold.ttf");
	mButtonSelected = mGame->GetTexture("Assets/Sad_face.png");
	mButtonUnSelected = mGame->GetTexture("Assets/Happy_face.png");
	AddButton("", [this]() {return this->ButtonResetGame(); });
	mButtons[0]->SetPosition(Vector2(mHeaderDims.x / 2, mHeaderDims.y - 32));
	mButtons[0]->SetDimension(Vector2(64, 64));
	mButtons[0]->SetSelectionTexts(mButtonSelected, mButtonUnSelected);
	mButtonSelected = mGame->GetTexture("Assets/unclick_hover.png");
	mButtonUnSelected = mGame->GetTexture("Assets/unclicked_tile.png");
	AddButton("Easy", [this]() {return this->SetEasy(); });
	mButtons[1]->SetDimension(Vector2(64, 20));
	mButtons[1]->SetPosition(Vector2(32, 10));
	mButtons[1]->SetSelectionTexts(mButtonSelected, mButtonUnSelected);
	AddButton("Medium", [this]() {return this->SetMedium(); });
	mButtons[2]->SetDimension(Vector2(64, 20));
	mButtons[2]->SetPosition(Vector2(32, 30));
	mButtons[2]->SetSelectionTexts(mButtonSelected, mButtonUnSelected);
	AddButton("Hard", [this]() {return this->SetHard(); });
	mButtons[3]->SetDimension(Vector2(64, 20));
	mButtons[3]->SetPosition(Vector2(32, 50));
	mButtons[3]->SetSelectionTexts(mButtonSelected, mButtonUnSelected);
	
}

void GameUI::ButtonResetGame()
{
	if (mState == Easy)
	{
		mGameBoard->ResetGame(13, Vector2(9.0, 9.0));
		mHeaderDims.x = (9 * 32);
		mHeaderDims.y = (2 * 32);
		mButtons[0]->SetPosition(Vector2((9 * 32) / 2, mHeaderDims.y - 32));
	}
	if (mState == Medium)
	{
		mGameBoard->ResetGame(30, Vector2(15.0, 15.0));
		mHeaderDims.x = (15 * 32);
		mHeaderDims.y = (2 * 32);
		mButtons[0]->SetPosition(Vector2((15 * 32) / 2, mHeaderDims.y - 32));
	}
	if (mState == Hard)
	{
		mGameBoard->ResetGame(60, Vector2(18.0, 18.0));
		mHeaderDims.x = (18 * 32);
		mHeaderDims.y = (2 * 32);
		mButtons[0]->SetPosition(Vector2((18 * 32) / 2, mHeaderDims.y - 32));
	}
}

void GameUI::SetEasy()
{
	Vector2 dims(9.0, 9.0);
	SetHeaderDims(Vector2(dims.y * 32, 2 * 32));
	SetState(GameUI::Easy);
	SetFlaggedCountPos();
	mGameBoard->SetFlagChange(true);
}

void GameUI::SetMedium()
{
	Vector2 dims(15.0, 15.0);
	SetState(GameUI::Medium);
	SetHeaderDims(Vector2(dims.x * 32, 2 * 32));
	SetFlaggedCountPos();
	mGameBoard->SetFlagChange(true);
}

void GameUI::SetHard()
{
	Vector2 dims(18.0, 18.0);
	SetState(GameUI::Hard);
	SetHeaderDims(Vector2(dims.y * 32, 2 * 32));
	SetFlaggedCountPos();
	mGameBoard->SetFlagChange(true);
}

void GameUI::SetFlaggedCountPos()
{
	mNumberPos.x = mHeaderDims.x - 60;
	mNumberPos.y = mHeaderDims.y / 2 - 20;
}

void GameUI::SetState(State state)
{
	mState = state;
	ButtonResetGame();
}
