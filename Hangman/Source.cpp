/**
* @file
* @author Melanie Roy-Plommer
* @version 1.0
*
*
* @section DESCRIPTION
* < brief description of the purpose of this file >
*
*
* @section LICENSE
*
*
* Copyright 2018
* Permission to use, copy, modify, and/or distribute this software for
* any purpose with or without fee is hereby granted, provided that the
* above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
* @section Academic Integrity
* I certify that this work is solely my own and complies with
* NBCC Academic Integrity Policy (policy 1111)
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <Windows.h>


using std::cout;
using std::cin;
using std::endl;
using std::string;


bool isCharInString(string& str, char c);
std::vector<string> getWordsFromFile(const string& path);
string getWord(const std::vector<string>& words);
std::vector<int> findOccurences(string str, char c);

int main()
{
	char play = 'y';

	std::vector<string> words;

	// read file to get possible words
	words = getWordsFromFile("words.txt");


	while (play == 'y') {
		srand(time(NULL)); // new seed for random
		char guess;
		int numberGuesses = 0;
		int guessesLeft = 7;
		
		string lettersUsed = "";		

		// Get random word to play game with
		string wordToGuess = getWord(words);
		//cout << wordToGuess << endl;
		string x = "";

		for (int i = 0; i < wordToGuess.size(); i++) {
			x.push_back('X');
		}
		cout << x << endl;

		do {
			cout << "guess a letter" << endl;
			cin >> guess;

			// TODO: check if only one letter is input.

			if (isCharInString(lettersUsed, guess)) {
				cout << "You have already guessed that letter! Try again!" << endl;
			}
			else { //play game
				lettersUsed += guess;
				if (isCharInString(wordToGuess, guess)) {
					cout << "YES!!" << endl;
					//find letter(s) in string (function)
					std::vector<int> charsPos = findOccurences(wordToGuess, guess);

					//put found letter in the progress string  XXXXXXX

					for (int i = 0; i < charsPos.size(); i++) {
						x.at(charsPos[i]) = wordToGuess.at(charsPos[i]);
					}
				}
				else {
					guessesLeft--;
					if (guessesLeft == 0) {
						cout << "You have been hanged!! Oh no!! Play again? y/n" << endl;
						cin >> play;
						system("cls");
						break;
					}
					else {
						cout << "NO! You have " << guessesLeft << " guesses left!" << endl;

					}
					numberGuesses++;
				}
				cout << x << endl;
				cout << lettersUsed << endl;

				if (x == wordToGuess)
				{
					cout << "Congratulations!!! You guessed my word! Play again? y/n" << endl;
					cin >> play;
					system("cls");
					break;
				}
			}

		} while (numberGuesses < 7);
	}
	
	
	getchar();
	getchar();
}

// takes wordToGuess and guess as arguments
std::vector<int> findOccurences(string str, char c)
{
	std::vector<int> characterLocations;
	for (int i = 0; i < str.size(); i++)
		if (str[i] == c)
			characterLocations.push_back(i);

	return characterLocations;
}

 // is the guess in the wordToGuess?
bool isCharInString(string& str, char c) {	
	if (str.find(c) != std::string::npos)
		return true;
	else
		return false;
}

std::vector<string> getWordsFromFile(const string & path)
{
	std::ifstream gameFile;
	gameFile.open(path, std::ios::in);
	std::vector<std::string> words;
	std::string word;
	
	// reads the words, separately
	while (gameFile >> word)
	{
		words.push_back(std::string(word));
		//std::cout << word << '\n';
	}
	gameFile.close();
	return words;

}

string getWord(const std::vector<string>& words)
{ // use random to get word from a random index of the vector words	
	return words.at(rand() % words.size());
}
