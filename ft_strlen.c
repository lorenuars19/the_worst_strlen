/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenuar <lorenuar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 16:15:13 by lorenuar          #+#    #+#             */
/*   Updated: 2020/04/03 23:02:04 by lorenuar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define N_THREADS		25

typedef struct		s_tchain
{
	pthread_t		*thid;
	char			*str;
	size_t			res;
	struct s_tchain	*next;
}					t_tchain;

t_tchain			*new_tchain(char *str)
{
	t_tchain	*new;
	pthread_t	*thread;

	new = NULL;
	thread = 0;
	if (!(new = (t_tchain*)malloc(sizeof(t_tchain))))
	{
		return (NULL);
	}
	new->thid = thread;
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
		free(link->thid);
		link->thid = NULL;
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

void					print_tchain(t_tchain *chain)
{
	t_tchain	*tmp;

	tmp = chain;
	if (!tmp)
	{
		puts("NULL LIST");
		return ;
	}
	printf("chain of %lu link(s)", size_tchain(tmp));
	while (tmp)
	{
		printf("[>%p | thid %lu | str \"%s\" | res %lu | next> %p]", \
		tmp, *tmp->thid, tmp->str, tmp->res, tmp->next);
		if (tmp->next)
		{
			putchar(',');
		}
	}
}

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

#define D printf("%d\t", __LINE__);

size_t					ft_strlen(char *str)
{
	D;
	size_t		i;
	t_tchain	*head;
	t_tchain	*tmp;

	D;
	head = NULL;
	D;
	head = tmp = NULL;
	D;
	if (!str)
	{
		D;
		return (0);
	}
	D;
	i = 0;
	D;
	while (i < N_THREADS)
	{
	D;
		append_tchain(&head, new_tchain(str));
	D;
		i++;
	}
	D;
	print_tchain(head);
	D;
	tmp = head;
	D;
	while (tmp)
	{
	D;
		pthread_create(tmp->thid, NULL, thread_len, (void *)&tmp);
	D;
		tmp = tmp->next;
	D;
	}
	D;
	print_tchain(head);
	D;

	pthread_exit(NULL);
	D;
	return (0);
}
