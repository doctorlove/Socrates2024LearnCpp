# Socrates2024LearnCpp
Learn C++ workshop

This is the repo for my [SoCraTesUK](https://scrts.de/socratesuk2024/) workshop, "Learn C++ by Example".

We created a game of Rock, Paper, Scissors. You need a C++ tool, or can try on [Godbolt](https://godbolt.org/z/qanE4doMo).

One day, we might all import std, rather than use headers, but for now I used includes. 
The code uses 

 * cassert
 * algorithm
 * array
 * iostream
 * limits
 * optional
 * print
 * random
 * ranges
 * sstream 
 * stdexcept
 * vector


You need to write some output, figure out how to get input and make your computer randomly pick a turn. Bonus points for deciding who won.

This repo does more than I had time to cover in the workshop. 
For example I store the input, showing how you could keep track in a vector. 
I also include a game with exntensions, which keeps a tally og human turns in an array and uses a weighted average to "predict" the next human move. 
You could extend further to try to spot patterns. 
The internet has lots of ways to use stats/machine learning to play rock, paper, scissosrs.

As [Emily Bache](https://www.youtube.com/@EmilyBache-tech-coach)says, "Happy coding". 

cd to LearnCpp, and build the code, using All warnings (Wall) and C++ standard 23 (std=c++23)

$ g++ -Wall -std=c++23 main.cpp -o rps

(Or find similar instructions for your compiler).

The slides are [here](https://docs.google.com/presentation/d/1Jjln1Qs1xmrB_ko2itmKW9_0rXGreHkRpXwo1IPML48/edit?usp=sharing) and in this repo too as a pdf.




