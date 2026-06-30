// FUNC_NAME: DebugUtils::printEntityInfo
void DebugUtils::printEntityInfo(int entityId, int param2, int param3)
{
    // Temporary buffer for string construction (local_10)
    char buffer[12]; // Actually used as int array, but likely for string building
    int* localPtr = reinterpret_cast<int*>(buffer);
    code* funcPtr = nullptr;

    // Get a string pointer from some internal table via entityId
    char** stringPtr = reinterpret_cast<char**>(FUN_0049a5b0(localPtr, entityId));
    char* str = *stringPtr;
    if (str == nullptr) {
        str = reinterpret_cast<char*>(&DAT_0120546e); // Some fallback string
    }

    // Print the string
    FUN_004d3d90(str);

    // If the buffer indicates something (maybe a vtable or callback), call it
    if (buffer[0] != 0) {
        // local_4 was captured from somewhere? Actually local_4 is uninitialized here.
        // Probably the function pointer was stored in localPtr[2]? Ghidra might have misassigned.
        // Assume it's a callback stored in the buffer.
        if (funcPtr != nullptr) {
            funcPtr(buffer[0]);
        }
    }

    // Check if the entity is not "local" (param3+4 == 1 might mean local/player)
    if (*(int*)(param3 + 4) != 1) {
        int index = DAT_00e506b4 * 8; // stride for some table
        int searchResult[3];
        searchResult[0] = (int)((char)entityId); // low byte only? suspicious
        searchResult[1] = 0;

        // Search in a global hash table or array starting from DAT_00e506b8
        char* found = reinterpret_cast<char*>(FUN_0069c7c0(&DAT_00e506b8, &DAT_00e506b8 + index, searchResult, 0));
        if (found != reinterpret_cast<char*>(&DAT_00e506b8 + index)) {
            int entryData = *(int*)(found + 4);
            if (entryData != 0) {
                int nameOrInfo = FUN_0068b910(entryData);
                FUN_004d3d90(nameOrInfo);
            }
        }
    }
}