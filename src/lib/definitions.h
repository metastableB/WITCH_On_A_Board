/*
 * definitions.h
 *
 * Contains global macro definitions
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 19-Jul-2015
 * 
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/*
 * DekatronStore Array[row][col] form to index the dekatron stores
 * row in [1,9] and column in [0,9]
 */
#define NO_OF_STORE_ROW 10
#define NO_OF_STORE_COL	10

/*
 * The logger is configured to output to stderr by default. You can modify this
 * in the logger.cpp file. Look at function Logger::log(X,X,X);
 */

/*
 * File and folder locations
 */
#define HOME		"$WITCH_HOME"
#define DIR_COMMANDS	HOME"/docs/COMMANDS"
#define DIR_DEFINITIONS HOME"/src/lib/definitions.h"

#define HISTORY_NUMBER 10	/* Number of commands to store in history */
#endif /* DEFINITIONS_H */




