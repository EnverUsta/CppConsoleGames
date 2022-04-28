#pragma once
#include <iostream>
#include <array>


enum CardSuit {
	SUIT_CLUB,
	SUIT_DIAMOND,
	SUIT_HEART,
	SUIT_SPADE,
	MAX_SUITS,
};

enum CardRank {
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,
	MAX_RANKS,
};

struct Card {
	CardRank rank;
	CardSuit suit;
};

enum BlackJackResult{
	BLACKJACK_PLAYER_WIN,
	BLACKJACK_DEALER_WIN,
	BLACKJACK_TIE,
};


void printCard(const Card& card);
void printDeck(const std::array<Card, 52> & deck);
void swapCard(Card& card1, Card& card2);
void shuffleDeck(std::array<Card, 52> & deck);
int getCardValue(const Card& card);
BlackJackResult playBlackjack(const std::array<Card, 52> &deck);