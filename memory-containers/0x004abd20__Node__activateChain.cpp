// FUNC_NAME: Node::activateChain
class Node {
public:
    // +0x1c: Node* nextNode
    // +0x44: char activeFlag

    void __thiscall activateChain();
};

void Node::activateChain()
{
    this->activeFlag = 1;  // mark this node as active

    // traverse the linked list, activating all consecutive inactive nodes
    for (Node* current = this->nextNode; current != nullptr && current->activeFlag == 0; current = current->nextNode)
    {
        current->activeFlag = 1;
    }
}