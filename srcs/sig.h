/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:58:25 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/31 17:59:14 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

// Signals
void	sigint_handler(int sig);
int		handle_signals(void);
void	setup_signal_handlers(void);
void	setup_readline(void);

#endif
