#include "monty.h"

void push(stack_t **stack, unsigned int line_number)
{

}

void pall(stack_t **stack, unsigned int line_number)
{
	
}

void pint(stack_t **stack, unsigned int line_number)
{
	
}

void pop(stack_t **stack, unsigned int line_number)
{
	
}

void swap(stack_t **stack, unsigned int line_number)
{
	
}

void add(stack_t **stack, unsigned int line_number)
{
	
}

void nop(stack_t **stack, unsigned int line_number)
{
	(void) stack, (void) line_number;
}

void (*get_op_func(char *s))(stack_t **, unsigned int)
{
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"swap", swap},
		{"pop", pop},
		{"add", add},
		{"nop", nop},
		{NULL, NULL}
	};
	int i;

	i = 0;
	while (ops[i].opcode != NULL)
	{
		if (strcmp(ops[i].opcode, s) == 0)
		{
			printf("%s\n", ops[i].opcode);
			return (ops[i].f);
		}
		i++;
	}
	return (NULL);
}

int main(int ac, char **av)
{
	int ln = 0;
    FILE *fptr;
    char *line = NULL, *tok;
    size_t len = 0;
	stack_t **stack;

	if (ac != 2)
	{
		printf("USAGE: monty file");
		exit(EXIT_FAILURE);
	}
    if (!(fptr = fopen(av[1], "r")))
	{
		printf("Error: Can't open file %s\n", av[1]);
        exit(EXIT_FAILURE);
	}
    while ((getline(&line, &len, fptr)) != -1) 
	{
		tok = strtok(line, " ");
		get_op_func(tok);
    }
    fclose(fptr);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}