#include <stdlib.h>
#include <math.h>

// Generate a random coordinate from 0 to d
int GenerateRandomCoordinate(int d)
{
    return rand() % (d + 1);
}

// Generate a random escort ship type
char GenerateRandomEscortType()
{
    int randomtype = rand() % 5;  // Generate a number from 0 to 4

    if (randomtype == 0) {
        return 'A';  // Return type A
    }
    else if (randomtype == 1) {
        return 'B';  // Return type B
    }
    else if (randomtype == 2) {
        return 'C';  // Return type C
    }
    else if (randomtype == 3) {
        return 'D';  // Return type D
    }
    else {
        return 'E';  // Return type E
    }
}

// Get the angle range for the escort type
float GetAngleRange(char type)
{
    if (type == 'A') {
        return 20.0;  // Angle range for type A
    }
    else if (type == 'B') {
        return 30.0;  // Angle range for type B
    }
    else if (type == 'C') {
        return 25.0;  // Angle range for type C
    }
    else if (type == 'D') {
        return 50.0;  // Angle range for type D
    }
    else {
        return 70.0;  // Angle range for type E
    }
}

// Generate a random minimum angle
float GetMinimumAngle()
{
    return rand() % 46;
}

// Generate a random minimum velocity
float GetMinimumVelocity(int maxVelocity)
{
    return rand() % maxVelocity;
}

// Get the maximum velocity based on the escort type
float GetMaximumVelocity(char type, int battleshipMaxVelocity)
{
    if (type == 'A') {
        return 1.2 * battleshipMaxVelocity;  // Type A gets 120% velocity
    }
    else {
        return rand() % battleshipMaxVelocity;  // Generate random velocity
    }
}

// Get the impact power for each escort type
float GetImpactPower(char type)
{
    if (type == 'A') {
        return 0.08;  // Impact power of type A
    }
    else if (type == 'B') {
        return 0.06;  // Impact power of type B
    }
    else if (type == 'C') {
        return 0.07;  // Impact power of type C
    }
    else if (type == 'D') {
        return 0.05;  // Impact power of type D
    }
    else {
        return 0.04;  // Impact power of type E
    }
}

// Calculate the distance between two points
float CalculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) +
                (y2 - y1) * (y2 - y1));
}

// Calculate the maximum range of the battleship
float CalculateBattleshipMaxRange(float maxVelocity)
{
    float g = 9.81;  // Gravity

    return (maxVelocity * maxVelocity) / g;
}

// Check whether the battleship can hit the target
int CanBattleshipHit(float distance, float maxAttackRange)
{
    if (distance <= maxAttackRange) {
        return 1;  // Target is within range
    }
    else {
        return 0;  // Target is out of range
    }
}

// Find the best firing angle
float GetBestAngle(float minAngle, float maxAngle)
{
    if (minAngle <= 45.0 && maxAngle >= 45.0) {
        return 45.0;  // Use 45 degrees if possible
    }
    else if (maxAngle < 45.0) {
        return maxAngle;  // Use maximum angle
    }
    else {
        return minAngle;  // Use minimum angle
    }
}

// Calculate the maximum attack range of an escort ship
float CalculateEscortMaxRange(float maxVelocity, float bestAngle)
{
    float g = 9.81;  // Gravity

    // Convert angle from degrees to radians
    float angleInRadians = bestAngle * 3.14159 / 180.0;

    return (maxVelocity * maxVelocity *
            sin(2 * angleInRadians)) / g;
}

// Check whether the escort ship can hit the battleship
int CanEscortHitBattleship(float distance, float maxAttackRange)
{
    if (distance <= maxAttackRange) {
        return 1;  // Battleship is within range
    }
    else {
        return 0;  // Battleship is out of range
    }
}

// Calculate the firing angle needed to hit the target
float CalculateFiringAngle(float distance, float maxVelocity)
{
    float g = 9.81;  // Gravity
    float value;
    float angleRadians;
    float angleDegrees;

    // Calculate the value used in the angle formula
    value = (distance * g) / (maxVelocity * maxVelocity);

    // Calculate angle in radians
    angleRadians = 0.5 * asin(value);

    // Convert radians to degrees
    angleDegrees = angleRadians * 180.0 / 3.14159;

    return angleDegrees;
}

// Calculate the time needed for the projectile to hit the target
float CalculateTimeToHit(float distance, float velocity, float angle)
{
    float angleRadians;

    // Convert angle from degrees to radians
    angleRadians = angle * 3.14159 / 180.0;

    // Calculate and return the time
    return distance / (velocity * cos(angleRadians));
}