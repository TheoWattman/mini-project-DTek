# mini-project-DTek

# Pacman

A Pacman game devloped for the IS1200 course at KTH which ended up winning "Best Project". The game is designed for the Chipkit Uno32 devlopment board together with the Chipkit Basic I/O shield.

## Running the game

The game is compiled and built onto the board using the MCB32 toolchain available at: https://github.com/is1200-example-projects/mcb32tools.

1. Navigate to the folder of the game using bash.
2. Type ". /opt/mcb32tools/environment" into bash to enter the cross compile environment.
3. Type "make" into bash to compile the code.
4. Install the code onto the device by typing "make install TTYDEV=/dev/ttySX", replace X with COM numbero for the chipkit UNO32.

## Controls
 * Switch 1 : Invert display

### Menu
   
 * Button 4 : Next option

 * Button 3 : Select option

### Game

 * Button 4 : Left

 * Button 3 : Up

 * Button 2 : Down

 * Button 1 : Right
