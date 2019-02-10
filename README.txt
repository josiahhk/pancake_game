You can either use "make" and then "./Game" or

g++-8.2.0 -std=c++2a *.cpp -lfltk -lfltk_images -static-libstdc++
and then running with ./a.out

In regards to -static-libstdc++, I was having trouble with my linker throughout this
project. This links something on Windows 10, HOWEVER, I am not sure if it works the
same through all Windows 10 PCs. It might have to do with the location of libstdc or
something. If it doesn't work on your computer, I cannot really help.

In order to actually play the game, you generally have to click the text box,
input, and then clikc submit. As for playing the game, you click the pancake you
want to flip.