#include <cstdlib>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//操作给定的二叉树，将其变换为源二叉树的镜像。 

class Solution {
public:
    void Mirror(TreeNode *pRoot) {
		if (pRoot == NULL)
            return;
        swap(pRoot->left, pRoot->right);
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }
};