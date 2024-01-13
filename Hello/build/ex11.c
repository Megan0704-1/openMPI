#include <stdio.h>

int main(int argc, char* argv[]){
    int nums[4] = {0};
    char name[4] = {'a'};

    printf("raw:\n");
    printf("numbers: %d, %d, %d, %d\n", nums[0], nums[1], nums[2], nums[3]);
    printf("chars: %c, %c, %c, %c\n", name[0], name[1], name[2], name[3]);
    printf("like string %s\n", name);

    // set up numbers
    for(int i=0; i<4; i++){
        nums[i] = i;
    }
    name[0] = 'M';
    name[1] = 'e';
    name[2] = 'g';
    name[3] = '\0';


    printf("after set up:\n");
    printf("numbers: %d, %d, %d, %d\n", nums[0], nums[1], nums[2], nums[3]);
    printf("chars: %c, %c, %c, %c\n", name[0], name[1], name[2], name[3]);
    printf("like string: %s\n", name);

    // another way of string
    char* another = "Meg";
    printf("another way: %s\n", another);
    printf("antoehr char: %c, %c, %c, %c\n", another[0], another[1], another[2], another[3]);

    return 0;
}
