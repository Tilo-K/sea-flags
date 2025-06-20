# SeaFlags: A Simple C Library for Command Line Argument Parsing

<div style="text-align: center; align-items: center; justify-content: center; display: flex; width: 100%;">
<img src="https://github.com/tilo-k/sea-flags/blob/master/logo.png" alt="SeaFlags Logo" width="300" height="300">
</div>

SeaFlags is a straightforward C library designed for parsing command-line arguments. It offers a simple and efficient way for developers to manage flags and options in their C applications, making command-line interfaces easier to build and maintain.

## Features

*   **Simplified API:** Easy-to-use functions for defining and parsing flags.
*   **Flexible Flag Support:** Handles both short (`-s`) and long (`--long`) argument formats.
<!-- *   **Automatic Help:** Generates `--help` messages. -->
*   **Error Reporting:** Provides clear feedback on parsing issues.

## Getting Started

Here's a basic example demonstrating how to parse a string argument:

```c
#include <seaflags.h>
#include <stdio.h> // Required for printf

int main(int argc, char** argv) {
    struct SeaFlagSet flags;
    // Initialize with program info: name, version, author, description
    seaflags_init(&flags, "Sea Flag Example", "0.0.0", "Tilo" , "Example for the seaflags library");

    char* name = NULL; // Variable to store the parsed --name argument

    // Add a flag: long_name, short_name, is_required, pointer_to_store_value
    seaflags_add_flag(&flags, "--name", "-n", true, &name);

    // Parse the command line arguments
    int result = seaflags_parse(&flags, argc, argv);

    if (result != 0) {
        fprintf(stderr, "Error parsing flags.\n"); // SeaFlags typically prints error details too
        return 1;
    }

    // Access the parsed argument
    printf("Hello, %s!\n", name);


    seaflags_free(&flags); // Free the memory allocated by SeaFlags

    return 0;
}
```

## Contributing

Contributions are welcome. Please refer to the [Code of Conduct](https://tilok.dev/coc).

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
