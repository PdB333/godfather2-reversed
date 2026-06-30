// FUNC_NAME: InputDeviceManager::releaseController
// Address: 0x0060b4c0
// Destructor/release function for a controller device. Iterates 16 controller slots,
// finds the slot holding this controller, detaches it, then destroys the controller object.
// param_1: pointer to a pointer to the controller object (i.e., Controller**)
void InputDeviceManager::releaseController(int **param_1)
{
    // Global array of 16 controller slots (each slot: state, pointer)
    // Base address: DAT_011da7f0 (padded due to Ghidra offset)
    // Slot structure: offset 0: state (int), offset 4: pointer to Controller (Controller*)
    // The code actually uses a pointer that points to the 'pointer' field, thus piVar1[-1] is state,
    // and *piVar1 is the controller pointer.
    int *slotPtr = &DAT_011da7f4; // Points to first slot's pointer field (base+4)
    for (uint slotIndex = 0; slotIndex < 16; ++slotIndex)
    {
        // Check if this slot holds the controller we're releasing
        if (*slotPtr == *param_1)
        {
            // If slot state is not 1 (possible states: 0=free, 1=active), set it to 1
            if (slotPtr[-1] != 1)
            {
                // Call g_inputManager->setSlotState(slotIndex, 1)
                // g_inputManager = DAT_01205750
                (**(code **)(*DAT_01205750 + 0x198))(DAT_01205750, slotIndex, 1);
                slotPtr[-1] = 1;
            }
            // Clear the slot's controller pointer if it is not null
            if (*slotPtr != 0)
            {
                // Call g_inputManager->clearSlot(slotIndex, 0, 0, 0)
                (**(code **)(*DAT_01205750 + 400))(DAT_01205750, slotIndex, 0, 0, 0);
                *slotPtr = 0;
            }
        }
        slotPtr += 4; // Move to next slot's pointer field (8 bytes per slot, but pointer jumps 4 bytes because each int is 4)
    }

    // Now destroy the controller object itself
    int *controllerPtr = (int *)*param_1;
    if (controllerPtr != (int *)0x0)
    {
        // Call controller->vtable[2] (offset 8) - likely destructor
        (**(code **)(*controllerPtr + 8))(controllerPtr);
        *param_1 = 0; // Nullify the user's pointer
    }

    // Handle a child pointer (offset 8 in the caller's structure? Or param_1 is actually a larger struct?)
    int *childPtr = (int *)param_1[2];
    if (childPtr != (int *)0x0)
    {
        if (DAT_01205868 != (int *)0x0)
        {
            // Call g_childManager->removeChild(childPtr, 0)
            (**(code **)(*DAT_01205868 + 4))(childPtr, 0);
        }
        // Condition: if param_1 != childPtr, set child pointer to null
        // This condition is always true since param_1 is address of pointer, childPtr is different.
        if (param_1 != childPtr)
        {
            param_1[2] = 0;
        }
    }
    return;
}