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
	stack_t *p = *stack;
	stack_t *d = *stack;

	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	p = p->next, p->prev = NULL;
	*stack = p, free(d);
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
	stack_t *p = *stack;
	stack_t *d = (*stack)->next;

	if ((!(*stack)) || ((*stack)->next == NULL))
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	d->prev = NULL, p->prev = d;
	p->next = d->next, d->next = p;
	*stack = d;
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
	stack_t *p = *stack, *newelement;
	stack_t *d = (*stack)->next;

	if ((!(*stack)) || ((*stack)->next == NULL))
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
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
