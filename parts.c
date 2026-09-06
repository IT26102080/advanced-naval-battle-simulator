#include <stdio.h>
#include "parts.h"

void RunPart1A(BattleShip B, EscortShip E[], int n)
{
    printf("\n=== PART 1-A ===\n");

    FILE *file;

    int battleshipSunk = 0;
    int sinkingEscortIndex = -1;
    int hitEscortCount = 0;
    float totalBattleTime = 0;

    //check weather escort ship can hit battleship sunk
     for (int i = 0; i < n; i++){  
          if (E[i].canHitB == 1){
                battleshipSunk = 1;
                sinkingEscortIndex = E[i].index;
                break;
            }
        }
            if (battleshipSunk == 1){
         printf("\nBattleship SANK!\n");
         printf("Battleship was sunk by Escort Ship E%d\n", sinkingEscortIndex);
   }
  else{
    printf("\nBattleship SURVIVED!\n");

    for (int i = 0; i < n; i++) //count the no of escort ships ditroyed
    {
        if (E[i].canBeHitByB == 1)
        {
            hitEscortCount++;
        if (E[i].timeToHitFromB > totalBattleTime){
                totalBattleTime = E[i].timeToHitFromB;
        }
        }
    }
    printf("Number of Escort Ships hit by B = %d\n", hitEscortCount);
    printf("Total Battle Time = %.2f seconds\n", totalBattleTime);
   }

   file = fopen("final_conditions.txt", "w"); // Display the final+_+ battle result to text file
    if (file == NULL){
        printf("Error opening final conditions file!\n");
        return ;
    }

    fprintf(file, "=== FINAL BATTLE CONDITIONS ===\n\n");  

        if (battleshipSunk == 1){
            fprintf(file, "Battleship SANK!\n");
            fprintf(file, "Battleship was sunk by Escort Ship E%d\n",sinkingEscortIndex);
        }
        else{
            fprintf(file, "Battleship SURVIVED!\n");
            fprintf(file, "Number of Escort Ships hit by B = %d\n",hitEscortCount);
            fprintf(file, "Total Battle Time = %.2f seconds\n",totalBattleTime);
            fprintf(file, "\nHit Escort Ship Details: \n");
            for (int i = 0; i < n; i++){
                if (E[i].canBeHitByB == 1){
                        fprintf(file, "Escort Ship E%d\n", E[i].index);
                        fprintf(file, "Time to Hit = %.2f seconds\n",E[i].timeToHitFromB);
                    }
                else{
                    fprintf(file, "  None !\n");
                }
            }
        }   
    fprintf(file, "\n=== FINAL ESCORT SHIP STATUS ===\n");
            for (int i = 0; i < n; i++){               
                fprintf(file, "Escort Ship E%d: ", E[i].index);
                if (E[i].canBeHitByB == 1){
                        fprintf(file, "DESTROYED\n");
                }
                else{
                        fprintf(file, "NOT DESTROYED\n");
                }   
            }
fclose(file);
}

    FILE *file;
    void RunPart1BSimulation1(BattleShip B, EscortShip E[], int n, int k, int pathX[], int pathY[], int d){
        printf("\n=== PART 1-B SIMULATION 1 ===\n");


    int battleshipSunk = 0;
    int sinkingEscortIndex = -1;
    int pointHitCount = 0;
    float pointBattleTime = 0;
    file = fopen("part1b_simulation1.txt", "w"); //open part 1b file

    if (file == NULL){ //check wether errors comming or not
        printf("Error opening Part1b file!\n");
        return ;
    }
    fprintf(file, "=== PART 1-B SIMULATION 1 ===\n\n");
    fprintf(file, "Number of Path Points = %d\n\n", k);
        for (int i = 0; i < k; i++){ 
            pathX[i] = GenerateRandomCoordinate(d);
            pathY[i] = GenerateRandomCoordinate(d);
            printf("Path Point %d = (%d, %d)\n",i + 1, pathX[i], pathY[i]);
        }
        for (int i = 0; i < k; i++){     // Move the battleship to each path point
            pointHitCount = 0;
            pointBattleTime = 0;
            B.x = pathX[i];
            B.y = pathY[i];
            printf("\nBattleship moved to Point %d\n", i + 1);
            printf("Battleship Position = (%d, %d)\n", B.x, B.y);

            fprintf(file, "=== Path Point %d ===\n", i + 1);
            fprintf(file, "Battleship Position = (%d, %d)\n",B.x, B.y);
        
            for (int j = 0; j < n; j++){ // Check only escort ships that are still active
                if (E[j].isAlive == 1){
                   // E[j].maxAttackRange = 0;  
                    E[j].distanceFromB = CalculateDistance(B.x, B.y, E[j].x, E[j].y); // Recalculate the distance from the new battleship position
                // Check if the battleship and esscort ship can hit each other
                    E[j].canBeHitByB = CanBattleshipHit(E[j].distanceFromB, B.maxAttackRange);
                    E[j].canHitB = CanEscortHitBattleship(E[j].distanceFromB, E[j].maxAttackRange);
                    printf("Distance to E%d = %.2f\n",E[j].index, E[j].distanceFromB);
                        
                    fprintf(file, "Escort Ship E%d\n", E[j].index);
                    fprintf(file, "Position = (%d, %d)\n", E[j].x, E[j].y);
                    fprintf(file, "Distance from B = %.2f\n", E[j].distanceFromB);

                if (E[j].canBeHitByB == 1){
                    fprintf(file, "B Can Hit = YES\n");
                }
                else{
                    fprintf(file, "B Can Hit = NO\n");
                }
                if (E[j].canHitB == 1){
                    fprintf(file, "E Can Hit B = YES\n");
                }
                else{
                    fprintf(file, "E Can Hit B = NO\n");
                }
                fprintf(file, "\n");
                         if (E[j].canHitB == 1){         // Check if the escort ship can sink the battleship
                                battleshipSunk = 1;
                                sinkingEscortIndex = E[j].index;
                                printf("Battleship was sunk by Escort Ship E%d\n",E[j].index);
                                fprintf(file, "Result = BATTLESHIP SUNK\n");
                                fprintf(file, "Battleship was sunk by Escort Ship E%d\n\n",E[j].index);
                                break;
                        }
                         if (E[j].canBeHitByB == 1){         // Destroy the escort ship if B can hit it
                                E[j].firingAngleFromB = CalculateFiringAngle(E[j].distanceFromB,B.maxVelocity);
                                E[j].timeToHitFromB = CalculateTimeToHit(E[j].distanceFromB,B.maxVelocity,E[j].firingAngleFromB);
                                if (E[j].timeToHitFromB > pointBattleTime){
                                    pointBattleTime = E[j].timeToHitFromB;
                                }
                                E[j].isAlive = 0;
                                pointHitCount++;
                                printf("Escort Ship E%d was destroyed by B\n",E[j].index);
                                printf("Time to Hit = %.2f seconds\n",E[j].timeToHitFromB);
                                fprintf(file, "Result = DESTROYED BY B\n");
                                fprintf(file, "Time to Hit = %.2f seconds\n\n",E[j].timeToHitFromB);
                        }
                }
            }
            if (battleshipSunk == 0){     // Save results if B survived this path point
                fprintf(file, "Battleship SURVIVED this point\n");
                fprintf(file, "Number of Escort Ships hit by B = %d\n\n",pointHitCount);
                fprintf(file, "Battle Time at this Point = %.2f seconds\n\n",pointBattleTime);
            }
            if (battleshipSunk == 1){     // Stop the simulation if the battleship is sunk
                break;
            }
        }
        fprintf(file, "\n=== FINAL SIMULATION 1 STATUS ===\n");
        if (battleshipSunk == 1){
            fprintf(file, "Battleship Status = SUNK\n");
            fprintf(file, "Sunk by Escort Ship E%d\n",sinkingEscortIndex);
        }
        else{
            fprintf(file, "Battleship Status = SURVIVED\n");
        }
        fprintf(file, "\nEscort Ships Final Status:\n");

        for (int i = 0; i < n; i++){
            if (E[i].isAlive == 1){
                fprintf(file, "Escort Ship E%d = ALIVE\n",E[i].index);
            }
            else{
                fprintf(file, "Escort Ship E%d = DESTROYED\n",E[i].index);
            }
        }   
    fclose(file);
}