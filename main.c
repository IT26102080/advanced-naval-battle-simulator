#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simulator.h"

int main(void)
{
    int d;
    int n;
    int k;

    BattleShip battleship;

    EscortShip escorts[MAX_ESCORTS];

    srand(time(NULL));

    printf("=====================================\n");
    printf("     ADVANCED NAVAL BATTLE SIMULATOR\n");
    printf("=====================================\n");

    printf("\nEnter battlefield size D: ");
    scanf("%d", &d);

    printf("Enter number of escort ships: ");
    scanf("%d", &n);

    printf("Enter number of battleship path positions: ");
    scanf("%d", &k);

    if (n > MAX_ESCORTS)
    {
        printf("Maximum escort ships allowed: %d\n",
               MAX_ESCORTS);

        return 1;
    }

    setupBattleShip(&battleship, d);

    setupEscortShips(
        escorts,
        n,
        d,
        battleship.maxVelocity
    );

    displayBattlefield(
        battleship,
        escorts,
        n
    );


saveInitialConditions(
    battleship,
    escorts,
    n,
    d
);

simulatePart1A(
    &battleship,
    escorts,
    n
);

    return 0;
}
