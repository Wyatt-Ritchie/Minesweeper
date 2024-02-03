#pragma once
#include "SDL.h"
#include <unordered_map>
#include "Math.h"
#include <string>

struct BoardTile {
	int id;
	SDL_Texture* tileTexture = nullptr;
	SDL_Texture* numberTexture = nullptr;
	SDL_Texture* mineTexture = nullptr;
	SDL_Texture* flagTexture = nullptr;
	Vector2 gridPosition;
	bool mine = false;
	int numAdjacentMines = 0;
	bool highlighted = false;
	bool clicked = false;
	bool flagged = false;
	bool operator==(const BoardTile* other) const {
		return id == other->id;
	}
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

	bool ContainsPoint(const Vector2& pt, BoardTile* bt) const;

	void GenerateGraph(std::vector<BoardTile*> tiles);

	void ClearSpace(BoardTile* t);

	void ResetGame(const int mines, const Vector2 dims);

	void printAdjacencyList();

	bool RequiresUpdate() const { return mFlagChange; }
	void SetFlagChange(bool changed) { mFlagChange = changed; }

	void SetPosition(Vector2 vec) { mPosition = vec; }

	int GetFlaggedCount() const { return mNumMines - mNumFlags; }

	Vector2 GetPosition() const { return mPosition; }

private:

	State mState;
	class Game* mGame;

	bool mFlagChange;

	// map containing the textures for the tiles. 
	// There are 3 tile textures; Unclicked, Unclicked_Hover, Clicked and Explosion
	std::unordered_map<std::string, SDL_Texture*> mTileTextures;

	// This map contains the texture for the numbers 1-8
	std::unordered_map<int, SDL_Texture*> mNumbers;

	// The adjacency list
	std::unordered_map<int, std::vector<BoardTile*>> mBoardGraph;

	std::vector<BoardTile*> mBoardTiles;

	// The texture for the mine
	SDL_Texture* mMine;

	SDL_Texture* mFlag;

	Vector2 mPosition;

	Vector2 mGridSize;

	int mNumMines;

	int mNumFlags;
};

