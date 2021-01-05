#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include "fetch.h"

int main(){
    struct utsname sys_info;
    char username[USERSTRING_MAX];
    struct sysinfo uptime_mem;
    char time_string[TIMESTRING_MAX];
    char os_string[OSSTRING_MAX];
    char cpu_string[CPUSTRING_MAX];

    if (uname(&sys_info) != 0){
        printf("Error getting uname.\n");
        exit(0);
    }

    if (getlogin_r(username, _SC_LOGIN_NAME_MAX) != 0){
        printf("Error getting username.\n");
        exit(0);
    }

    if (sysinfo(&uptime_mem) != 0){
        printf("Error getting memory and ram\n");
        exit(0);
    }
    if (seconds_to_str(time_string, uptime_mem.uptime) != 0){
        printf("Error getting the time string");
        exit(0);
    }

    if (get_os(os_string) != 0){
        printf("Error getting the OS name");
        exit(0);
    }

    if (get_cpu(cpu_string) != 0){
        printf("Error getting cpu name");
        exit(0);
    };

    printf("%s@%s\n\n", username,sys_info.nodename);
    printf("Kernel\t%s %s\n", sys_info.sysname, sys_info.release);
    printf("OS\t%s %s\n", os_string, sys_info.machine);
    printf("Uptime\t%s\n", time_string); // time in seconds
    printf("CPU\t%s\n", cpu_string);
    printf("Memory\t%lu/%lu MB\n\n", (uptime_mem.freeram)/1000000, uptime_mem.totalram/1000000);

    // print colors
    printf("\e[0;30m███\e[0;30m");
    printf("\e[0;31m███\e[0;31m");
    printf("\e[0;32m███\e[0;32m");
    printf("\e[0;33m███\e[0;33m");
    printf("\e[0;34m███\e[0;34m");
    printf("\e[0;35m███\e[0;35m");
    printf("\e[0;36m███\e[0;36m");
    printf("\e[0;37m███\e[0;37m\n");
    printf("\e[0;90m███\e[0;90m");
    printf("\e[0;91m███\e[0;91m");
    printf("\e[0;92m███\e[0;92m");
    printf("\e[0;93m███\e[0;93m");
    printf("\e[0;94m███\e[0;94m");
    printf("\e[0;95m███\e[0;95m");
    printf("\e[0;96m███\e[0;96m");
    printf("\e[0;97m███\e[0;97m\n");

    return 0;
}

int seconds_to_str(char* time_string, long time){
    int hour = time/3600;
    int min = (time%3600)/60;
    int sec = (time%3600)%60;
    if (sprintf(time_string, "%d:%02d:%02d", hour, min, sec) < 0){
        return -1;
    }
    return 0;
}

void trim_leading(char* str, char remove_char){
    int start = 0;
    while(str[start]== remove_char){
        start++;
    }
    if (start != 0){
        int i=0;
        while(str[i+start] != '\0'){
            str[i] = str[i+start];
            i++;
        }
        str[i] = '\0';
    }
}

void trim_trailing(char* str, char remove_char){
    int end = strlen(str)-1;
    while (str[end] == remove_char){
        end--;
    }
    str[end+1] = '\0';
}

void trim_whitespaces(char* str){
    int start = 0;
    while(str[start]==' ' 
        || str[start]=='\t' 
        || str[start]=='\r' 
        || str[start]=='\n')
    {
        start++;
    }
    if (start != 0){
        int i=0;
        while(str[i+start] != '\0'){
            str[i] = str[i+start];
            i++;
        }
        str[i] = '\0';
    }

    int end = strlen(str)-1;
    while (str[end] == ' '
        || str[end] == '\t'
        || str[end] == '\n'
        || str[end] == '\r')
    {
        end--;
    }
    str[end+1] = '\0';
}

int delimit_key_value(char* input, char* delimiter, char* key, char* value){
    char* split_ptr = strtok(input, delimiter);

    if (split_ptr != NULL){
        
        if (sprintf(key, "%s", split_ptr) < 0){
            printf("Error writing the key\n");
            return -1;
        }

        split_ptr = strtok(NULL, delimiter);
        if (sprintf(value, "%s", split_ptr) < 0){
            printf("Error writing the value\n");
            return -1;
        }

        return 0;
    }
    return -1;
}

int extract_key_value(char* file_name, char* find_key, char* delimeter, char* output){
    FILE *fp;
    char buffer[120];

    fp = fopen(file_name, "r");
    if (fp == NULL){
        printf("Error opening the file: %s\n", file_name);
        return -1;
    }
    while(fgets(buffer,120,fp) != NULL){ // read each line into the buffer

        char key_buffer [30];
        char val_buffer [90];
        if (delimit_key_value(buffer, delimeter, key_buffer, val_buffer) != 0){
            printf("Error getting the key value strings using delimiter");
            return -1;
        }

        trim_whitespaces(key_buffer);
        trim_whitespaces(val_buffer);

        if (strcmp(find_key, key_buffer) == 0){
            if (sprintf(output, "%s", val_buffer) < 0){
                return -1;
            }
            return 0;
        }
    }
    return -1;
}

int get_os(char* os_string){
    int status=extract_key_value("/etc/os-release", "PRETTY_NAME", "=", os_string);
    trim_leading(os_string, '\"');
    trim_trailing(os_string, '\n');
    trim_trailing(os_string,'\"');
    return status;
}

int get_cpu(char* cpu_string){
    return extract_key_value("/proc/cpuinfo", "model name", ":", cpu_string);
}
