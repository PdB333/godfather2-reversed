// FUNC_NAME: EventManager::registerEventHandler
// Address: 0x0090b4e0
// Registers an event handler (param_3) for a specific event type (param_2).
// The manager holds up to 7 fixed-size slots (each 0x24 bytes) starting at offset 0x18.
// Each slot: struct { uint flags; uint eventId; /* 0x24 bytes total */ }
// Returns 1 on success, 0 if no free slot found.

int __thiscall EventManager::registerEventHandler(EventManager* this, uint eventType, void* handler, undefined4 param_4, int preferredSlotIndex, undefined4 param_6)
{
    int i;
    uint* slot;
    int foundIndex;
    
    if (handler != 0) {
        // Check if handler is already registered using some lookup function
        if (FUN_0090b0a0(handler) != -1) {
            return 1; // Already registered
        }
        
        // If a preferred slot index is given (-1 means none), check that slot first
        if (preferredSlotIndex != -1) {
            slot = (uint*)((int)this + 0x18 + preferredSlotIndex * 0x24);
            if ((*(uint*)((int)this + 0x1c + preferredSlotIndex * 0x24) == eventType) &&
                ((*slot & 1) != 0) &&
                (((*slot >> 1) & 1) == 0)) {
                goto foundSlot;
            }
            preferredSlotIndex = -1;
        }
        
        // Search all 7 slots for a matching event type with status: allocated (bit0=1) but not busy (bit1=0)
        i = 0;
        slot = (uint*)((int)this + 0x18);
        do {
            if ((slot[1] == eventType) && ((*slot & 1) != 0) && (((*slot >> 1) & 1) == 0)) {
                foundIndex = i;
                break;
            }
            i++;
            slot += 9; // advance by 0x24 bytes
            foundIndex = preferredSlotIndex; // remains -1 if not found
        } while (i < 7);
        
        if (foundIndex != -1) {
foundSlot:
            // Get the global singleton's "something" offset
            int globalVal;
            if (*(int**)(DAT_012233a0 + 4) == 0) {
                globalVal = 0;
            }
            else {
                globalVal = **(int**)(DAT_012233a0 + 4) + -0x1f30;
            }
            
            // Call a processing function with the handler, global, param_4, param_6
            FUN_0090aa60(handler, globalVal, param_4, param_6);
            
            // Get the "this" pointer shifted by 0x10 for some sub-object
            int subThis = (this == 0) ? 0 : (int)this + 0x10;
            FUN_00791e70(subThis); // Possibly initializes or updates something
            
            // Get a timestamp or sequence number
            undefined4 uVar3 = FUN_00790150();
            
            // Set something at handler+0x20 with that value
            FUN_008bcf90((int)handler + 0x20, uVar3);
            
            return 1;
        }
    }
    return 0;
}