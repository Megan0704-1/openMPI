#include <stdio.h>

int main(int argc, char* argv[]){
    int i=0;

    // go through each string in argv
    // why am I skipping argv[0]?

    for(i=1; i<argc; i++){
        printf("arg %d: %s\n", i, argv[i]);
    }

    //make out own arr of strings
    char *states[] = {
        "CA", "OI", "UW", "TX"
    };
    int num_states = 4;

    for(int j=0; j<num_states; j++){
        printf("states %d: %s\n", j, states[j]);
    }
}
