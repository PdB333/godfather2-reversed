// FUNC_NAME: SortedKeyList::findFirstGreaterOrEqual
/**
 * @brief Traverses a sorted singly-linked list to find the first node whose key is >= the target key.
 * 
 * The list nodes are at `node` (passed in EAX), each with a next pointer at +0x04 and an index
 * into a global key table at +0x0C. The target key structure is pointed to by `targetKey` (passed in EDI).
 * The key is a compound of up to 5 32-bit fields starting at keyBase+0x08 (first field), then +0x0C, +0x10, +0x14, +0x18.
 * keyBase is computed as (node->index * 0x20 + this->tableBase) where this->tableBase is at this+0x10.
 * 
 * The loop walks the list until a node with key >= target is found, leaving that node pointer in EAX.
 * 
 * @param node Pointer to the first node of the list (passed in EAX by previous code).
 * @param targetKey Pointer to the target key structure (passed in EDI by previous code).
 * @return Pointer to the node with key >= target (returned in EAX).
 * @note Uses __fastcall: node in ECX? Actually Ghidra indicates param_1 (this) in ECX, node in EAX, target in EDI.
 *       For reconstruction we treat node as first parameter (actually EAX) and target as second (EDI).
 *       To match calling convention we use __fastcall with "this" in ECX but there is no this? We'll adapt.
 */
int* __fastcall SortedKeyList::findFirstGreaterOrEqual(int* node, int* targetKey)
{
    int* currentNode = node;
    int* target = targetKey;  // actually passed in EDI, but we treat as second parameter

    while (true)
    {
        // Fetch index into the global key table from the current node
        int keyIndex = *(int*)(currentNode + 0x0C);
        // Compute the base address of the key entry in the global table
        int keyBase = keyIndex * 0x20 + *(int*)(this + 0x10); // this->keyTableBase

        // Compare first field (offset +0x08 from keyBase)
        uint firstField = *(uint*)(keyBase + 0x08);
        uint targetFirst = *(uint*)(target + 0x08);
        bool isLess = (firstField < targetFirst);
        bool isEqual = (firstField == targetFirst);

        if (isEqual)
        {
            // Compare second field (+0x0C)
            uint secondField = *(uint*)(keyBase + 0x0C);
            uint targetSecond = *(uint*)(target + 0x0C);
            isLess = (secondField < targetSecond);
            isEqual = (secondField == targetSecond);
            if (isEqual)
            {
                // Compare third field (+0x10)
                uint thirdField = *(uint*)(keyBase + 0x10);
                uint targetThird = *(uint*)(target + 0x10);
                isLess = (thirdField < targetThird);
                isEqual = (thirdField == targetThird);
                if (isEqual)
                {
                    // Compare fourth field (+0x14)
                    uint fourthField = *(uint*)(keyBase + 0x14);
                    uint targetFourth = *(uint*)(target + 0x14);
                    isLess = (fourthField < targetFourth);
                    isEqual = (fourthField == targetFourth);
                    if (isEqual)
                    {
                        // Compare fifth field (+0x18)
                        uint fifthField = *(uint*)(keyBase + 0x18);
                        uint targetFifth = *(uint*)(target + 0x18);
                        // Only need to compute isLess for the last field; isEqual not used further
                        isLess = (fifthField < targetFifth);
                    }
                }
            }
        }

        // If current node's key is NOT less than target, break out of the loop.
        // That is, stop when the current node's key is greater or equal.
        if (!isLess || isEqual)
            break;

        // Otherwise, move to the next node in the list.
        currentNode = *(int**)(currentNode + 0x04); // next pointer
    }

    // currentNode now points to the first node whose key >= targetKey.
    // The caller will read EAX for the result.
    return currentNode;
}