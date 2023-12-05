#include "GameBoard.h"
#include "Game.h"

GameBoard::GameBoard(Game* game, int numMines, Vector2 GridSize) : mGame(game)
																  ,mState(InProgress)
															      ,mNumMines(numMines)
																  ,mGridSize(GridSize)
																  ,mPosition(Vector2(0.0f,0.0f))
{
	mMine = mGame->GetTexture("Assets/Mine.png");

	mTileTextures.emplace("Clicked", mGame->GetTexture("Assets/clicked_tile.png"));
	mTileTextures.emplace("Unclicked", mGame->GetTexture("Assets/unclicked_tile.png"));
	mTileTextures.emplace("Unclicked_Hover", mGame->GetTexture("Assets/unclick_hover.png"));
	mTileTextures.emplace("Explosion", mGame->GetTexture("Assets/Explosion.png"));

	// add the number textures when I get around to making them

	// call SetUp board funcition
	SetUpBoard();
}

GameBoard::~GameBoard() 
{

}

void GameBoard::Update(const float deltaTime)
{
	// First: Check the state of the game to see if the player has won or lost

	// Second: we are going to process player inputs

	// Third: If the player clicks on a tile we update that tile on the board

	// Fourth: call the pathfinding function to reveal other tiles

	// Fifth: Set textures on revealed tiles 

	// Sixth: Update the game timer

}

void GameBoard::Draw(SDL_Renderer* renderer)
{
	if (mBoardTiles.empty()) return;
	Vector2 startPos = mPosition;
	// Iterate through each tile, and draw it's texture, and the number/mine on the tile
	for (auto& e : mBoardTiles)
	{
		Vector2 posOffset = startPos + e.gridPosition;
		if (e.highlighted && !e.clicked)
		{
			e.tileTexture = mTileTextures["Unclicked_Hover"];
		}
		else if(!e.clicked)
		{
			e.tileTexture = mTileTextures["Unclicked"];
		}
		SDL_Rect r;
		r.w = 32;
		r.h = 32;
		r.x = (int)posOffset.x - 32 / 2;
		r.y = (int)posOffset.y - 32 / 2;

		SDL_RenderCopyEx(renderer,
			e.tileTexture,
			nullptr,
			&r,
			0.0,
			nullptr,
			SDL_FLIP_NONE);
	}

}

void GameBoard::ProcessInput(const uint8_t* keys)
{
	if (!mBoardTiles.empty() && mState == InProgress)
	{
		// Get mouse position
		int x, y;
		uint32_t state = SDL_GetMouseState(&x, &y);
		Vector2 mousePos(static_cast<float>(x), static_cast<float>(y));
		// Highlight any buttons
		for (auto& e : mBoardTiles)
		{
			if (ContainsPoint(mousePos, e))
			{
				e.highlighted = true;

			}
			else
			{
				e.highlighted = false;
			}
		}


	}
}

bool GameBoard::ContainsPoint(const Vector2& pt, BoardTile bt) const
{
	bool no = pt.x < (bt.gridPosition.x - 32 / 2.0f) ||
		pt.x >(bt.gridPosition.x + 32 / 2.0f) ||
		pt.y < (bt.gridPosition.y - 32 / 2.0f) ||
		pt.y >(bt.gridPosition.y + 32 / 2.0f);
	return !no;
}

void GameBoard::HandleKeyPress(const int key)
{
	switch (key)
	{
	case SDL_BUTTON_LEFT:
		if (!mBoardTiles.empty())
		{
			for (auto& t : mBoardTiles)
			{
				if (t.highlighted == true && t.clicked == false)
				{
					// Change the texture to clicked, and call the search algo
					t.clicked = true;
					t.tileTexture = mTileTextures["Clicked"];
					break;
				}
			}
		}
		break;
	default:
		break;
	}


}

void GameBoard::SetUpBoard()
{
	int rows, cols;
	rows = mGridSize.x;
	cols = mGridSize.y;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			BoardTile t;
			t.gridPosition = Vector2(i * 32+16, j * 32+16);
			t.tileTexture = mTileTextures["Unclicked"];
			mBoardTiles.push_back(t);
		}
	}
}