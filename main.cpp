/* This is the console executable, that makes use of the BullCow Class.
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
The methods available to members of the FBullCowGame class include:
GetHiddenWordLength; GetMaxTries; GetCurrentTry; CheckGuessValidity; IsGameWon; and Reset;
SubmitGuess is a method of the BullCowCount struct type. 
*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class 
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game which we re-use across plays


// entry point for our application
int main() {
	bool bPlayAgain = false;
	do {
	PrintIntro();
	PlayGame();
	bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0; // exit the game
}


void PrintIntro() {

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	return;
}

// plays a single game to completion. 
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "\n";

	// loop asking for guesses while game is not won
	// and there are still tries remaining



	while(!BCGame.IsGameWon()&& BCGame.GetCurrentTry()<=MaxTries)
		{
			FText Guess = GetValidGuess(); 
			// Submit valid guess to game and receive counts

			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
			std::cout << "Bulls: " << BullCowCount.Bulls << " -|- ";
			std::cout << "Cows: " << BullCowCount.Cows << "\n\n";
		}
	PrintGameSummary();
	return;
}
//loop continually until user gives valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do 
	{
		//get a guess from the player 
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter Your Guess: ";
		std::getline(std::cin, Guess);  // player enters his guess in the loop

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_isogram:
			std::cout << "\nPlease enter an isogram (each letter appears only once in the word). \n\n";
			break;
		case EGuessStatus::Not_lowercase:
			std::cout << "Please make your word lowercase. \n\n";
			break;
		default:
			// assuming guess is valid
			break;
		}

	} while (Status != EGuessStatus::Ok); //keep looping until we get valid input. 

		return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with same word? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "WELL DONE - YOU WIN!\n\n";
	}
	else
	{
		std::cout << "BETTER LUCK NEXT TIME\n\n";
	}

}