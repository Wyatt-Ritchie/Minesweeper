#pragma once
#include "SDL.h"
#include "unordered_map"
#include"Math.h"
#include <string>

struct BoardTile {
	SDL_Texture* tileTexture = nullptr;
	SDL_Texture* numberTexture = nullptr;
	SDL_Texture* mineTexture = nullptr;
	Vector2 gridPosition;
	bool mine = false;
	int numAdjacentMines = 0;
	bool highlighted = false;
	bool clicked = false;
};

class GameBoard
{
public:
	// State of the game board
	enum State {
		InProgress,
		Won,
		Lost
	};

	GameBoard(class Game* game, int numMines, Vector2 GridSize);
	~GameBoard();

	State GetState() const { return mState; }
	class Game* GetGame() const { return mGame; }

	void SetState(State state) { mState = state; }

	void Update(const float deltaTime);
	void Draw(SDL_Renderer* renderer);
	void ProcessInput(const uint8_t* keys);
	void HandleKeyPress(const int key);

	void SetUpBoard();

	bool ContainsPoint(const Vector2& pt, BoardTile bt) const;

private:

	State mState;
	class Game* mGame;

	// map containing the textures for the tiles. 
	// There are 3 tile textures; Unclicked, Unclicked_Hover, Clicked and Explosion
	std::unordered_map<std::string, SDL_Texture*> mTileTextures;

	// This map contains the texture for the numbers 1-8
	std::unordered_map<int, SDL_Texture*> mNumbers;

	std::vector<BoardTile> mBoardTiles;

	// The texture for the mine
	SDL_Texture* mMine;

	const Vector2 mPosition;

	const Vector2 mGridSize;

	const int mNumMines;
};

