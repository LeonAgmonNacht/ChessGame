#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

# define SYM_COUNT_PROG_PATH "./sym_count"
# define SYM_ARGV_SYMBOL_INDEX 2
# define COUNT_BND_ARGV_INDEX 3
# define FILE_DATA_ARGV_INDEX 1
# define MALLOC_ERR_MSG "Malloc error, exiting"
# define EXECVP_ERR_MSG "execvp error"

int main(int argc, const char * argv[]) {
    // Init:
    int count_bound = atoi(argv[COUNT_BND_ARGV_INDEX]);
    int sym_count = strlen(argv[SYM_ARGV_SYMBOL_INDEX]);
    int num_proc = sym_count;
    // Dynamic alloc arrays:
    int* pids = (int*)malloc(sym_count*sizeof(int*));
    int * stop_counters = (int*)malloc(sym_count*sizeof(int));
    
    if (pids == NULL || stop_counters == NULL) {
        printf(MALLOC_ERR_MSG);
        return 1;
    }
    // Init processes and counters:
    char* symbol = (char*)malloc(2);
    if (symbol == NULL) {
        printf(MALLOC_ERR_MSG);
        return 1;
    }
    symbol[1] = '\0';
    for (int i = 0; i<sym_count; i++) {
        pid_t c_pid = fork();
        if (c_pid == 0) { // Child
            symbol[0] = argv[SYM_ARGV_SYMBOL_INDEX][i];
            char* c_argv[] = {SYM_COUNT_PROG_PATH, argv[FILE_DATA_ARGV_INDEX], symbol, NULL};
            if (execvp(SYM_COUNT_PROG_PATH, c_argv) == -1) {
                printf(EXECVP_ERR_MSG);
		perror("Error: ");
                return 2;
            }
        }
        else { // Parent
            pids[i] = c_pid;
        }
    }
    free(symbol);
    printf("Here a");
    // Main loop:
    while (num_proc>0) {
        sleep(1);
        for (int i = 0; i<sym_count; i++) {
            int status;
	    printf("Here");
            int r_pid = waitpid(pids[i], &status, WNOHANG);
	    printf("p:%d", r_pid);
            if (r_pid < 0 && WIFSTOPPED(status)) { // Proc is stopped
                stop_counters[i] += 1;
                if (stop_counters[i] == count_bound) {
                    num_proc -= 1;
                    kill(pids[i], SIGTERM);
                }
                else kill(pids[i], SIGCONT);
            }
        }
    }
}