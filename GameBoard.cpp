#include "GameBoard.h"
#include "Game.h"
#include <iostream>
#include <queue>
#include <unordered_set>

GameBoard::GameBoard(Game* game, int numMines, Vector2 GridSize) : mGame(game)
																  ,mState(InProgress)
															      ,mNumMines(numMines)
																  ,mGridSize(GridSize)
																  ,mPosition(Vector2(0.0f,0.0f))
																  ,mBoardGraph()
																  ,mFlagChange(true)
{
	mMine = mGame->GetTexture("Assets/Mine.png");
	mFlag = mGame->GetTexture("Assets/Flag.png");
	mTileTextures.emplace("Clicked", mGame->GetTexture("Assets/clicked_tile.png"));
	mTileTextures.emplace("Unclicked", mGame->GetTexture("Assets/unclicked_tile.png"));
	mTileTextures.emplace("Unclicked_Hover", mGame->GetTexture("Assets/unclick_hover.png"));
	mTileTextures.emplace("Explosion", mGame->GetTexture("Assets/Explosion.png"));
	mNumbers.emplace(1, mGame->GetTexture("Assets/Numbers/1.png"));
	mNumbers.emplace(2, mGame->GetTexture("Assets/Numbers/2.png"));
	mNumbers.emplace(3, mGame->GetTexture("Assets/Numbers/3.png"));
	mNumbers.emplace(4, mGame->GetTexture("Assets/Numbers/4.png"));
	mNumbers.emplace(5, mGame->GetTexture("Assets/Numbers/5.png"));
	mNumbers.emplace(6, mGame->GetTexture("Assets/Numbers/6.png"));
	mNumbers.emplace(7, mGame->GetTexture("Assets/Numbers/7.png"));
	mNumbers.emplace(8, mGame->GetTexture("Assets/Numbers/8.png"));

	// add the number textures when I get around to making them

	// call SetUp board funcition
	SetUpBoard();
	GenerateGraph(mBoardTiles);
}

GameBoard::~GameBoard() 
{
	for (auto& t : mBoardTiles)
	{
		delete t;
	}

	mBoardTiles.clear();
	mBoardGraph.clear();
	mNumbers.clear();
	mTileTextures.clear();

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
		Vector2 posOffset = startPos + e->gridPosition;
		if (e->highlighted && !e->clicked)
		{
			e->tileTexture = mTileTextures["Unclicked_Hover"];
		}
		else if(!e->clicked)
		{
			e->tileTexture = mTileTextures["Unclicked"];
		}

		if (e->clicked && e->mine)
		{
			e->tileTexture = mTileTextures["Explosion"];
		}

		SDL_Rect r;
		r.w = 32;
		r.h = 32;
		r.x = (int)posOffset.x - 32 / 2;
		r.y = (int)posOffset.y - 32 / 2;

		SDL_RenderCopyEx(renderer,
			e->tileTexture,
			nullptr,
			&r,
			0.0,
			nullptr,
			SDL_FLIP_NONE);

		if (e->numberTexture && !e->mine && e->clicked)
		{
			SDL_RenderCopyEx(renderer,
				e->numberTexture,
				nullptr,
				&r,
				0.0,
				nullptr,
				SDL_FLIP_NONE);
		}
		

		if (e->flagTexture)
		{
			SDL_RenderCopyEx(renderer,
				e->flagTexture,
				nullptr,
				&r,
				0.0,
				nullptr,
				SDL_FLIP_NONE);
		}

		if (mState == Lost)
		{
			SDL_RenderCopyEx(renderer,
				e->mineTexture,
				nullptr,
				&r,
				0.0,
				nullptr,
				SDL_FLIP_NONE);
		}

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
				e->highlighted = true;

			}
			else
			{
				e->highlighted = false;
			}
		}


	}
}

bool GameBoard::ContainsPoint(const Vector2& pt, BoardTile* bt) const
{
	bool no = pt.x < (bt->gridPosition.x - 32 / 2.0f) ||
		pt.x >(bt->gridPosition.x + 32 / 2.0f) ||
		pt.y < (bt->gridPosition.y - 32 / 2.0f + mPosition.y) ||
		pt.y >(bt->gridPosition.y + 32 / 2.0f + mPosition.y);
	return !no;
}

void GameBoard::GenerateGraph(std::vector<BoardTile*> tiles) {

	for (BoardTile* tile : tiles) {
		if (!tile->mine) 
		{ // Consider only tiles with mine=false
			// Add the adjacent tiles to the adjacency list
			int row, col;
			row = static_cast<int>(tile->gridPosition.x);
			col = static_cast<int>(tile->gridPosition.y);
			for (auto& e : mBoardTiles)
			{
				if (!(tile == e))
				{
					//  Corners
					if ((static_cast<int>(e->gridPosition.x) == row - 32 || static_cast<int>(e->gridPosition.x) == row + 32)
						&& (static_cast<int>(e->gridPosition.y) == col - 32 || static_cast<int>(e->gridPosition.y) == col + 32))
					{
						
						if (e->mine)
						{
							tile->numAdjacentMines++;
						}
						else
						{
							mBoardGraph[tile->id].push_back(e);
						}
					}
					// vertical
					if ((static_cast<int>(e->gridPosition.x) == row)
						&& (static_cast<int>(e->gridPosition.y) == col - 32 || static_cast<int>(e->gridPosition.y) == col + 32))
					{
						if (e->mine)
						{
							tile->numAdjacentMines++;
						}
						else
						{
							mBoardGraph[tile->id].push_back(e);
						}
					}
					// horizontal
					if ((static_cast<int>(e->gridPosition.x) == row - 32 || static_cast<int>(e->gridPosition.x) == row + 32)
						&& (static_cast<int>(e->gridPosition.y) == col))
					{
						if (e->mine)
						{
							tile->numAdjacentMines++;
						}
						else
						{
							mBoardGraph[tile->id].push_back(e);
						}
					}
				}
				
			}
			tile->numberTexture = mNumbers[tile->numAdjacentMines];
		}
		else
		{
			mBoardGraph[tile->id];
		}
	}
}

void GameBoard::ClearSpace(BoardTile* t)
{
	if (t->numAdjacentMines != 0 || t->mine) return;

	std::queue<BoardTile*> unvisited;
	unvisited.push(t);

	while (!unvisited.empty())
	{
		int curId = unvisited.front()->id;
		unvisited.pop();
		for (auto& tile : mBoardGraph[curId])
		{
			if (!tile->clicked)
			{
				tile->clicked = true;
				tile->tileTexture = mTileTextures["Clicked"];
				if (!tile->numberTexture)
				{
					unvisited.push(tile);
				}
			}
		}
	}
}

void GameBoard::ResetGame(const int mines, const Vector2 dims)
{
	for (auto& t : mBoardTiles)
	{
		delete t;
	}

	mBoardTiles.clear();
	mBoardGraph.clear();
	mNumMines = mines;
	mNumFlags = 0;
	mGridSize = dims;
	mState = InProgress;
	SetUpBoard();
	GenerateGraph(mBoardTiles);
	mGame->ResizeWindow(Vector2(dims.x * 32, (2 * 32) + (dims.y * 32)));

}

void GameBoard::printAdjacencyList() {
	if (mBoardGraph.empty()) SDL_Log("no graph");
	for (const auto& t : mBoardGraph) {
		std::cout << "Tile id (" << t.first << ") is adjacent to: ";
		for (const BoardTile* neighbor : t.second) {
			std::cout << "(" << neighbor->id << ") ";
		}
		std::cout << std::endl;
	}
}

void GameBoard::HandleKeyPress(const int key)
{
	switch (key)
	{
	case SDL_BUTTON_LEFT:
		if (!mBoardTiles.empty() && mState == InProgress)
		{
			for (auto& t : mBoardTiles)
			{
				if (t->highlighted == true && t->clicked == false && !t->flagged)
				{
					// Change the texture to clicked, and call the search algo
					t->clicked = true;
					t->tileTexture = mTileTextures["Clicked"];
					ClearSpace(t);
					if (t->numAdjacentMines > 0)
					{
						t->numberTexture = mNumbers[t->numAdjacentMines];
					}
					
					if (t->mine)
					{
						SetState(Lost);
					}
					break;
				}
			}
		}
		break;
	case SDL_BUTTON_RIGHT:
		if (!mBoardTiles.empty() && mState == InProgress)
		{
			for (auto& t : mBoardTiles)
			{
				if (t->highlighted && !t->clicked)
				{
					if (t->flagged)
					{
						t->flagged = false;
						t->flagTexture = nullptr;
						mNumFlags--;
						SetFlagChange(true);
					}
					else
					{	
						if (mNumFlags >= mNumMines) break;
						t->flagged = true;
						t->flagTexture = mFlag;
						mNumFlags++;
						SetFlagChange(true);
					}
					break;
				}
				if (t->highlighted && t->flagged)
				{
					t->flagged = false;
					t->flagTexture = nullptr;
					mNumFlags--;
					SetFlagChange(true);
				}
			}
		}
	default:
		break;
	}


}

void GameBoard::SetUpBoard()
{
	int rows, cols, id;
	rows = static_cast<int>(mGridSize.x);
	cols = static_cast<int>(mGridSize.y);
	id = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			BoardTile* t = new BoardTile;
			t->id = id;
			t->gridPosition = Vector2(j * 32+16, i * 32+16);
			t->tileTexture = mTileTextures["Unclicked"];
			mBoardTiles.push_back(t);
			++id;
		}
	}

	std::unordered_set<int> mineLoc;
	int minesUnused = mNumMines;
	int n = 0;
	while(minesUnused > 0)
	{
		n = std::rand() % static_cast<int>(mGridSize.x * mGridSize.y);
		if (mineLoc.count(n) < 1)
		{
			mineLoc.emplace(n);
			--minesUnused;
			mBoardTiles[n]->mine = true;
			mBoardTiles[n]->mineTexture = mMine;
		}
	}
}
