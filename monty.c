#include "monty.h"

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *newelement;
	char *n_num;

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
		newelement->n = atoi(n_num);
	else
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	if (newelement->next != NULL)
		newelement->next->prev = newelement;
	*stack = newelement;
}

void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack, (void)line_number;
}

void (*get_op_func(char *s))(stack_t **, unsigned int)
{
	instruction_t ops[] = {
		{"push", push}, {"pall", pall}, {"pint", pint}, {"swap", swap}, {"pop", pop}, {"add", add}, {"nop", nop}, {NULL, NULL}};
	int i = 0;

	while (ops[i].opcode != NULL)
	{
		if (strcmp(ops[i].opcode, s) == 0)
			return (ops[i].f);
		i++;
	}
	return (NULL);
}

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
	if (!(fptr = fopen(av[1], "r")))
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	while ((getline(&line, &len, fptr)) != -1)
	{
		ln++;
		tok = strtok(line, " \n");
		if ((*get_op_func(tok)))
			(*get_op_func(tok))(&stack, ln);
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", ln, tok);
			exit(EXIT_FAILURE);
		}
	}
	fclose(fptr);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}