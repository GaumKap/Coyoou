# Add SQLite in Sources

SQLite sources are available at :
https://www.sqlite.org/download.html

Download those files :
- sqlite-amalgamation-3340000.zip
- sqlite-dll-win64-x64-3340000.zip
- sqlite-dll-win32-x86-3340000.zip

<u>After Downloading SQLite sources, build SQLite3 lib and exp files</u>

To create those file open in Administrative mode **Developer Command Prompt for VS 2019** and in **sqlite3.def** Directory do :

in **./sqlite-dll-win64-x64-3340000**:
~~~ bash
lib /DEF:sqlite3.def /OUT:sqlite3.lib /MACHINE:x64
~~~

in **./sqlite-dll-win32-x86-3340000**:
~~~ bash
lib /DEF:sqlite3.def /OUT:sqlite3.lib /MACHINE:x86
~~~

put **all files from sqlite win64** folder **in SQLite64 folder in Coyoou Sources**.
And **all files from sqlite win32** folder **in SQLiteWin32 folder in Coyyou Sources.**

**All files in sqlite-amalgamation, exept sqlite3ext.h** (not used), move it **in Coyyou Sources files** (in the same place of Coyoou.cpp)

if you are lost you can see this video on YouTube :
https://youtu.be/MFPa4ZZgbpM
