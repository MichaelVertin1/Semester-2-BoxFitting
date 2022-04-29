# Semester-2-BoxFitting

CS136 Professor showed program that another class was working on to fit several small boxes into a large box. This looked entertaining, so I attempted to recreate it. 

I inserted a SLEEP_TIME constant to slow down the program for viewers to observe the process. The box set is defined as a constant two-dimmensional array. I provided several examples within a block comment. 

This program was one of the first C programs I made, before arrays were discussed in CS136. Several of the methods I created were overly complicated, and there are much more efficient ways to handle what I did. 

The program uses an "algorithm state" to keep track of where blocks are inside of the box. When the algorithm state changes, the content inside the main block also changes. 
Every iteration, the program first attempts to add another block into the box. If a block cannot be placed into the bottom-left most location, the program will replace the last block with the next largest avaliable block. When there are no more avaliable blocks, the last block is removed, and iteration ends. 

This program requires that each block is identified by it's bottom-left most location being at (0,0), and other locations of the block are relative to that. The relative x-coordinate for a block can be negative iff it does not have a 0 y-coordinate. The y-coordinate can never be negative. 
This program assumes that a solution is possible, and will not end until one is found. Therefore, if a solution is not possible, after the program has the greatest potential algorithm state, all blocks will be removed, and the process will repeat forever. 
