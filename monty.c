#include "monty.h"

/**
 * free_stack - free a stack
 *
 * @head: the stack pointer
 * Return: void
 */

void free_stack(stack_t *head)
{
	stack_t *p_elem, *elem;

	elem = head;
	while (elem)
	{
		p_elem = elem;
		elem = elem->next;
		free(p_elem);
	}
}

/**
 * push - pushes an element onto the stack
 *
 * @stack: the stack pointer
 * @line_number: the line number
 * Return: void
 */

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *newelement;
	char *n_num;
	int i = 0;

	newelement = malloc(sizeof(stack_t));
	if (newelement == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	newelement->next = *stack;
	newelement->prev = NULL;
	n_num = strtok(NULL, " \n");
	if (n_num != NULL)
	{
		for (; n_num[i]; i++)
		{
			if (((n_num[i] > 47) && (n_num[i] < 58)) || (n_num[i] == '-'))
				continue;
			else
			{
				fprintf(stderr, "L%d: usage: push integer\n", line_number);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	newelement->n = atoi(n_num);
	if (newelement->next != NULL)
		newelement->next->prev = newelement;
	*stack = newelement;
}

/**
 * nop - does nothing
 *
 * @stack: the stack pointer
 * @line_number: the line number
 * Return: void
 */

void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack, (void)line_number;
}

/**
 * get_op_func - function selector for monty main
 *
 * @s: input line
 * Return: void
 */

void (*get_op_func(char *s))(stack_t **, unsigned int)
{
	instruction_t ops[] = {
		{"push", push}, {"pall", pall},
		{"pint", pint}, {"swap", swap},
		{"pop", pop}, {"add", add},
		{"nop", nop}, {NULL, NULL}
		};
	int i = 0;

	while (ops[i].opcode != NULL)
	{
		if (strcmp(ops[i].opcode, s) == 0)
			return (ops[i].f);
		i++;
	}
	return (NULL);
}

/**
 * main - main monty function
 *
 * @ac: argument count
 * @av: argument array
 * Return: exit status
 */

int main(int ac, char **av)
{
	unsigned int ln = 0;
	FILE *fptr;
	char *line = NULL, *tok;
	size_t len = 0;
	stack_t *stack = NULL;

	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fptr = fopen(av[1], "r");
	if (!fptr)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	while ((getline(&line, &len, fptr)) != -1)
	{
		ln++;
		tok = strtok(line, " \n");
		if (tok == NULL)
			continue;
		else
		{
			if ((*get_op_func(tok)))
			(*get_op_func(tok))(&stack, ln);
			else
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", ln, tok);
				exit(EXIT_FAILURE);
			}
		}
	}
	fclose(fptr);
	if (line)
		free(line);
	if (stack)
		free_stack(stack);
	exit(EXIT_SUCCESS);
}
