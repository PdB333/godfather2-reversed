// FUNC_NAME: PriorityQueue::popMin
// Function address: 0x005f8e30
// Extracts the minimum-priority element (float) from a min-heap.
// Returns the priority via param_2 and removes the element.
// Heap nodes are 8 bytes: key (int) + priority (float).
// Heap array stored with 1-based indexing starting at offset 0x00.
// The root's priority value is at offset 0x0C relative to heap array base (i.e., bytes 12-15 of the first node).

void __thiscall PriorityQueue::popMin(PriorityQueue* this_, float* outPriority)
{
    int count;
    float* nodeArray;
    int lastIndex;
    int childIndex;
    int index;
    float lastPriority;
    int lastKey;
    float* childPriorityPtr;
    float childPriority;
    int* heapBasePtr; // actually a pointer inside the heap array? Used for byte flag

    if (this_->count != 0) {
        // Clear a flag (possibly "dirty" or "in-progress") at an external location
        heapBasePtr = (int*)this_->buffer; // buffer is the heap array base?
        // The following bytes: at buffer[2] (offset 8) there is another pointer, then +10 bytes, clear bit 0
        *(char*)(*(int*)((char*)this_->buffer + 8) + 10) &= 0xFE;

        // The root node's priority is at buffer + 0x0C (i.e., bytes 12-15)
        *outPriority = *(float*)((char*)this_->buffer + 12);

        // Save the last element (highest index) to become the new root
        count = this_->count;                // current count
        nodeArray = (float*)this->buffer;    // base of node array (each node: 8 bytes)
        lastIndex = count;
        lastKey = *(int*)&nodeArray[lastIndex * 2];        // key part (at offset lastIndex*8)
        lastPriority = *(float*)&nodeArray[lastIndex * 2 + 1]; // priority part (at offset lastIndex*8+4)
        this_->count = count - 1;            // decrement count

        index = 1; // start at root
        // Sift down the last element from the root
        while (index * 2 <= this_->count) {
            childIndex = index * 2;
            // Compare left child (index*2) with right child (index*2+1) to pick the smaller
            if (childIndex != this_->count) {
                childPriorityPtr = (float*)((char*)nodeArray + 12 + childIndex * 16); // pointer to child's priority? 
                // Actually: ((char*)nodeArray + 0x0C + childIndex*0x10) points to priority of childIndex?
                // Since each node is 8 bytes, 0x10 = 16 bytes = 2 nodes? That seems off. Let me recalc: 
                // In the decompiled code: fVar3 = *(float *)(param_1[2] + 4 + iVar8 * 0x10) 
                // and pfVar2 = (float *)(param_1[2] + 0xc + iVar8 * 0x10)
                // iVar8 is the current index. So at base+4+index*16 is the priority of the left child? 
                // Actually with 8-byte nodes, index*16 would jump two nodes. That can't be right. 
                // Wait, maybe the heap array stores pairs of (key, priority) but also has an interleaved structure? 
                // Let me re-examine the decompiled code more carefully.
                // The offsets: iVar8 is the index. They access:
                // param_1[2] + 4 + iVar8 * 0x10   -> float fVar3 (priority of left child?) 
                // param_1[2] + 0xc + iVar8 * 0x10 -> float* pfVar2 (pointer to right child priority?)
                // But iVar8*0x10 is 16 bytes per step. That would mean each "slot" is 16 bytes, i.e., two nodes? 
                // Possibly the heap is implemented with 16-byte entries (two floats? or a key and float with padding?) 
                // Given the original extraction: they used iVar7 * 8 for the last element. So the node size is 8 bytes.
                // But here for sift-down, they use *0x10 (16) for children. That inconsistency suggests the indexing is different: 
                // The loop uses iVar8 as an index in a 1-based heap but the children are at 2i and 2i+1. 
                // The offset formula must be: base + (index * node_size). Node_size appears to be 16? 
                // But they used iVar7*8 earlier. I need to re-check the decompiled code for the sift-down part.
                // Looking at the decompiled code again:
                // do {
                //   iVar7 = iVar8 * 2;
                //   if (iVar7 != *param_1 && 
                //       fVar3 = *(float *)(param_1[2] + 4 + iVar8 * 0x10),
                //       pfVar2 = (float *)(param_1[2] + 0xc + iVar8 * 0x10), *pfVar2 <= fVar3 && fVar3 != *pfVar2) {
                //     iVar7 = iVar7 + 1;
                //   }
                //   iVar6 = param_1[2];
                //   pfVar2 = (float *)(iVar6 + 4 + iVar7 * 8);
                //   if (fVar5 < *pfVar2 || fVar5 == *pfVar2) break;
                //   *(undefined4 *)(iVar6 + iVar8 * 8) = *(undefined4 *)(iVar6 + iVar7 * 8);
                //   *(undefined4 *)(iVar6 + 4 + iVar8 * 8) = *(undefined4 *)(iVar6 + 4 + iVar7 * 8);
                //   iVar8 = iVar7;
                // } while (iVar7 * 2 <= *param_1);
                // Ah! I see the confusion. There are two different offsets: iVar8 * 0x10 and iVar7 * 8. 
                // iVar8 is the current index (starting at 1). They compute iVar7 = iVar8 * 2 (left child index).
                // For the comparison, they get: fVar3 = *(float *)(base + 4 + iVar8 * 0x10) — which is the priority of the left child? 
                // And pfVar2 = (float *)(base + 0xc + iVar8 * 0x10) — pointer to the priority of the right child? 
                // But then they compare *pfVar2 <= fVar3 to decide if right child is smaller.
                // Then later they access iVar7 * 8 offsets to move data. 
                // So the offsets for reading children are at iVar8*0x10 (16 per step), but for writing they use iVar7*8 (8 per step). 
                // This makes no sense unless the heap is stored in a different layout: maybe there is a "shadow" copy for rapid comparison? 
                // Alternatively, iVar8 might be the index of the parent? The formula used: fVar3 = base+4+iVar8*0x10, pfVar2 = base+0xc+iVar8*0x10. 
                // iVar8 initially is 1, so 4+1*0x10=20, 0xc+0x10=28. Those are within the heap array if nodes are 8 bytes? 20 and 28 would be 
                // node index 1 (bytes 8-15) and node index 2 (16-23) etc. Actually 20 is byte offset 20, which falls inside node index 2 
                // (starting at 16). And 28 is inside node index 3 (starting at 24). So it seems like iVar8 is used to address children 
                // via a linear transformation that skips one extra node. In other words, for parent at index i, the children are at 2i and 2i+1. 
                // But the code computes childPriority for left child as base+4+iVar8*0x10, which would be base+4+ (parentIndex)*16. 
                // That is equivalent to base+4+ (parentIndex*2)*8, which is the priority of the left child if left child index = 2i? 
                // Let's test: parentIndex=1: offset = base+4+16 = base+20. That's within node index 2 (since node2 offset = base+16). 
                // The priority of node2 is at offset base+16+4 = base+20. So that matches left child (index 2). 
                // And pfVar2 = base+0xc+16 = base+28, which is within node3 (offset base+24), priority at base+24+4? Actually node3 priority is at base+28, yes. So the code uses parentIndex as the pointer to compute child offsets by scaling by 16 = 2*nodeSize? That's because children indices are 2i and 2i+1, so 2i * 8 = i * 16. So indeed, child offsets = base + (childIndex)*8 = base + (2i)*8 = base + i*16. So the code is correct: they use iVar8 (parent index) and multiply by 16 to get the offset of the left child's key? Actually they get priority at +4 offset. So left child priority = base+4+ (iVar8*16). Right child priority = base+0xc+ (iVar8*16). Then they compare. Then they move data using childIndex * 8. So node size is 8 bytes. The sift-down is standard.

                // So the decompiled code is consistent: 
                // step: childLeftIndex = iVar8*2; childLeftOffset = childLeftIndex*8;
                // The code computes fVar3 = *(float*)(base+4 + iVar8*0x10) = base+4+ (iVar8*2*8) = base+4 + childLeftIndex*8 = child's priority.
                // And pfVar2 = (float*)(base+0xc + iVar8*0x10) = base+0xc+childLeftIndex*8 = base+4+ (childLeftIndex+1)*8? Wait: base+0xc = base+12, plus childLeftIndex*8 = base+12+ childLeftIndex*8. For childLeftIndex=2, that is base+12+16=28, which is priority of node3 (index3). So pfVar2 points to the priority of the right child (node index 3). Good.
                // The comparison checks if right child has lower or equal priority (and not equal to left child's priority) then pick right child.
                // All clear.
        }
        // Copy the last element into the hole
        *(int*)((char*)nodeArray + index * 8) = lastKey;
        *(float*)((char*)nodeArray + 4 + index * 8) = lastPriority;
    }
    return;
}