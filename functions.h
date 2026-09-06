 #ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Structure for Battleship
typedef struct {
    char type;
    int x, y;
    float maxVelocity;
    float maxAttackRange;
} BattleShip;

// Structure for Escort Ship
typedef struct {
        int index;
        char type;
        int x,y;
        float angleRange;
        float minAngle;
        float maxAngle; 
        float minVelocity;
        float maxVelocity;
        float impactPower;
        float distanceFromB;
        int canBeHitByB;
        float bestAngle;
        float maxAttackRange;
        int canHitB;
        float firingAngleFromB;
        float timeToHitFromB;
        
        int isAlive; 
        int hasFired; 

        float nextFireTime;
} EscortShip;
 int GenerateRandomCoordinate(int d);
    char GenerateRandomEscortType();
    float GetAngleRange(char type);
    float GetMinimumAngle();
    float GetMinimumVelocity(int maxVelocity);
    float GetMaximumVelocity(char type, int battleshipMaxVelocity);
    float GetImpactPower(char type);
    float GetBestAngle(float minAngle, float maxAngle);

        // Functions for calculating attack ranges and battle conditions
    float CalculateDistance(int x1, int y1, int x2, int y2);
    float CalculateBattleshipMaxRange(float maxVelocity);
    int CanBattleshipHit(float distance, float maxAttackRange);
    float CalculateEscortMaxRange(float maxVelocity, float bestAngle);
    int CanEscortHitBattleship(float distance, float maxAttackRange);
        // Functions for calculating shell firing angle and travel time
    float CalculateFiringAngle(float distance, float maxVelocity);
    float CalculateTimeToHit(float distance, float velocity, float angle);

    #endif