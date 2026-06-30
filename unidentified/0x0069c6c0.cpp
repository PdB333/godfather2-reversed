// FUN_0069c6c0: heapSiftDown (min-heap priority queue down-heap operation)
// Function address: 0x0069c6c0
// Handles sifting a node down in an array of 8-byte elements (key is first byte)

void heapSiftDown(void* heapArray, int startIndex, int endIndex, void* arg4, void* arg5) {
    int childIdx;
    int currentIdx = startIndex;
    int parentIdx = startIndex * 2; // left child index (0-based? No, 1-based array? StartIndex acts as current note position)

    // Standard array heap: children are at 2*i+1 and 2*i+2, but here indices seem 0-based with +2 offset?
    // Actually logic: iVar3 = param_2 (startIndex) then iVar1 = param_2 * 2 (left child)
    // Then while (iVar2 = iVar1 + 2) < param_3  ... compare bytes at iVar2*8 and (iVar2-1)*8? Wait careful:
    // Access: byte at (heapArray + iVar2 * 8) and (heapArray - 8 + iVar2 * 8) => (heapArray + (iVar2-1)*8)
    // That means we're comparing child indices iVar2 and iVar2-1, i.e., left child (2i+1) and right child (2i+2) in standard 0-based heap.
    // iVar1 = parentIdx * 2? Let's re-derive:
    // Given startIndex = i, left child index = 2*i+1, right = 2*i+2.
    // Here iVar1 = param_2 * 2 = 2*startIndex.
    // Then iVar2 = iVar1 + 2 = 2*startIndex + 2. That would be right child in 0-based if left is 2*startIndex+1? Actually left = 2*startIndex+1, right = 2*startIndex+2. So iVar2 is right child index when startIndex is considered 0-based? Let's test: if startIndex=0, left=1, right=2. iVar2 = 0*2+2=2 => right. Then compare byte at index 2*8 and index 1*8 (child 2 vs child 1). That picks the smaller child.
    // Then if (byte at right < byte at left) -> use right; else use left? Actually condition: if *(byte*)(heapArray + iVar2*8) < *(byte*)(heapArray - 8 + iVar2*8) => if (heapArray[right]) < (heapArray[right-1]) i.e., heapArray[right] < heapArray[left]. So if right key < left key, choose right (iVar2), else iVar2 = iVar1+1 (left child).
    // Then swap current node with the smaller child (8-byte copy).
    // Then continue down.
    // So it's a standard min-heap sift-down.

    while (1) {
        childIdx = parentIdx + 2; // right child index (2*currentIdx + 2)
        if (childIdx >= endIndex) {
            break; // out of range -> handle only one child or exit
        }
        // Compare right and left child keys
        if (*(byte*)((char*)heapArray + childIdx * 8) < *(byte*)((char*)heapArray + (childIdx - 1) * 8)) {
            // right child is smaller than left, use right
            // childIdx already points to right
        } else {
            childIdx = parentIdx + 1; // use left child
        }
        // Copy child's 8 bytes to current node (overwrite)
        *(unsigned int*)((char*)heapArray + currentIdx * 8) = *(unsigned int*)((char*)heapArray + childIdx * 8);
        *(unsigned int*)((char*)heapArray + currentIdx * 8 + 4) = *(unsigned int*)((char*)heapArray + childIdx * 8 + 4);
        // Move down
        currentIdx = childIdx;
        parentIdx = childIdx * 2;
    }

    // Handle the case where only left child exists (childIdx == endIndex)
    if (childIdx == endIndex) {
        // Swap current node with the left child (the last element)
        *(unsigned int*)((char*)heapArray + currentIdx * 8) = *(unsigned int*)((char*)heapArray + (endIndex - 1) * 8);
        *(unsigned int*)((char*)heapArray + currentIdx * 8 + 4) = *(unsigned int*)((char*)heapArray + (endIndex - 1) * 8 + 4);
        currentIdx = endIndex - 1; // new position is the parent of the last element
    }

    // Call the other heap adjustment function (probably sift-up or build-heap continuation)
    // FUN_0069c4b0(heapArray, currentIdx, startIndex, arg4, arg5);
    // (We cannot inline because it's a separate function; but we can call it with proper signature)
    void FUN_0069c4b0(void* heapArray, int currentIdx, int startIndex, void* arg4, void* arg5);
    FUN_0069c4b0(heapArray, currentIdx, startIndex, arg4, arg5);
}