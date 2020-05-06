typedef struct TreeNode {
	struct TreeNode *left;
	struct TreeNode *right;
	long double item;
	int key;
} TreeNode;

typedef struct ListNode {
	struct TreeNode *item;
	struct ListNode *next;

} ListNode;

TreeNode *createTreeNode(long double);
ListNode *createListNode(long double, int);
ListNode *getList(int);
ListNode *insertListNode(ListNode *, ListNode *);
void freeTree(TreeNode *);
TreeNode *mergeTree(TreeNode *, TreeNode *);
void printCodes(TreeNode *, char *);
void checkOptions(int, char **);
