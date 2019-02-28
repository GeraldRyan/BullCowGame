#include "FBullCowGame.h"
#include <map>
#pragma once

// to make Unreal Engine friendly
#define Tmap std::map
using int32 = int;

FBullCowGame::FBullCowGame() {Reset(); }  // default constructor 


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	Tmap<int32, int32> WordLengthToMaxTries{ {3,3},{4,4},{5,6},{6,11},{7,12} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
//	return MyMaxTries;
}

void FBullCowGame::Reset()
{
//	constexpr int32 MAX_TRIES = 3;  DEPRICATED
	const FString HIDDEN_WORD = "planet";  // This must be an isogram (no repeating letters)

//	MyMaxTries = MAX_TRIES; DEPRICATED
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
// receives a valid guess, increments turn and returns count 

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount; // sets up a return variable

	// loop through all letters in hidden word
	int32 WordLength = MyHiddenWord.length(); 
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			// if they match, then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar==GChar) // If they're in the same place
				{ 
				BullCowCount.Bulls++; // increment bulls
				}	
				else { BullCowCount.Cows++; }

				// increment cows if not
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;	}
	else { bGameIsWon = false; }
		return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// set up our map
	Tmap <char, bool> LetterSeen;
	for (auto Letter : Word) 
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true;
	}
			// if letter already in map, return false
			// otherwise add letter to map	
	}

	return true; // for example in cases of /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		// if not a lc letter return false
		if (!islower(Letter)) { return false; }
	}
	return true;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if guess !isogram 
	{
		return EGuessStatus::Not_isogram; 
	}
	else if (!IsLowerCase(Guess))	// if guess !lowercase 
	{
		return EGuessStatus::Not_lowercase; //TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength()) //guess length wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::Ok;
	}

}


	