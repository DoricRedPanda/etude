#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "huffman.h"

int dflag;

ListNode *createListNode(double item)
{
	ListNode *node;

	if ((node = malloc(sizeof(ListNode))) < 0) {
		err(1, "malloc failure");
		exit(EXIT_FAILURE);
	}
	node->item = createTreeNode(item);
	node->next = NULL;
	return node;
}

TreeNode *createTreeNode(double item)
{
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

ListNode *insertListNode(ListNode *list, ListNode *new)
{
	ListNode *prev, *cur;
	double item = new->item->item;

	if (list == NULL)
		return new;
	for (prev = cur = list; cur != NULL; prev = cur, cur = cur->next) {
		if (item <= cur->item->item) {
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

TreeNode *mergeTree(TreeNode *l, TreeNode *r)
{
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
		if (dflag)
			printf("%s\t%lf\n", s, node->item);
		else
			printf("%s\n", s);
		return;
	}
	printCodes(node->left, strcat(s, "0"));
	s[strlen(s)-1] = 0;
	printCodes(node->right, strcat(s, "1"));
	s[strlen(s)-1] = 0;
}

void freeTree(TreeNode *node)
{
	if (node == NULL)
		return;
	freeTree(node->left);
	freeTree(node->right);
	free(node);
}

ListNode *getList(int num)
{
	ListNode *list = NULL;
	double val, total = 0.0;

	if (num <= 0) {
		errx(1, "%d <= 0, Wrong input", num);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < num; i++) {
		if (scanf("%lf", &val) <= 0) {
			errx(1, "scanf failure");
			exit(EXIT_FAILURE);
		}
		if (val <= 0.0) {
			errx(1, "%lf <= 0, Wrong input", val);
			exit(EXIT_FAILURE);
		}
		total += val;
		list = insertListNode(list, createListNode(val));
	}
	if (total > 1.0) {
		errx(1, "%lf > 1: Wrong sum of probabilities", total);
		exit(EXIT_FAILURE);
	}
	return list;
}

void checkOptions(int argc, char *argv[])
{
	if (argc == 1)
		return;
	if (argc == 2) {
		if (!strcmp(*(++argv), "-d")) {
			dflag = 1;
			return;
		} else if (!strcmp(*argv, "-h")) {
			puts("Usage: huffman [OPTION]");
			puts("Enter number n, then n doubles");
			puts("Options:");
			puts("  -h\t To display this message");
			puts("  -d\t Verbose output");
			exit(EXIT_SUCCESS);
		}
	}
	errx(1, "Wrong usage.\nTry 'huffman -h' for more information.");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	ListNode *list, *tmpList, *mergedList;
	TreeNode *tmpTree;
	char *string;
	int num;

	checkOptions(argc, argv);

	if (scanf("%d", &num) <= 0) {
		errx(1, "scanf failure");
		exit(EXIT_FAILURE);
	}
	list = getList(num);
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
