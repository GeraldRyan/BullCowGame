/* The game logic (no view code or direct user interaction)
The game is a simple 'guess the word' game based on mastermind. 
*/

#pragma once
#include <string>

// to make syntax 'Unreal' friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus 
{
	Invalid_Status,
	Ok,
	Not_isogram,
	Wrong_Length,
	Not_lowercase

};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 


	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);
	// please try and ignore this and focus on the interface above ^^
private:
	// see constructor for initialization

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	int32 MyCurrentTry;
	// int32 MyMaxTries; DEPRICATED
	FString MyHiddenWord;
	bool bGameIsWon;
};