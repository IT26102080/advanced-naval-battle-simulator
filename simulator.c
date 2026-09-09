#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "simulator.h"


int generateRandomCoordinate(int d)
{
    return rand() % (d + 1);
}


char generateRandomEscortType(void)
{
    int randomType = rand() % 5;

    if (randomType == 0)
        return 'A';

    else if (randomType == 1)
        return 'B';

    else if (randomType == 2)
        return 'C';

    else if (randomType == 3)
        return 'D';

    else
        return 'E';
}


float getAngleRange(char type)
{
    if (type == 'A')
        return 20.0;

    else if (type == 'B')
        return 30.0;

    else if (type == 'C')
        return 25.0;

    else if (type == 'D')
        return 50.0;

    else
        return 70.0;
}


float getImpactPower(char type)
{
    if (type == 'A')
        return 0.08;

    else if (type == 'B')
        return 0.06;

    else if (type == 'C')
        return 0.07;

    else if (type == 'D')
        return 0.05;

    else
        return 0.04;
}


void setupBattleShip(BattleShip *B, int d)
{
    printf("\nEnter battleship type (U/M/R/S): ");
    scanf(" %c", &B->type);

    printf("Enter battleship X position (0-%d): ", d);
    scanf("%d", &B->x);

    printf("Enter battleship Y position (0-%d): ", d);
    scanf("%d", &B->y);

    printf("Enter battleship maximum shell velocity: ");
    scanf("%f", &B->maxVelocity);
}


void setupEscortShips(
    EscortShip escorts[],
    int n,
    int d,
    float battleshipMaxVelocity
)
{
    for (int i = 0; i < n; i++)
    {
        escorts[i].index = i + 1;

        escorts[i].type = generateRandomEscortType();

        escorts[i].x = generateRandomCoordinate(d);
        escorts[i].y = generateRandomCoordinate(d);


        escorts[i].minAngle =
            (float)(rand() % 10 + 1);

        escorts[i].maxAngle =
            escorts[i].minAngle +
            getAngleRange(escorts[i].type);

if (escorts[i].type == 'A')
{
    escorts[i].maxVelocity =
        1.2 * battleshipMaxVelocity;
}
else
{
    escorts[i].maxVelocity =
        (float)(rand() % (int)battleshipMaxVelocity + 1);
}

/* Minimum velocity must be less than or equal to maximum velocity */
escorts[i].minVelocity =
    (float)(rand() % (int)escorts[i].maxVelocity + 1);

        escorts[i].impactPower =
            getImpactPower(escorts[i].type);


        escorts[i].destroyed = 0;
    }
}


void displayBattlefield(
    BattleShip B,
    EscortShip escorts[],
    int n
)
{
    printf("\n========== BATTLEFIELD ==========\n");

    printf("\nBattleship\n");
    printf("Type: %c\n", B.type);
    printf("Position: (%d, %d)\n", B.x, B.y);
    printf("Maximum Velocity: %.2f\n", B.maxVelocity);

    printf("\nEscort Ships\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nEscort Ship %d\n", escorts[i].index);

        printf("Type: E%c\n", escorts[i].type);

        printf(
            "Position: (%d, %d)\n",
            escorts[i].x,
            escorts[i].y
        );

        printf(
            "Angle Range: %.2f - %.2f\n",
            escorts[i].minAngle,
            escorts[i].maxAngle
        );

        printf(
            "Velocity Range: %.2f - %.2f\n",
            escorts[i].minVelocity,
            escorts[i].maxVelocity
        );

        printf(
            "Impact Power: %.2f\n",
            escorts[i].impactPower
        );
    }
}



float calculateDistance(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    return sqrt(dx * dx + dy * dy);
}


float calculateProjectileRange(float velocity, float angle)
{
    const float PI = 3.14159265;
    const float g = 9.8;

    float radians = angle * PI / 180.0;

    return (velocity * velocity * sin(2 * radians)) / g;
}







int canBattleshipHit(BattleShip B, EscortShip E)
{
    float distance = calculateDistance(
        B.x,
        B.y,
        E.x,
        E.y
    );

    /* Battleship can fire between 0 and 90 degrees.
       Maximum projectile range occurs at 45 degrees. */
    float maxRange = calculateProjectileRange(
        B.maxVelocity,
        45.0
    );

    if (distance <= maxRange)
    {
        return 1;
    }

    return 0;
}




int canEscortHitBattleship(EscortShip E, BattleShip B)
{
    float distance = calculateDistance(
        E.x,
        E.y,
        B.x,
        B.y
    );

    float minRange = calculateProjectileRange(
        E.minVelocity,
        E.minAngle
    );

    float maxRange;

    /*
       Maximum projectile range occurs at 45 degrees.
       If 45 is inside the escort ship's angle range,
       use 45 degrees for maximum range.
    */
    if (E.minAngle <= 45.0 && E.maxAngle >= 45.0)
    {
        maxRange = calculateProjectileRange(
            E.maxVelocity,
            45.0
        );
    }
    else
    {
        float range1 = calculateProjectileRange(
            E.maxVelocity,
            E.minAngle
        );

        float range2 = calculateProjectileRange(
            E.maxVelocity,
            E.maxAngle
        );

        if (range1 > range2)
        {
            maxRange = range1;
        }
        else
        {
            maxRange = range2;
        }
    }

    if (distance >= minRange && distance <= maxRange)
    {
        return 1;
    }

    return 0;
}




void saveInitialConditions(
    BattleShip B,
    EscortShip escorts[],
    int n,
    int d
)
{
    FILE *file = fopen("initial_conditions.txt", "w");

    if (file == NULL)
    {
        printf("Error creating initial conditions file.\n");
        return;
    }

    fprintf(file, "ADVANCED NAVAL BATTLE SIMULATOR\n");
    fprintf(file, "================================\n");

    fprintf(file, "\nBattlefield Size: %d x %d\n", d, d);

    fprintf(file, "\nBATTLESHIP\n");
    fprintf(file, "Type: %c\n", B.type);
    fprintf(file, "Position: (%d, %d)\n", B.x, B.y);
    fprintf(file, "Maximum Velocity: %.2f\n", B.maxVelocity);

    fprintf(file, "\nESCORT SHIPS\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "\nEscort Ship %d\n", escorts[i].index);
        fprintf(file, "Type: E%c\n", escorts[i].type);

        fprintf(
            file,
            "Position: (%d, %d)\n",
            escorts[i].x,
            escorts[i].y
        );

        fprintf(
            file,
            "Angle Range: %.2f - %.2f\n",
            escorts[i].minAngle,
            escorts[i].maxAngle
        );

        fprintf(
            file,
            "Velocity Range: %.2f - %.2f\n",
            escorts[i].minVelocity,
            escorts[i].maxVelocity
        );

        fprintf(
            file,
            "Impact Power: %.2f\n",
            escorts[i].impactPower
        );
    }

    fclose(file);

    printf("\nInitial conditions saved to initial_conditions.txt\n");
}




void saveFinalConditions(
    BattleShip B,
    EscortShip escorts[],
    int n,
    int battleshipDestroyed
)
{
    FILE *file = fopen("final_conditions.txt", "w");

    if (file == NULL)
    {
        printf("Error creating final conditions file.\n");
        return;
    }

    fprintf(file, "FINAL BATTLEFIELD CONDITIONS\n");
    fprintf(file, "============================\n");

    fprintf(file, "\nBattleship Type: %c\n", B.type);
    fprintf(file, "Position: (%d, %d)\n", B.x, B.y);

    if (battleshipDestroyed)
    {
        fprintf(file, "Status: DESTROYED\n");
    }
    else
    {
        fprintf(file, "Status: ALIVE\n");
    }

    fprintf(file, "\nESCORT SHIPS\n");

    for (int i = 0; i < n; i++)
    {
        fprintf(
            file,
            "Escort %d (E%c): ",
            escorts[i].index,
            escorts[i].type
        );

        if (escorts[i].destroyed)
        {
            fprintf(file, "DESTROYED\n");
        }
        else
        {
            fprintf(file, "ALIVE\n");
        }
    }

    fclose(file);

    printf("Final conditions saved to final_conditions.txt\n");
}


int simulatePart1A(
    BattleShip *B,
    EscortShip escorts[],
    int n
)
{
    int battleshipDestroyed = 0;
    int destroyedBy = -1;
    int escortHits = 0;
    float battleTime = 0.0;

    FILE *hitFile = fopen("hit_details.txt", "w");

    if (hitFile == NULL)
    {
        printf("Error creating hit details file.\n");
        return battleshipDestroyed;;
    }

    printf("\n=====================================\n");
    printf("          PART 1-A SIMULATION\n");
    printf("=====================================\n");

    for (int i = 0; i < n; i++)
    {
if (escorts[i].destroyed)
{
    continue;
}
        if (canEscortHitBattleship(escorts[i], *B))
        {
            battleshipDestroyed = 1;
            destroyedBy = escorts[i].index;

            printf(
                "\nBattleship was hit by Escort Ship %d.\n",
                destroyedBy
            );

            printf("BATTLESHIP DESTROYED!\n");

            break;
        }
    }

    if (!battleshipDestroyed)
    {
        printf("\nBattleship survived the escort attacks.\n");
        printf("Battleship is attacking escort ships...\n");

        for (int i = 0; i < n; i++)
        {
    if (escorts[i].destroyed)
    {
        continue;
    }

            if (canBattleshipHit(*B, escorts[i]))
            {
                escorts[i].destroyed = 1;
                escortHits++;

float distance = calculateDistance(
    B->x,
    B->y,
    escorts[i].x,
    escorts[i].y
);

float hitTime = calculateTimeToHit(
    distance,
    B->maxVelocity,
    45.0
);

if (hitTime > battleTime)
{
    battleTime = hitTime;
}



                printf(
                    "Escort Ship %d DESTROYED\n",
                    escorts[i].index
                );

                fprintf(
                    hitFile,
                    "Escort Index: %d\n",
                    escorts[i].index
                );

                fprintf(
                    hitFile,
                    "Type: E%c\n",
                    escorts[i].type
                );

                fprintf(
                    hitFile,
                    "Time to Hit: %.2f seconds\n\n",
                    hitTime
                );
            }
        }

        printf(
            "\nTotal Escort Ships Destroyed: %d\n",
            escortHits
        );

        printf("Battle Time: %.2f seconds\n", battleTime);
    }
    else
    {
        fprintf(
            hitFile,
            "Battleship destroyed by Escort Ship %d\n",
            destroyedBy
        );
    }

    fclose(hitFile);

    saveFinalConditions(
        *B,
        escorts,
        n,
        battleshipDestroyed
    );

    printf("\nSimulation results saved successfully.\n");
return battleshipDestroyed;
}






float calculateTimeToHit(float distance, float velocity, float angle)
{
    const float PI = 3.14159265;

    float radians = angle * PI / 180.0;

    float horizontalVelocity = velocity * cos(radians);

    if (horizontalVelocity <= 0)
    {
        return 0.0;
    }

    return distance / horizontalVelocity;
}



void generateBattleShipPosition(BattleShip *B, int d)
{
    B->x = generateRandomCoordinate(d);
    B->y = generateRandomCoordinate(d);
}




void simulatePart1B(
    BattleShip *B,
    EscortShip escorts[],
    int n,
    int d,
    int k
)
{


FILE *part1BFile = fopen("part1b_simulation1.txt", "w");

if (part1BFile == NULL)
{
    printf("Error opening Part 1-B output file.\n");
    return;
}


    printf("\n===== PART 1-B SIMULATION 1 =====\n");

    for (int i = 0; i < k; i++)
{
        printf("\n--- Position %d ---\n", i + 1);

        generateBattleShipPosition(B, d);

        printf("Battleship Position: (%d, %d)\n",
               B->x,
               B->y);

fprintf(part1BFile,
        "Position %d - Battleship Position: (%d, %d)\n",
        i + 1, B->x, B->y);

if (simulatePart1A(B, escorts, n))
{
    fprintf(part1BFile,
            "Battleship destroyed at Position %d\n",
            i + 1);

    break;
}

int destroyedCount = 0;

for (int j = 0; j < n; j++)
{
    if (escorts[j].destroyed)
    {
        destroyedCount++;
    }
}

fprintf(part1BFile,
        "Total Escort Ships Destroyed: %d\n\n",
        destroyedCount);    


}
fclose(part1BFile);
}



void simulatePart1B2(
    BattleShip *B,
    EscortShip escorts[],
    int n,
    int d,
    int k,
    int t,
    float thetaMin
)
{
    printf("\n===== PART 1-B SIMULATION 2 =====\n");

FILE *part1B2File = fopen("part1b_simulation2.txt", "w");

if (part1B2File == NULL)
{
    printf("Error opening Part 1-B Simulation 2 output file.\n");
    return;

fclose(part1B2File);

printf("\nPart 1-B Simulation 2 results saved.\n");
}



    printf("Gun will jam after iteration %d\n", t);
    printf("Minimum angle after jam: %.2f degrees\n", thetaMin);

for (int i = 0; i < k; i++)
{
    printf("\n--- Simulation 2 Position %d ---\n", i + 1);

    generateBattleShipPosition(B, d);

fprintf(part1B2File,
        "Position %d - Battleship Position: (%d, %d)\n",
        i + 1, B->x, B->y);

if ((i + 1) <= t)
{
    fprintf(part1B2File,
            "Gun Status: NORMAL\n");
}
else
{
    fprintf(part1B2File,
            "Gun Status: JAMMED (Angle %.2f - 90.00)\n",
            thetaMin);
}

    printf("Battleship Position: (%d, %d)\n",
           B->x, B->y);

if ((i + 1) <= t)
{
    printf("Battleship gun status: NORMAL\n");

    if (simulatePart1A(B, escorts, n))
    {
        break;
    }
}
else
{
    printf("Battleship gun status: JAMMED\n");
    printf("Allowed vertical angle range: %.2f - 90.00 degrees\n",
           thetaMin);

    int battleshipDestroyed = 0;

    for (int j = 0; j < n; j++)
    {
        if (escorts[j].destroyed)
        {
            continue;
        }

        if (canEscortHitBattleship(escorts[j], *B))
        {
            printf("Battleship destroyed by Escort Ship %d\n",
                   escorts[j].index);

            battleshipDestroyed = 1;
            break;
        }
    }

    if (battleshipDestroyed)
    {
        break;
    }

    for (int j = 0; j < n; j++)
    {
        if (escorts[j].destroyed)
        {
            continue;
        }

        if (canBattleshipHitAfterJam(
                *B,
                escorts[j],
                thetaMin))
        {
            escorts[j].destroyed = 1;

            printf("Escort Ship %d DESTROYED\n",
                   escorts[j].index);
        }
    }
}
}


}


int canBattleshipHitAfterJam(
    BattleShip B,
    EscortShip E,
    float thetaMin
)
{
    float dx = E.x - B.x;
    float dy = E.y - B.y;

    float distance = sqrt(dx * dx + dy * dy);

    for (float angle = thetaMin; angle <= 90.0; angle += 1.0)
    {
        float range = calculateProjectileRange(
            B.maxVelocity,
            angle
        );

        if (distance <= range)
        {
            return 1;
        }
    }

    return 0;
}


void simulatePart1C(
    BattleShip *B,
    EscortShip escorts[],
    int n
)
{
    printf("\n===== PART 1-C SIMULATION =====\n");

    FILE *file = fopen("part1c_results.txt", "w");

    if (file == NULL)
    {
        printf("Error opening Part 1-C output file.\n");
        return;
    }

    float cumulativeImpact = 0.0;
    int battleshipDestroyed = 0;

    /* Escort ships attack Battleship */
    for (int i = 0; i < n; i++)
    {
        if (escorts[i].destroyed)
        {
            continue;
        }

        if (canEscortHitBattleship(escorts[i], *B))
        {
            cumulativeImpact += escorts[i].impactPower;

            printf("Escort Ship %d hit Battleship - Impact: %.2f\n",
                   escorts[i].index,
                   escorts[i].impactPower);

            fprintf(file,
                    "Escort Ship %d hit Battleship - Impact: %.2f\n",
                    escorts[i].index,
                    escorts[i].impactPower);

            if (cumulativeImpact >= 1.0)
            {
                battleshipDestroyed = 1;
                break;
            }
        }
    }

    if (battleshipDestroyed)
    {
        printf("BATTLESHIP DESTROYED!\n");
        fprintf(file, "Battleship Destroyed: YES\n");
    }
    else
    {
        printf("Battleship survived.\n");
        printf("Cumulative Impact on Battleship: %.2f\n",
               cumulativeImpact);

        fprintf(file, "Battleship Destroyed: NO\n");
        fprintf(file,
                "Cumulative Impact on Battleship: %.2f\n",
                cumulativeImpact);

        /* Battleship attacks remaining escort ships */
        for (int i = 0; i < n; i++)
        {
            if (escorts[i].destroyed)
            {
                continue;
            }

            if (canBattleshipHit(*B, escorts[i]))
            {
                escorts[i].destroyed = 1;

                printf("Escort Ship %d DESTROYED\n",
                       escorts[i].index);

                fprintf(file,
                        "Escort Ship %d DESTROYED\n",
                        escorts[i].index);
            }
        }
    }

    fclose(file);

    printf("Part 1-C results saved to part1c_results.txt\n");
}

void simulatePart1CPath(
    BattleShip *B,
    EscortShip escorts[],
    int n,
    int d,
    int k
)
{
    printf("\n===== PART 1-C PATH SIMULATION =====\n");

    FILE *file = fopen("part1c_path_results.txt", "w");

    if (file == NULL)
    {
        printf("Error opening Part 1-C path output file.\n");
        return;
    }

    float cumulativeImpact = 0.0;
    int fired[n];

    /* Initially no escort ship has fired */
    for (int i = 0; i < n; i++)
    {
        fired[i] = 0;
    }

    for (int p = 0; p < k; p++)
    {
        printf("\n--- Part 1-C Position %d ---\n", p + 1);

        generateBattleShipPosition(B, d);

        printf("Battleship Position: (%d, %d)\n",
               B->x, B->y);

        fprintf(file,
                "\nPosition %d - Battleship Position: (%d, %d)\n",
                p + 1, B->x, B->y);

        /* Escort ships attack */
        for (int i = 0; i < n; i++)
        {
            if (escorts[i].destroyed || fired[i])
            {
                continue;
            }

            if (canEscortHitBattleship(escorts[i], *B))
            {
                fired[i] = 1;

                cumulativeImpact += escorts[i].impactPower;

                printf("Escort Ship %d hit Battleship - Impact: %.2f\n",
                       escorts[i].index,
                       escorts[i].impactPower);

                fprintf(file,
                        "Escort Ship %d hit Battleship - Impact: %.2f\n",
                        escorts[i].index,
                        escorts[i].impactPower);
            }
        }

        printf("Cumulative Impact: %.2f\n",
               cumulativeImpact);

        fprintf(file,
                "Cumulative Impact: %.2f\n",
                cumulativeImpact);

        /* Battleship destroyed */
        if (cumulativeImpact >= 1.0)
        {
            printf("BATTLESHIP DESTROYED at Position %d!\n",
                   p + 1);

            fprintf(file,
                    "Battleship Destroyed: YES\n");

            break;
        }

        /* Battleship attacks escort ships */
        for (int i = 0; i < n; i++)
        {
            if (escorts[i].destroyed)
            {
                continue;
            }

            if (canBattleshipHit(*B, escorts[i]))
            {
                escorts[i].destroyed = 1;

                printf("Escort Ship %d DESTROYED\n",
                       escorts[i].index);

                fprintf(file,
                        "Escort Ship %d DESTROYED\n",
                        escorts[i].index);
            }
        }

        fprintf(file,
                "Battleship Destroyed: NO\n");
    }

    if (cumulativeImpact < 1.0)
    {
        printf("\nBattleship survived Part 1-C path simulation.\n");
        printf("Final Cumulative Impact: %.2f\n",
               cumulativeImpact);

        fprintf(file,
                "\nFinal Cumulative Impact: %.2f\n",
                cumulativeImpact);
    }

    fclose(file);

    printf("Part 1-C path results saved to part1c_path_results.txt\n");
}
