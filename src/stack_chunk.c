/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_chunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:42:25 by tjensen           #+#    #+#             */
/*   Updated: 2022/12/02 18:22:26 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


/* Searchs for the smallest chunk in a stack */
int	stack_get_smallest_chunk(t_stack *stack)
{
	int		smallest;
	t_stack	*tmp;

	if (stack == NULL)
		return (STACK_EMPTY);
	tmp = stack;
    smallest = stack->chunk;
	while (tmp->next->num != stack->num)
	{
		tmp = tmp->next;
		if (smallest == NO_CHUNK
            || (tmp->chunk != NO_CHUNK && smallest > tmp->chunk))
			smallest = tmp->chunk;
	}
	return (smallest);
}

/* Searchs for the biggest chunk in a stack */
int	stack_get_biggest_chunk(t_stack *stack)
{
	int		biggest;
	t_stack	*tmp;

	if (stack == NULL)
		return (STACK_EMPTY);
	tmp = stack;
    biggest = stack->chunk;
	while (tmp->next->num != stack->num)
	{
		tmp = tmp->next;
		if (biggest == NO_CHUNK
            || (tmp->chunk != NO_CHUNK && biggest < tmp->chunk))
			biggest = tmp->chunk;
	}
	return (biggest);
}
