#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../includes/seaflags.h"

#define SEAFLAGS_DEBUG

void seaflags_init(struct SeaFlagSet *flags, char *programName, char *programVersion, char *programAuthor, char *programDescription) {
    flags->firstFlag = NULL;

    flags->programName = programName;
    flags->programVersion = programVersion;
    flags->programAuthor = programAuthor;
    flags->programDescription = programDescription;
}

void seaflags_add_flag(struct SeaFlagSet *flags, char *name, char *short_name, bool is_required, char** value) {
    struct SeaFlag* flag = malloc(sizeof(struct SeaFlag));
    flag->name = name;
    flag->short_name = short_name;
    flag->is_required = is_required;
    flag->value = value;
    flag->next = NULL;

    if (flags->firstFlag == NULL) {
        flags->firstFlag = flag;
        return;
    }

    struct SeaFlag* current = flags->firstFlag;
    if(current == NULL) {
        flags->firstFlag = flag;
        return;
    }
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = flag;
}

void seaflags_free(struct SeaFlagSet *flags){
    struct SeaFlag* current = flags->firstFlag;
    while (current != NULL) {
        struct SeaFlag* next = current->next;
        free(current->name);
        free(current->short_name);
        free(current->value);
        free(current);
        current = next;
    }
    free(flags);
}

struct SeaFlag* _seaflags_find_flag(struct SeaFlagSet *flags, char *name) {
    struct SeaFlag* current = flags->firstFlag;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 || strcmp(current->short_name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int seaflags_parse(struct SeaFlagSet *flags, int argc, char **argv) {
    int i = 1;
    int result = 0;

    #ifdef SEAFLAGS_DEBUG
    printf("Parsing %d arguments\n", argc);
    #endif

    while (i < argc) {
        char* current = argv[i];
        struct SeaFlag* flag = _seaflags_find_flag(flags, current);

        if (flag == NULL) {
            fprintf(stderr, "Unknown flag: %s\n", current);
            result |= SEAFLAGS_UNKNOWN_FLAG;
        }

        if(flag != NULL && i+1 < argc) {
            #ifdef SEAFLAGS_DEBUG
            printf("Setting value for %s to %s\n", current, argv[i+1]);
            #endif

            *(flag->value) = argv[i+1];
            i++;
        }

        i++;
    }

    struct SeaFlag* current = flags->firstFlag;
    while (current != NULL) {
        if (*(current->value) == NULL) {
            if (current->is_required == true) {
                fprintf(stderr, "Missing required flag: %s\n", current->name);
                result |= SEAFLAGS_MISSING_REQUIRED_FLAG;
            }
        }
        current = current->next;
    }

    return result;
}
