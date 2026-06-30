// FUNC_NAME: TreeIterator::advanceToNextValidNode
void __fastcall TreeIterator::advanceToNextValidNode(Iterator* this)
{
    // this: pointer to iterator struct
    // this->empty (offset 0x00): flag indicating if tree is empty
    // this->current (offset 0x04): current node pointer

    if (this->empty == 0)
    {
        panic(); // FUN_00b97aea - assert failure or debug break
    }

    Node* curNode = this->current;
    if (curNode->flag == 0) // node is valid
    {
        Node* parent = curNode->parent;
        if (parent->flag == 0)
        {
            // Walk down the leftmost chain from parent's child until we find a node with flag != 0
            Node* tempParent = parent;
            Node* child = tempParent->child;
            while (child->flag == 0)
            {
                tempParent = child;
                child = child->child;
            }
            this->current = tempParent;
            return;
        }
        else
        {
            // parent is invalid; move to next sibling of current node
            curNode = curNode->next;
            // Traverse up until we find a sibling that is valid or until we reach a place where parent is current?
            while ((curNode->flag == 0) && (this->current == curNode->parent))
            {
                this->current = curNode;
                curNode = curNode->next;
            }
            if (this->current->flag != 0)
            {
                panic();
                return;
            }
            this->current = curNode;
        }
    }
    else // current node is invalid
    {
        // Move to child of current node
        Node* child = curNode->child;
        this->current = child;
        if (child->flag != 0)
        {
            panic();
            return;
        }
    }
}