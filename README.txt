
SunRiZe is a simplified Model Driven Development software, generating C code for micro platforms, like Arduino.

SunRiZe is written in pure C++-1x with wxWidget and embedded python scripting.

The current version of SunRiZe can be compile on Linux only, my system is a Debian Stretch.

I'm working to a porting for Windows, python 3 support (and documentation).

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

from there, run SunRiZe and enjoy !

Marco



