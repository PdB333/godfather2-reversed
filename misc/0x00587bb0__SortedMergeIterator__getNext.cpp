// FUNC_NAME: SortedMergeIterator::getNext
int __fastcall SortedMergeIterator::getNext(void* /*unused*/, MergeState* state)
{
    // state layout:
    // +0x00: searchKey (int)
    // +0x04: currentA (int* pointer to a slot in an array of SortedNode*)
    // +0x08: currentB (int* pointer to a slot in array)
    // +0x0C: end (int* end of the same array)

    SortedNode** currentA = reinterpret_cast<SortedNode**>(state->currentA);
    SortedNode** currentB = reinterpret_cast<SortedNode**>(state->currentB);
    SortedNode** end = reinterpret_cast<SortedNode**>(state->end);
    int searchKey = state->searchKey;

    // Helper: extract an element value from a SortedNode* (used for comparison)
    // If bit5 of flags byte is set and id >= 2, use id; else use the node pointer itself as integer
    auto extractKey = [](SortedNode* node) -> int {
        if ((node->flags & 0x20) != 0 && node->id >= 2) {
            return node->id;
        } else {
            return reinterpret_cast<int>(node);
        }
    };

    // Similarly, extract a priority (used for tie-breaking) - actually 5th int (offset +0x14)
    auto extractPriority = [](SortedNode* node) -> int {
        if ((node->flags & 0x20) != 0 && node->id >= 4) {
            return node->priority;  // offset +0x14
        } else {
            return 0;
        }
    };

    // --- A is exhausted ---
    if (currentA == nullptr)
    {
        if (currentB == nullptr)
        {
            return 0;  // both empty
        }

        // Take element from B
        int result = reinterpret_cast<int>(*currentB);   // current element pointer
        SortedNode** nextB = currentB + 1;               // advance iterator
        state->currentB = reinterpret_cast<int>(nextB);

        if (nextB < end)
        {
            // Peek at the next element in B
            SortedNode* nextNode = *nextB;
            int nextKey = extractKey(nextNode);
            if (nextKey == searchKey)
            {
                // If next element matches search key, leave iterator pointing to it
                return result;
            }
        }

        // Otherwise, invalidate iterator (mark as exhausted)
        state->currentB = 0;
        return result;
    }

    // --- Both iterators are valid ---
    if (currentB != nullptr)
    {
        // Compare priorities of the two current elements
        SortedNode* nodeA = *currentA;
        SortedNode* nodeB = *currentB;
        int prioA = extractPriority(nodeA);
        int prioB = extractPriority(nodeB);

        if (prioB < prioA)
        {
            // B has lower priority -> take from B
            int result = reinterpret_cast<int>(*currentB);
            SortedNode** nextB = currentB + 1;
            state->currentB = reinterpret_cast<int>(nextB);

            if (nextB < end)
            {
                SortedNode* nextNode = *nextB;
                int nextKey = extractKey(nextNode);
                if (nextKey == searchKey)
                {
                    return result;
                }
            }

            state->currentB = 0;
            return result;
        }
    }

    // --- Take from A (default, or when B is exhausted or has higher priority) ---
    int result = reinterpret_cast<int>(*currentA);
    SortedNode** nextA = currentA + 1;
    state->currentA = reinterpret_cast<int>(nextA);

    if (nextA < end)
    {
        SortedNode* nextNode = *nextA;
        int nextKey = extractKey(nextNode);
        if (nextKey == searchKey)
        {
            return result;
        }
    }

    state->currentA = 0;
    return result;
}