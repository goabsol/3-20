/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:38:09 by arhallab          #+#    #+#             */
/*   Updated: 2022/01/21 14:50:54 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_msg	*newmsg(char *msg, long t, int id)
{
	t_msg	*new;

	new = (t_msg *)malloc(sizeof(t_msg));
	new->msg = msg;
	new->t = t;
	new->id = id;
	new->next = NULL;
	return (new);
}

int	msgadd(t_msg **msg, t_msg *nmsg)
{
	t_msg	*a;

	if (!msg || !nmsg)
		return (0);
	if (!(*msg))
	{
		*msg = nmsg;
		return (1);
	}
	a = *msg;
	while (a->next)
		a = a->next;
	a->next = nmsg;
	return (1);
}

void	printmsg(t_msg **msg, t_constraints *cons)
{
	if ((*msg)->next || cons->firstmsg)
	{
		printf((*msg)->msg, (*msg)->t, (*msg)->id);
		cons->firstmsg = 0;
		((*msg)->next) && ((*msg) = (*msg)->next);
	}
}
