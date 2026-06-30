// FUN_0046a100: SimGroup::getGroupData
// Reconstructed C++ function from Ghidra decompilation
// Purpose: Validates that the given object is a 'Group' type and retrieves group data from a global table.

// Global data pointer (likely a pointer to a global structure containing an array of group data)
extern int* gGroupDataTable; // DAT_01223414

// Helper function to get group index from object (returns pointer to index)
int* getGroupIndex(int arg, const char* typeName); // FUN_00627e50

// Helper function to set group info on object
void setGroupInfo(void* object, int groupDataPtr); // FUN_0046aac0

// Debug print function
void debugPrint(const char* format, ...); // FUN_00627bd0

// Software interrupt for debug break
void debugBreak(); // swi(3)

int SimGroup::getGroupData(void* object)
{
    int* groupIndexPtr;
    int result;

    // Attempt to get the group index from the object
    groupIndexPtr = getGroupIndex(1, "Group");
    if (groupIndexPtr != nullptr) {
        // Retrieve group data from global table using the index
        // Structure: gGroupDataTable + 4 -> pointer to array of group data (size 0x1C each)
        // Offset 0x10 within each group data entry
        int* tablePtr = *(int**)((char*)gGroupDataTable + 4);
        int groupDataOffset = 0x10 + (*groupIndexPtr) * 0x1C;
        int groupData = *(int*)((char*)tablePtr + groupDataOffset);
        setGroupInfo(object, groupData);
        return 1; // Success
    }

    // Object is not a valid 'Group' type
    debugPrint("Object is not a '%s'.\n", "Group");
    debugBreak(); // Trigger breakpoint
    // Note: swi(3) typically causes a breakpoint; for reconstruction we call debugBreak()
    // The original assembly likely raised a debug exception, but we simulate with a call
    result = debugBreak(); // unreachable but kept for structure
    return result;
}