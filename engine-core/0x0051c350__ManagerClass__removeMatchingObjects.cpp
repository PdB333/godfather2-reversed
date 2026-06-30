// FUNC_NAME: ManagerClass::removeMatchingObjects
void ManagerClass::removeMatchingObjects(int id)
{
    // iterate through global linked list starting at head
    int* node = reinterpret_cast<int*>(DAT_01205514);
    while (node != nullptr)
    {
        int* objectPtr = reinterpret_cast<int*>(node[0x20 / 4]); // +0x20: pointer to object
        bool match;
        if (objectPtr == nullptr)
        {
            match = (id == -1);
        }
        else
        {
            // call virtual function at offset 0xC (index 3) to get object ID
            int objId = (*(int (**)(int*))(objectPtr[0] + 0xC))(objectPtr);
            match = (objId == id);
        }
        int* next = reinterpret_cast<int*>(node[0x14 / 4]); // +0x14: next node pointer
        if (match)
        {
            // remove current node via helper function
            FUN_0051bc80(node);
        }
        node = next;
    }
    return;
}