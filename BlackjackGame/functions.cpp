#include <iostream>
#include <array>
#include "functions.h"
#include <random> // for std::mt19937
#include <ctime> // for std::time

namespace MyRandom
{
	// Initialize our mersenne twister with a random seed based on the clock (once at system startup)
	std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
}

int getRandomNumber(int min, int max)
{
	std::uniform_int_distribution<> die(min, max); // we can create a distribution in any function that needs it
	return die(MyRandom::mersenne); // and then generate a random number from our global generator
}

void printCard(const Card& card) {
	switch (card.rank)
	{
	case RANK_2:
		std::cout << 2;
		break;
	case RANK_3:
		std::cout << 3;
		break;
	case RANK_4:
		std::cout << 4;
		break;
	case RANK_5:
		std::cout << 5;
		break;
	case RANK_6:
		std::cout << 6;
		break;
	case RANK_7:
		std::cout << 7;
		break;
	case RANK_8:
		std::cout << 8;
		break;
	case RANK_9:
		std::cout << 9;
		break;
	case RANK_10:
		std::cout << 10;
		break;
	case RANK_ACE:
		std::cout << 'A';
		break;
	case RANK_QUEEN:
		std::cout << 'Q';
		break;
	case RANK_JACK:
		std::cout << 'J';
		break;
	case RANK_KING:
		std::cout << 'K';
		break;
	default:
		break;
	}

	switch (card.suit)
	{
	case SUIT_CLUB:
		std::cout << 'C';
		break;
	case SUIT_DIAMOND:
		std::cout << 'D';
		break;
	case SUIT_HEART:
		std::cout << 'H';
		break;
	case SUIT_SPADE:
		std::cout << 'S';
		break;
	default:
		break;
	}
}

void printDeck(const std::array<Card, 52> & deck) {
	for (const auto& element : deck) {
		printCard(element);
		std::cout << '\n';
	}
}

void swapCard(Card& card1, Card& card2) {
	Card temp;
	temp = card1;
	card1 = card2;
	card2 = temp;
}

void shuffleDeck(std::array<Card, 52> & deck) {
	for (auto& element : deck) {
		int randomNumber = getRandomNumber(1, 51);
		swapCard(element, deck[randomNumber]);
	}
}

int getCardValue(const Card& card) {
	switch (card.rank)
	{
	case RANK_2:	 return 2;
	case RANK_3:	 return 3;
	case RANK_4:	 return 4;
	case RANK_5:	 return 5;
	case RANK_6:	 return 6;
	case RANK_7:	 return 7;
	case RANK_8:	 return 8;
	case RANK_9:	 return 9;
	case RANK_10:	 return 10;
	case RANK_ACE:	 return 11;
	case RANK_JACK:	 return 10;
	case RANK_KING:	 return 10;
	case RANK_QUEEN: return 10;
	default:
		break;
	}
}

BlackJackResult playBlackjack(const std::array<Card, 52> &deck) {
	int playerScore{ 0 };
	int dealerScore{ 0 };
	const Card* cardPtr = &deck[0];
	bool dealerNewCard{ true };
	bool playerNewCard{ true };
	while (true)
	{
		if (dealerScore < 17) {
			std::cout << "Dealer is getting a card..." << '\n';
			if (getCardValue(*cardPtr) == 11 && dealerScore > 10) {
				dealerScore += 1;
			}
			else {
				dealerScore += getCardValue(*cardPtr++);
			}
		}
		else {
			std::cout << "Dealer stopped..." << '\n';
			dealerNewCard = false;
		}
		if (playerNewCard) {
			std::cout << "do you wanna get a new card? ";
			std::cin >> playerNewCard;
			std::cin.ignore(32767, '\n');
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
		}
		if (playerNewCard) {
			if(getCardValue(*cardPtr++) == 11 && playerScore > 10){
				playerScore++;
			}
			else {
				playerScore += getCardValue(*cardPtr++);
			}
			std::cout << playerScore << '\n';
		}
		if (dealerNewCard == false && playerNewCard == false) {
			std::cout << "DealerScore : " << dealerScore << '\n';
			break;
		}
	}
	if (dealerScore > 21 && playerScore > 21)
		return BLACKJACK_TIE;
	else if (playerScore == dealerScore)
		return BLACKJACK_TIE;
	else if (dealerScore > 21)
		return BLACKJACK_PLAYER_WIN;
	else if (playerScore > 21)
		return BLACKJACK_DEALER_WIN;
	else if (playerScore > dealerScore)
		return BLACKJACK_PLAYER_WIN;
	else if (dealerScore > playerScore)
		return BLACKJACK_DEALER_WIN;
}	