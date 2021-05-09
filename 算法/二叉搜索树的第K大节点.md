# 二叉搜索树的第K大节点

## 中序遍历的思想



`class Solution {`
`public:`
    `TreeNode* KthNode(TreeNode* pRoot, int k) {`
       `if(k==0||pRoot==nullptr)`
           `return nullptr;`
        `return KthNodeCore(pRoot,k);`
    `}`
    `TreeNode* KthNodeCore(TreeNode* pRoot,int& k)`
    `{`
        `TreeNode* target = nullptr;`
        `if(pRoot->left!=nullptr&&target==nullptr)`
            `target = KthNodeCore(pRoot->left,k);`
        `if(target==nullptr)`
        `{`
            `if(k==1)`
                `target=pRoot;`
            `--k;`
        `}`
        `if(target==nullptr&&pRoot->right!=nullptr)`
            `target=KthNodeCore(pRoot->right,k);`
        `return target;`
    `}`

`};`