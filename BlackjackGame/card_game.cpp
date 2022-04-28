#include <iostream>
#include <array>

#include "functions.h"


int main() {

	std::cout << "This is a blackjack game if you don't know it please google it as 'blackjack game'\n";
	std::cout << "you're gonna play against the dealer\n";

	std::array<Card, 52> deck;

	using index_t = std::array<Card, 52>::size_type;
	index_t card = 0;

	for (int suit = 0; suit < MAX_SUITS; ++suit) 
		for (int rank = 0; rank < MAX_RANKS; ++rank) {
			deck[card].suit = static_cast<CardSuit>(suit);
			deck[card].rank = static_cast<CardRank>(rank);
			++card;
		}

	shuffleDeck(deck);


	BlackJackResult result = playBlackjack(deck);
	switch (result)
	{
	case BLACKJACK_PLAYER_WIN:
		std::cout << "YOU WON !!!";
		break;
	case BLACKJACK_DEALER_WIN:
		std::cout << "DEALER WON !!!";
		break;
	case BLACKJACK_TIE:
		std::cout << "YOU ARE TIED WITH DEALER !!!";
		break;
	default:
		break;
	}

	

	return 0;
}