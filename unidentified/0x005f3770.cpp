// FUN_005f3770: ObjectManager::processMatchingObjects(int matchValue)
void ObjectManager::processMatchingObjects(int matchValue)
{
    // Global head pointer to a singly linked list of objects
    // each object has next pointer at +0x04 and a match field at +0x60
    int* currentNode = reinterpret_cast<int*>(DAT_011a0ef0); // head of list

    while (currentNode != nullptr)
    {
        if (currentNode[0x60 / 4] == matchValue) // compare field at offset 0x60
        {
            FUN_005f1ef0(currentNode); // call handler on matching node
        }
        currentNode = reinterpret_cast<int*>(currentNode[1]); // next node at +0x04
    }
}