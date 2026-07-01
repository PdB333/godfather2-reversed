// FUNC_NAME: processSlotArray
void __fastcall processSlotArray(int* slotArray)
{
    // slotArray points to an array of 4 slots, each 12 bytes (3 ints)
    // Slot structure: [0x00] pointer to an object, [0x04] unknown, [0x08] unknown
    int slotIndex = 4;
    do {
        int* slotPtr = slotArray;
        if (*slotPtr != 0) {
            int* objectPtr = (int*)*slotPtr; // dereference slot's first field to get object pointer
            int vtable = *objectPtr;          // first field of object is vtable pointer
            void* context = getUpdateContext(); // FUN_004d94d0 - returns some context/manager
            // Call virtual function at vtable offset 0x14 (likely a method like update or process)
            // The function takes one argument (context) and uses the object as 'this' (__thiscall)
            (**(code**)(vtable + 0x14))(context);
        }
        slotArray += 3; // advance to next slot (12 bytes)
        slotIndex--;
    } while (slotIndex != 0);
}