#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummaray();
bool AskToPlayAgain();
FText GetValidGuess();
FBullCowGame BCGame;

int main() 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummaray();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void PlayGame()
{
	BCGame.Reset();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << " | Cows =  " << BullCowCount.Cows << std::endl;
	}

	return;
}

bool AskToPlayAgain()
{
	std::cout << "Would you like to play again? (y/n)" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	return;
}

void PrintGameSummaray()
{
	if (BCGame.IsGameWon())
	{
		std::cout << std::endl << "WELL DONE - YOU WIN!!!" << std::endl;
	}
	else
	{
		std::cout << std::endl << "BETTER LUCK NEXT TIME - YOU LOSE!!!" << std::endl;
	}

	return;
}

FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::INVALID;

	do {
		std::cout << std::endl << "Current try: " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << " | ";
		std::cout << "Enter you guess: ";
		getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word!" << std::endl;
			break;
		case EGuessStatus::EMPTY_GUESS:
			std::cout << "You must guess something, can't leave it empty!" << std::endl;
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "That word is not an isogram it has repeating letters!" << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "That word is not all lowercase!" << std::endl;
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}