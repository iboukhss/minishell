/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:37:11 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/24 19:34:00 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_sigint_received = 0;

/*
 * SIGINT signal handler, we avoid using readline functions here because they
 * are not signal-safe.
 */
void	sigint_handler(int sig)
{
	(void)sig;
	g_sigint_received = 1;
}

/*
 * This function is used by rl_event_hook to handle readline operations safely
 * outside of the main signal handler.
 */
int	handle_signals(void)
{
	if (g_sigint_received)
	{
		g_sigint_received = 0;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return (0);
}

/*
 * Prepares the signals for the shell, using sigaction over signal as it is
 * considered a best practice.
 */
void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/*
 * Prepares necessary readline variables for signals.
 * Disables readline's built-in signal handling.
 * Sets a custom readline event hook.
 */
void	setup_readline(void)
{
	rl_catch_signals = 0;
	rl_event_hook = handle_signals;
}
