
SunRiZe is a simplified Model Driven Development software, used to generate C code 
for micro platforms, like Arduino.

SunRiZe is written in pure C++-1x with wxWidget and embedded python scripting.

SunRiZe has been developed on Linux with the mind to be portable.


Compiling On Linux
==================

SunRiZe requires :
wxWidgets (development) 3.0 or greater
python2.x Libraries (development), does not work with 3.x

cmake v. 2.8 or greater
 
To compile SunRiZe, make a checkout or download the archive.
Then 

cd SunRiZe 
cmake .
make

If everything goes fine, in bin you will find :

GenCode.py
libSunRiZeModel.so
SunRiZe

That is the standalone program folder you can move everywhere.

from there, run SunRiZe and enjoy.



Compiling on Windows (new)
==========================

There is a specific build for Windows.
Look in Build, at the file "HowToCompile.rtf"



I'm working to the tool documentation.

Good luck, Marco


