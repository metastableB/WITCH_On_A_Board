

# WITCH On A Board

*WARNING: Development Branch. Unstable and Possibly Radio Active. Proceed at your own risk*

Project to develop a simulator for the [Harwell WITCH](http://en.wikipedia.org/wiki/Harwell_computer) based on the [Minnowboard Max](http://www.minnowboard.org/meet-minnowboard-max/)  as part of Google Summer of Code, 2015.

For more information:

* [witch-e Home Page](http://witch-e.org/Main_Page)
* [WITCH\_On\_A\_Board project page](http://witch-e.org/Witch_On_A_Board)
* [Online WITCH emulator](http://emulator.witch-e.org/)

### Running  (on UNIX env)
We use make to compile from source. Make sure you have it on your system. To run, in the project directory, run

    $ make WITCH-e
    $ ./bin/witch-e

You can turn on the logging feature as well as the debug messages by the `debug=1` and `log=1` arguments. By default log and debug messages are sent to `stderr`. You can use regular console redirection to send the messages to files of your choice. This feature will be added later on.

    $ make WITCH-e debug=1 log=1
    $ ./bin/witch_sim

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
