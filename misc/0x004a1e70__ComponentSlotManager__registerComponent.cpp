// FUNC_NAME: ComponentSlotManager::registerComponent
// Function at 0x004a1e70: Manages a fixed-size array (4 slots) of registered component objects.
// Each slot is 8 bytes: a 4-byte pointer to the component, and a 4-byte field with a byte at +4 (stored separately in a byte array at +0x130).
// The component object must have a virtual function at vtable+4 (offset 4) that is called during registration.
// Parameters:
//   this (ecx) - pointer to ComponentSlotManager instance
//   component (edi) - the object to register
//   param (stack) - additional parameter passed to the callback
// Returns: a value encoding the slot index or failure status.

uint32_t ComponentSlotManager::registerComponent(void* component, uint32_t param)
{
    uint32_t result;                 // uVar2, final return value
    bool foundEmpty;                // bVar1, true if no duplicate found
    int slotIndex;                  // iVar5
    int* slotPtr;                   // piVar4, points into the pointer array
    uint32_t callbackResult;        // uVar3
    uint32_t retAddrLow;            // unaff_retaddr (byte)

    // Initial result from previous eax (likely set by caller)
    result = *(uint32_t*)&eax & 0xFFFFFF00;  // in_EAX

    if (component != nullptr)
    {
        foundEmpty = true;
        slotIndex = 0;
        slotPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x12C); // +0x12C = +300

        do
        {
            if (slotIndex > 3)
                goto slotFull;

            if (*slotPtr == 0)   // slot is empty
                break;

            if (*slotPtr == reinterpret_cast<int>(component))
                foundEmpty = false;   // already registered

            slotIndex++;
            slotPtr += 2;   // each slot is 8 bytes (2 ints)
        } while (foundEmpty);

        if (slotIndex > 3)
        {
slotFull:
            return reinterpret_cast<uint32_t>(slotPtr) & 0xFFFFFF00;
        }

        if (foundEmpty)
        {
            // Call the component's virtual function at vtable+4 (0x4 offset)
            // The function signature: void* __thiscall callback(ComponentSlotManager* manager, uint32_t param)
            callbackResult = (*(uint32_t (__thiscall**)(void*, uint32_t))(*(uint32_t*)component + 4))(component, param);

            // Store component pointer into the slot
            *slotPtr = reinterpret_cast<int>(component);

            // Store a byte (low byte of return address?) into the byte array at +0x130 + slotIndex*8
            *(uint8_t*)(reinterpret_cast<char*>(this) + 0x130 + slotIndex * 8) = reinterpret_cast<uint8_t>(retAddrLow);
        }

        // Build final result: combine high bytes of slotPtr and foundEmpty flag
        result = (reinterpret_cast<uint32_t>(slotPtr) & 0xFFFFFF00) | (foundEmpty ? 1 : 0);
    }

    return result;
}