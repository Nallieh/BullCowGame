#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() 
{
	Reset();
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	const FString HIDDEN_WORD = "potatis"; // This MUST be an isogram (no repeating letters)
	MyHiddenWord = HIDDEN_WORD;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (Guess.length() == 0)
	{
		return EGuessStatus::EMPTY_GUESS;
		
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString GuessRecieved)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;
	int32 HIDDEN_WORD_LENGTH = MyHiddenWord.length();

	for (int32 i = 0; i < HIDDEN_WORD_LENGTH; i++) {
		for (int32 j = 0; j < HIDDEN_WORD_LENGTH; j++) {
			if (GuessRecieved[j] == MyHiddenWord[i]) {
				if (i == j) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == HIDDEN_WORD_LENGTH)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}
