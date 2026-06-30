// FUNC_NAME: ArrayContainer::removeAt
void __thiscall ArrayContainer::removeAt(void* thisPtr, uint index) {
    int* piVar1;
    undefined4* puVar2;
    int iVar3;
    int* piVar4;
    int count;
    
    // Count stored at offset +0xA00
    count = *(int*)((int)thisPtr + 0xA00);
    if (index >= (uint)count) {
        return;
    }
    
    if (index < count - 1) {
        // Remove element at index by shifting subsequent elements left
        piVar4 = (int*)((int)thisPtr + 0x30 + index * 0x28); // pointer to element at index
        do {
            // Shift element content: copy last int of current to first int of previous? (complex)
            // Actually, this is shifting the entire 0x28-byte structure left by one slot.
            piVar4[-0xb] = piVar4[-1]; // Move one field? Possibly handles linked list node update
            if (piVar4 + -10 != piVar4) { // Always true, but check for null? Actually piVar4-10 is the previous element's start
                iVar3 = *piVar4;
                piVar1 = piVar4 + -10; // pointer to previous element
                if (piVar4[-10] != iVar3) {
                    // Release old reference
                    if (piVar4[-10] != 0) {
                        FUN_004daf90(piVar1); // release function
                    }
                    *piVar1 = iVar3; // assign new pointer
                    if (iVar3 != 0) {
                        // Update doubly linked list: set previous node's next to piVar1
                        piVar4[-9] = *(int*)(iVar3 + 4);
                        *(int**)(iVar3 + 4) = piVar1;
                    }
                }
            }
            // Copy remaining 8 ints (bytes 8-39 of the structure)
            *(undefined8*)(piVar4 + -8) = *(undefined8*)(piVar4 + 2);
            piVar4[-6] = piVar4[4];
            piVar4[-5] = piVar4[5];
            piVar4[-4] = piVar4[6];
            piVar4[-3] = piVar4[7];
            
            piVar4 += 10; // move to next element (0x28 bytes)
            index++;
        } while (index < (*(int*)((int)thisPtr + 0xA00) - 1));
    }
    
    // Decrement count
    *(int*)((int)thisPtr + 0xA00) = count - 1;
    
    // Clear the last (now unused) element
    puVar2 = (undefined4*)((int)thisPtr + (*(int*)((int)thisPtr + 0xA00)) * 0x28);
    if (puVar2[2] != 0) {
        FUN_004daf90(puVar2 + 2);
    }
    // Reset to default values
    *puVar2 = &PTR_LAB_00e2f0c0; // virtual function table
    puVar2[1] = 0xFFFFFFFF;
    puVar2[2] = 0;
    puVar2[3] = 0;
    *(undefined1*)(puVar2 + 7) = 0;
    puVar2[6] = 0;
    puVar2[5] = 0;
    puVar2[4] = 0;
    puVar2[8] = DAT_01205228;
    puVar2[9] = DAT_00d5ccf8;
}