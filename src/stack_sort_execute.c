/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sort_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:20:52 by tjensen           #+#    #+#             */
/*   Updated: 2022/12/02 17:03:21 by tjensen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	stack_sort_execute_rot_reverse(t_ps *ps, t_sort *sort, bool print);
static void	stack_sort_execute_rot_forward(t_ps *ps, t_sort *sort, bool print);

/*
**	Executes all operations to "isolate" a marked snake on stack_A
**	pushs all not marked items to stack_B
*/
int	stack_sort_push_b(t_ps *ps, bool print, t_snake *snake)
{
    int i;
    int chunk;
	int	count;

    // print = true;
    i = 0;
    chunk = 0;
	count = 0;
	// while (i < 100)
	while (ps->a_size > snake->max_len)
	{
        // printf("ps-a_size: %d\t snake-max_len: %d\n", ps->a_size, snake->max_len);
        // if (ps->a_top->is_snake)
        //     count += operation_ra(ps, print);
        // else
        //     count += operation_pb(ps, print);

        // write(2, "efw", 3);
        while (stack_get_smallest_chunk(ps->a_top) > chunk + 1)
            chunk += 2;
		if (ps->a_top->chunk == chunk)
        {
            count += operation_pb(ps, print);
        }
		else if (ps->a_top->chunk == chunk + 1)
        {
			count += operation_pb(ps, print);
			count += operation_rb(ps, print);
        }
		else
            count += operation_ra(ps, print);
        i++;
	}
	return (count);
}

/*
**	Executes all rotations to rotate both stacks to prepare for the next push
*/
int	stack_sort_execute_rotation(t_ps *ps, t_sort *sort, bool print)
{
	int	rotation_count;

	rotation_count = sort->rotation_sum;
	stack_sort_execute_rot_forward(ps, sort, print);
	stack_sort_execute_rot_reverse(ps, sort, print);
	sort->rotation_sum = 0;
	return (rotation_count);
}

static void	stack_sort_execute_rot_forward(t_ps *ps, t_sort *sort, bool print)
{
	while (sort->ra_rra_count[0])
	{
		operation_ra(ps, print);
		sort->ra_rra_count[0]--;
	}
	while (sort->rb_rrb_count[0])
	{
		operation_rb(ps, print);
		sort->rb_rrb_count[0]--;
	}
	while (sort->rr_rrr_count[0])
	{
		operation_rr(ps, print);
		sort->rr_rrr_count[0]--;
	}
}

static void	stack_sort_execute_rot_reverse(t_ps *ps, t_sort *sort, bool print)
{
	while (sort->ra_rra_count[1])
	{
		operation_rra(ps, print);
		sort->ra_rra_count[1]--;
	}
	while (sort->rb_rrb_count[1])
	{
		operation_rrb(ps, print);
		sort->rb_rrb_count[1]--;
	}
	while (sort->rr_rrr_count[1])
	{
		operation_rrr(ps, print);
		sort->rr_rrr_count[1]--;
	}
}
