//Elementary Cellular Automaton

#include <stdio.h>
#include <stdbool.h> 

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    bool state[3]; //active status for [left, me, right] cells 
    bool active; //current active status for this cell
} cell;

//convert an 8-bit integer rule (0-255) to array of bits 
//(stored in reverse order)
//   ex: rule = 6  = 00000110 -> [01100000] 
//   ex: rule = 30 = 00011110 -> [01111000] 
//   ex: rule = 65 = 01000001 -> [10000010]
//return true if input rule is valid (0-255)
//return false if input rule is invalid
bool setBitArray(bool bitArray[8], int rule) {
int bRule;
        //TODO: Task 1 - write the setBitArray() function
    if(rule<0||rule>255) 
    {
        return false;
    }

    for(int i=0;i<8;i++)  //this condition will compare rule between 0-255
    {
        bitArray[i]=false;
    }
    int index=0;
    while(rule>0) //this will convert the number to bitArray and increase the value of index.
    {
        bitArray[index]=rule%2==1;
        rule/=2;
        index++;
    }
    return true;
}

//convert a 3-bit state array to its 
//associated index of the rule# bit array
//   ex: {0 0 0} -> 0
//   ex: {0 0 1} -> 1
//   ex: {1 0 1} -> 5
int stateToIndex(bool state[3]) {

    //TODO: Task 4 - write the stateToIndex() function
    int index=0; //state array to the associated index of the rule bit array. 
    for(int i=0;i<3;i++) //it will start the loop from left to right
    {
        index=(index*2+state[i]%8); 
    } 
    return index;
}

//update the state array for each cell in the world array based on the
//current status of active for the nearby [left,me,right] cells
//note: world is assumed periodic/cyclic,
//with front-to-back and back-to-front wrapping 
void updateCellState(cell world[WORLD_SIZE], int index)//Created this function for updating the values on the cell state. Assinging WORLD_SIZE
{
    int Lindex=(index - 1 + WORLD_SIZE)%WORLD_SIZE;
    int Rindex=(index + 1) % WORLD_SIZE;

    world[index].state[0] = world[Lindex].active; //update the arrays-1
    world[index].state[1] = world[index].active; //update the arrays-2
    world[index].state[2] = world[Rindex].active; //update the arrays-3
}
void setStates(cell world[WORLD_SIZE]) {

    //TODO: Task 5 - write the setStates() function
    for(int i=0;i<WORLD_SIZE;i++)
    {
        updateCellState(world,i); // to update the array I used this function
    }
    return;
}

void Iworld(cell world[WORLD_SIZE]) //This function is specially created to initialize the world to middle cell
{
    for(int i=0;i<WORLD_SIZE;i++) //assigning false to the state array
    {
        world[i].active=false;
        world[i].state[0]=false; //Initializing state array 
        world[i].state[1]=false;
        world[i].state[2]=false;
    }
    int mIndex=WORLD_SIZE/2;  // to calculate world array
    world[mIndex].active=true;
    world[mIndex].state[1]=true;

    for(int i=0;i<WORLD_SIZE;i++)  //loop through world
    {
        if(world[i].active)
        {
            printf("*");
        }
        else
        {
            printf(" ");
        }
        
    }
    printf("\n");
}
//evolve each cell's active status to the next generation 
//  using its state array
//ruleBitArray contains the 8-bits for the rule#, 
//  stored in reverse order
void evolveWorld(cell world[WORLD_SIZE], bool ruleBitArray[8]) {
    setStates(world);
    //TODO: Task 7 - write the evolveWorld() function
    cell newWorld[WORLD_SIZE]; //to store new gens 

    for(int i=0;i<WORLD_SIZE;i++) //// Loop through all cells in the world array
    {
        int rIndex=stateToIndex(world[i].state); //counts the index      
        world[i].active=ruleBitArray[rIndex];//updates the index
    }

    //Adding task-8 here
    for(int i=0;i<WORLD_SIZE-1;i++) //this is going to print the current value of world to cell
        {
            if(world[i].active)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
            if(i==WORLD_SIZE-1)
            {
                printf("\n");
            }
        }
        printf(" \n");
}


int main() {
    cell world[WORLD_SIZE];

    printf("Welcome to the Elementary Cellular Automaton!\n");

    //TODO: Task 2 - read in a valid rule# and
    //      generate the rule's 8-bit rule bit array 
    //      print the bit array in correct binary number order
    int rule;
    bool bitArray[8];

     do
     {
         printf("Enter the rule # (0-255): ");
         scanf("%d",&rule);
     }while(!setBitArray(bitArray,rule)); //continue loops till setBitArray gets false
        
    printf("\nThe bit array for rule #%d is ",rule);
    for(int i=7;i>=0;i--) //loop starting from 7 to each bit
    {
        printf("%d",bitArray[i]);
    }
    printf("\n");
    


    //TODO: Task 3 - use the rule bit array to report the evolution 
    //      step for all possible cell states.
    //      follow the format of the sample output exactly
   // int index;
    //bool state[3];
     printf("The evolution of all possible states are as follows:\n|***|   |** |   |* *|   |*  |   | **|   | * |   |  *|   |   |\n"); //This is the first line that we have to print
    
    for(int i=7;i>=0;i--) 
    {
        if(bitArray[i]==0) //check the current value of bitarray[i] ==0
        {
            if(i!=0)
            {
                printf(" | |    ");  //if its 0 the it prints this
            }
            else
            {
                printf(" | | "); //if its not then prints this
            }
            
        }
        else
        {
            if(i!=0) // checks if i is not equal 0
            {
                printf(" |*|    "); //if it is then prints this
            }
            else
            {
                printf(" |*| ");
            }
        }
    }
    
    printf("\n");

    //setStates(world);

    //TODO: Task 6 - read in the total number of generation evolution 
    //      steps from the user and initialize the world with ONLY the 
    //      middle cell active, all other cells should be inactive; 
    //      make sure to set the state array for each cell.
    int gen;
    printf("Enter the number of generations: \n");
    scanf("%d",&gen);
    printf("Initializing world & evolving...\n");
    //printf("                                *");
    Iworld(world);

    //TODO: Task 8 - evolve the world the user-specified number  
    //      of generations, printing each active cell as '*' and
    //      each non-active cell as ' ' (whitespace) after each
    //      evolution step to the next generation

        //printf("");
        //int world[WORLD_SIZE];
    
    for(int j=1;j<=gen-1;j++) //the loop iterate some outputs and gen-1 is used to adjust the pattern 
    {
        evolveWorld(world,bitArray); //calling this function because we worked inside this function for task-8
    }
    return 0;
}
