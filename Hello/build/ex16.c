#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int h;
    int w;
};

struct Person *Person_create(char *name, int age, int height, int weight){
    struct Person* who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->h = height;
    who->w = weight;

    return who;
}

void Person_destroy(struct Person *who){
    assert(who != NULL);

    printf("dectrying: %s", who->name);
    free(who->name);
    free(who);
}

void Person_print(struct Person *who){
    printf("name: %s\n", who->name);
}

int main(int argc, char* argv[]){
    struct Person *joe = Person_create("Joe Alex", 32, 32, 140);
    struct Person *frank = Person_create("Frank Black", 45, 65, 170);

    printf("Joe is at mem location: %p:\n", joe);
    printf("Frank is at mem location: %p:\n", frank);
    
    frank->age = 87;
    Person_print(frank);

    Person_destroy(joe);
    Person_destroy(frank);
}
