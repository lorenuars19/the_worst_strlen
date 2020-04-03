/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenuar <lorenuar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 16:13:01 by lorenuar          #+#    #+#             */
/*   Updated: 2020/04/03 19:57:03 by lorenuar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS     5

size_t	ft_strlen(char *str);

void *PrintHello(void *threadid)
{
	 long tid;
	 tid = (long)threadid;
	 printf("Hello World! It's me, thread #%ld!\n", tid);
	 pthread_exit(NULL);
}

int main(void)
{
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	for(t=0; t<NUM_THREADS; t++){
	   printf("In main: creating thread %ld\n", t);
	   rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
	   if (rc){
	      printf("ERROR; return code from pthread_create() is %d\n", rc);
	      exit(-1);
	   }
	}
	/* Last thing that main() should do */
	pthread_exit(NULL);
}
