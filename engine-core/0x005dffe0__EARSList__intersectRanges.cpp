// FUNC_NAME: EARSList::intersectRanges
// Address: 0x005dffe0
// This function computes the intersection of two ranges within the same list.
// Parameters:
//   outFirst, outSecond: output pair (head of intersection, tail of intersection)
//   listHeadA, listHeadB: must be either nullptr or equal to 'this' (the list)
//   nodeA, nodeB: arbitrary nodes within the list.
// Behavior depends on whether nodeA is the last node (sentinel->prev).

void __thiscall EARSList::intersectRanges(Node*& outFirst, Node*& outSecond,
                                          Node* listHeadA, Node* nodeA,
                                          Node* listHeadB, Node* nodeB)
{
    // +0x1c: pointer to sentinel node
    Node* sentinel = *(reinterpret_cast<Node**>(reinterpret_cast<char*>(this) + 0x1c));
    // sentinel->prev is last node (offset 0)
    Node* lastNode = sentinel->prev;

    // Sanity check: listHeadA must be either null or equal to this list
    if ((listHeadA != nullptr) && (listHeadA != reinterpret_cast<Node*>(this)))
    {
        // assertion failure (FUN_00b97aea)
        __debugbreak();
    }

    if (nodeA == lastNode)
    {
        sentinel = *(reinterpret_cast<Node**>(reinterpret_cast<char*>(this) + 0x1c));
        if ((listHeadB != nullptr) && (listHeadB != reinterpret_cast<Node*>(this)))
        {
            __debugbreak();
        }
        if (nodeB == lastNode)
        {
            // Special case: both ranges are at the very end → empty the list
            // Call destructor on node at sentinel+4 (likely the first node's data)
            // offset +4 is next pointer, here reinterpreted as data address
            FUN_005e1350(*(reinterpret_cast<uint32_t*>(sentinel + 4)));
            // Reset sentinel to point to itself (empty list)
            sentinel->next = sentinel;  // +4
            sentinel->prev = sentinel;  // +0
            *(reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0x20)) = 0; // count
            outFirst = reinterpret_cast<Node*>(this);
            outSecond = sentinel;
            return;
        }
    }

    // Search loop: advance nodeA until it matches nodeB
    while (true)
    {
        if ((listHeadA != nullptr) && (listHeadA != listHeadB))
        {
            __debugbreak();
        }
        if (nodeA == nodeB) break;

        // Advance through the list using internal helpers
        FUN_005e09e0();   // possibly increment or helper
        FUN_005dec30(this, reinterpret_cast<someType*>(local8), listHeadA, nodeA);
    }

    outFirst = listHeadA;
    outSecond = nodeA;
}