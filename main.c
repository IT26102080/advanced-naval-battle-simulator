#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "parts.h"


void ShowStatistics(){
    FILE *file;
    char line[300];
    int choice;

    printf("\n=== SIMULATION STATISTICS ===\n");

    printf("1. Initial Conditions\n");

    printf("\n--- PART 1 ---\n");
    printf("2. Part 1-A\n");
    printf("3. Part 1-B Simulation 1\n");
    printf("4. Part 1-B Simulation 2\n");
    printf("5. Part 1-C Simulation A\n");
    printf("6. Part 1-C Simulation B1\n");
    printf("7. Part 1-C Simulation B2\n");
}
void RunAllSimulations(){
    int d, n;
    int k;

    int pathX[100];
    int pathY[100];
    
    FILE *file;
    BattleShip B;
    
    int initialBX;
    int initialBY;

    printf("\n=== SIMULATION SETUP ===\n");

    printf("Enter battlefield size: ");
    scanf("%d", &d);

    printf("Enter the no of escort ships: ");
    scanf("%d", &n);

    printf("Enter Battleship type (U/M/R/S): ");
    scanf(" %c", &B.type);

    printf("Enter battleship X position: ");
    scanf("%d", &B.x);

    printf("Enter battleship Y position: ");
    scanf("%d", &B.y);

    printf("Enter battleship maximum shell velocity: ");
    scanf("%f", &B.maxVelocity);

    B.maxAttackRange = CalculateBattleshipMaxRange(B.maxVelocity);

    printf("\n--- Battleship Details ---\n");
    printf("Type = %c\n", B.type);
    printf("Position = (%d, %d)\n", B.x, B.y);
    printf("Maximum Shell Velocity = %.2f m/s\n", B.maxVelocity);
    printf("Battleship Maximum Attack Range = %.2f\n", B.maxAttackRange);

    initialBX = B.x;
    initialBY = B.y;
    EscortShip E[n];

        printf("\n--- Escortship Details ---\n");

    for (int i = 0; i < n; i++){
        E[i].index = i + 1;
        E[i].isAlive = 1;

        E[i].x = GenerateRandomCoordinate(d);
        E[i].y = GenerateRandomCoordinate(d);

        E[i].distanceFromB = CalculateDistance(B.x, B.y, E[i].x, E[i].y);

        E[i].type = GenerateRandomEscortType();
        E[i].angleRange = GetAngleRange(E[i].type);
        E[i].minAngle = GetMinimumAngle();
        E[i].maxAngle = E[i].minAngle + E[i].angleRange;
        E[i].bestAngle = GetBestAngle(E[i].minAngle, E[i].maxAngle);

        E[i].maxVelocity = GetMaximumVelocity(E[i].type, B.maxVelocity);
        E[i].minVelocity = GetMinimumVelocity(E[i].maxVelocity);

        E[i].impactPower = GetImpactPower(E[i].type);
        E[i].maxAttackRange = CalculateEscortMaxRange(E[i].maxVelocity, E[i].bestAngle);

        E[i].canBeHitByB = CanBattleshipHit(E[i].distanceFromB, B.maxAttackRange);
        E[i].canHitB = CanEscortHitBattleship(E[i].distanceFromB, E[i].maxAttackRange);


        if (E[i].canBeHitByB == 1){
            E[i].firingAngleFromB = CalculateFiringAngle(E[i].distanceFromB, B.maxVelocity);
            E[i].timeToHitFromB = CalculateTimeToHit(E[i].distanceFromB,B.maxVelocity, E[i].firingAngleFromB);
        }
        else{
            E[i].firingAngleFromB = 0;
            E[i].timeToHitFromB = 0;
        }
        printf("\nEscort Ship E%d\n", E[i].index);
        printf("Position = (%d, %d)\n", E[i].x, E[i].y);
        printf("Type = E%c\n", E[i].type);
        printf("Angle Range = %.1f\n", E[i].angleRange);
        printf("Min Angle = %.1f\n", E[i].minAngle);
        printf("Max Angle = %.1f\n", E[i].maxAngle);
        printf("Max Velocity = %.1f\n", E[i].maxVelocity);
        printf("Min Velocity = %.1f\n", E[i].minVelocity);
        printf("Impact Power = %.2f\n", E[i].impactPower);
        printf("Distance From B = %.2f\n", E[i].distanceFromB);
        printf("Best Angle = %.1f\n", E[i].bestAngle);
        printf("E Max Attack Range = %.2f\n", E[i].maxAttackRange);

        if (E[i].canBeHitByB == 1){
            printf("B Can Hit = YES\n");
        }
        else{
            printf("B Can Hit = NO\n");
        }

        if (E[i].canHitB == 1){
            printf("E Can Hit B = YES\n");
        }
        else{
            printf("E Can Hit B = NO\n");
        }
    }


    file = fopen("initial_conditions.txt", "w");

    if (file == NULL){
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "=== INITIAL BATTLEFIELD CONDITIONS ===\n\n");

    fprintf(file, "Battleship\n");
    fprintf(file, "Type = %c\n", B.type);
    fprintf(file, "Position = (%d, %d)\n", B.x, B.y);
    fprintf(file, "Max Velocity = %.2f\n", B.maxVelocity);
    fprintf(file, "Max Attack Range = %.2f\n\n", B.maxAttackRange);

    fprintf(file, "Escort Ships\n\n");

    for (int i = 0; i < n; i++){
        fprintf(file, "Escort Ship E%d\n", E[i].index);
        fprintf(file, "Position = (%d, %d)\n", E[i].x, E[i].y);
        fprintf(file, "Type = E%c\n", E[i].type);
        fprintf(file, "Angle Range = %.1f\n", E[i].angleRange);
        fprintf(file, "Min Angle = %.1f\n", E[i].minAngle);
        fprintf(file, "Max Angle = %.1f\n", E[i].maxAngle);
        fprintf(file, "Min Velocity = %.1f\n", E[i].minVelocity);
        fprintf(file, "Max Velocity = %.1f\n", E[i].maxVelocity);
        fprintf(file, "Impact Power = %.2f\n\n", E[i].impactPower);
    }

    fclose(file);

        RunPart1A(B, E, n);
            
        printf("\nEnter number of path points: ");
        scanf("%d", &k);
        
        if (k < 1 || k > 100){
            printf("Number of path points must be between 1 and 100.\n");
            return;
    }
        RunPart1BSimulation1(B, E, n, k, pathX, pathY, d);


}

int main() {
float CalculateBattleshipMaxRange(float maxVelocity);
    // Display program title
    int d;
    int n, choice;

 while (1) {   // Keep showing the menu until the user exits

    printf("\n");   
    printf("\n");  

    // Display the main title
    printf(" A D V A N C E D   N A V A L   B A T T L E\n");
    printf("          S I M U L A T O R\n");

    // Display menu options
    printf("1. Start Simulation\n");
    printf("2. View Instructions\n");
    printf("3. Simulation Statistics\n");
    printf("4. Set Random Seed\n");
    printf("5. Exit\n");

    // Ask the user to select an option
    printf("Enter choice: ");
    scanf("%d", &choice);   // Read the choice
     
    if (choice == 1)
    {
            RunAllSimulations();
    }
    else if (choice == 3){
           ShowStatistics();
    }
    else if (choice == 5)
    {
        printf("Exiting...\n");
        break;
    }
}
   
    // Create Battleship variable
    BattleShip B;

    // Create Escort Ship array
    EscortShip E[n];

    B.maxAttackRange = CalculateBattleshipMaxRange(B.maxVelocity);

    // Display battlefield details
    printf("battlefield size is %d x %d\n", d, d);
    printf("Number of escort ships: %d\n", n);

    // Display battleship details
    printf("\n--- Battleship Details ---\n");
    printf("Type: %c\n", B.type);
    printf("Position: (%d,%d)\n", B.x, B.y);
    printf("Maximum Shell Velocity: %.2f m/s\n", B.maxVelocity);
    printf("Battleship Maximum Attack Range = %.2f\n", B.maxAttackRange);


    printf("\n--- Escortship Details ---\n");

return 0;
}