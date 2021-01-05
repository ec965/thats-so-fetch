#pragma once

//ASCII escape character color codes
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YLW "\e[0;33m"
#define BLU "\e[0;34m"
#define MGN "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define BLK2 "\e[0;90m"
#define RED2 "\e[0;91m"
#define GRN2 "\e[0;92m"
#define YLW2 "\e[0;93m"
#define BLU2 "\e[0;94m"
#define MAG2 "\e[0;95m"
#define CYN2 "\e[0;96m"
#define WHT2 "\e[0;97m"

// trim spaces, '\t', '\r', '\n' from a string
void trim_whitespaces(char* str);
// convert seconds into a string of HH:MM:SS
char* seconds_to_str(long time);
// For a given file with a structure of:
// file:garf.txt
/*
1 * cat:garfield
2 * dag:odie
3 * man:john
 */
// Gets the line defined by `lines` (line 1 = index 0) as a string.
// Trims the given number of characters from the front and back of the string.
// Removes white spaces from the front and back of the trimmed string.
// If an error is encountered, the `err_name` string will be returned instead.
char* get_file_info(char* file_name, char* err_name, int lines, int trim_front, int trim_back );
// Runs `get_file_info()` on `/etc/os-release` to get the OS name
char* get_osname();
// Runs `get_file_info()` on `/proc/cpuinfo` to get the CPU name
char* get_cpu();
// Gets the shell name from the environmental variable
char* get_shell();
// Helper function to check if an environmental variable exists before printing it
void check_getenv(char* env, char* label);
