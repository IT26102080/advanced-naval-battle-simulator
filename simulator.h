#ifndef SIMULATOR_H
#define SIMULATOR_H

#define MAX_ESCORTS 100

typedef struct
{
    char type;
    int x;
    int y;
    float maxVelocity;
} BattleShip;

typedef struct
{
    int index;
    char type;

    int x;
    int y;

    float minAngle;
    float maxAngle;

    float minVelocity;
    float maxVelocity;

    float impactPower;

    int destroyed;

} EscortShip;


/* Function declarations */

int generateRandomCoordinate(int d);

char generateRandomEscortType(void);

float getAngleRange(char type);

float getImpactPower(char type);

void setupBattleShip(BattleShip *B, int d);

void setupEscortShips(
    EscortShip escorts[],
    int n,
    int d,
    float battleshipMaxVelocity
);

void displayBattlefield(
    BattleShip B,
    EscortShip escorts[],
    int n
);




float calculateDistance(int x1, int y1, int x2, int y2);

float calculateProjectileRange(float velocity, float angle);



int canBattleshipHit(BattleShip B, EscortShip E);

int canEscortHitBattleship(EscortShip E, BattleShip B);




void saveInitialConditions(
    BattleShip B,
    EscortShip escorts[],
    int n,
    int d
);

void saveFinalConditions(
    BattleShip B,
    EscortShip escorts[],
    int n,
    int battleshipDestroyed
);

int simulatePart1A(
    BattleShip *B,
    EscortShip escorts[],
    int n
);


float calculateTimeToHit(float distance, float velocity, float angle);

void generateBattleShipPosition(BattleShip *B, int d);

void simulatePart1B(
    BattleShip *B,
    EscortShip escorts[],
    int n,
    int d,
    int k
);

void simulatePart1B2(
    BattleShip *B,
    EscortShip escorts[],
    int n,
    int d,
    int k,
    int t,
    float thetaMin
);

int canBattleshipHitAfterJam(
    BattleShip B,
    EscortShip E,
    float thetaMin
);

void simulatePart1C(
    BattleShip *B,
    EscortShip escorts[],
    int n
);

void simulatePart1CPath(
    BattleShip *B,
    EscortShip escorts[],
    int n,
    int d,
    int k
);

#endif
