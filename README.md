# SportsBetManager
This program allows users to track and store potential MoneyLine sports bets. MoneyLine bet objects are denoted by class SportsBet, and the structure for managing SportsBets is a linked list defined by SportsBetManager. Bets are stored in SportsBetManager according to their date.

## SportsBet
Includes SportsBet.h & SportsBet.cpp. 

This class describes a MoneyLine bet object. 

### Private Variables 
* int odds - Indicates the odds of the bet, 110, 300, etc.
* char oddsSymbol - '+' or '-' to denote the direction of the odds
* Date gameDate - Date object storing the date of the event for which the bet is placed about
* std::string sport - The sport of the bet: football, basketball, etc.
* std::string betFor - Who the bet is for: Liverpool, Raiders, etc.
* std::string betAgainst - Who is the opposing team

### Functionality
* getOddsSymbol - returns char '+' or '-' depending on the direction of the odds
* setOddsSymbol - sets oddsSymbol
* getOdds - returns the odds
* setOdds - sets the odds
* getDate - returns gameDate
* setDate - sets gameDate
* getSport - returns sport
* setSport - sets sport
* getFor - returns betFor
* setFor - sets betFor
* getAgainst - returns betAgainst
* setAgainst - sets betAgainst
* toString - method for displaying bet object to screen. Returns a string of how bet object is displayed. 
```
Sample return string:
Moneyline - Football
Football Team +110 vs. Chargers
Date: 1/9/2022
```
* equals - checks if two SportsBet objects are equal
* operator== - equality overload

## Date
Includes Date.h & Date.cpp. An object to hold and compare dates

### Private Variables
int month, day, year 

### Functionality
* setDate - set the date (day, month, and year)
* equals - check if two dates are the same
* operator overloads: >, <, ==, <=, >=, !=

## BetNode
Includes BetNode.h. SportsBetManager helper function which declares the structure for a node of a linked list. Each node contains a SportsBet object and pointer to the next BetNode.

## SportsBetManager
Includes SportsBetManager.h & SportsBetManager.cpp. 

### Private Variables
* numBets - number of bets held by Manager
* betList - Pointer to beginning of Linked List

### Functionality
* getNumBets - return the number of bets held by the SportsBetManager
* addBet - add a bet to the Manager. Bets are added in order of date. If other bets exist on the same date, the bet will be added after all the other bets on that date
* getBetsOnDate - returns a string of all bets occuring on a specified date
* getBetsFor - returns a string of all bets placed for a specified team
* getBetsAgainst - returns a string of all bets placed against a specified team
* getBetsOfSport - returns a string of all bets placed for a given sport
* getAllBets - returns a string containing all bets held by the SportsBetManager
* deleteAllBets - deletes all bets held by the SportsBetManager
* deleteBetsBefore - deletes all bets held by the SportsBetManager which occur before a specified date
* deleteBet - deletes a specified bet object from the SportsBetManager
* deleteBetsFor - deletes all bets placed for a specified team from the SportsBetManager
* deleteBetsAgainst - deletes all bets placed against a specified team from the SportsBetManager
* exists - acceptes a SportsBet object as a parameter and determines if that objects already exists in the SportsBetManager



