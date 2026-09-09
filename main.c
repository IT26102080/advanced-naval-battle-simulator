#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "simulator.h"

int main(void)
{
    int d;
    int n;
    int k;
    int t;
    float thetaMin;
    float firingDelay;

    BattleShip battleship;

    EscortShip escorts[MAX_ESCORTS];
    EscortShip escortsPart1C[MAX_ESCORTS];
    EscortShip escortsSimulation2[MAX_ESCORTS];
    EscortShip escortsPart2A[MAX_ESCORTS];
    EscortShip escortsInitial[MAX_ESCORTS];
    EscortShip escortsPart2AC[MAX_ESCORTS];

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

printf("Enter iteration when battleship gun gets jammed: ");
scanf("%d", &t);

printf("Enter minimum vertical angle after gun jam: ");
scanf("%f", &thetaMin);

printf("Enter Battleship gun firing delay (seconds): ");
scanf("%f", &firingDelay);

if (t <= 0 || t >= k)
{
    printf("Invalid jam iteration. t must be between 1 and k-1.\n");
    return 1;
}

if (thetaMin <= 0 || thetaMin >= 30)
{
    printf("Invalid minimum angle. Angle must be between 0 and 30 degrees.\n");
    return 1;
}


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

/* Keep original escort conditions */
for (int i = 0; i < n; i++)
{
    escortsInitial[i] = escorts[i];
}

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

for (int i = 0; i < n; i++)
{
    escortsSimulation2[i] = escorts[i];
}

simulatePart1B(
    &battleship,
    escorts,
    n,
    d,
    k
);

simulatePart1B2(
    &battleship,
    escortsSimulation2,
    n,
    d,
    k,
    t,
    thetaMin
);

for (int i = 0; i < n; i++)
{
    escortsPart1C[i] = escortsSimulation2[i];
}

simulatePart1C(
    &battleship,
    escortsPart1C,
    n
);

for (int i = 0; i < n; i++)
{
    escortsPart1C[i] = escortsSimulation2[i];
}

simulatePart1CPath(
    &battleship,
    escortsPart1C,
    n,
    d,
    k
);

/* Fresh copy for Part 2-A */
for (int i = 0; i < n; i++)
{
    escortsPart2A[i] = escortsInitial[i];
}

/* Part 2-A single position simulation */
simulatePart2A(
    &battleship,
    escortsPart2A,
    n,
    firingDelay
);

/* Reset escorts before Part 2-A path simulation */
for (int i = 0; i < n; i++)
{
    escortsPart2A[i] = escortsInitial[i];
}

/* Part 2-A path simulation */
simulatePart2APath(
    &battleship,
    escortsPart2A,
    n,
    d,
    k,
    firingDelay
);

/* Fresh escort copy for Part 2-A / Part 1-C */
for (int i = 0; i < n; i++)
{
    escortsPart2AC[i] = escortsInitial[i];
}

simulatePart2AC(
    &battleship,
    escortsPart2AC,
    n,
    firingDelay
);

    return 0;
}
