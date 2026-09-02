#include <stdio.h>

// Structure for Battleship
typedef struct {
    char type;
    int x, y;
    float maxVelocity;
} BattleShip;

// Structure for Escort Ship
typedef struct {
    int index;
    char type;
    int x, y;
    float minAngle;
    float maxAngle;
    float minVelocity;
    float maxVelocity;
    float impactPower;
} EscortShip;

int main() {

    // Display program title
    printf(" ADVANCED NAVAL BATTLE SIMULATOR \n");

    int d;
    int n;

    // Create Battleship variable
    BattleShip B;

    // Create Escort Ship array
    EscortShip E[n];

    // Get battlefield size
    printf("Enter battlefield size: ");
    scanf("%d", &d);

    // Get number of escort ships
    printf("Enter the no of escort ships: ");
    scanf("%d", &n);

    // Get battleship type
    printf("Enter battleship types: ");
    scanf(" %c", &B.type);

    // Get X position
    printf("Enter battleship X position: ");
    scanf("%d", &B.x);

    // Get Y position
    printf("Enter battleship Y position: ");
    scanf("%d", &B.y);

    // Get maximum velocity
    printf("Enter battleship maximum shell velocity: ");
    scanf("%f", &B.maxVelocity);

    // Display battlefield details
    printf("battlefield size is %d x %d\n", d, d);
    printf("Number of escort ships: %d\n", n);

    // Display battleship details
    printf("\n--- Battleship Details ---\n");
    printf("Type: %c\n", B.type);
    printf("Position: (%d,%d)\n", B.x, B.y);
    printf("Maximum Shell Velocity: %.2f m/s\n", B.maxVelocity);

    return 0;
}
