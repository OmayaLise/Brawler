# Project Gladiator

**Authors : Lise Omaya, Vincent Devine**

For ISART Digital

<hr /><br />

## **Project description :**
This project was made to discover the C++ environment of Unreal Engine 4 and its IA system (BehaviorThree, Blackboard). We made a level using the basic mecanics of a brawler. <br />

<br />

## **To build and run the project :** 
Use the build (launch the .exe) or open the project in Unreal Engine 4.
<br /><hr />

## **Commands :**
- W/S : Move forward/backward
- A/D : Move left/right
- Mouse : Look around
- Right Click Mouse : Attack
- Left Click Mouse : Shield

<br /><hr />

## **Feature :**
Enemy AI:
- 5 Enemies with 3 PV
- Enemies stand around the player in circle until it is their turn to attack
- They move to the player position before attacking (only one enemy can attack at a time)
- They wait a bit before going back on the circle outside the player range

Player :
- Player has 5 PV
- He can attack but he can't move while doing so
- He can block attack in an 180 angle in front of him but can't move while he does it

Visual effect : 
- Poof of dust appear for each of the enemies and player steps
- Explosion will occur at the enemy death 

Other features : 
- Background music (loop)
- Sound for the attacks
- Day and Night cycle
- Win/Lose/Retry Menu

<br /><hr />

Engine : Unreal Engine 4.27 <br />
System : Windows
