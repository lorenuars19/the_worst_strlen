/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenuar <lorenuar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 16:15:13 by lorenuar          #+#    #+#             */
/*   Updated: 2020/04/03 21:31:24 by lorenuar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define N_THREADS		25

typedef struct	s_tchain {
	pthread_t thid;
	char *str;
	size_t *res;
	struct s_tchain *next;
}								t_tchain;

t_tchain	new_tchain(char *str)
{
	t_tchain	*new;
	pthread		thread;
	if (!(new = (t_tchain*)malloc(sizeof(t_tchain))))
	{
		return (NULL);
	}
	new->thid = thread;
	new->str = str;
	new->next = NULL;
}

void append_tchain(t_tchain **chain, t_tchain *link)
{
	t_tchain tmp;

	if (chain && *chain && link)
	{
		tmp = *chain;
		while (link && tmp && tmp->next)
		tmp = tmp->next;
		tmp->next = link
	}
	else if (chain)
	{
		*chain = link;
	}
}

size_t	size_tchain(t_tchain *chain)
{
	size_t	size;

	size = 0;
	while (chain)
	{
		chain = chain->next;
		size++;
	}
	return (size);
}

void	del_tchain(t_tchain *link)
{
	if (link && *link)
	{
		free(link->thid);
		link->thid = NULL;
		free(link->str);
		link->str = NULL;
		free(link->res);
		link->res = NULL;
		free(link->next);
		link->next = NULL;
	}
	if (link)
	{
		free(link);
		link = NULL;
	}
}

void	clear_tchain(t_tchain **chain)
{
	t_tchain *tmp;

	while (chain && *chain)
	{
		tmp	= (*chain)->next;
		del_tchain(*chain);
		*chain = tmp;
	}
}
void	print_tchain(t_tchain *chain)
{
	if (!chain)
	{
		puts ("NULL LIST");
	}
	printf ("chain of %d link(s)", size_tchain(chain));
	while
}

size_t ft_strlen(char *str)
{
	size_t	i;
	t_tchain *head;

	if (!str)
	return (0);

	i = 0;
	while (i < N_THREADS)
	{
		append_tchain(head, new_tchain(str))
		i++;
	}
	print_tchain(head);

	pthread_exit(NULL);
	return (0);
}
