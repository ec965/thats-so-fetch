#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
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

void trim_whitespaces(char* str){
    int i=0, start=0, end=strlen(str)-1;

    while(str[start]==' ' 
        || str[start]=='\t' 
        || str[start]=='\r' 
        || str[start]=='\n')
    {
        start++;
    }
    if (start != 0){
        while(str[i+start] != '\0'){
            str[i] = str[i+start];
            i++;
        }
    }
    
    if (i != 0){ // if `i` isn't zero then the above code ran
        end = i-1;
    }
    while (str[end] == ' '
        || str[end] == '\t'
        || str[end] == '\n'
        || str[end] == '\r')
    {
        end--;
    }
    str[end+1] = '\0';
}


char* seconds_to_str(long time){
    int hour = time/3600;
    int min = (time%3600)/60;
    int sec = (time%3600)%60;

    char* str = calloc(16, sizeof(char));
    
    sprintf(str, "%d:%02d:%02d", hour, min, sec);
    return str;
}

char* get_file_info(char* file_name, char* err_name, int lines, int trim_front, int trim_back ){
    FILE *fp;
    char* buffer = calloc(128, sizeof(char));
    int i, len;

    fp=fopen(file_name, "r");
    if (fp == NULL || buffer == NULL){
        return err_name; 
    }
    
    i=0; // find the PRETTY_NAME
    while(fgets(buffer, 128*sizeof(char), fp) != NULL && i<lines){
        i++;
    }

    fclose(fp);

    len = strlen(buffer);
    for(i=0; i<len; i++){
        buffer[i] = buffer[i + trim_front];
    }
    buffer[len - trim_back] = '\0';

    trim_whitespaces(buffer);

    return buffer;
}

char* get_osname(){
    return get_file_info("/etc/os-release", "Operating System", 4, 13, 15);
}

char* get_cpu(){
    return get_file_info("/proc/cpuinfo", "CPU", 4, 12, 12);
}

char* get_shell(){
    char* shell = getenv("SHELL");
    char* dptr = strtok(shell, "/"); // delimit with `/`

    // take the last piece of the delimited string
    while (dptr != NULL) {
        shell = dptr;
        dptr = strtok(NULL, "/");
    }
     
    return shell;
}

int main(){
    struct utsname osinfo;
    struct sysinfo mem;
    uname(&osinfo);
    sysinfo(&mem);

    char* uptime = seconds_to_str(mem.uptime);
    char* osname = get_osname(); 
    char* cpu = get_cpu();

    printf("%s@%s\n", getenv("USER"), osinfo.nodename);
    printf("Kernel\t%s %s\n", osinfo.sysname, osinfo.release);
    printf("OS\t%s %s\n", osname,osinfo.machine);
    printf("Uptime\t%s\n", uptime);
    
    printf("Shell\t%s\n", get_shell());
    char* de = getenv("XDG_CURRENT_DESKTOP");
    if (de != NULL){
        printf("DE\t%s\n", de);
    }
    printf("Lang\t%s\n", getenv("LANG"));
    
    printf("Memory\t%lu/%lu MB\n", (mem.freeram)/1000000, mem.totalram/1000000);
    printf("CPU\t%s\n", cpu);
    
    // print colors
    printf(BLK"███"BLK);
    printf(RED"███"RED);
    printf(GRN"███"GRN);
    printf(YLW"███"YLW);
    printf(BLU"███"BLU);
    printf(MGN"███"MGN);
    printf(CYN"███"CYN);
    printf(WHT"███"WHT"\n");
    printf(BLK2"███"BLK2);
    printf(RED2"███"RED2);
    printf(GRN2"███"GRN2);
    printf(YLW2"███"YLW2);
    printf(BLU2"███"BLU2);
    printf(MAG2"███"MAG2);
    printf(CYN2"███"CYN2);
    printf(WHT2"███"WHT2"\n");


    free(uptime);
    free(osname);
    free(cpu);
    return 0;
}
