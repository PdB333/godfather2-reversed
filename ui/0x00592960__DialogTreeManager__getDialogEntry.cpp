// FUNC_NAME: DialogTreeManager::getDialogEntry
void __fastcall DialogTreeManager::getDialogEntry(void* this, int source, int param3, int param4)
{
    // 'this' points to an output structure (likely a stack-allocated 'DialogEntryResult')
    // The function initializes the result structure from the given 'source' (an NPC or dialog owner)
    // source is at EDX, but stored as first field of output
    int* out = (int*)this;
    out[0] = source;          // +0x00: store source object
    out[1] = param3;          // +0x04: context parameter 1
    out[2] = param4;          // +0x08: context parameter 2
    out[3] = 0;               // +0x0C: flag (unused, always zero)
    
    // Get the data table pointer from the source object (offset +0x70)
    int* dataTable = *(int**)(source + 0x70);
    if (dataTable == 0) {
        out[4] = 0;           // +0x10: null entry pointer
        return;
    }
    
    // dataTable layout: +0x18 = count, +0x1C = array of entries (each 0x18 bytes)
    int count = *(int*)(dataTable + 0x18 / 4);
    int* entries = *(int**)(dataTable + 0x1C / 4);
    short index = *(short*)(source + 0x76);  // source's current selection index
    
    // Check bounds: index must be >= 0 and < count
    if (count > 0 && entries != 0 && index >= 0 && (int)index < count) {
        out[4] = (int)(entries + index * (0x18 / 4)); // pointer to the selected entry
    } else {
        out[4] = 0;
    }
}