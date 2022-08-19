#include "monty.h"

/**
 * pall - prints all elements of the stack
 *
 * @stack: the stack pointer
 * @line_number: the line number
 * Return: void
 */

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *p = *stack;

	(void) line_number;
	if (!(*stack))
	{
	}
	else
	{
		for (; p != NULL; p = p->next)
			printf("%d\n", p->n);
	}
}

/**
 * pint - prints top element of stack
 *
 * @stack: the stack pointer
 * @line_number: the line number
 * Return: void
 */

void pint(stack_t **stack, unsigned int line_number)
{
	(void) line_number;
	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
		printf("%d\n", (*stack)->n);
}

/**
 * pop - pops an element from the stack
 *
 * @stack: the stack pointer
 * @line_number: the line number
 * Return: void
 */

void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *pp, *np;

	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
	{
		if ((*stack)->next == NULL)
		{
			pp = *stack;
			*stack = NULL;
			free(pp);
		}
		else
		{
			pp = *stack, np = (*stack)->next;
			np->prev = NULL, *stack = np;
			free(pp);
		}
	}
}

/**
 * swap - swaps last two elements from stack
 *
 * @stack: the stack pointer
 * @line_number: the line number
 * Return: void
 */

void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *p, *d;

	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	else if ((*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	else
	{
		p = *stack, d = (*stack)->next;
		d->prev = NULL, p->prev = d;
		p->next = d->next, d->next = p;
		*stack = d;
	}
}

/**
 * add - adds the last two elements from the stack
 *
 * @stack: the stack pointer
 * @line_number: the line number
 * Return: void
 */

void add(stack_t **stack, unsigned int line_number)
{
	int sum;
	stack_t *p, *newelement, *d;

	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	else if ((*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	p = *stack, d = (*stack)->next;
	sum = (p->n) + (d->n);
	pop(stack, line_number), pop(stack, line_number);
	newelement = malloc(sizeof(stack_t));
	if (newelement == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	newelement->next = *stack;
	newelement->prev = NULL;
	newelement->n = sum;
	if (newelement->next != NULL)
		newelement->next->prev = newelement;
	*stack = newelement;
}
