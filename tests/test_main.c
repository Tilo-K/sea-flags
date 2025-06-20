#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SEAFLAGS_DEBUG
#include "../includes/seaflags.h"

int test_basic_create() {
    printf("Running test_basic_create\n");
    struct SeaFlagSet flags;
    seaflags_init(&flags, "Sea Flag Test", "0.0.0", "Tilo-K" , "A test for the seaflags library");
    char* name = NULL;
    seaflags_add_flag(&flags, "name", "n", true, &name);

    if (flags.firstFlag == NULL) {
        printf("Flags not created\n");
        return 1;
    }

    if (flags.firstFlag->name == NULL) {
        printf("Flag name not set\n");
        return 1;
    }

    if (flags.firstFlag->short_name == NULL) {
        printf("Flag short name not set\n");
        return 1;
    }

    if (flags.firstFlag->is_required != true) {
        printf("Flag is_required not set\n");
        return 1;
    }

    if (flags.firstFlag->value == NULL) {
        printf("Flag value not set\n");
        return 1;
    }

    return 0;
}

int test_get_flag_value() {
    printf("Running test_get_flag_value\n");
    struct SeaFlagSet flags;
    seaflags_init(&flags, "Sea Flag Test", "0.0.0", "Tilo-K" , "A test for the seaflags library");
    char* name = NULL;

    printf("Adding flag\n");
    seaflags_add_flag(&flags, "--name", "-n", true, &name);
    printf("Parsing\n");
    seaflags_parse(&flags, 3, (char*[]){"./test", "--name", "test"});
    printf("Parsed\n");


    if (name == NULL || strcmp(name, "test") != 0) {
        printf("Flag value name not set, found %s\n", name);
        return 1;
    }

    return 0;
}

int test_missing_required_flag() {
    printf("Running test_missing_required_flag\n");
    struct SeaFlagSet flags;
    seaflags_init(&flags, "Sea Flag Test", "0.0.0", "Tilo-K" , "A test for the seaflags library");
    char* name = NULL;

    printf("Adding flag\n");
    seaflags_add_flag(&flags, "--name", "-n", true, &name);
    printf("Parsing\n");
    int result = seaflags_parse(&flags, 1, (char*[]){"./test"});
    printf("Parsed\n");

    if ((result & SEAFLAGS_MISSING_REQUIRED_FLAG) > 0) {
        return 0;
    }

    printf("Missing required flag not detected %d\n", result);

    return 1;
}

int main(void) {
    printf("Running main\n");

    int result = test_basic_create();
    if (result != 0) {
        printf("Basic Test failed with result %d\n", result);
        return 1;
    }

    result = test_get_flag_value();
    if (result != 0) {
        printf("Get Flag Value Test failed with result %d\n", result);
        return 1;
    }

    result = test_missing_required_flag();
    if (result != 0) {
        printf("Missing Required Flag Test failed with result %d\n", result);
        return 1;
    }

    return 0;
}
