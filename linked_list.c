/* m0nad, linkedlist */
#include <stdio.h>
#include <stdlib.h>

struct node_struct {
	int data;
	struct node_struct *next;
};

struct list_struct {
	struct node_struct *first;
};

void
add_after(struct node_struct *node, struct node_struct *newnode)
{
	newnode->next = node->next;
	node->next = newnode;
}

void
add_beginning(struct list_struct *list, struct node_struct *newnode)
{
	newnode->next = list->first;
	list->first = newnode;
}

void
del_after(struct node_struct *node)
{
	struct node_struct *obsolete;
	obsolete = node->next;
	node->next = node->next->next;
	free(obsolete);
}

void
del_beginning(struct list_struct *list)
{
	struct node_struct *obsolete = list->first;
	list->first = list->first->next;
	free(obsolete);
}

struct node_struct *
get_node(struct list_struct *list, int data)
{
	struct node_struct *node;
	for (node = list->first; node; node = node->next) 
		if (node->data == data)
			return node;
	return NULL;
}

#define NDNULL 1
#define ENOMEM 2
// alloc node and init data
struct node_struct *
node_struct_alloc_init(int data)
{
	struct node_struct *newnode;
	newnode = malloc(sizeof(struct node_struct));
	if (newnode == NULL)
		return NULL;
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}

int
data_struct_create(struct list_struct *list, int data)
{
	struct node_struct *newnode;

	newnode = node_struct_alloc_init(data);
	if (newnode == NULL)
		return -ENOMEM;

	add_beginning(list, newnode);
	return 0;
}

int
data_struct_destroy(struct list_struct *list)
{
	if (list->first == NULL)
		return -NDNULL;
	del_beginning(list);
	return 0;
}

int
data_struct_create_after(struct list_struct *list, int data, int newdata)
{
	struct node_struct *newnode;
	struct node_struct *node = get_node(list, data);
	if (!node)
		return -NDNULL;

	newnode = node_struct_alloc_init(newdata);
	if (newnode == NULL)
		return -ENOMEM;

	add_after(node, newnode);
	return 0;
}

int
data_struct_destroy_after(struct list_struct *list, int data)
{
	struct node_struct *node = get_node(list, data);
	if (node == NULL || node->next == NULL)
		return -NDNULL;

	del_after(node);
	return 0;
}

void
free_list(struct list_struct *list)
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
show_list(struct list_struct *list)
{
	struct node_struct *node;
	for (node = list->first; node; node = node->next)
		printf("node->data %d\n", node->data);
}

int
main(void)
{
	int opt, err, data1, data2;
	struct list_struct *list;

	list = malloc(sizeof(struct list_struct));
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
				err = data_struct_create(list, data1);
				if (err)
					print_error(err);
				break;
			case 2:
				printf("del beginning...\n");
				err = data_struct_destroy(list);
				if (err)
					print_error(err);
				break;
			case 3:
				printf("add after data: ");
				scanf("%d", &data1);
				printf("new data: ");
				scanf("%d", &data2);
				err = data_struct_create_after(list, data1,
					data2);
				if (err)
					print_error(err);
				break;
			case 4:
				printf("del after data: \n");
				scanf("%d", &data1);
				err = data_struct_destroy_after(list, data1);
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
