typedef struct TreeNode {
	double item;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct ListNode {
	struct TreeNode *item;
	struct ListNode *next;

} ListNode;

TreeNode *createTreeNode(double);
ListNode *createListNode(double);
ListNode *insertListNode(ListNode *, ListNode *);
void freeTree(TreeNode *);
TreeNode *mergeTree(TreeNode *, TreeNode *);
void printCodes(TreeNode *, char *);
