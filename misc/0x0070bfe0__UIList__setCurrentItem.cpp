// FUNC_NAME: UIList::setCurrentItem
int __thiscall UIList::setCurrentItem(int this, int newNode)
{
    int *currentItemPtr; // pointer to this->m_currentItem at +0x374
    char state;          // this->m_state at +0x1ad
    int result;
    int baseNode;
    int returnVal;

    currentItemPtr = (int *)(this + 0x374); // +0x374: pointer to current item (or sentinel)

    // If there is a current item (not null and not sentinel 0x48) OR we are setting a new item
    if (((*currentItemPtr != 0) && (*currentItemPtr != 0x48)) || (newNode != 0))
    {
        // Convert newNode from a pointer to a sub-object (offset 0x48) to the actual base pointer?
        // newNode is expected to be a pointer within a larger structure; add 0x48 to get the sub-pointer? 
        // Actually it seems newNode itself is the base, and we adjust to the sub-field at +0x48.
        if (newNode == 0)
        {
            newNode = 0;
        }
        else
        {
            newNode = newNode + 0x48;  // point to the sub-object (e.g., a child list entry)
        }

        // If the current item is different from the new one
        if (*currentItemPtr != newNode)
        {
            // Free the old current item (if it exists)
            if (*currentItemPtr != 0)
            {
                UIList::freeNode(currentItemPtr); // FUN_004daf90 – likely deletion code
            }
            *currentItemPtr = newNode; // set to new item

            if (newNode != 0)
            {
                // Store the old 'prev' pointer of the new node into this->m_currentItemPrev (+0x378)
                *(int *)(this + 0x378) = *(int *)(newNode + 4);
                // Set the new node's 'prev' pointer to point to this->m_currentItem (the pointer itself)
                *(int **)(newNode + 4) = currentItemPtr;
            }
        }
        return 1; // operation succeeded
    }

    // No current item and no new item to set – check if we need to remove based on state
    state = *(char *)(this + 0x1ad); // +0x1ad: state flag (e.g., active/inactive)
    if ((((state == 0x1a) || (state == 0x1b)) &&                    // active or some other state
         ((*(int *)(this + 0x2d4) != 0 && (*(int *)(this + 0x2d4) != 0x48)))) && // a list header is valid
        ((((*(int *)(this + 0x364) != 0 || (*(int *)(this + 0x368) != 0)) ||   // any of four child pointers exist
          (*(int *)(this + 0x36c) != 0)) || (*(int *)(this + 0x370) != 0))))
    {
        // Get the base node from the first child pointer (at +0x364)
        baseNode = UIList::getChildList(this + 0x364, 0); // FUN_00446100 – returns a pointer to a list head
        if (baseNode != 0)
        {
            returnVal = UIList::findNodeByType(baseNode, 0x346d561a); // FUN_0070afb0 – find node with specific type ID
            UIList::removeNode(returnVal); // FUN_0070af00 – remove that node from list
        }

        // If we have a current item (not null/sentinel) and state is active (0x1a)
        if (*currentItemPtr != 0 && *currentItemPtr != 0x48 && state == 0x1a)
        {
            // Get the base of the current item by subtracting 0x48
            if (*currentItemPtr == 0)
                baseNode = 0;
            else
                baseNode = *currentItemPtr - 0x48;

            // Check a flag at offset 0x1a8 in the base structure
            if (*(int *)(baseNode + 0x1a8) == 0) // 0 means something like "not selected"?
                return 1; // bail out, nothing more to do
        }

        // If state is 0x1b, check similarly
        if (state == 0x1b)
        {
            if (*currentItemPtr == 0)
                baseNode = 0;
            else
                baseNode = *currentItemPtr - 0x48;

            if (*(int *)(baseNode + 0x1a8) == 1) // 1 means "selected"?
                return 1; // already in correct state, done
        }

        // If we reach here, free the current item (remove from list)
        if (*currentItemPtr != 0)
        {
            UIList::freeNode(currentItemPtr); // FUN_004daf90
            *currentItemPtr = 0; // clear
        }
    }
    return 0; // no change
}