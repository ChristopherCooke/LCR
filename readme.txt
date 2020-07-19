Final Project: Documentation
Christopher Cooke
06/21/2020
Problem Statement: 
Develop a program that follows the rules of Left Center Right (LCR) as described. 
1.	On program start-up, it shall display the rules to the user.
a.	As read from a text file submitted with the program.
2.	The user can then set up the game by entering the number of players. 
a.	Any number below three shall ask the user to add more players. 
Once gameplay has started based on the game rules, there are a few main pieces to address. 
3.	Rolling the die should be performed by randomly generating the side of the die displayed for each of the three using a random number generator.
4.	For this game, if the generated number is 1, that will be L. 
a.	Additionally, 2 is R
b.	3 is C
c.	and 4–6 are dots that can be represented with the asterisk symbol *.
5.	Be sure to check the current player’s number of chips before rolling.
6.	After each player’s roll, calculate the number of chips for players based on the actions dictated by the dice.
7.	Continue playing until only one player has chips.
8.	Display a message to the game winner
Additional Rules:
1.	The Dice
a.	There are three dice rolled each turn. 
b.	Each die has the letters L, C, and R on it along with dots on the remaining three sides.
c.	These dice determine where the player’s chips will go.
i.	For each L, the player must pass one chip to the player sitting to the left
ii.	For each R, the player must pass one chip to the player sitting to the right.
iii.	For each C, the player must place one chip into the center pot and those chips are now out of play.
iv.	Dots are neutral and require no action to be taken for that die.
2.	The Chips
a.	Each player will start with three chips.
b.	If a player only has one chip, he/she rolls only one die.
c.	If a player has two chips left, he/she rolls two dice. 
d.	Once a player is out of chips, he/she is still in the game (as he/she may get chips passed to him/her) but passes the dice to the next player.

Overall Process:
1.	5/31/2020
a.	I feel like I am making great progress towards the completion of my final project. Milestone 1 went very smoothly, and I have given thought towards what the architecture of the program shall look like. I am largely for putting objects into individual files and am curious how I need to approach that in C++. For the time being, I merely defined a ‘Die’ class within the same file as the main function.
2.	06/06/2020
a.	At this point, I am feeling incredibly confident in knocking out this final project. I have set up player, dice, and game classes. The pseudocode just developed will be a great aid in expediting completion. Now I am just looking for the right block of time to do it.
3.	06/13/2020
a.	Progress on my Final Project is coming along great. I am now comfortable reading / writing to files, utilizing header files, and working with multiple classes. Small pieces such as the player, dice rolling, menus, and i/o have all been worked out. Now I only need to implement the actual game logic.
Pseudocode:
Class Player:
	Chip Count property with getters/setters
Class Die:
	function RollDie():
		OBTAIN random number
		CONVERT random number to LCR* values
		RETURN converted random number
Class Manager:
	Player Count property
	Victory property
function Init():
		READ rules file
		DISPLAY rules file
		WHILE player count is not valid
			OBTAIN player count
			IF player count is not valid
				DISPLAY error message
		RETURN player count

	Function CheckVictory():
		FOREACH Player
			IF Player’s Chip Count EQUALS the total amount of chips in the game
				RETURN Winning Player
		RETURN No Winner
Function Main():
		Player Count = Init()
		FOR EACH Player Count
			CREATE Player
		CREATE 3 Die
		WHILE Victory IS FALSE
			FOR EACH Player
				IF Player’s Chip Count is BETWEEN 1 AND 3
					FOREACH Chip
						RollDie()
						DISPLAY Die Value
				IF Player’s Chip Count is GREATER THAN 3
					ROLL 3 Die AND DISPLAY Die Value
				FOR EACH Die Value rolled
					PROCESS Player’s Chip Counts
				Victory EQUALS CheckVictory()
				IF Victory IS NOT FALSE
					BREAK out of loop
		DISPLAY Victory Player

Methods and Classes:
My application follows the same flow as the pseudocode provided above. However, to increase modularity and attempt to reduce clutter, additional classes / methods have been added. This is largely due to my propensity to over engineer things. We now do things like output ASCII art from files and take special care to formatting, which the pseudocode did not address.
