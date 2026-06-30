// FUNC_NAME: QueueManager_pushEntry
// Function at 0x005a6710: Adds an entry to a circular buffer queue (size 0x14 per entry) with reference counting for object pointers.
// The queue is stored at this+0x1400 (head pointer?) and this+0x1404 (write pointer).
// Entry layout: [flag(4)=1, param4(4), obj1(4), obj2(4), param3(4)] total 0x14 bytes.
// param1 and param2 are object pointers that must be reference-counted if they are valid object types.
// param4 and param3 are additional data.

void __thiscall QueueManager_pushEntry(void* thisPtr, uint param4, void* param1, void* param2, uint param3)
{
    uint* puVar1;
    uint uVar2;
    // thisPtr is stored in ESI
    uint* writePtr = *(uint**)((int)thisPtr + 0x1404); // current write position in queue
    uint* headPtr  = (uint*)((int)thisPtr + 0x1400);  // pointer to head (maybe base of buffer)
    uint newWrite  = (uint)writePtr + 0x14;             // advance by entry size

    // Wrap if new write reaches head (circular buffer)
    if ((uint*)newWrite == headPtr) {
        newWrite = (uint)thisPtr; // wrap to start? Actually wraps to thisPtr as base? This is unusual but matches decompile.
    }

    // Validate write pointer is within buffer range
    if (newWrite != *headPtr) { // only proceed if not full?
        // Assertions: write pointer must be >= thisPtr and > headPtr? Actually checks:
        if (*(uint*)((int)thisPtr + 0x1404) < (uint)thisPtr) {
            FUN_0059bf00(); // assert/error
        }
        if (headPtr <= *(uint**)((int)thisPtr + 0x1404)) {
            FUN_0059bf00(); // assert/error
        }

        // Write entry at current write pointer
        *(uint*)writePtr = 1;               // flag
        *(uint*)((int)writePtr + 4) = param4;
        *(void**)((int)writePtr + 8) = param1;
        // Reference count param1 if it's a non-null object of certain types
        if (param1 != (void*)DAT_0119cbbc) {
            uVar2 = *(uint*)param1 & 0x7fff;
            if (uVar2 != 0x19 &&
                ((~(uint)(*(uint*)param1 >> 0xf) & 1) != 0 ||
                 (uVar2 != 0xb && uVar2 != 0x18 && uVar2 != 0x17))) {
                FUN_0059c230(param1); // addRef
            }
        }
        *(void**)((int)writePtr + 0xc) = param2;
        // Reference count param2 similarly
        if (param2 != (void*)DAT_0119cbbc) {
            uVar2 = *(uint*)param2 & 0x7fff;
            if (uVar2 != 0x19 &&
                ((~(uint)(*(uint*)param2 >> 0xf) & 1) != 0 ||
                 (uVar2 != 0xb && uVar2 != 0x18 && uVar2 != 0x17))) {
                FUN_0059c230(param2); // addRef
            }
        }
        *(uint*)((int)writePtr + 0x10) = param3;
        // Update write pointer
        *(uint*)((int)thisPtr + 0x1404) = newWrite;
    }
}