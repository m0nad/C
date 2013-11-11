/* doubly linked list */
#include <stdio.h>
#include <stdlib.h>

struct doubly_linked_node {
	int data;
	struct doubly_linked_node *prev;
	struct doubly_linked_node *next;
};

struct doubly_linked_list {
	struct doubly_linked_node *first;
	struct doubly_linked_node *last;
};

struct doubly_linked_node *
search_node_forward(struct doubly_linked_list *list, int data)
{
	struct doubly_linked_node *node = list->first;
	while (node != NULL) {
		if (node->data == data)
			return node;
		node = node->next;
	}
	return NULL;
}

struct doubly_linked_node *
search_node_backward(struct doubly_linked_list *list, int data)
{
	struct doubly_linked_node *node = list->last;
	while (node != NULL) {
		if (node->data == data)
			return node;
		node = node->prev;
	}
	return NULL;
}

void
insert_after(struct doubly_linked_list *list, struct doubly_linked_node *node,
	struct doubly_linked_node *newnode)
{
	newnode->prev = node;
	newnode->next = node->next;
	if (node->next == NULL)
		list->last = newnode;
	else
		node->next->prev = newnode;
	node->next = newnode;
}

void
insert_before(struct doubly_linked_list *list, struct doubly_linked_node *node,
	struct doubly_linked_node *newnode)
{
	newnode->prev = node->prev;
	newnode->next = node;
	if (node->prev == NULL)
		list->first = newnode;
	else
		node->prev->next = newnode;
	node->prev = newnode;
}

void
insert_beginning(struct doubly_linked_list *list, 
	struct doubly_linked_node *newnode)
{
	if (list->first == NULL) {
		list->first = newnode;
		list->last = newnode;
		newnode->prev = NULL;
		newnode->next = NULL;
	} else
		insert_before(list, list->first, newnode);
}

void
insert_end(struct doubly_linked_list *list, struct doubly_linked_node *newnode)
{
	if (list->last == NULL)
		insert_beginning(list, newnode);
	else
		insert_after(list, list->last, newnode);
}

void
remove_node(struct doubly_linked_list *list, struct doubly_linked_node *node)
{
	if (node->prev == NULL)
		list->first = node->next;
	else
		node->prev->next = node->next;
	if (node->next == NULL)
		list->last = node->prev;
	else
		node->next->prev = node->prev;
	free(node);
}

#define NDNULL 1
#define ENOMEM 2

struct doubly_linked_node *
node_alloc_init(int data)
{
	struct doubly_linked_node *newnode;
	newnode = malloc(sizeof(struct doubly_linked_node));
	if (newnode == NULL)
		return NULL;
	newnode->data = data;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}

void
print_list(struct doubly_linked_list *list) //forward
{
	struct doubly_linked_node *node;
	for (node = list->first; node != NULL; node = node->next)
		printf("node->data %d\n", node->data);
}

void
free_list(struct doubly_linked_list *list)
{
	while (list->first)
		remove_node(list, list->first);
	free(list);
}

struct doubly_linked_node *
search_opt(struct doubly_linked_list *list, int searchopt, int data)
{
	switch (searchopt) {
		case 1:
			return search_node_forward(list, data);
		case 2:
			return search_node_backward(list, data);
	}
	return NULL;
}

int
create_after(struct doubly_linked_list *list, int searchopt,
	int afterdata, int data)
{
	struct doubly_linked_node *node, *newnode;
	node = search_opt(list, searchopt, afterdata);
	if (node == NULL)
		return -NDNULL;
	newnode = node_alloc_init(data);
	if (newnode == NULL)
		return -ENOMEM;
	insert_after(list, node, newnode);
	return 0;
}

int
create_before(struct doubly_linked_list *list, int searchopt,
	int beforedata, int data)
{
	struct doubly_linked_node *node, *newnode;
	node = search_opt(list, searchopt, beforedata);
	if (node == NULL)
		return -NDNULL;
	newnode = node_alloc_init(data);
	if (newnode == NULL)
		return -ENOMEM;
	insert_before(list, node, newnode);
	return 0;
}

int
create_beginning(struct doubly_linked_list *list, int data)
{
	struct doubly_linked_node *newnode;
	newnode = node_alloc_init(data);
	if (newnode == NULL)
		return -ENOMEM;
	insert_beginning(list, newnode);
	return 0;
}

int
create_end(struct doubly_linked_list *list, int data)
{
	struct doubly_linked_node *newnode;
	newnode = node_alloc_init(data);
	if (newnode == NULL)
		return -ENOMEM;
	insert_end(list, newnode);
	return 0;
}

int
delete_node(struct doubly_linked_list *list, int searchopt, int data)
{
	struct doubly_linked_node *node;
	node = search_opt(list, searchopt, data);
	if (node == NULL)
		return -NDNULL;
	remove_node(list, node);
	return 0;
}

void
print_error(int err)
{
	printf("ERROR: ");
	switch (err) {
		case -NDNULL:
			printf("node not found\n");
			break;
		case -ENOMEM:
			printf("no memory\n");
			break;
		default:
			printf("unkwon\n");
	}
}

int
main(void)
{
	int auxdata, data, opt, err;
	struct doubly_linked_list *list;
	list = malloc(sizeof(struct doubly_linked_list));
	if (list == NULL)
		return -1;
	list->first = NULL;
	list->last = NULL;
	do {
		printf("1 - insert after\n2 - insert before\n"
			"3 - insert beginning\n4 - insert end\n"
			"5 - delete node\n6 - print list\n"
			"0 - exit\n");
		scanf("%d", &opt);
		switch (opt) {
			case 0:
				free_list(list);
				break;
			case 1:
				printf("insert after node with data: ");
				scanf("%d", &auxdata);
				printf("search mode:\n1 - forward\n"
					"2 - backward\n");
				scanf("%d", &opt);
				printf("insert data: ");
				scanf("%d", &data);
				err = create_after(list, opt, auxdata, data);
				if (err)
					print_error(err);
				break;
			case 2:
				printf("insert before node with data: ");
				scanf("%d", &auxdata);
				printf("search mode:\n1 - forward\n"
					"2 - backward\n");
				scanf("%d", &opt);
				printf("insert data: ");
				scanf("%d", &data);
				err = create_before(list, opt, auxdata, data);
				if (err)
					print_error(err);
				break;
			case 3:
				printf("insert beginnig, data: ");
				scanf("%d", &data);
				err = create_beginning(list, data);
				if (err)
					print_error(err);
				break;
			case 4:
				printf("insert end, data: \n");
				scanf("%d", &data);
				err = create_end(list, data);
				if (err)
					print_error(err);
				break;
			case 5:
				printf("delete node with data: ");
				scanf("%d", &data);
				printf("search node:\n1 - forward\n"
					"2 - backward\n");
				scanf("%d", &opt);
				err = delete_node(list, opt, data);
				if (err)
					print_error(err);
				break;
			case 6:
				print_list(list);
				break;
		}
	} while (opt);
	return 0;
}
