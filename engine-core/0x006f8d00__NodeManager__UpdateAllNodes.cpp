// FUNC_NAME: NodeManager::UpdateAllNodes
// Function address: 0x006f8d00
// Iterates over a singly linked list of nodes (next pointer at +0x14) and calls processNode on each, then finalizes.
void __fastcall NodeManager::UpdateAllNodes(NodeManager* this)
{
    Node* pNode = *(Node**)((int)this + 0x14); // +0x14: head of linked list
    while (pNode != nullptr)
    {
        Node_Process(pNode); // FUN_006f89e0
        if (pNode == nullptr)
        {
            pNode = nullptr;
        }
        else
        {
            pNode = *(Node**)((int)pNode + 0x14); // +0x14: next node pointer
        }
    }
    NodeManager_FinalizeUpdate(); // FUN_006f8370
}