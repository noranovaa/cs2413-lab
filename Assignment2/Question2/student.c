/*
 * Assignment 2 / Question 2 / student.c
 * ------------------------------------------------------------
 * Check if a BST is an AVL tree
 *
 * Implement:
 *   bool isAVL(struct TreeNode* root);
 *
 * AVL (for this assignment) means:
 * 1) strict BST property (no duplicates)
 * 2) height-balanced: abs(height(left) - height(right)) <= 1 at every node
 *
 * Rules:
 * - Do NOT allocate new nodes.
 * - Do NOT modify the tree.
 * - Do NOT print anything.
 *
 * Build/Run (from Assignment2 folder):
 *   make run2
 */

#include <stdbool.h>
#include <stddef.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


int check(struct TreeNode* node, int min, int max, bool has_min, bool has_max) {
    if (node == NULL) return 0;

    // BST violation
    if (has_min && node->val <= min) return -1;
    if (has_max && node->val >= max) return -1;

    int left  = check(node->left,  min,       node->val, has_min, true);
    int right = check(node->right, node->val, max,       true,    has_max);

    if (left == -1 || right == -1) return -1;

    int diff = left - right;
    if (diff > 1 || diff < -1) return -1;

    return (left > right ? left : right) + 1;
}

bool isAVL(struct TreeNode* root) {
    return check(root, 0, 0, false, false) != -1;
}
