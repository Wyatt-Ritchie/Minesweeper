#include "GameBoard.h"
#include "Game.h"

GameBoard::GameBoard(Game* game, int numMines, Vector2 GridSize) : mGame(game)
																  ,mState(InProgress)
															      ,mNumMines(numMines)
																  ,mGridSize(GridSize)
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

	// Iterate through each tile, and draw it's texture, and the number/mine on the tile

}

void GameBoard::ProcessInput(const uint8_t* keys)
{

}

void GameBoard::HandleKeyPress(const int key)
{
}

void GameBoard::SetUpBoard()
{

}
