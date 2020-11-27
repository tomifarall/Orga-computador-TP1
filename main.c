#define _POSIX_C_SOURCE 200112L

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>

#ifndef USE_MIPS32

#include "mcfunctions.h"

#else 

#include <unistd.h>

extern unsigned int mcm(unsigned int m, unsigned int n);
extern unsigned int mcd(unsigned int m, unsigned int n);

#endif /* USE_MIPS32 */ 

#define SUCCESS 0
#define ERROR -1

void display_help(){
	fprintf(stdout, "%s \n", "Usage:");
	fprintf(stdout, "   %s \n", "common -h");
	fprintf(stdout, "   %s \n", "common -V");
	fprintf(stdout, "   %s \n", "common [options] M N");
	fprintf(stdout, "%s \n", "Options:");
	fprintf(stdout, "   %s \n", "-h, --help      Prints usage information.");
	fprintf(stdout, "   %s \n", "-V, --version   Prints version information.");
	fprintf(stdout, "   %s \n", "-o, --output    Path to output file.");
	fprintf(stdout, "   %s \n", "-d, --divisor   Just the divisor.");
	fprintf(stdout, "   %s \n", "-m, --multiple  Just the multiple.");
	fprintf(stdout, "%s\n \n","Examples:");
	fprintf(stdout, "   %s\n", "     common -o - 256 192");
}

int main(int argc, char **argv){ 
	if (argc > 6){
		fprintf(stderr,"%s \n","Invalid command");
		return ERROR;
	}
	static struct option long_options[] = {
        {"divisor", no_argument, 0, 'd' },
        {"output", required_argument, 0, 'o' },
        {"multiple", no_argument, 0, 'm' },
        {"help", no_argument, 0,'h'},
        {"version", no_argument, 0, 'V'},
    };
	FILE* output_file;
	int option_index = 0;
	bool multiple = false;
    bool divisor = false;
    bool received_output_command = false;
    int offset = 1;
	int option;
	while ((option = getopt_long(argc, argv, "hVo:dm", long_options, &option_index)) != -1) {
    	switch (option) {
    		case 'm':
    			multiple = true;
                offset++;
    			break;
    		case 'o':
                if (strcmp(optarg, "-") == 0) output_file = stdout;
    			else output_file = fopen(optarg, "wt");
                offset += 2;
                received_output_command = true;
    			break;
    		case 'h':
    			display_help();
    			return SUCCESS;
    		case 'V':
    			fprintf(stdout,"%s \n", "Version 1.3");
    			return SUCCESS;
            case 'd':
                divisor = true;
                offset++;
                break;
            default:
				return ERROR;
        }
    }
    if (!received_output_command) output_file = stdout;
    int n1 = atoll(argv[offset]);
    int n2 = atoll(argv[offset + 1]);
    if (n1 > INT_MAX || n1 < 2 || n2 > INT_MAX || n2 < 2){
		fprintf(stderr, "%s \n", "Invalid numbers");
        fclose(output_file);
		return ERROR;
    }
    int result;
    if (!multiple && !divisor){
        result = mcd(n1, n2);
        int result2 = mcm(n1, n2);
        fprintf(output_file, "%d\n%d\n", result, result2);
        fclose(output_file);
        return SUCCESS;
    }
    else if (divisor) result = mcd(n1, n2);
	else result = mcm(n1, n2);
    fprintf(output_file, "%d\n", result);
    fclose(output_file);
	return SUCCESS;
}
