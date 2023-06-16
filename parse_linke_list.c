#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
  int data;
  struct node *next;
} Node;

int is_char_invalid(const char c)
{
  return (c == ' ' || c == '-' || c == '>');
}

int count_nodes(const char *string)
{
  int counter;
  
  counter = 0;
  while (*string)
  {
    while (is_char_invalid(*string))
      string++;
    if (*string && *string >= '0' && *string <= '9')
      counter++;
    while (*string && !is_char_invalid(*string))
      string++;
  }
  return (counter);
}

Node  *create_nodes(int nodes_amount)
{
	Node	*head;
	Node	*node;

	node = (Node *)malloc(sizeof(Node));
	if (!node)
		return (NULL);
	head = node;
	while (nodes_amount--)
	{
		node->next = (Node *)malloc(sizeof(Node));
		if (!node->next)
			return (NULL);
		node = node->next;
	}
	node->next = NULL;
	return (head);
}

int		ft_atoi(const char *string)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while ((*string >= '\t' && *string <= '\r') || *string == ' ')
		string++;
	if (*string == '+' || *string == '-')
		if(*string == '-')
			sign = -1;
	while (*string >= '0' && *string <= '9')
		res = res * 10 + (*string++ - 48);
	return (sign * res);
}

void	fill_list(const char *string, Node *head, int nodes_amount)
{
	while (*string && nodes_amount--)
	{
		while (is_char_invalid(*string))
			string++;
		head->data = ft_atoi(string);
		head = head->next;
		while (*string && !is_char_invalid(*string))
			string++;
	}
}

int		is_string_valid(const char *string)
{
	while (*string)
	{
		if (!(*string >= '0' && *string <= '9')
			&& !is_char_invalid(*string) && *string != 'N'
			&& *string != 'U' && *string != 'L')
			return (0);
		string++;
	}
	return (1);
}

Node	*parse(const char *string)
{
	Node	*head;
	int		nodes_amount;

	if (!is_string_valid(string))
		return (NULL);
	nodes_amount = count_nodes(string);
	head = create_nodes(nodes_amount);
	fill_list(string, head, nodes_amount);
	return (head);	
}

int	main(int ac, char **av)
{
	Node	*head;
	Node	*next;

	if (ac == 2)
	{
		head = parse(av[1]);
		next = head;
		while (next)
		{
			next = head->next;
			if (next)
				printf("data = %i, next's address = %p\n", head->data, head->next);
			else
				printf("next's address = %p\n", head->next);
			free(head);
			head = next;
		}
	}
	else
		printf("usage: \"0 -> 1 -> 4 -> 9 -> 16 -> NULL\"\n");
	return (0);
}
