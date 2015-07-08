

# WITCH On A Board



Project to develop a simulator for the [Harwell WITCH](http://en.wikipedia.org/wiki/Harwell_computer) based on the [Minnowboard Max](http://www.minnowboard.org/meet-minnowboard-max/)  as part of Google Summer of Code, 2015.

For more information:

* [witch-e Home Page](http://witch-e.org/Main_Page)
* [WITCH\_On\_A\_Board project page](http://witch-e.org/Witch_On_A_Board)
* [Online WITCH emulator](http://emulator.witch-e.org/)

### Running  (on UNIX env)
We use make to compile from source. Make sure you have it on your system. To run, in the project directory, run

    $ make all
    $ ./witch_sim

To clean the executables and other files, run

    $ make clean

To run the test suit

    $ make testAll
    $ ./testAll

To run interactive alu tests

    $ make ui_alu
    $ ./ui_alu

and to clean test files use,

    $ make cleanTests

**&copy; Don Dennis (metastableB)**
