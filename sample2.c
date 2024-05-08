#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int playerScore, dealerScore;
    int playerMoney = 100;
    char choice, devam;
    int bet;

    const int MAX_CARDS = 20;
    int players_cards [MAX_CARDS];
    int dealers_cards [MAX_CARDS];
    
    srand(time(0)); // Rastgelelik ayarı
    printf("Welcome to Blackjack!\n");

    do {
        for(int i =0;i<MAX_CARDS;i++){
            players_cards[i]=-1;
            dealers_cards[i]=-1;
        }

        int dealers_card_count = 2;
        int players_card_count = 2;

        printf("You currently have %d chips.\n", playerMoney);
        printf("Enter your bet: ");
        scanf("%d", &bet);
        if (bet > playerMoney || bet==0) {
            printf("Invalid bet. Please enter a valid bet.\n");
            main();
        }

        playerMoney -= bet;
        playerScore = 0;
        dealerScore = 0;

        // Kartları dağıt
        players_cards[0] = rand() % 13 + 1;
        players_cards[1] = rand() % 13 + 1;
        dealers_cards[0] = rand() % 13 + 1;
        dealers_cards[1] = rand() % 13 + 1;

        // Oyuncu kartları
        if(players_cards[0]>10)playerScore+=10;
        else playerScore += players_cards[0];
        if(players_cards[1]>10)playerScore+=10;
        else playerScore += players_cards[1];
        
        if(players_cards[0]>10){
            char card;
            if(players_cards[0]==11)card = 'Q';
            else if(players_cards[0]==12)card = 'J';
            else if(players_cards[0]==13)card = 'K';
            printf("\nYour cards: %c",card);
        }
        else printf("\nYour cards: %d",players_cards[0]);
        if(players_cards[1]>10){
            char card;
            if(players_cards[1]==11)card = 'Q';
            else if(players_cards[1]==12)card = 'J';
            else if(players_cards[1]==13)card = 'K';
            printf(" and %c\n",card);
        }
        else printf(" and %d\n",players_cards[1]);
        printf("Total score: %d\n" , playerScore);

        // Blackjack kontrolü
        if (playerScore == 21) {
            printf("Blackjack! Congratulations, you win 3 times your bet!\n");
            playerMoney += bet * 4; // Bet + 3 * bet
            continue;
        }

        // Dağıtıcının kartları
        if(dealers_cards[1]>10){
            char card;
            if(dealers_cards[1]==11)card = 'Q';
            else if(dealers_cards[1]==12)card = 'J';
            else if(dealers_cards[1]==13)card = 'K';
            printf("Dealer's cards: [hidden] and %c\n\n",card);
        }
        else printf("Dealer's cards: [hidden] and %d\n\n",dealers_cards[1]);
        if(dealers_cards[1]>10)dealerScore = 10;
        else dealerScore = dealers_cards[1];

        // Oyuncu hamleleri
        printf("Press 'H' to hit, 'S' to stand: ");
        scanf(" %c", &choice);
        while ((choice == 'H' || choice == 'h') && playerScore <= 21) {
            players_cards[players_card_count]=rand() % 13 + 1;
            if(players_cards[players_card_count]>10){
                char card;
                if(players_cards[players_card_count]==11)card = 'Q';
                else if(players_cards[players_card_count]==12)card = 'J';
                else if(players_cards[players_card_count]==13)card = 'K';
                printf("Your new card: %c\n", card);
            }
            else printf("Your new card: %d\n",players_cards[players_card_count]);
            if(players_cards[players_card_count] > 10)playerScore +=10;
            else playerScore += players_cards[players_card_count];
            players_card_count++;
            printf("Your total score: %d\n\n" , playerScore);
            if (playerScore > 21) {
                printf("Busted! You lose.\n");
                break;
            }
            printf("Press 'H' to hit, 'S' to stand: ");
            scanf(" %c", &choice);
        }

        // Dağıtıcının hamleleri
        printf("Dealer's hidden card was: %d\n\n", dealers_cards[0]);
        if(dealers_cards[0]>10)dealerScore+=10;
        else dealerScore += dealers_cards[0];
        while (dealerScore < 17 && playerScore <= 21) {
            dealers_cards[dealers_card_count]=rand() % 13 + 1;
            if(dealers_cards[dealers_card_count]>10){
                char card;
                if(dealers_cards[dealers_card_count]==11)card = 'Q';
                else if(dealers_cards[dealers_card_count]==12)card = 'J';
                else if(dealers_cards[dealers_card_count]==13)card = 'K';
                printf("Dealer's new card: %c\n", card);
            }
            else printf("Dealer's new card: %d\n",dealers_cards[dealers_card_count]);
            if(dealers_cards[dealers_card_count] > 10)dealerScore +=10;
            else dealerScore += dealers_cards[dealers_card_count];
            dealers_card_count++;
            printf("Dealer's total score: %d\n\n" , dealerScore);
        }

        // Oyuncunun ve dağıtıcının kartlarını göster
        printf("Your cards: ");
        for(int i = 0;i<players_card_count;i++){
            char card;
            if(players_cards[i]>10){
                if(players_cards[i]==11)card = 'Q';
                else if(players_cards[i]==12)card = 'J';
                else if(players_cards[i]==13)card = 'K';
                printf("%c",card);
            }
            else printf("%d",players_cards[i]);
            if(i!=players_card_count-1)printf(", ");
        }
        printf("\nYour total score: %d\n", playerScore);
        printf("Dealer's cards: ");
        for(int i = 0;i<dealers_card_count;i++){
            char card;
            if(dealers_cards[i]>10){
                if(dealers_cards[i]==11)card = 'Q';
                else if(dealers_cards[i]==12)card = 'J';
                else if(dealers_cards[i]==13)card = 'K';
                printf("%c",card);
            }
            else printf("%d",dealers_cards[i]);
            if(i!=dealers_card_count-1)printf(", ");
        }
        printf("\nDealer's total score: %d\n\n" , dealerScore);

        // Oyun sonucunu kontrol et
        if (playerScore > 21  || (dealerScore <= 21 && dealerScore > playerScore)) {
            printf("Dealer wins!\n");
        } else if (dealerScore > 21 || playerScore > dealerScore) {
            if(dealerScore > 21)printf("Dealer busts! You win.\n");
            else printf("Congratulations! You win.\n");
            playerMoney += bet * 2;
        } else {
            printf("It's a tie!\n");
            playerMoney += bet;
        }
        if (playerMoney >= 500) {
            printf("You have reached 500 chips. The casino will bankrupt if we let you play anymore! You win!\n");
            break;
        }
        else if(playerMoney <=0){
            printf("You've run out of chips. Game over.\n");
            break;
        } 
        printf("Do you want to play a new game with %d chips? (Y/N): ",playerMoney);
        scanf(" %c", &devam);
        if (devam=='N' || devam=='n')
            break;
    } while (devam == 'Y' || devam == 'y');

    printf("You have left the table. Goodbye!\n");
    return 0;
}