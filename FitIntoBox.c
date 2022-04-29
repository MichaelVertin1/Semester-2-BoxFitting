
/////////////////////////////////////////////////////
///////         start of program        /////////////
/////////////////////////////////////////////////////

// include headers
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

// define constants

#define LOC_SIZE 2 // x and y
const int EMPTY_LOCATION = -1001;  // for getBlockNumberOfCoordinate
const int UNDEFINED_BLOCK = -2002; // for algorithmState
#define NO_AVALIABLE_BLOCK -3003   // findLowestAvaliableBlock, last index of boxInfo
#define END_OF_BLOCK -4004 // for BLOCK_INTO and boxInfo
const int xIndex = 0;
const int yIndex = 1;
const char TOP_BOTTOM_LINE_CHAR = 'X';
const char BOX_BORDER_CHAR = 'X';
#define NA END_OF_BLOCK
const int UNIT_HEIGHT = 3;                       // scale
const int UNIT_WIDTH = 6;
const int SLEEP_TIME = 200000;                   // time between rotations (us)
const bool DISPLAY_BOX = true;





const int MAIN_BOX_WIDTH = 6;
const int MAIN_BOX_HEIGHT = 6;
// 002 resolved001
#define MAX_BLOCK_SIZE 7                               // size of largest block
#define TOTAL_BLOCKS 8                              // total quantity of blocks
const int BLOCK_INFO[TOTAL_BLOCKS][MAX_BLOCK_SIZE + 1][LOC_SIZE] = 
{
   {{0, 0}, {-2, 1}, {-2, 2}, {-1, 1}, {-1, 2}, {0, 1}, {0, 2}, {NA, NA}}, // block 3
   {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {NA, NA}}, // block 5
   {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {0, 1}, {0, 2}, {NA, NA}}, // block 6
   {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {NA, NA}}, // block 7
   {{0, 0}, {0, 1}, {1, 1}, {NA, NA}}, // block 2
   {{0, 0}, {0, 1}, {NA, NA}}, // block 4
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {NA, NA}}, // block 0
   {{0, 0}, {1, 0}, {1, 1}, {NA, NA}}, // block 1
};




///////////////////////// FIT_INTO_BOX BLOCK_INFO EXAMPLES ////////////////////////////////
/*
const int MAIN_BOX_WIDTH = 8;
const int MAIN_BOX_HEIGHT = 8;
// 001
#define MAX_BLOCK_SIZE 10                              // size of largest block
#define TOTAL_BLOCKS 13                             // total quantity of blocks
const int BLOCK_INFO[TOTAL_BLOCKS][MAX_BLOCK_SIZE + 1][LOC_SIZE] = 
{
   {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {NA, NA}}, // block 0
   {{0, 0}, {1, 0}, {1, 1}, {NA, NA}}, // block 1
   {{0, 0}, {0, 1}, {1, 1}, {NA, NA}}, // block 2
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, {NA, NA}}, // block 3
   {{0, 0}, {0, 1}, {NA, NA}}, // block 4
   {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {NA, NA}}, // block 5
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 2}, {NA, NA}}, // block 6
   {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {3, 1}, 
                                                  {3, 2}, {NA, NA}}, // block 7
   {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {-1, 2}, {-1, 3}, {NA, NA}}, // block 8
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {NA, NA}}, // block 9
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {NA, NA}}, // block 10
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {NA, NA}}, // block 11
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 2}, {1, 2}, {NA, NA}}, // block 12
};

const int MAIN_BOX_WIDTH = 6;
const int MAIN_BOX_HEIGHT = 6;
// 002
#define MAX_BLOCK_SIZE 6                               // size of largest block
#define TOTAL_BLOCKS 8                              // total quantity of blocks
const int BLOCK_INFO[TOTAL_BLOCKS][MAX_BLOCK_SIZE + 1][LOC_SIZE] = 
{
   {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {NA, NA}}, // block 0
   {{0, 0}, {1, 0}, {1, 1}, {NA, NA}}, // block 1
   {{0, 0}, {0, 1}, {1, 1}, {NA, NA}}, // block 2
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, {NA, NA}}, // block 3
   {{0, 0}, {0, 1}, {NA, NA}}, // block 4
   {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {NA, NA}}, // block 5
   {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {0, 1}, {0, 2}, {NA, NA}}, // block 6
   {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {NA, NA}}, // block 7
};

const int MAIN_BOX_WIDTH = 8;
const int MAIN_BOX_HEIGHT = 8;
// 001 modified 001
#define MAX_BLOCK_SIZE 10                              // size of largest block
#define TOTAL_BLOCKS 13                             // total quantity of blocks
const int BLOCK_INFO[TOTAL_BLOCKS][MAX_BLOCK_SIZE + 1][LOC_SIZE] = 
{
   {{0, 0}, {1, 0}, {1, 1}, {NA, NA}}, // block 1
   {{0, 0}, {0, 1}, {1, 1}, {NA, NA}}, // block 2
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, {NA, NA}}, // block 3
   {{0, 0}, {0, 1}, {NA, NA}}, // block 4
   {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {NA, NA}}, // block 5
   {{0, 0}, {1, 0}, {1, 1}, {0, 2}, {NA, NA}}, // block 6
   {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {3, 1}, 
                                                  {3, 2}, {NA, NA}}, // block 7
   {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {-1, 2}, {-1, 3}, {NA, NA}}, // block 8
   {{0, 0}, {0, 1}, {1, 1}, {NA, NA}}, // block 9
   {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, 
                                   {2, 1}, {NA, NA}}, // block 0
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {NA, NA}}, // block 10
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {NA, NA}}, // block 11
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {0, 2}, {1, 2}, {NA, NA}}, // block 12
};

const int MAIN_BOX_WIDTH = 6;
const int MAIN_BOX_HEIGHT = 6;
// 002 modified 001
#define MAX_BLOCK_SIZE 6                               // size of largest block
#define TOTAL_BLOCKS 8                              // total quantity of blocks
const int BLOCK_INFO[TOTAL_BLOCKS][MAX_BLOCK_SIZE + 1][LOC_SIZE] = 
{
   {{0, 0}, {1, 0}, {1, 1}, {NA, NA}}, // block 1
   {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {NA, NA}}, // block 2
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}, {NA, NA}}, // block 3
   {{0, 0}, {0, 1}, {NA, NA}}, // block 4
   {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {NA, NA}}, // block 5
   {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {NA, NA}}, // block 7
   {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {NA, NA}}, // block 0
   {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {0, 1}, {0, 2}, {NA, NA}}, // block 6
};

const int MAIN_BOX_WIDTH = 6;
const int MAIN_BOX_HEIGHT = 6;
// 002 resolved001
#define MAX_BLOCK_SIZE 7                               // size of largest block
#define TOTAL_BLOCKS 8                              // total quantity of blocks
const int BLOCK_INFO[TOTAL_BLOCKS][MAX_BLOCK_SIZE + 1][LOC_SIZE] = 
{
   {{0, 0}, {-2, 1}, {-2, 2}, {-1, 1}, {-1, 2}, {0, 1}, {0, 2}, {NA, NA}}, // block 3
   {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {NA, NA}}, // block 5
   {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {0, 1}, {0, 2}, {NA, NA}}, // block 6
   {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {NA, NA}}, // block 7
   {{0, 0}, {0, 1}, {1, 1}, {NA, NA}}, // block 2
   {{0, 0}, {0, 1}, {NA, NA}}, // block 4
   {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {NA, NA}}, // block 0
   {{0, 0}, {1, 0}, {1, 1}, {NA, NA}}, // block 1
};
*/
//////////////////////////////////////// END EXAMPLES ////////////////////////////////








typedef enum { ADDED_BLOCK, REMOVED_BLOCK, CHANGED_BLOCK } BLOCK_STATE_CHANGE;





// forward declarations
/*
Name: 
process: 
Function input/parameters: none
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/



/*
Name: addNewBlock()
process: adds a new block to boxInfo
Function input/parameters: boxInfo, block number, target location
Function output/parameters: boxInfo
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
void addNewBlock( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], int blockNum, 
                                                             int targetLoc[] );


/*
Name: checkLegalBlockPlacement()
process: checks if the last block in algorithmState is in a legal location
Function input/parameters: boxInfo, algorithm state, target location
Function output/parameters: none
Function output/returned: whether block placement was legal
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
bool checkLegalBlockPlacement( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                                       int algorithmState[], int targetLoc[] );


/*
Name: checkOutsideBox
process: takes in x and y val. Returns if both are legal dimmensions. 
Function input/parameters: location (int *)
Function output/parameters: none
Function output/returned: whether the coordinate is legal (bool)
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
bool checkOutsideBox( int location[ LOC_SIZE ] );


/*
Name: displayBox()
process: displays the box to the user
Function input/parameters: boxInfo
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
void displayBox( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ] );


/*
Name: displayCoordinate()
process: displays the number of the box at the coordinate(space if empty)
Function input/parameters: none
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
void displayCoordinate( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                                                  int xVal, int yVal ); 

/*
Name: displayTopLine()
process: displays the top line of the table
Function input/parameters: none
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/monitor: top line of table
Dependencies: none
*/
void displayTopLine();


/*
Name: emptyBoxInfo()
process: initializes the pattern of the block algorithm (with NAN reps)
Function input/parameters: patternArray
Function output/parameters: patternArray
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
void emptyBoxInfo( int patternArray[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ] );


/*
Name: findLastIndexOfArray()
process: iterates of the array until finds an empty space
Function input/parameters: array, empty space value
Function output/parameters: none
Function output/returned: index of last non empty space
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
int findLastIndexOfArray( int array[] );


/*
Name: findLastIndexOfIntArray2
process: finds the last index of a 2 dimmensional integer array(denoted by 
                                              EMPTY_LOCATION)
Function input/parameters: arrayName, arraySizeInner, arraySizeOuter
Function output/parameters: none
Function output/returned: value of last index that is avaliable
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
int findLastIndexOfIntArray2( int arraySizeInner, int arraySizeOuter, 
                                           int arrayName[][ arraySizeInner ] );



/*
Name: findLowestAvaliableBlock()
process: finds the lowest block value that is not already used, and returns it.
Function input/parameters: algorithmState
Function output/parameters: none
Function output/returned: lowestBlockValue
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
int findLowestAvaliableBlock( int algorithmState[], int minValue );



/*
Name: findNextTargetLocation()
process: determines if the box is full, returns full/not full
Function input/parameters: box information
Function output/parameters: none
Function output/returned: whether box is full (boolean)
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
bool findNextTargetLocation( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                                                             int targetLoc[] );



/*
Name: findNextValidState()
process: uses algorithm to test unique possibilities until finds one block 
                                  that can be used or removes last block placed
Function input/parameters: boxInfo, algorithmState
Function output/parameters: boxInfo, algorithmState
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
void findNextValidState( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                                                        int algorighmSnake[] );


/*
Name: generateNextAlgorithmState()
process: finds the next algorithm state. ( not for adding new blocks )
Function input/parameters: algorithmState
Function output/parameters: algorithmState
Function output/returned: REMOVED_BLOCK or replaced block
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
BLOCK_STATE_CHANGE generateNextAlgorithmState( int algorithmState[] );

/*
Name: generateNextAlgorithmStateForNewBlock()
process: finds the next algorithm state. ( for adding new blocks )
Function input/parameters: algorithmState
Function output/parameters: algorithmState
Function output/returned: ADDED_BLOCK
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
BLOCK_STATE_CHANGE generateNextAlgorithmStateForNewBlock( 
                                                        int algorithmState[] );



/*
Name: getBlockNumberOfCoordinate
process: finds the number of the block at the given location. 
                      returns EMPTY_LOCATION if no block exists at the location
Function input/parameters: information of the box, coordinate to be analyzed
Function output/parameters: none
Function output/returned: integer representation of block number
                                EMPTY_LOCATION if not valid
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
int getBlockNumberOfCoordinate( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ],
                                                            int coordinate[] );


/*
Name: initializeAlgorithmState
process: initializes the algorithm before processing
Function input/parameters: algorithmState
Function output/parameters: algorithmState
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
void initializeAlgorithmState( int algorithmState[] );


/*
Name: intArrayContainsInt()
process: determines if an integer is in one of the valuues of an integer array
Function input/parameters: integer array, arraySize, integer
Function output/parameters: none
Function output/returned: whether the integer is in the array
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
bool intArrayContainsInt( int integerArray[], int arraySize, int integer );


/*
Name: integerToCharacter()
process: creates a character representative of the integer
Function input/parameters: integer
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
char integerToCharacter( int integer );


/*
Name: printIntArray1()
process: prints a one dimmensional integer array
Function input/parameters: arrayName, arraySize
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/monitor: array contents
Dependencies: none
*/
void printIntArray1( int arrayName[] );


/*
Name: printBoxInfo()
process: displays the information in boxInfo
Function input/parameters: boxInfo
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/monitor: information in boxInfo
Dependencies: none
*/
void printBoxInfo( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ] );


/*
Name: removeBlock()
process: removes the given block from boxInfo
Function input/parameters: boxInfo, block number to be removed
Function output/parameters: boxInfo
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
void removeBlock( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], int blockNum );


/*
Name: removeMaxedBlockSeries()
process: Determines how many values need to be removed to increment the current by 1. 
                        Removes the values from the algorithmPhase and boxInfo. 
                        determines the next lowest value of the last non-maxed block
                        and adds that to algorithmsPhase. 
                        
Function input/parameters: boxInfo, algorithm state
Function output/parameters: boxInfo, algorithmState
Function output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
void removeMaxedBlockSeries( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                 int algorithmState[] );




// main function
int main()
   {
    // initialize variables / functions

       // initialize variables
    int boxInfo[ TOTAL_BLOCKS ][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ];
    int algorithmState[ TOTAL_BLOCKS + 1 ], targetLocFiller[ LOC_SIZE ];
    int count = 0;

       // display title
          // functions: printf()
    printf( "\nPut Blocks in Box Program\n" );
    printf( "=========================\n\n\n" );

    // get user input

    // conduct processing

       // initialize the values in the algorithm's state
          // functions: initializeAlgorithState()
    initializeAlgorithmState( algorithmState );

       // fill box with empty spaces
          // functions: emptyBoxInfo()
    emptyBoxInfo( boxInfo );

       // display the current box (empty)
          // functions: displayBox()
    displayBox( boxInfo );

       // while the box is not complete
          // functions: findNextTargetLocation()
    while( findNextTargetLocation( boxInfo, targetLocFiller ) )
    {

          // determine the next pattern
             // functions: findNextValidState()
          findNextValidState( boxInfo, algorithmState );

          // display the current box
             // functions: displayBox()
if( DISPLAY_BOX )
{
          displayBox( boxInfo );
}

          // sleep for the sleep time
             // functions: usleep()
          usleep( SLEEP_TIME );
// test
printIntArray1( algorithmState );
          count += 1;
          printf( "%i iterations\n", count );
 
    }

    // display results
// test
// display the end result
displayBox( boxInfo );

    // end program

       // print program end
          // functions: printf()
    printf( "Program End\n" );

       // return program success
    return 0;
   }





// OTHER FUNCTIONS: 

void addNewBlock( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], int blockNum, 
                                                             int targetLoc[] )
   {
    int locationNum = 0, xVal, yVal;

    // get every location of the block
    while( BLOCK_INFO[ blockNum ][ locationNum ][ xIndex ] != END_OF_BLOCK )
    {

       // find the xVal of the general location
       xVal = targetLoc[ xIndex ] + BLOCK_INFO[ blockNum ][ locationNum ]
                                                                    [ xIndex ];

       // find the yVal of the general location
       yVal = targetLoc[ yIndex ] + BLOCK_INFO[ blockNum ][ locationNum ]
                                                                    [ yIndex ];

       // add the x value to boxInfo
       boxInfo[ blockNum ][ locationNum ][ xIndex ] = xVal;

       // add the y value to the boxInfo
       boxInfo[ blockNum ][ locationNum ][ yIndex ] = yVal;

       // increment the location number by 1
       locationNum++;
    }

    // add no avaliable block to the end of the array (x and y values )
    boxInfo[ blockNum ][ locationNum ][ xIndex ] = END_OF_BLOCK;
    boxInfo[ blockNum ][ locationNum ][ yIndex ] = END_OF_BLOCK;
   }


bool checkLegalBlockPlacement( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                                            int algorithmState[], int targetLoc[] )
   {
    int lastBlockNum, blockArray[ TOTAL_BLOCKS ][ LOC_SIZE ], locationNum = 0;
    int lastBlockArrayIndex, blockIndex, adjustedLoc[ LOC_SIZE ];

    // calculate the block number of the last location in algorithmState
       // functions: findLastIndexOfArray()
    lastBlockNum = algorithmState[ findLastIndexOfArray( algorithmState ) ];

    // get the information of the corresponding block from the BLOCK_INFO
       // for every location:
    while( BLOCK_INFO[ lastBlockNum ][ locationNum ][ xIndex ] != END_OF_BLOCK )
    {

          // add the x value
       blockArray[ locationNum ][ xIndex ] = 
                           BLOCK_INFO[ lastBlockNum ][ locationNum ][ xIndex ];

          // add the y value
       blockArray[ locationNum ][ yIndex ] = 
                           BLOCK_INFO[ lastBlockNum ][ locationNum ][ yIndex ];

          // increment locationNum by 1
       locationNum += 1;

    }

    // find the last index of the block being analyzed
    lastBlockArrayIndex = locationNum - 1;

    // analyze every adjustment array in the corresponding block(for loop)
    for( blockIndex = 0; blockIndex <= lastBlockArrayIndex; blockIndex++ )
    {
       // calculate the location of the adjustment array
          // calculate xCoordinate
       adjustedLoc[ xIndex ] = blockArray[ blockIndex ][ xIndex ] + 
                                                           targetLoc[ xIndex ];

          // calculate yCoordinate
       adjustedLoc[ yIndex ] = blockArray[ blockIndex ][ yIndex ] + 
                                                           targetLoc[ yIndex ];

       // if the location is filled or outside of box boundary:
       if( getBlockNumberOfCoordinate( boxInfo, adjustedLoc ) != 
                                                               EMPTY_LOCATION )
       {     
          // return false (not legal block placement)
          return false;
       }

       // check outside boundaries
       if( checkOutsideBox( adjustedLoc )  )
       {
          // return false (not legal block placement)
          return false;
       }

    }

    // return true (assume other tests passed)
    return true;
   }


bool findNextTargetLocation( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                                                              int targetLoc[] )
   {
    // initialize variables
    int coordinate[ LOC_SIZE ], xVal, yVal;

    // iterate over y-values (top - bottom)
    for( yVal = 0; yVal < MAIN_BOX_HEIGHT; yVal++ )
    {
       // iterate over x-values (top - bottom)
       for( xVal = 0; xVal < MAIN_BOX_WIDTH; xVal++ )
       {
          // find the x- and y- values of the coordinate
          coordinate[ xIndex ] = xVal;
          coordinate[ yIndex ] = yVal;

          // check location is empty
          if( getBlockNumberOfCoordinate( boxInfo, coordinate ) == 
                                                               EMPTY_LOCATION )
          {
             // assign the x value to the target location xIndex
             targetLoc[ xIndex ] = xVal;

             // assign the y value to the target location yIndex
             targetLoc[ yIndex ] = yVal;

             // return that has more locations
             return true;
          }
       }
    }

    // return false (there are no empty locations left)
    return false;
   }

int getBlockNumberOfCoordinate( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ],
                                                            int coordinate[] )
   {
    int blockNum, locationIndex, xCoor, yCoor;

    // itegerate over block numbers
    for( blockNum = 0; blockNum < TOTAL_BLOCKS; blockNum++ )
    {
       // initialize first location index
       locationIndex = 0;

       // calculate x and y coordinates of location
       xCoor = boxInfo[ blockNum ][ locationIndex ][ xIndex ];
       yCoor = boxInfo[ blockNum ][ locationIndex ][ yIndex ];

       // analyze every location (while locations are valid)
       while( xCoor != END_OF_BLOCK )
       {

          // check xValue and yValue match the given coordinate
          if( xCoor == coordinate[ xIndex ] && yCoor == coordinate[ yIndex ] )
          {          
             // return the current block number
             return blockNum;
          }

          // start to analyze next location index
          locationIndex += 1;

          // calculate x and y coordinates of the location
          xCoor = boxInfo[ blockNum ][ locationIndex ][ xIndex ];
          yCoor = boxInfo[ blockNum ][ locationIndex ][ yIndex ];
       }
    }

    return EMPTY_LOCATION;
   }


/*
Name: checkOutsideBox
process: takes in x and y val. Returns if both are legal dimmensions. 
Function input/parameters: location (int *)
Function output/parameters: none
Function output/returned: whether the coordinate is legal (bool)
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
bool checkOutsideBox( int location[ LOC_SIZE ] )
   {
    // return whether outside boundaries
    return location [ xIndex ] < 0 || 
           location[ xIndex ] >= MAIN_BOX_WIDTH ||
           location[ yIndex ] < 0 || 
           location[ yIndex ] >= MAIN_BOX_HEIGHT;
   }

void displayBox( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ] )
   {
    int yVal, xVal, heightCount, widthCount;

    // display top line of box
       // functions: displayTopLine()
    displayTopLine();
    // iterate over every y value (reverse)
    for( yVal = MAIN_BOX_HEIGHT - 1; yVal >= 0; yVal-- )
    {
       // dipslay the line for its unit height
       for( heightCount = 0; heightCount < UNIT_HEIGHT; heightCount++ ) // alter: create string, then print
       {
          // display left side of table
             // functions: printf()
          printf( "%c", BOX_BORDER_CHAR );

          // iterate over every x value
          for( xVal = 0; xVal < MAIN_BOX_WIDTH; xVal++ )
          {
             // display the coordinate for its width
             for( widthCount = 0; widthCount < UNIT_WIDTH; widthCount++ )
             {
                // display one coordinate
                   // functions: displayCoordinate()
                displayCoordinate( boxInfo, xVal, yVal );
             }
          }

          // display right side of table, move one line down
             // functions: printf()
          printf( "%c\n", BOX_BORDER_CHAR );
       }
    }

    // display bottom line of box
       // functions: displayTopLine(), printf()
    displayTopLine();
    printf( "\n\n" );
   }



void displayTopLine()
   {
    int xVal;

    // print for every unit width
    for( xVal = 0; xVal < MAIN_BOX_WIDTH * UNIT_WIDTH + 2; xVal++ )
    {
       // print the topline character
       printf( "%c", TOP_BOTTOM_LINE_CHAR );
    }

    // move to the next line
    printf( "\n" );

   }



void emptyBoxInfo( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ] )
   {
    // initialize iteration values
    int blockNum, locationNum;

    // iterate over each block
    for( blockNum = 0; blockNum < TOTAL_BLOCKS; blockNum++ )
    {
       // iterate over each location within the block
       for( locationNum = 0; locationNum < MAX_BLOCK_SIZE + 1; locationNum++ )
       {
          // set x-value to "empty"
          boxInfo[ blockNum ][ locationNum ][ xIndex ] = END_OF_BLOCK;

          // set y-value to "empty"
          boxInfo[ blockNum ][ locationNum ][ yIndex ] = END_OF_BLOCK;
       }
    }
   }




void displayCoordinate( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                                                 int xVal, int yVal )
   {
    char blockChar;
    int blockInt;
    int coordinate[] = {xVal, yVal};

    // get the block number where the coordinate is
       // functions: getBlockNumberCoordinate()
    blockInt = getBlockNumberOfCoordinate( boxInfo, coordinate );

    // check there is a block at the coordinate:
    if( blockInt != EMPTY_LOCATION )
    {
       // find character value of the block integer
          // functions: integerToCharacter()
       blockChar = integerToCharacter( blockInt );       

       // display the character
          // functions: printf()
       printf( "%c", blockChar );
    }

    // otherwise
    else
    {
       // display empty coordinate charcter (space)
          // functions: printf()
       printf( " " );
    }
   }




void findNextValidState( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                                                        int algorithmState[] )
   {
    // initialize variables
    int targetLoc[ LOC_SIZE ];

    BLOCK_STATE_CHANGE changeBlockStateFlag;

    int blockNum;// tempBlockNum, minValueIndex;

    // initialize blockNum as the last block before removal/addition
       // functions: findLastIndexOfArray()
    blockNum = algorithmState[ findLastIndexOfArray( algorithmState ) ];

    // find location that needs to be filled next
       // functions: findNextTargetLoc()
    findNextTargetLocation( boxInfo, targetLoc );

    // generate next algorithm state 
       // functions: generateNextAlgorithmStateForNewBlock()
    changeBlockStateFlag = generateNextAlgorithmStateForNewBlock( algorithmState );

    // while the algorithm phase is not legal:
       // functions: checkLegalBlockPlacement()
    while( !checkLegalBlockPlacement( boxInfo, algorithmState, targetLoc ) )
    {
       // generate next algorithm state
          // functions: generateNextAlgorithmState()
       changeBlockStateFlag = generateNextAlgorithmState( algorithmState );

       // check that a block was removed
       if( changeBlockStateFlag == REMOVED_BLOCK )
       {
          // functions: removeMaxedBlockSeries
          removeMaxedBlockSeries( boxInfo, algorithmState );
          break;

          // state that a block has been added
          changeBlockStateFlag = ADDED_BLOCK;
   

       }

    }

    // check that a block was added
    if( changeBlockStateFlag == ADDED_BLOCK )
    {
       // find the block number
          // functions: findLastIndexOfArray
       blockNum = algorithmState[ findLastIndexOfArray( algorithmState ) ];

       // add the block to boxInfo
          // functions: addNewBlock()
       addNewBlock( boxInfo, blockNum, targetLoc );
    }
    
    // check that a block was changed
    if( changeBlockStateFlag == CHANGED_BLOCK )
    {
       // add the new block
          // get the new block number
             // functions: findLastIndexOfArray()
       blockNum = algorithmState[ findLastIndexOfArray( algorithmState ) ];

          // get the new target location
             // functions: findNextTargetLocation()
       findNextTargetLocation( boxInfo, targetLoc );

          // add the new block
             // functions: addNewBlock()
       addNewBlock( boxInfo, blockNum, targetLoc );
    }    
   }




int findLowestAvaliableBlock( int algorithmState[], int minValue )
   {
    int blockNum;

    // iterate over blocks from lowest to highest value
    for( blockNum = minValue; blockNum < TOTAL_BLOCKS; blockNum++ )
    {
       // check the block is not used
          // functions: contains()
       if( !intArrayContainsInt( algorithmState, TOTAL_BLOCKS, blockNum )  )
       {
          // return the value of the block
          return blockNum;
       }
    }

    // return there are no blocks avaliable
    return NO_AVALIABLE_BLOCK;
   }




int findLastIndexOfArray( int array[] )
   {
    int index;

    // iterate over array
    for( index = 0; index < TOTAL_BLOCKS + 1; index++ )
    {
       // if the element is an undefined block
       if( array[ index ] == UNDEFINED_BLOCK )
       {
          // return the previous index
          return index - 1;
       }
    }

    // print an error
       // functions: printf()
    printf( "Error: The last index does not exist\n" );
    return 0;
   }




int findLastIndexOfIntArray2( int arraySizeInner, int arraySizeOuter, 
                                             int arrayName[][ arraySizeInner ] )
   {
    int outerIndex;

    // iterate over outer array
    for( outerIndex = 0; outerIndex < arraySizeOuter; outerIndex++ )
    {
       // check the first value in the array descibes not avaliable
       if( arrayName[ arraySizeOuter ][ 0 ] == END_OF_BLOCK )
       {
          // return the previous index( last location of avaliable position
          return outerIndex - 1;
       }
    }

    return NO_AVALIABLE_BLOCK;
   }




BLOCK_STATE_CHANGE generateNextAlgorithmState( int algorithmState[] )
   {
    int lastIndex, minBlockRequirement = 0, avaliableBlockNum;

    // find the index of the last block in algorithmState
       // functions: findLastIndexOfArray()
    lastIndex = findLastIndexOfArray( algorithmState );

    // find the minimum block number requirement
    minBlockRequirement = algorithmState[ lastIndex ];

    // determine the next largest value block for the last block
       // functions: findLowestAvaliableBlock()
    avaliableBlockNum = findLowestAvaliableBlock( algorithmState, 
                                                         minBlockRequirement );

    // if the last block is too large to increase:
    if( avaliableBlockNum == NO_AVALIABLE_BLOCK )
    {        

       // remove the block
       algorithmState[ lastIndex ] = UNDEFINED_BLOCK;             

       // return REMOVED_BLOCK
       return REMOVED_BLOCK;
    }

    // otherwise change the block
    else
    {

       // replace the last block with the next largest avaliable block
       algorithmState[ lastIndex ] = avaliableBlockNum;

       // return CHANGED_BLOCK
       return CHANGED_BLOCK;
    }

   }

BLOCK_STATE_CHANGE generateNextAlgorithmStateForNewBlock( int algorithmState[] )
{
    int lastIndex, minBlockRequirement = 0, avaliableBlockNum;

    // find the index of the last block in algorithmState
       // functions: findLastIndexOfArray()
    lastIndex = findLastIndexOfArray( algorithmState );

    // find the lowest valued avaliable block
       // functions: findLowestAvabliableBlock()
    avaliableBlockNum = findLowestAvaliableBlock( algorithmState, 
                                                         minBlockRequirement );

    if( avaliableBlockNum != NO_AVALIABLE_BLOCK )
    {
       // add the avaliable block to the algorithm state
       algorithmState[ lastIndex + 1 ] = avaliableBlockNum;
          
       // declare the next index as not avaliable
       algorithmState[ lastIndex + 2 ] = UNDEFINED_BLOCK;
    }

    // return ADDED_BLOCK
    return ADDED_BLOCK;
}


void initializeAlgorithmState( int algorithmState[] )
   {
    int stateIndex;

    // for every other value
    for( stateIndex = 0; stateIndex < TOTAL_BLOCKS; stateIndex++ )
    {
       // assign to empty
       algorithmState[ stateIndex ] = UNDEFINED_BLOCK;
    }

   }



bool intArrayContainsInt( int integerArray[], int arraySize, int integer )
   {
    int index;

    // iterate over array
    for( index = 0; index < arraySize; index++ )
    {
       // check integer is equal to the correspoding index
       if( integerArray[ index ] == integer )
       {      
          // return success (integer found in array)
          return true;
       }
    }

    // return fail (integer not found in array)
    return false;
   }



char integerToCharacter( int integer )
   {
    char returnChar;

    // if the integer is a single digit:
    if( integer <= 9 )
    {
       // transform to character of that digit
       returnChar = '0' + integer;
    }

    // otherwise:
    else
    {
       // use letters to represent the digit (extended hex)
       returnChar = 'a' + (integer - 10);
    }

    return returnChar;
   }



void printIntArray1( int arrayName[] )
   {
    int index = 0;

    // initialize the array
    printf("{ " );

    // for every value in the array
    while( arrayName[ index ] != UNDEFINED_BLOCK )
    {
       // display the contents of the array
       printf( "%i, ", arrayName[ index ] );

       index += 1;
    }
    
    // end the array
    printf( "}\n" );
   }



void printBoxInfo( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ] )
   {

    int blockNum, locNum;

    // initialize box info print
    printf( "{\n" );

    // iterate over blocks
    for( blockNum = 0; blockNum < TOTAL_BLOCKS; blockNum++ )
    {
       // print initialize block array
       printf( "   { " );

       // iterate over locations of block
       for( locNum = 0; locNum < MAX_BLOCK_SIZE + 1; locNum++ )
       {
          // print x value
          printf( "{ %i, ", boxInfo[ blockNum ][ locNum ][ xIndex ] );

          // print y value
          printf( "%i }, ", boxInfo[ blockNum ][ locNum ][ yIndex ] );
       }

       // print end block array
       printf( " }, \n" );
    }
    // end box info print
    printf( "}\n" );
   }




void removeBlock( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], int blockNum )
   {
    // change the first x value of the block in boxInfo to END_OF_BLOCK
    boxInfo[ blockNum ][ 0 ][ xIndex ] = END_OF_BLOCK;

    // change the first y value of the block in boxInfo to END_OF_BLOCK
    boxInfo[ blockNum ][ 0 ][ yIndex ] = END_OF_BLOCK;
   }



void removeMaxedBlockSeries( int boxInfo[][ MAX_BLOCK_SIZE + 1][ LOC_SIZE ], 
                 int algorithmState[] )
   {
    int lastIndex, lastBlockNum, targetLoc[ LOC_SIZE ], nextAvaliableBlock;
    int minBlockNum;
    bool foundLegalReplacement = false;

    // get the index of the last block
       // functions: findLastIndexOfArray()
    lastIndex = findLastIndexOfArray( algorithmState );

    // do not allow the last block to be repeated on the first iteration
    minBlockNum = algorithmState[ lastIndex ] + 1;

    // remove the last block
       // functions: removeBlock()
    removeBlock( boxInfo, algorithmState[ lastIndex ] );
    algorithmState[ lastIndex ] = UNDEFINED_BLOCK;
    lastIndex -= 1;

    // as long as the change is not legal:
    while( !foundLegalReplacement )
    {
       // find the next target location
          // functions: findNextTargetLocation()
       findNextTargetLocation( boxInfo, targetLoc );

       // find the value of the last block
          // functions: findLastIndexOfArray()
       lastBlockNum = algorithmState[ findLastIndexOfArray( algorithmState ) ];

       // find the lowest avaliable block
          // functions: findLowestAvaliableBlock()
       nextAvaliableBlock = findLowestAvaliableBlock( algorithmState, 
                                                                 minBlockNum );

       // do not allow the next block to repeat
       minBlockNum = lastBlockNum + 1;

       // as long as there is another avaliable block to replace the removed block
       //                            and a legal replacement has not been found
       while( nextAvaliableBlock != NO_AVALIABLE_BLOCK && !foundLegalReplacement )
       {
          // add the next avaliable to ONLY algorithmState
          algorithmState[ lastIndex + 1 ] = nextAvaliableBlock;

          // check if the replacement block can be added legally
             // functions: checkLegalBlockPlacement()
          if( checkLegalBlockPlacement( boxInfo, algorithmState, targetLoc ) )
          {
             // add the replacement block
                // functions: addNewBlock()
             addNewBlock( boxInfo, nextAvaliableBlock, targetLoc );

             // the change has become legal (stop processing)
             foundLegalReplacement = true;
          }

          // otherwise (not a legal block placement)
          else
          {
             // remove the nextAvaliableBlock from ONLY algorithmState
             algorithmState[ lastIndex + 1 ]  = UNDEFINED_BLOCK;

             // find the next avaliable block
                // functions: findLowestAvaliableBlock()
             nextAvaliableBlock = findLowestAvaliableBlock( algorithmState, 
                                                       nextAvaliableBlock + 1 );
          }
       }

       // check a legal replacement has not been found
       if( !foundLegalReplacement )
       {
          // remove the new last block (it prevents continuation)
             // functions: removeBlock()
          algorithmState[ lastIndex ] = UNDEFINED_BLOCK;
          removeBlock( boxInfo, lastBlockNum);
          lastIndex -= 1;
       }
    }
   }

