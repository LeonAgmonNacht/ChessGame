#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

# define BUF_SIZE 2048
# define SIG_CONT_MSG "Process %d continues"
# define SIG_TERM_MSG "Process %d finishes. Symbol %c. Instances %d.\n"
# define F_O_ERR_MSG "Error openning file"
# define F_ERR_MSG "Error with file"
# define SIG_CONT_SET_ERR "Error setting SIGCONT"
# define SIG_TERM_SET_ERR "Error setting SIGTERM"
# define FOUND_SYM_MSG "Process %d, symbol %c, going to sleep\n"

int num_symbols = 0;
char buffer[BUF_SIZE];
char symbol;

void handle_signal(int sig) {
    pid_t pid = getpid();
    if (sig == SIGTERM) {
        printf(SIG_TERM_MSG, pid, symbol, num_symbols);
        abort();
    }
    else if (sig == SIGCONT) {
        printf(SIG_CONT_MSG, pid);
    }
}

int main(int argc, const char * argv[]) {
    
    symbol = *argv[2];
    int c_read = 0;
    pid_t pid = getpid();
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf(F_O_ERR_MSG);
        return 1;
    }
    
    // Catch signals:
    if (signal(SIGTERM, handle_signal) == SIG_ERR) {
        printf(SIG_TERM_SET_ERR);
        return 1;
    }
    if (signal(SIGCONT, handle_signal) == SIG_ERR) {
        printf(SIG_CONT_SET_ERR);
        return 2;
    }
    
    // While can read from file:
    while ((c_read = fread(buffer, sizeof(char), BUF_SIZE, f)) > 0)
        for (int i = 0; i<c_read; i++)
            if (buffer[i] == symbol) {
                num_symbols += 1;
                printf(FOUND_SYM_MSG, pid, symbol);
                raise(SIGSTOP);
            }
                
    if (ferror(f)) {
        printf(F_ERR_MSG);
        return 3;
    }
    
    if (!c_read) {
        raise(SIGTERM);
    }
}
