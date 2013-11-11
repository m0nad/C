/* m0nad, linkedlist */
#include <stdio.h>
#include <stdlib.h>

struct linked_node {
	int data;
	struct linked_node *next;
};

struct linked_list {
	struct linked_node *first;
};

void
add_after(struct linked_node *node, struct linked_node *newnode)
{
	newnode->next = node->next;
	node->next = newnode;
}

void
add_beginning(struct linked_list *list, struct linked_node *newnode)
{
	newnode->next = list->first;
	list->first = newnode;
}

void
del_after(struct linked_node *node)
{
	struct linked_node *obsolete;
	obsolete = node->next;
	node->next = node->next->next;
	free(obsolete);
}

void
del_beginning(struct linked_list *list)
{
	struct linked_node *obsolete = list->first;
	list->first = list->first->next;
	free(obsolete);
}

struct linked_node *
get_node(struct linked_list *list, int data)
{
	struct linked_node *node;
	for (node = list->first; node; node = node->next) 
		if (node->data == data)
			return node;
	return NULL;
}

#define NDNULL 1
#define ENOMEM 2
// alloc node and init data
struct linked_node *
linked_node_alloc_init(int data)
{
	struct linked_node *newnode;
	newnode = malloc(sizeof(struct linked_node));
	if (newnode == NULL)
		return NULL;
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}

int
node_create_beginning(struct linked_list *list, int data)
{
	struct linked_node *newnode;

	newnode = linked_node_alloc_init(data);
	if (newnode == NULL)
		return -ENOMEM;

	add_beginning(list, newnode);
	return 0;
}

int
node_destroy_beginning(struct linked_list *list)
{
	if (list->first == NULL)
		return -NDNULL;
	del_beginning(list);
	return 0;
}

int
node_create_after(struct linked_list *list, int data, int newdata)
{
	struct linked_node *newnode;
	struct linked_node *node = get_node(list, data);
	if (!node)
		return -NDNULL;

	newnode = linked_node_alloc_init(newdata);
	if (newnode == NULL)
		return -ENOMEM;

	add_after(node, newnode);
	return 0;
}

int
node_destroy_after(struct linked_list *list, int data)
{
	struct linked_node *node = get_node(list, data);
	if (node == NULL || node->next == NULL)
		return -NDNULL;

	del_after(node);
	return 0;
}

void
free_list(struct linked_list *list)
{
	while (list->first)
		del_beginning(list);
	free(list);
}

void
print_error(int err)
{
	printf("ERROR: ");
	switch (err) {
		case -NDNULL:
			printf("node null\n");
			break;
		case -ENOMEM:
			printf("no memory\n");
			break;
		default:
			printf("unkwon\n");
	}
}

void
show_list(struct linked_list *list)
{
	struct linked_node *node;
	for (node = list->first; node; node = node->next)
		printf("node->data %d\n", node->data);
}

int
main(void)
{
	int opt, err, data1, data2;
	struct linked_list *list;

	list = malloc(sizeof(struct linked_list));
	if (list == NULL)
		return -1;
	list->first = NULL;

	do {
		printf("1 - add beginning\n2 - del beginning\n3 - add after\n"
			"4 - del after\n5 - show list\n0 - exit\n");
		scanf("%d", &opt);
		switch (opt) {
			case 0:
				free_list(list);
				break;
			case 1:
				printf("add beginning, data: ");
				scanf("%d", &data1);
				err = node_create_beginning(list, data1);
				if (err)
					print_error(err);
				break;
			case 2:
				printf("del beginning...\n");
				err = node_destroy_beginning(list);
				if (err)
					print_error(err);
				break;
			case 3:
				printf("add after data: ");
				scanf("%d", &data1);
				printf("new data: ");
				scanf("%d", &data2);
				err = node_create_after(list, data1,
					data2);
				if (err)
					print_error(err);
				break;
			case 4:
				printf("del after data: \n");
				scanf("%d", &data1);
				err = node_destroy_after(list, data1);
				if (err)
					print_error(err);
				break;
			case 5:
				show_list(list);
				break;
		}
	} while (opt);
	return 0;
}
