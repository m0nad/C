/* binarytree */
#include <stdio.h>
#include <stdlib.h>
struct tree_node {
	int data;
	struct tree_node *right, *left;
};

void
pre_order(struct tree_node *tree)
{
	if (tree == NULL)
		return;
	printf("%d\n", tree->data);
	if (tree->left) pre_order(tree->left);
	if (tree->right) pre_order(tree->right);
}

void
in_order(struct tree_node *tree)
{
	if (tree == NULL)
		return;
	if (tree->left) in_order(tree->left);
	printf("%d\n", tree->data);
	if (tree->right) in_order(tree->right);
}

void
post_order(struct tree_node *tree)
{
	if (tree == NULL)
		return;
	if (tree->left) post_order(tree->left);
	if (tree->right) post_order(tree->right);
	printf("%d\n", tree->data);
}

struct tree_node *
search(struct tree_node *tree, int data)
{
	if (tree == NULL || tree->data == data)
		return tree;
	if (data < tree->data)
		return search(tree->left, data);
	if (data > tree->data) 
		return search(tree->right, data);
	return NULL;
}

struct tree_node *
delete(struct tree_node *tree, int data)
{
	struct tree_node *tmp;
	if (tree == NULL)
		return NULL;
	if (data < tree->data) {
		tree->left = delete(tree->left, data);
	} else if (data > tree->data) {
		tree->right = delete(tree->right, data);
	} else
		if (tree->right && tree->left) {
			tmp = tree->right;
			while (tmp->left)
				tmp = tmp->left;
			tree->data = tmp->data;
			tree->right = delete(tree->right, tmp->data);
		} else {
			tmp = tree;
			if (tree->left == NULL)
				tree = tree->right;
			else if (tree->right == NULL)
				tree = tree->left;
			free(tmp);
		}
	return tree;
}

void
delete_tree(struct tree_node *tree)
{
	if (tree == NULL)
		return;
	delete_tree(tree->left);
	delete_tree(tree->right);
	free(tree);
}

struct tree_node *
tree_node_alloc_init(int data)
{
	struct tree_node *item;
	item = malloc(sizeof(struct tree_node));
	if (item == NULL)
		return NULL;
	item->data = data;
	item->left = item->right = NULL;
	return item;
}

struct tree_node *
insert(struct tree_node *tree, int data)
{
	if (tree == NULL) 
		return tree_node_alloc_init(data);
	if (data < tree->data)
		tree->left = insert(tree->left, data);
	else if (data > tree->data)
		tree->right = insert(tree->right, data);
	return tree;
}

int
main(void)
{
	int opt, data;
	struct tree_node *root = NULL;
	do {
		printf("1 - add\n2 - del\n3 - show tree\n0 - exit\n");
		scanf("%d", &opt);
		switch (opt) {
			case 0:
				delete_tree(root);
				break;
			case 1:
				printf("add data: ");
				scanf("%d", &data);
				root = insert(root, data);
				break;
			case 2:
				printf("del data: \n");
				scanf("%d", &data);
				root = delete(root, data);
				break;
			case 3:
				printf("1 - pre-order\n2 - in-order\n"
					"3 - post-order\n");
				scanf("%d", &opt);
				printf("----start show tree----\n");
				switch (opt) {
					case 1:
						pre_order(root);
						break;
					case 2:
						in_order(root);
						break;
					case 3:
						post_order(root);
						break;
				}
				printf("-----end show tree-----\n");
				break;
		}
	} while (opt);
	return 0;
}
