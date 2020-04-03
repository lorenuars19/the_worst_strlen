/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenuar <lorenuar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 16:15:13 by lorenuar          #+#    #+#             */
/*   Updated: 2020/04/03 20:16:59 by lorenuar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

typedef struct 	s_tchain
{
	pthread_t				thid;
	char						*str;
	size_t					*res;
	struct s_tchain	*next;
}								t_tchain;

pthread		create_thread(pthread_t *thid, void *(*routine)(void *), t_tchain *arg)
{
		if (thid && routine && arg)
			pthread_create(thid, NULL)
}

int		append_thread(t_tchain **list, char *str, )
{
	t_tchain tmp;

	if (list && *list)
}

size_t	ft_strlen(char *str)
{
	if (str)
		return (1);
	pthread_exit(NULL);
	return (0);
}
