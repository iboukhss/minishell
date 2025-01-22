#include "minishell.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

/*
Description: According to the Github pages :
CTRL + C = SIGINT -> will trigger the function handle_signal that will print a newline and read from it
CTRL + D = SIGQUIT -> sends an EOF signal to the terminal's input stream and readline() will return NULL.
CTRL + \ = SIGQUIT -> is ignored using signal(SIGQUIT,SIG_IGN)
*/

void handle_signal(int sig)
{
    (void) sig; //only added to avoid unused parameter warning
    write(0, "\n", 1); //without newline readline will read/write on the same line in the terminal
    rl_replace_line("", 0); //replace current line
    rl_on_new_line();
    rl_redisplay();
}

/*
Description: Setting up the signals to be handled.
- action.sa_handler: Specifies the handler function that will be called when the signal occurs. 
- signal() : used to ignore the SIGQUIT signal
*/

void setup_signals(void)
{
    struct sigaction action;
    
    action.sa_handler = handle_signal; 
    //action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, NULL);
    signal(SIGQUIT, SIG_IGN); //ignoring SIGQUIT -> 'CTRL + \'
    //for debugging
    //printf("PID : %d\n", getpid());
}
