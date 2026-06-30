// FUNC_NAME: SomeContainer::pushElements
// Function at 0x00636260: Pushes a number of 8-byte elements onto an internal stack/buffer.
// Structure offsets:
//   +0x08: endPtr (pointer to end of current data)
//   +0x0c: currentTop (pointer to current top of stack)
//   +0x14: stackPtr (pointer to stack of pointers, decremented by 0x18 per push)
//   +0x30: flags (bit 1: use external source from getSourceBuffer)

void __thiscall SomeContainer::pushElements(int count) {
    undefined4 *sourcePtr;
    undefined4 *destPtr;
    undefined4 *srcIter;
    undefined4 *destIter;
    
    // If flag bit 1 is set, obtain source pointer from external function
    if ((*(byte *)(this + 0x30) & 2) != 0) {
        sourcePtr = (undefined4 *)getSourceBuffer();
    }
    
    // Decrement stack pointer by 0x18 (24 bytes, likely 3 pointers or 3*8 bytes)
    *(int *)(this + 0x14) = *(int *)(this + 0x14) - 0x18;
    
    // Set currentTop to the pointer stored at the new stack position
    destPtr = (undefined4 *)(*(int *)(this + 0x0c) - 8);
    *(undefined4 *)(this + 0x0c) = **(undefined4 **)(this + 0x14);
    
    // Destination starts 8 bytes before the new top
    destIter = destPtr;
    srcIter = sourcePtr;
    
    // Copy up to 'count' elements (each 8 bytes) until source reaches end of destination buffer
    if (count != 0) {
        do {
            if (*(undefined4 **)(this + 0x08) <= srcIter) break;
            *destIter = *srcIter;
            *(destIter + 1) = *(srcIter + 1);
            srcIter += 2;
            destIter += 2;
            count--;
        } while (count != 0);
        
        // Zero out remaining destination slots if count > 0
        for (; 0 < count; count--) {
            *destIter = 0;
            destIter += 2;
        }
    }
    
    // Update end pointer to current destination position
    *(undefined4 **)(this + 0x08) = destIter;
}