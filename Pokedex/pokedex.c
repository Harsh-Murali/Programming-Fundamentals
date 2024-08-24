// Assignment 2 21T2 COMP1511: Pokedex
// pokedex.c
//
// This program was written by HARSH CHARU MURALI (z5361547)
// on 1-8-2021
//
// Version 1.0.0: Release
// Version 1.0.1: Fixed references to create_new_dexnode in comments and error messages

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "ext_save.h"

// Note you are not allowed to use the strstr function in this assignment
// There are some techniques we would like you to learn to code
// that this function makes easier.

// ----------------------------------------------
// Add any extra #includes your code needs here.
// ----------------------------------------------

#include "pokedex.h"


// ----------------------------------------------
// Add your own #defines here.
# define FOUND 1
# define UNKNOWN 0
# define FALSE 1
# define TRUE 0

// ----------------------------------------------


// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call, as well as the string
// returned by pokemon_name (from pokemon.h).
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.
struct pokedex {
    struct dexnode *head;
    struct dexnode *current_node;
};


// You don't have to use the provided struct dexnode, you are free to
// make your own struct instead.
//
// If you use the provided struct dexnode, you will need to add fields
// to it to store other information.
struct dexnode {
    Pokemon pokemon;
    struct dexnode *next;
    int found;
};


// ----------------------------------------------
// Add your own structs here.
// ----------------------------------------------




// ----------------------------------------------
// Add prototypes for your own functions here.


    static void add_to_pokedex(Pokedex pokedex, struct dexnode *create_new_dexnode);
static void print_pokemon_id(int id);
static void name_to_asterisks(char str[]);
static void found_pokemon_details(Pokedex pokedex, Pokemon pokemon);
static void unknown_pokemon_details(Pokedex pokedex, Pokemon pokemon);
static struct dexnode *previous_node(Pokedex pokedex);
static const char *first_type_char(struct dexnode *current_dexnode);
static const char *second_type_char(struct dexnode *current_dexnode);   
static struct dexnode *last_node(Pokedex pokedex);
static int different_first_type(Pokedex pokedex, struct dexnode *curr);
static int different_second_type(Pokedex pokedex, struct dexnode *curr);
// ----------------------------------------------

// Creates a new dexnode struct and returns a pointer to it.
static struct dexnode *create_new_dexnode(Pokemon pokemon);


// You need to implement the following functions in their stages.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h


// Creates a new Pokedex, and returns a pointer to it.
// Note: you will need to modify this function.
Pokedex new_pokedex(void) {
    // Malloc memory for a new Pokedex, and check that the memory
    // allocation succeeded.
    Pokedex pokedex = malloc(sizeof(struct pokedex));
    assert(pokedex != NULL);

    // Set the head of the linked list to be NULL.
    // (i.e. set the Pokedex to be empty)
    pokedex->head = NULL;
    pokedex->current_node = NULL;
    return pokedex;
}

// Create a new dexnode struct and returns a pointer to it.
//
// This function should allocate memory for a dexnode, set its pokemon
// pointer to point to the specified pokemon, and return a pointer to
// the allocated memory.
static struct dexnode *create_dexnode(Pokemon pokemon) {
    struct dexnode *create_new_dexnode = malloc(sizeof(struct dexnode));
    create_new_dexnode->pokemon = pokemon;
    create_new_dexnode->next = NULL;
    create_new_dexnode->found = FOUND;
    return create_new_dexnode;

    printf("The create_new_dexnode function has not been implemented yet!\n");

    return NULL;
}

//////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                        //
//////////////////////////////////////////////////////////////////////

// Add a new Pokemon to the Pokedex.
void add_pokemon(Pokedex pokedex, Pokemon pokemon) {

    // Note: you should use the create_new_dexnode function here, and add
    // the newly-created dexnode to the end of the linked list of
    // dexnodes in the Pokedex.
    struct dexnode *create_new_dexnode = create_dexnode(pokemon);
    add_to_pokedex(pokedex, create_new_dexnode);


}


// Print out all of the Pokemon in the Pokedex.
void print_pokedex(Pokedex pokedex) {

    if (pokedex != NULL && pokedex->head != NULL) {
        struct dexnode *current = pokedex->head;
        while (current != NULL) {
            if (current == pokedex->current_node) {
                printf("--> ");
            } else {
                printf("    ");
            }
            printf("#");
            print_pokemon_id(pokemon_id(current->pokemon));
            printf(": ");
            if (current->found == FOUND) {
                printf("%s \n", pokemon_name(current->pokemon));
            } else if (current->found == UNKNOWN) {
                name_to_asterisks(pokemon_name(current->pokemon));
            }
            current = current->next;
        }
    }
    

}

// Print out the details of the currently selected Pokemon.
void detail_current_pokemon(Pokedex pokedex) {
    
    if (pokedex->head == NULL) {
        return;
    } else {
        if (pokedex->current_node->found == FOUND) {
            found_pokemon_details(pokedex, pokedex->current_node->pokemon);
        } else if (pokedex->current_node->found == UNKNOWN) {
            unknown_pokemon_details(pokedex, pokedex->current_node->pokemon);
        }
   
    }

}

// Return the currently selected Pokemon.
Pokemon get_current_pokemon(Pokedex pokedex) {
        
    if (pokedex->head == NULL) {
        fprintf(stderr, "exiting because Pokedex currentently contains zero pokemon\n");
        exit(1);
    } else {
        return pokedex->current_node->pokemon;
    }   

}



// Change the currently selected Pokemon to be the next Pokemon in the Pokedex.
void next_pokemon(Pokedex pokedex) {
    if (pokedex->head != NULL) {
        if (pokedex->current_node->next != NULL) {
            pokedex->current_node = pokedex->current_node->next;
        }
    }
    

}

// Change the currently selected Pokemon to be the previous Pokemon in the Pokedex.
void prev_pokemon(Pokedex pokedex) {
    if (pokedex->head != NULL) {
        pokedex->current_node = previous_node(pokedex);
    }
          

}

// Change the currently selected Pokemon to be the Pokemon with the ID `id`.
void jump_pokemon(Pokedex pokedex, int id) {

    struct dexnode *current = pokedex->head;
    while (current != NULL) {
        if (pokemon_id(current->pokemon) == id) {
            pokedex->current_node = current;
        }
        current = current->next;
    }


}

//////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                        //
//////////////////////////////////////////////////////////////////////

// Sets the currently selected pokemon's "found" status
void set_current_pokemon_found(Pokedex pokedex, int found) {
    if (pokedex->head != NULL) {
        pokedex->current_node->found = FOUND;
    }
}
    



// Add a pokemon before the current pokemon.
void insert_pokemon_before_current(Pokedex pokedex, Pokemon pokemon) {

}

// Return the total number of Pokemon in the Pokedex.
int count_pokemon_of_type(Pokedex pokedex, char *type) {
    
    int count_pokemon_type = 0;
    struct dexnode *current = pokedex->head;
    while (current != NULL) {
        count_pokemon_type++;
        current = current->next;    
    }
    return count_pokemon_type;
}



//////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                        //
//////////////////////////////////////////////////////////////////////


// Remove the currently selected Pokemon from the Pokedex.
void remove_pokemon(Pokedex pokedex) {

    if (pokedex->head == NULL) {
        return;
    }   
    struct dexnode *last = last_node(pokedex);
    struct dexnode *previous = previous_node(pokedex);
    
    if (pokedex->head == last) {
        
        pokedex->current_node = NULL;
        destroy_pokemon(last->pokemon);
        free(last);
        pokedex->head = NULL;
        
    } else if (pokedex->current_node == pokedex->head) {
        // Removes the first dexnode
        pokedex->current_node = pokedex->head->next;
        destroy_pokemon(pokedex->head->pokemon);
        free(pokedex->head);
        pokedex->head = pokedex->current_node;
        
    } else if (pokedex->current_node == last) {
        // Removes the last dexnode
        pokedex->current_node = previous;
        previous->next = NULL;
        destroy_pokemon(last->pokemon);
        free(last);
        
    } else {
        // Removes any other dexnode
        previous->next = pokedex->current_node->next;
        destroy_pokemon(pokedex->current_node->pokemon);
        free(pokedex->current_node);
        pokedex->current_node = previous->next;
    }    
}

// Destroy the given Pokedex and free all associated memory.
void destroy_pokedex(Pokedex pokedex) {
    // Note: there is no fprintf or exit(1) in this function, as the
    // Stage 1 autotests call destroy_pokedex but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1, rather than exit).
    
    struct dexnode *current = pokedex->head;
    while (current != NULL) {
        destroy_pokemon(current->pokemon);
        struct dexnode *temp = current;         
        current = current->next;            
        free(temp);                 
    }
    free(pokedex); 
}


// Prints out all types of found Pokemon stored in the Pokedex
void show_types(Pokedex pokedex) {

    struct dexnode *current = pokedex->head;
    while (current != NULL) {          
        int check_first_type = different_first_type(pokedex, current);
        if (check_first_type == TRUE) {
             
            const char *first_type = first_type_char(current); 
            printf("%s\n", first_type);
        }    
        int check_second_type =  different_second_type(pokedex, current);
        if (check_second_type == TRUE) {            
            
            const char *second_type = second_type_char(current);
            printf("%s\n", second_type);
        }
        current = current->next;
    }
}


// Return the number of Pokemon in the Pokedex that have been found.
int count_found_pokemon(Pokedex pokedex) {

    int total_found_count = 0;
    struct dexnode *current = pokedex->head;
    while (current != NULL) {
        if (current->found == FOUND) {
            total_found_count++;
        } 
        current = current->next;    
    }
    return total_found_count;
}

// Return the total number of Pokemon in the Pokedex.
int count_total_pokemon(Pokedex pokedex) {

    int total_pokemon_count = 0;
    struct dexnode *current = pokedex->head;
    while (current != NULL) {
        total_pokemon_count++;
        current = current->next;    
    }
    return total_pokemon_count;
}


// NOTE: Make sure you submit ass2_pokedex before completing these.
//////////////////////////////////////////////////////////////////////
//                     Stage 4 Extension Functions                  //
//////////////////////////////////////////////////////////////////////

/*
 * Saves a pokedex to a text file
 * Use the functions in ext_save.h to save the contents to a file
 */
void save_pokedex(Pokedex pokedex, char *filename) {
    fprintf(stderr, 
    "exiting because you have not implemented the save_pokedex function\n");
    exit(1);

}

/*
 * Loads a pokedex from a text file
 * Use the functions in ext_save.h to load the text from a file
 */
Pokedex load_pokedex(char *filename) {
    fprintf(stderr, 
    "exiting because you have not implemented the load_pokedex function\n");
    exit(1);

    return NULL;
}

//////////////////////////////////////////////////////////////////////
//                     Stage 5 Extension Functions                  //
//////////////////////////////////////////////////////////////////////

// Create a new Pokedex which contains only the Pokemon of a specified
// type from the original Pokedex.
Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    fprintf(stderr, 
    "exiting because you have not implemented the get_pokemon_of_type function\n");
    exit(1);
}

// Create a new Pokedex which contains only the Pokemon that have
// previously been 'found' from the original Pokedex.
Pokedex get_found_pokemon(Pokedex pokedex) {
    fprintf(stderr, 
    "exiting because you have not implemented the get_found_pokemon function\n");
    exit(1);
}

// Create a new Pokedex containing only the Pokemon from the original
// Pokedex which have the given string appearing in its name.
Pokedex search_pokemon(Pokedex pokedex, char *text) {
    fprintf(stderr, 
    "exiting because you have not implemented the search_pokemon function\n");
    exit(1);
}

// Free's the current sub-list and returns the original pokedex state, 
// prior to the search
Pokedex end_search(Pokedex sub_pokedex) {
    fprintf(stderr, "exiting because you have not implemented the end_search function\n");
    exit(1);
}





// Add definitions for your own functions here.
                                                                                        

                          
// Adds the dexnode to the end of the pokedex

static void add_to_pokedex(Pokedex pokedex, struct dexnode *create_new_dexnode) {
    if (pokedex->head == NULL) {
        pokedex->head = create_new_dexnode;
        pokedex->current_node = create_new_dexnode;
    } else {
        struct dexnode *current = pokedex->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = create_new_dexnode;
    }
}      

              
// Prints out the pokemon id correctly

static void print_pokemon_id(int id) {
    if (id >= 0 && id <= 9) {
        printf("00%d", id);
    } else if (id >= 10 && id <= 99) {
        printf("0%d", id);
    } else if (id >= 100 && id <= 999) {
        printf("%d", id);
    }
}              
              
// Converts pokemon's first type to a string of characters

static const char *first_type_char(struct dexnode *current_dexnode) {
    return type_code_to_str(pokemon_first_type(current_dexnode->pokemon));
}   
                    
// Converts pokemon's second type to a string of characters
 
static const char *second_type_char(struct dexnode *current_dexnode) {
    return type_code_to_str(pokemon_second_type(current_dexnode->pokemon));
}                                                               


// Converts the name of pokemon to asterisks if it is an UNKNOWN pokemon
static void name_to_asterisks(char str[]) {
        
    int length_of_name = 0;
    while ((str[length_of_name] >= 'A' && str[length_of_name] <= 'Z') ||
        (str[length_of_name] >= 'a' && str[length_of_name] <= 'z') ||
        (str[length_of_name] >= ' ' && str[length_of_name] <= '-')) {
        length_of_name++;
    }
    
    int i=0;
    while (i < length_of_name) {
        printf("*");
        i++;
    }
    printf("\n");
}


// Prints in details of the found pokemon

static void found_pokemon_details(Pokedex pokedex, Pokemon pokemon) {
    printf("ID: "); 
    print_pokemon_id(pokemon_id(pokedex->current_node->pokemon));   
    printf("\n"); 
    printf("Name: %s\n", pokemon_name(pokedex->current_node->pokemon));   
    printf("Height: %lf m\n", pokemon_height(pokedex->current_node->pokemon));   
    printf("Weight: %lf kg\n", pokemon_weight(pokedex->current_node->pokemon));            
    const char *first_type = first_type_char(pokedex->current_node);
    printf("Type: %s ", first_type);   
    const char *second_type = second_type_char(pokedex->current_node);
    if (pokemon_second_type(pokedex->current_node->pokemon) != NONE_TYPE) {
        printf("%s\n", second_type);
    } else {
        printf("\n");
    }
}

// Prints asterisks and dashes for the unknown pokemon

static void unknown_pokemon_details(Pokedex pokedex, Pokemon pokemon) {
    printf("ID: "); 
    print_pokemon_id(pokemon_id(pokedex->current_node->pokemon));   
    printf("\n");    
    printf("Name: ");
    name_to_asterisks(pokemon_name(pokedex->current_node->pokemon));
    printf("Height: --\n");    
    printf("Weight: --\n");
    printf("Type: --\n"); 
}

// Returns the node before the current node

static struct dexnode *previous_node(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        return NULL;
    } else {
        struct dexnode *previous = pokedex->head; 
        if (pokedex->current_node == pokedex->head) {
            previous = pokedex->head;
        } else {   
            while (previous->next != pokedex->current_node) {
                previous = previous->next;
            }
        }
        return previous;
    }
}
    
// Loops through code and checks if the pokemon's second type is repeated earlier
static int different_second_type(Pokedex pokedex, struct dexnode *current) {
    if (pokemon_second_type(current->pokemon) == NONE_TYPE) {
        return FALSE;
    }
    struct dexnode *j = pokedex->head;
    while (j != current) {
        if (pokemon_second_type(current->pokemon) == pokemon_second_type(j->pokemon)) {
            return FALSE;
        }
        if (pokemon_second_type(current->pokemon) == pokemon_first_type(j->pokemon)) {
            return FALSE;
        }
        j = j->next;
    }
    return TRUE;
} 
    
// Returns the last node in the pokedex

static struct dexnode *last_node(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        return NULL;
    } else {
        struct dexnode *last = pokedex->head;
        while (last->next != NULL) {
            last = last->next;
        }
        return last;
    }
}
    
// Loops through code and checks if the pokemon's first type is repeated earlier
static int different_first_type(Pokedex pokedex, struct dexnode *current) {
    struct dexnode *j = pokedex->head;
    while (j != current) {
        if (pokemon_first_type(current->pokemon) == pokemon_first_type(j->pokemon)) {
            return FALSE;
        }
        if (pokemon_first_type(current->pokemon) == pokemon_second_type(j->pokemon)) {
            return FALSE;
        }
        j = j->next;
    }
    return TRUE;
}
