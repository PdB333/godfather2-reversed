// FUNC_NAME: EventManager::dispatchEvents
void __thiscall EventManager::dispatchEvents(void)
{
    int *descriptorList; // +0x10: pointer to array of EventDescriptor structs
    int *currentPtr;
    int *counterPtr;
    int *maxPtr;
    uint *descriptor;
    int *objectPtr;
    int *vtablePtr;
    uint mask;
    int localCount;
    uint savedMask;
    undefined4 stackStruct[2];
    undefined1 stackByte;

    // Global pointer to the EventManager instance (singleton?)
    iVar2 = DAT_0122341c; // EventManager global pointer
    descriptorList = *(int **)(DAT_0122341c + 0x10); // +0x10: list of event descriptors

    currentPtr = (int *)0x0;
    if (descriptorList != (int *)0x0) {
        localCount = 0;
        counterPtr = descriptorList; // used to track current descriptor index
        maxPtr = descriptorList;     // used for limit check (actually same as descriptorList)

        do {
            // Fetch next descriptor if we haven't reached the end of the list
            if (currentPtr < *(int **)(iVar2 + 0x10)) {
                descriptor = (uint *)(*(int *)(iVar2 + 0xc) + localCount); // +0xc: base of descriptor array
                objectPtr = (int *)*descriptor;
                vtablePtr = (int *)descriptor[1];
                mask = descriptor[2];
            }

            // Check if the descriptor is valid and matches the current event mask
            if ((vtablePtr != (int *)0x0) && ((*(uint *)(in_EAX + 0x34) & mask) != 0)) {
                if (*(code **)(in_EAX + 0x38) == (code *)0x0) {
                    // Default: call virtual function on the vtable
                    (**(code **)(*vtablePtr + 0xc))(objectPtr, 0, 0, in_EAX + 0x28); // likely a handler method
                }
                else {
                    // Custom callback at +0x38
                    (**(code **)(in_EAX + 0x38))(vtablePtr, objectPtr, 0, 0, in_EAX + 0x28);
                }
            }

            localCount += 0xc; // each descriptor is 0xC bytes (3 uint32s)
            currentPtr = (int *)((int)currentPtr + 1);
        } while (currentPtr < descriptorList); // loop until all descriptors processed
    }

    // Clear the event flags
    *(undefined4 *)(in_EAX + 0x20) = 0;
    *(undefined4 *)(in_EAX + 0x24) = 0;

    // Reset the event data container at +0x28
    FUN_004086d0(in_EAX + 0x28); // likely clears a queue or buffer
    FUN_00408310(in_EAX + 0x28); // likely resets internal state

    // If there's an attached structure at +0x30, destroy it
    if (*(undefined4 **)(in_EAX + 0x30) != (undefined4 *)0x0) {
        stackStruct[0] = **(undefined4 **)(in_EAX + 0x30); // copy first word
        stackStruct[1] = 0;
        stackByte = 0;
        FUN_00408a00(stackStruct, 0); // likely a destructor / release function
    }

    return;
}