// FUNC_NAME: SceneObject::updateSpatialSlots
// Address: 0x00475d30
// Role: Processes an array of 8 16-byte spatial slots (transforms), finds or creates associated objects, 
//        iterates over their children, calls an update function, and logs debug info.

// Assumed constants (from global data)
#define SPATIAL_SLOT_COUNT 8        // (0x9C - 0x1C) / 16
#define SPATIAL_SLOT_SIZE 16        // 4 ints

// Magic sentinel values representing an empty slot (not all zero, but specific pattern)
#define EMPTY_SLOT1 0xBABDBABA
#define EMPTY_SLOT2 0xBEEFBEEF
#define EMPTY_SLOT3 0xEAC15A55
#define EMPTY_SLOT4 0x91100911

extern int g_DebugEnableFlag;                // DAT_01223418
extern char *g_DebugStringBuffer;            // DAT_012067c4
extern int g_DebugStringCounter;             // _DAT_012067c8

// Helper functions (closest guesses based on usage)
int __fastcall FindSlotObject(void *slotPtr, int typeHash, int parentId);  // FUN_0043d0d0
int __fastcall AllocateSlotObject(int unknown, void *slotPtr, int typeHash, int parentId); // FUN_0043d020
int __fastcall IterateSlotChildren(void *slotPtr, int prevChild);         // FUN_00445ff0 (returns 0 if no more)
bool __fastcall StringIsEmpty(char *str);                                 // FUN_00402080 (returns '\0' if empty)
void __fastcall StringAppend(char *str, int appendValue);                 // FUN_004084d0 (appends 0x8000)

void __thiscall SceneObject::updateSpatialSlots(int thisObj, int *updateTickPtr)
{
    char cVar1;
    int childObj;
    uint shouldProcess;
    int *slotPtr;

    // Only process if the update tick matches the object's stored last update tick
    if (*updateTickPtr == *(int *)(thisObj + 0x14)) {
        // Determine whether to process slots based on a global flag and a bit in this object
        shouldProcess = -(uint)((*(byte *)(thisObj + 0x9C) & 1) != 0) & g_DebugEnableFlag;

        // Iterate over each 16-byte spatial slot in the array starting at offset 0x1C
        for (slotPtr = (int *)(thisObj + 0x1C); 
             slotPtr != (int *)(thisObj + 0x9C); 
             slotPtr = slotPtr + 4) // +4 ints = +16 bytes per iteration
        {
            // If processing is enabled and the slot is non-zero and not a sentinel pattern
            if ((shouldProcess != 0) &&
                ((slotPtr[0] != 0 || slotPtr[1] != 0 || slotPtr[2] != 0 || slotPtr[3] != 0) &&
                 ((slotPtr[0] != EMPTY_SLOT1 || slotPtr[1] != EMPTY_SLOT2 ||
                   slotPtr[2] != EMPTY_SLOT3 || slotPtr[3] != EMPTY_SLOT4))))
            {
                // Try to find an existing object for this slot; if not found, allocate one
                int existingObj = FindSlotObject(slotPtr, 0x137726B7, -1);
                int allocatedObj = AllocateSlotObject(0, slotPtr, 0x137726B7, -1);
                if (existingObj == 0 && allocatedObj != 0) {
                    // Set a flag at offset +4 (e.g., "dirty" or "new")
                    *(uint *)(allocatedObj + 4) |= 1;
                }
            }

            // Iterate over children (or similar linked list) associated with this slot
            childObj = IterateSlotChildren(slotPtr, 0);
            while (childObj != 0) {
                if (((*(byte *)(childObj + 0x40) & 1) != 0) &&
                    // Call a virtual function at index 2 (vtable at child+0x3C)
                    ((**(code **)(*(int *)(childObj + 0x3C) + 8))(), g_DebugStringBuffer != 0))
                {
                    cVar1 = StringIsEmpty(g_DebugStringBuffer);
                    if (cVar1 == '\0') {
                        g_DebugStringCounter++;
                        StringAppend(g_DebugStringBuffer, 0x8000);
                    }
                }
                childObj = IterateSlotChildren(slotPtr, childObj);
            }
        }
    }
}