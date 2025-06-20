#include <stdlib.h>

struct SeaFlag {
    char* name;
    char* short_name;
    bool is_required;

    char** value;
    struct SeaFlag* next;
};

struct SeaFlagSet {
    struct SeaFlag* firstFlag;

    char* programName;
    char* programVersion;
    char* programAuthor;
    char* programDescription;
};

#define SEAFLAGS_UNKNOWN_FLAG 0b00000001
#define SEAFLAGS_UNKNOWN_POSITIONAL_ARG 0b00000010
#define SEAFLAGS_MISSING_REQUIRED_FLAG 0b00000100


void seaflags_init(struct SeaFlagSet* flags, char* programName, char* programVersion, char* programAuthor, char* programDescription);
void seaflags_add_flag(struct SeaFlagSet* flags, char* name, char* short_name, bool is_required, char** value);
int seaflags_parse(struct SeaFlagSet* flags, int argc, char** argv);
void seaflags_free(struct SeaFlagSet* flags);
