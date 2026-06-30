// FUNC_NAME: GrowingArray::addElement
void GrowingArray::addElement(short param1, short param2, char param3)
{
    int *thisPtr = unaff_EDI; // this pointer stored in EDI
    int capacity = thisPtr[2]; // +0x08 - current capacity
    int count = (short)thisPtr[0xe]; // +0x38 - current element count
    
    if (capacity <= count) {
        // Need to grow the array
        int oldData = thisPtr[0x14]; // +0x50 - old data pointer
        int oldArray1 = thisPtr[0x11]; // +0x44 - old array1 pointer
        int oldArray2 = thisPtr[0x12]; // +0x48 - old array2 pointer
        int oldArray3 = thisPtr[0x13]; // +0x4c - old array3 pointer
        
        // Calculate new capacity: (capacity >> 1) + 32 + capacity
        int newCapacity = (capacity >> 1) + 0x20 + capacity;
        int elementSize = newCapacity + 4; // +4 for header
        
        // Allocate new memory block
        int newBlock = FUN_00672f60(elementSize * 0xd); // 13 arrays of elementSize
        thisPtr[0x14] = newBlock; // +0x50 - new data pointer
        
        // Calculate offsets for the three sub-arrays
        int array1 = newBlock + elementSize * 4;
        thisPtr[0x11] = array1; // +0x44
        
        int array2 = array1 + elementSize * 4;
        thisPtr[0x12] = array2; // +0x48
        
        int array3 = array2 + elementSize;
        thisPtr[0x13] = array3; // +0x4c
        
        thisPtr[2] = newCapacity; // +0x08 - update capacity
        
        // Copy existing elements
        int copyCount = (short)thisPtr[0xe] + 4; // copy count + 4 extra
        if (0 < copyCount) {
            int offset1 = oldArray1 - array1;
            int offset2 = oldArray2 - array1;
            int offset3 = array2 - array1;
            int offset4 = oldArray3 - array3;
            
            do {
                *(short *)array1 = *(short *)(offset1 + (int)array1);
                *(short *)(offset3 + (int)array1) = *(short *)((int)array1 + offset2);
                *(char *)array3 = *(char *)(offset4 + (int)array3);
                array1 = (short *)((int)array1 + 2);
                array3 = (short *)((int)array3 + 1);
                copyCount--;
            } while (copyCount != 0);
        }
        
        // Free old memory if needed
        int vtable = *thisPtr;
        if (oldData == *(int *)(vtable + 0x38)) {
            *(int *)(vtable + 0x70) = 1; // Mark as using internal buffer
        }
        else if (oldData != 0) {
            // Free allocated memory
            *(int *)(*(int *)(vtable + 0xc) + *(int *)(oldData + -8) * 4) = 0;
            *(int *)(vtable + 4) = *(int *)(vtable + 4) - 1;
            (*DAT_01206694)(oldData + -0x10); // Free memory
        }
    }
    
    // Add new element at the end
    int currentCount = (short)thisPtr[0xe];
    *(short *)(thisPtr[0x11] + currentCount * 2) = param1; // +0x44 - array1
    *(short *)(thisPtr[0x12] + currentCount * 2) = param2; // +0x48 - array2
    *(char *)(currentCount + thisPtr[0x13]) = param3; // +0x4c - array3
    *(short *)(thisPtr + 0xe) = (short)currentCount + 1; // +0x38 - increment count
}