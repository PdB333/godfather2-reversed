// FUNC_NAME: EventScheduler::~EventScheduler

void __fastcall EventScheduler::destroy(EventScheduler* thisPtr)
{
    // Temporary list head used by the callback (possibly to collect items for processing)
    EventListNode localListHead; // Actually just fields: next, prev? We treat it as a node.
    localListHead._prev = nullptr;
    localListHead._next = nullptr;

    // Call base class destructor (likely for memory management or base cleanup)
    BaseClass::destroy(); // FUN_005f5ce0

    // If there's a callback function at offset +0xA4, invoke it.
    // This callback likely modifies lists before destruction.
    if (thisPtr->callbackFn != nullptr)
    {
        // Callback signature: (this, listA head, listB head, &tempList, &tempList)
        thisPtr->callbackFn(thisPtr, &thisPtr->listA, &thisPtr->listB, &localListHead, &localListHead);
    }

    // Remove items from the temporary list (if any were added by callback)
    if (localListHead._prev != nullptr)
    {
        removeNodeFromList(localListHead);
    }

    // Remove all nodes from the main linked list at +0x118
    removeNodeFromList(thisPtr->mainList);

    // Remove nodes from four internal lists: +0x94, +0x88, +0x7C, +0x70
    int listIndex = 3; // Starts at 3 for the first list (offset +0x94)
    int* currentListHead = reinterpret_cast<int*>(reinterpret_cast<char*>(thisPtr) + 0xA0);
    do
    {
        int* headPtr = currentListHead - 3; // Offset by -0xC bytes = +0x94
        removeNodeFromList(headPtr);
        listIndex--;
        currentListHead = headPtr; // Move to next list (offset decreases by 0xC)
    } while (listIndex >= 0);

    // Remove nodes from lists at +0x4C and +0x44
    removeNodeFromList(thisPtr->extraList1);
    removeNodeFromList(thisPtr->extraList2);
}

// Helper: Remove the node from its doubly-linked list (sentinel-style)
void removeNodeFromList(int* headNode)
{
    if (*headNode == 0)
        return;

    int* nodePtr = *reinterpret_cast<int**>(*headNode + 4); // Get next pointer of first node
    if (nodePtr == headNode)
    {
        // List had only one node, update head's next to head's next (empty list)
        *reinterpret_cast<int*>(headNode + 1) = *reinterpret_cast<int*>(headNode + 2);
    }
    else
    {
        // Traverse to find the node that points to headNode as its next
        int* prevNode = nodePtr;
        while (*reinterpret_cast<int*>(prevNode + 1) != headNode)
        {
            prevNode = *reinterpret_cast<int**>(prevNode + 1);
        }
        // Update the previous node's next to headNode's next
        *reinterpret_cast<int*>(prevNode + 1) = *reinterpret_cast<int*>(headNode + 1);
    }
}