
// Brief note: This is not good code.  I made this a few yrs ago learning C, and literally built this only knowing like 5-6 things or
// so.  Also was learning Blackjack while coding.  So, yeah.  Code sucks.  If anyone's interested in running it or playing
// with it, it's here.

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <math.h>
#include <windows.h>
/*Splitting Aces*/


int main()
{
    int Decks = 1;
    int Round = 0;
    int AceHandleD=0;
    int AceHandleP=0;
    int Rearrange[Decks*52];
    int Points[Decks*52];
    int DealerPoints=0;
    int PlayerPoints=0;
    int swap[2];
    char Cards [Decks*52];
    char Again;
    char Choice;
    char Insurance;
    char Splitter;
    int i,j,r;
    int Money;
    int Bet;
    int DDflag=0;
    int StopA=0;
    int StopB=0;
    int SplitterFlag=0;
    int SplitterRoundA=0;
    int SplitterRoundB=0;
    int PlayerPointsA=0;
    int PlayerPointsB=0;
    int BetA=0;
    int BetB=0;
    srand(time(0));

    printf("Welcome to Blackjack!\nInput starting money value: ");
    scanf("%d",&Money);

    Game: /*Code returns here when process restarts*/

    Bet=0;
    printf("\nInput bet: ");
    scanf("%d",&Bet);

    if (Bet>Money) {
        printf("\n\nInvalid Bet.\n");
        goto Game;
    }


    for (i=0; i<52;i++) {
        Rearrange[i] = i;  /*This makes an array from 0-51*/
    }

    for (i=(Decks*52 - 1); i>0; i--){
        r = rand() % i;
        swap[0]=Rearrange[r];  /*This shuffles the numbers in the Rearrange array*/
        swap[1]=Rearrange[i];
        Rearrange[i]=swap[0];
        Rearrange[r]=swap[1];
    }

    i=-1; /*Sets up the while loop*/

    while (i++<51) { /*While loop determines where cards go in array based on number setting in Rearrange*/
        if (Rearrange[i] >= 0 && Rearrange[i] <=3) {
            Cards[i]='2';
            Points[i]=2;
        }
        else if (Rearrange[i] >=4 && Rearrange[i] <=7) {
            Cards[i]='3';
            Points[i]=3;
        }
        else if (Rearrange[i] >=8 && Rearrange[i] <=11) {
            Cards[i]='4';
            Points[i]=4;
        }
        else if (Rearrange[i] >=12 && Rearrange[i] <=15) {
            Cards[i]='5';
            Points[i]=5;
        }
        else if (Rearrange[i] >=16 && Rearrange[i] <=19) {
            Cards[i]='6';
            Points[i]=6;
        }
        else if (Rearrange[i] >=20 && Rearrange[i] <=23) {
            Cards[i]='7';
            Points[i]=7;
        }
        else if (Rearrange[i] >=24 && Rearrange[i] <=27) {
            Cards[i]='8';
            Points[i]=8;
        }
        else if (Rearrange[i] >=28 && Rearrange[i] <=31) {
            Cards[i]='9';
            Points[i]=9;
        }
        else if (Rearrange[i] >=32 && Rearrange[i] <=35) {
            Cards[i]='T';
            Points[i]=10;
        }
        else if (Rearrange[i] >=36 && Rearrange[i] <=39) {
            Cards[i]='J';
            Points[i]=10;
        }
        else if (Rearrange[i] >=40 && Rearrange[i] <=43) {
            Cards[i]='Q';
            Points[i]=10;
        }
        else if (Rearrange[i] >=44 && Rearrange[i] <=47) {
            Cards[i]='K';
            Points[i]=10;
        }
        else /*(Rearrange[i] >=48 && <=51)*/ {
            Cards[i]='A';
            Points[i]=11;
        }
    }

    char DealerHand[12];
    char PlayerHand[40];

    for (i=0;i<12;i++) {
        DealerHand[i]=Cards[i];
    }
    for (i=0;i<40;i++) {
        PlayerHand[i]=Cards[i+12];
    }


   /* PlayerHand[0]='3';
    PlayerHand[1]='3';
    Points[12]=3;
    Points[13]=3; */



while (Round<11) { /*11 Rounds just because*/
    AceHandleD=0;
    AceHandleP=0;
    DealerPoints=0;
    PlayerPoints=0;  /*resets values before game starts*/

    printf("\nDealer Hand:\n\n");

    if (DealerHand[0]=='T'){
        printf("10  ");
    }
    else{
        printf("%c  ",DealerHand[0]);
    }
    printf("\n\nDealer has %d points.\n\n\n",Points[0]); /*Dealer cards*/

    /*Player Details*/

    if (SplitterFlag==0) { /*No split hands situation*/
        printf("Player Hand:\n\n");
        for(i=0;i<=Round+1;i++) {
            if (PlayerHand[i]=='T') {
                printf("10  ");
            }
            else {
                printf("%c  ",PlayerHand[i]);  /*Checks the Player's Hand*/
            }
            if (PlayerHand[i]=='A') {
                AceHandleP=AceHandleP+1;  /*Checks to see if the Player has Aces*/
            }
            PlayerPoints=PlayerPoints+Points[i+12]; /*Adds up players points*/
        }
    }
    else if (SplitterFlag==2 && StopA==0) { /*Hand A from Split Hands*/
        PlayerPointsA=0;
        PlayerPoints=Points[12];
        printf("Player Hand A:\n\n");
        if (PlayerHand[0]=='T'){
            printf("10  ");
        }
        else {
            printf("%c  ",PlayerHand[0]);
        }
        if (PlayerHand[0]=='A'){
            AceHandleP=AceHandleP+1;
        }
        for (i=0;i<=SplitterRoundA;i++){
            if(PlayerHand[i+28]=='T'){
                printf("10  ");
            }
            else {
                printf("%c  ",PlayerHand[i+28]);
            }
            if (PlayerHand[i+28]=='A') {
                AceHandleP=AceHandleP+1;
            }
            PlayerPoints=PlayerPoints+Points[i+40];
        }
        PlayerPointsA=PlayerPoints;
        SplitterRoundA=SplitterRoundA+1;  /*Similar code: creates hand for Hand A*/
    }

    else if (SplitterFlag==3 && StopB==0) { /*Creates hand for Hand B*/
        PlayerPointsB=0;
        PlayerPoints=Points[13];
        printf("Player Hand B:\n\n");
        if(PlayerHand[1]=='T'){
            printf("10  ");
        }
        else{
            printf("%c  ",PlayerHand[1]);
        }
        if (PlayerHand[1]=='A'){
            AceHandleP=AceHandleP+1;
        }
        for (i=0;i<=SplitterRoundB;i++){
            if (PlayerHand[i+2]=='T') {
                printf("10  ");
            }
            else {
                printf("%c  ",PlayerHand[i+2]);
            }
            if (PlayerHand[i+2]=='A') {
                AceHandleP=AceHandleP+1;
            }
            PlayerPoints=PlayerPoints+Points[i+14];
        }
        PlayerPointsB=PlayerPoints;
        SplitterRoundB=SplitterRoundB+1;
    }

    while (PlayerPoints >21 && AceHandleP>0) {  /*Removes 10 points from each A if player is above 21*/
        PlayerPoints=PlayerPoints-10;
        if (PlayerPointsA>21 && SplitterFlag==2 && StopA==0) {
            PlayerPointsA=PlayerPointsA-10;
        }
        if (PlayerPointsB>21 && SplitterFlag==3 && StopB==0) {
            PlayerPointsB=PlayerPointsB-10;
        }

        AceHandleP=AceHandleP-1;
    }
    printf("\n\nPlayer has %d points.\n\n",PlayerPoints);

    if(Round==0 && (Points[0])==11 && Money - (Bet + ceil(0.5*Bet)) >= 0) { /*This is all for insurance*/
        printf("\n\nDo you want to take Insurance? [Y] [N]\n\n");
        Insurance = getchar();
        while (Insurance != 'Y' && Insurance != 'N') {
            if (Insurance != '\n') {
                printf("Invalid Choice\n\n");
            }
            Insurance = getchar();
        }
        if (Points[12]+Points[13]==21) {
            printf("\nDealer Hand:\n\n");
            for(i=0;i<=1;i++) {
                if (DealerHand[i]=='T'){
                    printf("10  ");
                }
                else {
                    printf("%c  ",DealerHand[i]);
                }
            }
            if (Insurance=='Y') {
                printf("\n\nYou win even money.");
                Bet=Bet*2;
                goto Replay;
            }
            else if (Insurance=='N' && Points[0]+Points[1]==21) {
                printf("\n\nYou tie.\n\n");
                Bet=0;
                goto Replay;
            }
            else if (Insurance=='N' && Points[0]+Points[1]!=21) {
                printf("\n\nYou have Blackjack and dealer does not. You win!");
                Bet=ceil(Bet*1.5);
                goto Replay;
            }
        }

        if ((Points[0]+Points[1])==21) {
            printf("\nDealer Hand:\n\n");
            for(i=0;i<=1;i++) {
                if (DealerHand[i]=='T'){
                    printf("10  ");
                }
                else {
                    printf("%c  ",DealerHand[i]);
                }
            }
            if (Insurance == 'Y') {
                printf("\n\nDealer has Blackjack.  Insurance and bet returned.");
                Bet=0;
            }
            else {
                printf("\n\nDealer has Blackjack.  You lose.");
                Bet=Bet*-1;
            }
            goto Replay;
        }
        else {
            if (Insurance == 'Y') {
                printf("\nDealer does not have Blackjack.  You have lost your insurance: %.0f\n\n", ceil(Bet*0.5)); /*Check here*/
                Money=Money-ceil(0.5*Bet);
            }
        }
    }

    if (Round==0 && PlayerHand[0]==PlayerHand[1] && Money-2*Bet>=0 && SplitterFlag==0) {
        printf("Would you like to split hands? [Y] [N]\n\n");
        Splitter=getchar();
        if (Splitter == '\n') {
            Splitter = getchar();
        }
        while (Splitter != 'Y' && Splitter != 'N') {
            if (Splitter != '\n') {
                printf("Invalid Choice\n\n");
            }
            Splitter = getchar();
        }
        if (Splitter=='Y') {
            SplitterFlag=1;
            BetA=Bet;
            BetB=Bet;
        }
    }

    if(PlayerPointsA>21 && StopA != 2){
        printf("\n\nHand A has busted.\n\n");
        Sleep(1000);
        StopA=2;
    }

    if(PlayerPointsB>21 && StopB != 2){
        printf("\n\nHand B has busted.\n\n");
        Sleep(1000);
        StopB=2;
    }

    if(StopA==2&&StopB==2) {
        BetA=BetA*-1;
        BetB=BetB*-1;
        printf("Both hands busted.  You lose.");
        goto Replay;
    }


    if (PlayerPoints>21&&SplitterFlag==0) {
        printf("You bust. You lose. "); /*Player bust condition*/
        Bet=Bet*-1;
        goto Replay;
    }

    if ((SplitterFlag == 1) || (StopA==2 && SplitterFlag==2 && StopB == 0) || (StopB==2 && SplitterFlag==3 && StopA == 0)) {
        SplitterFlag=2;
        Choice ='H';
    }
    else if((DDflag==1) || (StopA==1 && StopB!=0)||(StopB==1 && StopA != 0)) {
        Choice='S';
    }
    else {
        if ((Round==0 && Bet*2<=Money) || (SplitterFlag==2 && SplitterRoundA==1 && Money-(BetB+(BetA*2))>=0) || (SplitterFlag==3 && SplitterRoundB==1 && Money-((BetA+(BetB*2)))>=0)) {
            printf("\nHit, Stay, or Double Down? [H] [S] [D]\n\n");
        }
        else {
            printf("\nHit or Stay? [H] [S]\n\n");
        }
        Choice = getchar();
        if(Choice == '\n') {
            Choice = getchar();
        }
        if (Choice =='D'){  /*Problem line*/
            if(Round == 1 && SplitterRoundA==1 && StopA != 1){
                BetA=BetA*2;
                StopA=1;
            }
            if(Round == 2 && SplitterRoundB==1 && StopB != 1){
                BetB=BetB*2;
                StopB=1;
            }
            if(SplitterRoundA==0){
                Bet=Bet*2;
                DDflag=1;
            }
            Choice='H';
        }
        if (Choice=='D'&&Round>0) { /*Why is this here?*/
            Choice='a';
        }
        if (Choice=='S' && SplitterFlag==2){
            StopA=1;
            Choice='a';
        }
        if (Choice=='S' && SplitterFlag==3) {
            StopB=1;
            Choice='a';
        }
        if (StopA==1 && StopB==1) {
            Choice='S';
        }
    }


switch(Choice)
{
    case 'S': /* If you stay*/

        if (Points[12]+Points[13]==21){
            printf("\n\nYou have Blackjack.  You win!");
            Bet=ceil(Bet*1.5);
            goto Replay;
        }

        j=0;
        AceHandleD=0;
        while (DealerPoints <=16) {
            DealerPoints=DealerPoints+Points[j];  /*Dealer draws until he is at least at 17 points*/
            if (Points[j]==11) {
                AceHandleD=AceHandleD+1;
            }
            if (DealerPoints>21 && AceHandleD>0) {
                DealerPoints=DealerPoints-10;
                AceHandleD=AceHandleD-1;
            }
            j=j+1;
        }
        printf("\n\n\nDealer Hand:\n\n");
        for (i=0;i<j;i++) {
            if (DealerHand[i]=='T'){
                printf("10  ");
            }
            else {
                printf("%c  ",DealerHand[i]);  /*Dealer displays his hand*/
            }
        }

        if (SplitterFlag != 0) {
            if (StopA==1 && BetA==Bet*2) {
                printf("\n\nPlayer Hand A:\n\n");
                if (PlayerHand[0]=='T'){
                    printf("10  ");
                }
                else {
                    printf("%c  ",PlayerHand[0]);
                }
                for (i=0;i<=SplitterRoundA;i++){
                    if (PlayerHand[i+28]=='T'){
                        printf("10  ");
                    }
                    else {
                        printf("%c  ",PlayerHand[i+28]);
                    }
                }
                PlayerPointsA=PlayerPointsA+Points[41];
                if (PlayerPointsA>21){
                    StopA=2;
                }
            }
            if (StopB==1 && BetB==Bet*2) {
                printf("\n\nPlayer Hand B:\n\n");
                if (PlayerHand[1]=='T'){
                    printf("10  ");
                }
                else {
                    printf("%c  ",PlayerHand[1]);
                }
                for (i=0;i<=SplitterRoundB;i++){
                    if (PlayerHand[i+2]=='T'){
                        printf("10  ");
                    }
                    else {
                        printf("%c  ",PlayerHand[i+2]);
                    }
                }
                PlayerPointsB=PlayerPointsB+Points[15];
                if (PlayerPointsB>21) {
                    StopB=2;
                }
            }

            printf("\n\nDealer: %d Points.  Player:  Hand A: %d Points.  Hand B: %d Points.\n\n",DealerPoints,PlayerPointsA,PlayerPointsB);
            if (DealerPoints>21 && StopA != 2 && StopB != 2) {
                printf("Dealer Busts. Hand A wins!  Hand B wins!");
            }
            else if (DealerPoints<PlayerPointsA && DealerPoints<PlayerPointsB && StopA != 2 && StopB != 2){
                printf("Hand A wins!  Hand B wins!");
            }
            else if (DealerPoints==PlayerPointsA && DealerPoints<PlayerPointsB && StopB != 2) {
                printf("Hand A ties.  Hand B wins!");
                BetA=0;
            }
            else if ((DealerPoints>PlayerPointsA || StopA==2) && DealerPoints<PlayerPointsB && StopB != 2) {
                printf("Hand A loses...  Hand B wins!");
                BetA=BetA*-1;
            }
            else if (DealerPoints==PlayerPointsA && DealerPoints==PlayerPointsB) {
                printf("Hand A ties.  Hand B ties.");
                BetA=0;
                BetB=0;
            }
            else if ((DealerPoints>PlayerPointsA || StopA==2) && DealerPoints==PlayerPointsB) {
                printf("Hand A loses...  Hand B ties.");
                BetA=BetA*-1;
                BetB=0;
            }
            else if (DealerPoints<PlayerPointsA && DealerPoints==PlayerPointsB && StopA != 2) {
                printf("Hand A wins!  Hand B ties.");
                BetB=0;
            }
            else if (DealerPoints==PlayerPointsA && (DealerPoints>PlayerPointsB || StopB==2)) {
                printf("Hand A ties.  Hand B loses...");
                BetA=0;
                BetB=BetB*-1;
            }
            else if ((DealerPoints>PlayerPointsA || StopA==2) && (DealerPoints>PlayerPointsB || StopB==2)) {
                printf("Hand A loses...  Hand B loses...");
                BetA=BetA*-1;
                BetB=BetB*-1;
            }
            else {
                printf("Hand A wins!  Hand B loses...");
                BetB=BetB*-1;
            }
        }
        else {
            printf("\n\nDealer: %d Points.  Player: %d Points.\n\n",DealerPoints,PlayerPoints);
            if (DealerPoints>21) {
                printf("Dealer busts. You win!");
            }
            else if (DealerPoints>PlayerPoints) { /*Conditions for winning and losing are checked*/
                printf("You lose.");
                Bet=Bet*-1;
            }
            else if (DealerPoints==PlayerPoints) {
                printf("Tie.");
                Bet=0;
            }
            else /* (DealerPoints<PlayerPoints) */ {
                printf("You win!");
            }
        }
        goto Replay; /*exits program*/
        break;

    case 'H': /* If you hit*/
        printf("\n\n");
        Round=Round+1;

        if(StopA==2){
            SplitterFlag=3;
        }
        else if (StopB==2){
            SplitterFlag=2;
        }

        else if (((SplitterFlag==2 && StopB!=1) && Round !=1)) {
            SplitterFlag=3;
        }
        else if ((SplitterFlag==3 && StopA!=1)){
            SplitterFlag=2;
        }
        break;

    default:

        if(Choice=='a' && StopA==1) {
            printf("\nHand A stays.\n");
            SplitterFlag=3;
        }
        else if(Choice=='a' && StopB==1) {
            printf("\n\nHand B stays.\n");
            SplitterFlag=2;
        }
        else {
            printf("\nInvalid Choice\n\n");
        }
        break;
    }
}

Replay:

    if(SplitterFlag!=0) {
        Money=Money+BetA+BetB;
        StopA=0;
        StopB=0;
        SplitterFlag=0;
        SplitterRoundA=0;
        SplitterRoundB=0;
        PlayerPointsA=0;
        PlayerPointsB=0;
        BetA=0;
        BetB=0;
    }
    else {
        Money=Money+Bet;
    }
    DDflag=0;
    printf("\n\nYou have %d money.\n",Money);

    if(Money >0) {
        printf("\nDo you want to play again? [Y] [N]\n\n");
        Again=getchar();
        if(Again == '\n') {
            Again = getchar();
        }
    }
    else { /*If you have no money, you lose*/
        Again='N';
    }
    switch(Again)
    {
        case 'Y':
            system("cls");
            printf("Current money = %d\n\n",Money);
            Round=0;
            goto Game;

        case 'N':
            printf("\nThank you for playing.\n");
    }
    return 0;
}
