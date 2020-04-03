/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenuar <lorenuar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 16:15:13 by lorenuar          #+#    #+#             */
/*   Updated: 2020/04/04 00:20:46 by lorenuar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#ifndef VERBOSE
# define VERBOSE 0
#endif

#if VERBOSE == 1
# include <stdio.h>
#endif

#ifndef N_THREADS
# define N_THREADS	50
#endif

typedef struct		s_tchain
{
	pthread_t		thid;
	char			*str;
	size_t			res;
	struct s_tchain	*next;
}					t_tchain;

t_tchain			*new_tchain(char *str)
{
	t_tchain	*new;

	new = NULL;
	if (!(new = (t_tchain*)malloc(sizeof(t_tchain))))
	{
		return (NULL);
	}
	new->str = str;
	new->next = NULL;
	return (new);
}

void				append_tchain(t_tchain **chain, t_tchain *link)
{
	t_tchain *tmp;

	tmp = NULL;
	if (chain && *chain && link)
	{
		tmp = *chain;
		while (link && tmp && tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = link;
	}
	else if (chain)
	{
		*chain = link;
	}
}

size_t				size_tchain(t_tchain *chain)
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

void				del_tchain(t_tchain *link)
{
	if (link)
	{
		free(link->str);
		link->str = NULL;
		free(link->next);
		link->next = NULL;
		free(link);
		link = NULL;
	}
}

void				clear_tchain(t_tchain **chain)
{
	t_tchain *tmp;

	while (chain && *chain)
	{
		tmp = (*chain)->next;
		del_tchain(*chain);
		*chain = tmp;
	}
}

#if VERBOSE == 1
void					print_tchain(t_tchain *chain)
{
	t_tchain	*tmp;
	size_t		i;
	tmp = chain;
	i = 0;
	if (!tmp)
	{
		puts("NULL");
		return ;
	}
	while (tmp)
	{
		printf("<%lu>\t[link * %p | thread id %lu | str \"%s\" | result %lu | next *> %p]\n", \
		i++, tmp, tmp->thid, tmp->str, tmp->res, tmp->next);
		tmp = tmp->next;
	}
	printf(">> Chain of %lu link(s) <<\n", size_tchain(chain));
}
#endif

void					*thread_len(void *arg)
{
	t_tchain *link = (t_tchain *)arg;
	size_t	len;

	len = 0;
	while (link->str && link->str[len])
	{
		len++;
	}
	link->res = len;
	pthread_exit(NULL);
}

size_t					ft_strlen(char *str)
{
	size_t		i;
	t_tchain	*head;
	t_tchain	*tmp;
	size_t		old_value;

	head = NULL;
	head = tmp = NULL;
	if (!str)
	{
		return (0);
	}
	i = 0;
	while (i < N_THREADS)
	{
		append_tchain(&head, new_tchain(str));
#if VERBOSE == 1
		printf("<%lu> append\r", i);
#endif
		i++;
	}
	tmp = head;
	while (tmp)
	{
		if(pthread_create(&tmp->thid, NULL, thread_len, (void *)tmp))
		{
			return (0);
		}
#if VERBOSE == 1
		printf("thread %lu launched\r", tmp->thid);
#endif
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp)
	{
		if(pthread_join(tmp->thid, NULL))
		{
			return (0);
		}
#if VERBOSE == 1
		printf("thread %lu finished\r", tmp->thid);
#endif
		tmp = tmp->next;
	}
#if VERBOSE == 1
	print_tchain(head);
#endif
	tmp = head;
	old_value = head->res;
	while (tmp)
	{
		if (tmp->res != old_value)
		{
			return (0);
		}
		tmp = tmp->next;
	}
	return (old_value);
	pthread_exit(NULL);

}
