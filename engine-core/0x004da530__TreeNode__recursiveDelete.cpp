// FUNC_NAME: TreeNode::recursiveDelete
class TreeNode {
public:
    void recursiveDelete();
private:
    // offset 0x20: pointer to child node
    TreeNode* m_pChild;
};

void TreeNode::recursiveDelete()
{
    TreeNode* child = this->m_pChild;
    if (child != nullptr)
    {
        child->recursiveDelete();
        MemoryDealloc(child);
    }
}