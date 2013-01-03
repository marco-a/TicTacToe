/*
 ########################################################
 #                                                      #
 # TicTacToe                                            #
 #                                                      #
 # Copyright (c) 2013 Pro Fusion. All rights reserved.  #
 #                                                      #
 ########################################################
 */

#include <stdio.h>
#include <stdlib.h>

/*
 //////////////////
 language
 \\\\\\\\\\\\\\\\\\
 */

/// ---> set language to "de"
#define LANG_DE

// define

#define DRAW_STR "It's a draw"
#define WINNER_STR "Player %d won the game"
#define ROW_STR "Row"
#define COLUMN_STR "Column"
#define PLAYER_STR "Player %d"
#define INVALID_INPUT_STR "Invalid input"
#define FIELD_TAKEN_STR "Field is taken"

#ifdef LANG_DE

// undefine
#undef LANG_EN
#undef DRAW_STR
#undef WINNER_STR
#undef ROW_STR
#undef COLUMN_STR
#undef PLAYER_STR
#undef INVALID_INPUT_STR
#undef FIELD_TAKEN_STR

// redefine
#define DRAW_STR "Unentschieden"
#define WINNER_STR "Spieler %d hat das Spiel gewonnen"
#define ROW_STR "Zeile"
#define COLUMN_STR "Spalte"
#define PLAYER_STR "Spieler %d"
#define INVALID_INPUT_STR "Ungueltige Eingabe"
#define FIELD_TAKEN_STR "Feld ist besetzt"

#endif

/*
 //////////////////
 defines
 \\\\\\\\\\\\\\\\\\
 */

#define X 'X'
#define O 'O'
#define BLANK ' '

/*
 //////////////////
 typedefs
 \\\\\\\\\\\\\\\\\\
 */

typedef enum {
    NO_PLAYER,
    PLAYER_1,
    PLAYER_2
} players;

typedef enum {
    false = 0,
    true
} boolean;

typedef unsigned char byte;
typedef unsigned int uint;

/*
 //////////////////
 global vars
 \\\\\\\\\\\\\\\\\\
 */

static byte field[3][3] = {
    {BLANK, BLANK, BLANK},
    {BLANK, BLANK, BLANK},
    {BLANK, BLANK, BLANK}
};

static players current_player = NO_PLAYER;

/*
 //////////////////
 prototypes
 \\\\\\\\\\\\\\\\\\
 */

byte get_pattern_by_player(players player);

void print_field(void);

byte get_field(uint row, uint column);

boolean set_field(byte field_value, uint row, uint column);

boolean range(int num, int min, int max);

void ask_player(void);

boolean get_winner(void);

boolean is_done(void);

/*
 //////////////////
 implementation
 \\\\\\\\\\\\\\\\\\
 */

byte get_pattern_by_player(players player) {
    switch (player) {
        case PLAYER_1:
            return X;
        break;
            
        case PLAYER_2:
            return O;
        break;
        
        case NO_PLAYER:
            return BLANK;
        break;
    }
    
    return BLANK;
}

void print_field(void) {
    uint row = 0, column = 0;
    
#ifdef WINDOWS
    system("cls");
#else
    if (getenv("TERM")) system("clear");
#endif
    
    printf("+---+---+---+\n");
    
    for (row = 0; row < 3; ++row) {
        printf("|");
        
        for (column = 0; column < 3; ++column) {
            printf(" %c |", get_field(row, column));
        }
        
        printf("\n");
        
        printf("+---+---+---+\n");
    }
}

byte get_field(uint row, uint column) {
    if (range(row, 0, 2) && range(column, 0, 2)) {
        return field[row][column];
    }
    
    return BLANK;
}

boolean set_field(byte field_value, uint row, uint column) {
    if (range(row, 0, 2) && range(column, 0, 2)) {
        field[row][column] = field_value;
        
        return true;
    }
    
    return false;
}

boolean range(int num, int min, int max) {
    return (num >= min && num <= max);
}

void ask_player(void) {
    uint row = 0, column = 0, v_row = 0, v_column = 0;
    
    do {
        /// ---> INIT
        
        fflush(stdin);
        fseek(stdin, 0, SEEK_END);
        
        printf("\n\n> ");
        
        printf(PLAYER_STR, current_player);
        
        /// ---> ROW
        
        printf(" : \n# ");
        
        printf(ROW_STR);
        
        printf("      : ");
        
        v_row = scanf("%u", &row);
        
        getchar();
        
        /// ---> COLUMN
        
        printf("# ");
        
        printf(COLUMN_STR);
        
        printf("   : ");
        
        v_column = scanf("%u", &column);
        
        getchar();
        
        if (v_row == 1 && v_column == 1) {
            if (row > 0) --row;
            if (column > 0) --column;
            
            if (!range(row, 0, 2) || !range(column, 0, 2)) {
                printf(INVALID_INPUT_STR);
            } else if (get_field(row, column) != BLANK) {
                printf(FIELD_TAKEN_STR);
            } else {
                set_field(get_pattern_by_player(current_player), row, column);
                
                print_field();
                
                if (get_winner() == false) {
                    current_player = (current_player == PLAYER_1 ? PLAYER_2 : PLAYER_1);
                } else {
                    
                    printf("\n\t");
                    printf(WINNER_STR, current_player);
                    printf("\n");
                    
                    return;
                }
            }
        }
    } while (!is_done());
    
    printf("\n\t");
    printf(DRAW_STR);
    printf("\n");
}

boolean get_winner(void) {
    byte pattern = get_pattern_by_player(current_player);
    uint row = 0, column = 0;
    
    /*
     x - -
     x - -
     x - -
     */
    
    for (column = 0; column < 3; ++column) {
        if (get_field(0, column) == pattern && get_field(1, column) == pattern && get_field(2, column) == pattern) {
            return true;
        }
    }
    
    /*
     x x x
     - - -
     - - -
     */
    
    for (row = 0; row < 3; ++row) {
        if ((get_field(row, 0) == pattern) && (get_field(row, 1) == pattern) && (get_field(row, 2) == pattern)) return true;
    }
    
    /*
     x - -
     - x -
     - - x
     
     - - x
     - x -
     x - -
     */
    
    if (
        (get_field(0, 0) == pattern && get_field(1, 1) == pattern && get_field(2, 2) == pattern) ||
        (get_field(0, 2) == pattern && get_field(1, 1) == pattern && get_field(2, 0) == pattern)
        ) {
        return true;
    }
    
    
    return false;
}

boolean is_done(void) {
    uint row = 0, column = 0;
    
    for (row = 0; row < 3; ++row) {
        for (column = 0; column < 3; ++column) {
            if (get_field(row, column) == BLANK) return false;
        }
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    print_field();
    
    current_player = PLAYER_1;
    
    ask_player();
    
    return 0;
}
