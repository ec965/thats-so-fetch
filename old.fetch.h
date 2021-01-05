#pragma once
#define USERSTRING_MAX 72
#define TIMESTRING_MAX 12
#define OSSTRING_MAX 62
#define CPUSTRING_MAX 72

// takes a pointer to a time char buffer and a time in seconds
// returns 0 if ok, return -1 if error
int seconds_to_str(char*, long);

// trim the leading chararacters from the string
void trim_leading(char*, char);

// trim the trailing characters from the string
void trim_trailing(char*, char);

// trim all trailing and leading whitespaces
// this includes spaces, tabs, new lines, and carriage returns
// ' ', '\t', '\n', '\r'
void trim_whitespaces(char*);

// takes a string that is a key value pair:
// for example: NAME='Odie'
// key and value will point to the resulting strings after delimination
// returns 0 for ok, returns -1 for error
int delimit_key_value(char*, char*, char*, char*);

// extract a key value pair from a file with key value pairs
// for example a file contains:
// example.txt
/*
Dog:Odie
Cat:Garfield
Man:John
*/
// to extract the value of 'Dog' use:
// extract_key_value("path/to/example.txt", "Dog", ":", output);
// where output is a pointer to the output variable
// returns 0 for ok, returns -1 for error
int extract_key_value(char*, char*, char*, char*);

// get the OS name
// return -1 if name could not be found or error
// return 0 if ok
int get_os(char*);

// get the OS name
// return -1 if name could not be found or error
// return 0 if ok
int get_cpu(char*);
