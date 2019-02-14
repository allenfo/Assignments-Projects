The game is a text based adventure where you navigate through rooms until you find the end room. You can also check the current time by typing "time". </br>
Download the zip file. To play run:</br>
gcc -o allenfo.buildrooms allenfo.buildrooms.c</br>
gcc -o allenfo.adventure allenfo.adventure.c -lpthread</br>

then run the allenfo.buildrooms to create the files for the game
run the allenfo.adventure to play the game</br>

Example gameplay.

CURRENT LOCATION: Berkeley

POSSIBLE CONNECTIONS: Moraga, Hayward, SanJo, Frisco, Orinda.

WHERE TO? >time

10:11PM, Wednesday, February 13, 2019


CURRENT LOCATION: Berkeley

POSSIBLE CONNECTIONS: Moraga, Hayward, SanJo, Frisco, Orinda.

WHERE TO? >Moraga

CURRENT LOCATION: Moraga

POSSIBLE CONNECTIONS: Berkeley, Frisco, Orinda, Alameda.

WHERE TO? >Frisco

CURRENT LOCATION: Frisco

POSSIBLE CONNECTIONS: Berkeley, SanJo, Moraga, Hayward, Orinda, Alameda.

WHERE TO? >SanJo

YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!

YOU TOOK 3 STEPS. YOUR PATH TO VICTORY WAS:

Moraga
Frisco
SanJo
