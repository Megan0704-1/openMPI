#include <stdio.h>

int main(int argc, char* argv[]){
    int distance = 100;
    float power = 2.345f;
    double super_power = 5678.233;
    char initial = 'A';
    char first_name[] = "Megan";
    char last_name[] = "Kuo";

    printf("You are %d miles away.\n", distance);
    printf("My name is %s %s\n", first_name, last_name);
    printf("printing e: %e\n", super_power);

    char nul_byte = '\0';
    int percentage = 100 * nul_byte;
    printf("Strange output: %d%%.\n", percentage);
}
