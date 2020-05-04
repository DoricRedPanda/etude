#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "huffman.h"

ListNode *createListNode(double item) {
	ListNode *node;
	if ((node = malloc(sizeof(ListNode))) < 0) {
		err(1, "malloc failure");
		exit(EXIT_FAILURE);
	}
	node->item = createTreeNode(item);
	node->next = NULL;
	return node;
}

TreeNode *createTreeNode(double item) {
	TreeNode *node;
	if ((node = malloc(sizeof(TreeNode))) < 0) {
		err(1, "malloc failure");
		exit(EXIT_FAILURE);
	}
	node->item = item;
	node->left = NULL;
	node->right = NULL;
	return node;
}

ListNode *insertListNode(ListNode *list, ListNode *new) {
	ListNode *prev, *cur;
	double item = new->item->item;

	if (list == NULL)
		return new;
	for (prev = cur = list; cur != NULL; prev = cur, cur = cur->next) {
		if (item < cur->item->item) {
			if (cur == prev)
				list = new;
			else
				prev->next = new;
			new->next = cur;
			break;
		}
	}
	if (cur == NULL) {
		prev->next = new;
		new->next = NULL;
	}
	return list;
}

TreeNode *mergeTree(TreeNode *l, TreeNode *r) {
	TreeNode *node;

	node = createTreeNode(l->item + r->item);
	node->left = l;
	node->right = r;
	return node;
}

void printCodes(TreeNode *node, char *s)
{
	if (node->left == NULL) {
		if (strlen(s) == 0)
			strcat(s, "1");
		printf("%s\t%lf\n", s, node->item);
		return;
	}
	printCodes(node->left, strcat(s, "0"));
	s[strlen(s)-1] = 0;
	printCodes(node->right, strcat(s, "1"));
	s[strlen(s)-1] = 0;
}

void freeTree(TreeNode * node) {
	if (node == NULL)
		return;
	freeTree(node->left);
	freeTree(node->right);
	free(node);
}

int main(void)
{
	ListNode *list = NULL, *tmpList, *mergedList;
	TreeNode *tmpTree;
	char *string;
	double val;
	int num;

	scanf("%d", &num);
	if (num <= 0) {
		errx(1, "%d <= 0", num);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < num; i++) {
		scanf("%lf", &val);
		list = insertListNode(list, createListNode(val));
	}
	while (list->next != NULL) {
		tmpTree = mergeTree(list->item, list->next->item);
		tmpList = list;
		list->next->item = tmpTree;
		mergedList = list->next;
		list = list->next->next;
		free(tmpList);
		list = insertListNode(list, mergedList);
	}
	if ((string = calloc(num, sizeof(char))) < 0) {
		err(1, "calloc failure");
		exit(EXIT_FAILURE);
	}
	printCodes(list->item, string);
	free(string);
	freeTree(list->item);
	free(list);
	return 0;
}
