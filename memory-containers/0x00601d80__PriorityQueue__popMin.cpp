// FUNC_NAME: PriorityQueue::popMin
// Address: 0x00601d80
// Role: Pop the minimum element from a min-heap priority queue.
// Structure: Heap with fields: +0x00: Element* data (array), +0x04: int size (count of elements)
// Each Element is 16 bytes: first 4 bytes float key, next 8 bytes payload, last 4 bytes padding? (actually two 8-byte halves but first half contains key)
// The heap uses 1‑based indexing internally (root at index 1), but the stored array starts at index 0 as sentinel or unused.

void __thiscall PriorityQueue::popMin(Element* outElement, Heap* heap)
{
    Element* data = (Element*)heap->data;      // array base pointer (+0x00)
    int size = heap->size;                     // current element count (+0x04)
    int newSize = size - 1;

    // Copy the minimum (root at index 1 in 1‑based, i.e., array index 0) to output
    // In 1‑based heap, root is data[1]; but here they store root at index 0?
    // The move below replaces root with last element, so the root is at index 0.
    *outElement = data[0];                     // stores two 8‑byte values

    // Replace root with last element (index newSize in 1‑based? actually array index newSize*2? confusion from 8‑byte access)
    // Actually the code uses 16‑byte stride (two 8‑byte units), so last element at offset (newSize*16) from base.
    // That suggests the array is 0‑based with element size 16.
    Element* rootPtr = (Element*)heap->data;
    Element* lastPtr = rootPtr + newSize;
    *rootPtr = *lastPtr;                       // memcpy root = last

    // Call some helper (might be debug verification or update size)
    heap->size = newSize; // implied? but not shown; FUN_006027d0 might set it
    FUN_006027d0(); // Possibly checkHeapIntegrity or update internal pointer

    // Sift down starting from root (index 1 in 1‑based logic used below)
    int childIdx = 1;             // left child of root (1‑based index)
    int parentIdx = 0;            // parent index (1‑based, root is 1, but here stored as 1‑based index in code)

    if (1 < newSize)   // more than one element left to sift
    {
        do {
            int rightChildIdx = childIdx + 1;
            int smallerChildIdx;

            // Check if right child exists and compare left vs right
            if (rightChildIdx < newSize)
            {
                float rightKey = data[rightChildIdx].key;
                float leftKey = data[childIdx].key;

                // If left key <= right key, OR parent key <= right key, then the smaller is left? 
                // Confusing, but logic essentially selects the smaller child for comparison.
                if (leftKey <= rightKey || data[parentIdx].key <= rightKey)
                    goto compareWithParent;
            }
            else
            {
compareWithParent:
                // Compare parent key with left child key
                float parentKey = data[parentIdx].key;
                float leftChildKey = data[childIdx].key;
                if (parentKey <= leftChildKey)
                    return;   // heap property satisfied
                smallerChildIdx = childIdx;
            }

            // Swap parent with the smaller child
            Element* parentElem = &data[parentIdx];
            Element* childElem = &data[smallerChildIdx];
            Element temp = *parentElem;
            *parentElem = *childElem;
            *childElem = temp;

            // Move down: parent becomes child, child becomes its left child (2*child+1)
            parentIdx = smallerChildIdx;
            childIdx = 2 * smallerChildIdx + 1;   // next left child index (1‑based)
        } while (childIdx < newSize);
    }

    // Update heap size (likely already done in caller or inside FUN_006027d0)
    // heap->size = newSize; // if not done elsewhere
}