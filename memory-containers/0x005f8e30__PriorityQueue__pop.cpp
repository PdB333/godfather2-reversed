// FUNC_NAME: PriorityQueue::pop

void __thiscall PriorityQueue::pop(void* this, int& outData)
{
    int* thisPtr = (int*)this;
    if (thisPtr[0] != 0) {
        int* heapBase = (int*)thisPtr[2];
        // Clear a flag in some slot descriptor (bit 0 of byte at offset 0x0A in a structure pointed by heapBase[2])
        byte* flag = (byte*)(heapBase[2] + 10);
        *flag &= 0xfe;

        // Store the output data from header offset 0x0C
        outData = heapBase[3]; // +0x0C

        int size = thisPtr[0]; // number of elements
        // Last element (data and key) - heap is 1-indexed (node index 1 at offset 0x08)
        int lastData = heapBase[size * 2];       // offset + size*8 (since int* arithmetic)
        float lastKey = *(float*)(heapBase + size * 2 + 1); // offset + size*8 + 4
        thisPtr[0] = size - 1; // decrement size

        // Sift down
        int current = 1;
        while (current * 2 <= thisPtr[0]) {
            int child = current * 2;
            // Choose the smaller child (min-heap)
            if (child != thisPtr[0]) {
                float leftKey = *(float*)(heapBase + child * 2 + 1);
                float rightKey = *(float*)(heapBase + (child + 1) * 2 + 1);
                if (rightKey <= leftKey && leftKey != rightKey) {
                    child = child + 1;
                }
            }
            // Compare last key with child key
            float childKey = *(float*)(heapBase + child * 2 + 1);
            if (lastKey < childKey || lastKey == childKey) {
                break;
            }
            // Move child up
            heapBase[current * 2] = heapBase[child * 2];
            *(float*)(heapBase + current * 2 + 1) = *(float*)(heapBase + child * 2 + 1);
            current = child;
        }
        // Place the last element in the correct position
        heapBase[current * 2] = lastData;
        *(float*)(heapBase + current * 2 + 1) = lastKey;
    }
    return;
}