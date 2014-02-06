/*
	Kai Austin
	Software Systems, Spring 2014

	cards.c = Enter in the name of a card from a standard deck
	If the card is a King, Queen, Jack, or Ten, deduct a point
	All cards between 2-7, add a point
*/


#include <stdio.h>
#include <stdlib.h>


/*	Prompts the user to enter a card, then sets the val
	Of the card.

	val: The value of the card
	cname: where the name of the card is stored
*/
void getCardValue(int *val, char cname[]){
	puts("Enter the card_name: ");
	scanf("%2s", cname);

	switch(cname[0]) {
		case 'K':
		case 'Q':
		case 'J':
			*val = 10;
			break;
		case 'A':
			*val = 11;
			break;
		case 'X':
			break;
		default:
			*val = atoi(cname);
			if ((*val < 1) || (*val > 10)) {
				puts("I dont understand that value!");
				break;
			}
		}
}

/*	Increments the counter for the total score

	val: The value of the card
	counter: Pointer to the total score
*/
void incCounter(int val, int *counter){
	if ((val > 2) && (val < 7)) {
		*counter = *counter + 1;
	} else if (val == 10) {
		*counter = *counter -1;
	}
}

/*	Main function which runs the program until the
	user types in 'X', otherwise prints out total
	score after each card in entered.
*/
int main()
{
	char card_name[3];
	int count = 0;
	int val = 0;

	while ( card_name[0] != 'X' ) {

		getCardValue(&val, card_name);
		incCounter(val, &count);
		
		printf("Current count: %i\n", count);
	}
	return 0;
}