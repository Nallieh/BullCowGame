#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	INVALID,
	OK,
	NOT_ISOGRAM,
	NOT_VALID_CHAR,
	EMPTY_GUESS,
	WRONG_LENGTH,
	NOT_LOWERCASE
};

class FBullCowGame 
{
public:
	FBullCowGame();
	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	FBullCowCount SubmitValidGuess(FString);

private:
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
};