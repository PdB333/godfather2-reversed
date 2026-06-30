// FUNC_NAME: StateInfo::getStateString
char* __fastcall StateInfo::getStateString(int* thisState)
{
    int stateType = *thisState; // offset 0x00: state type
    if (stateType == 0) {
        // state 0: return pointer to embedded string at offset 0x04
        return (char*)(thisState + 1); // (thisState + 1) points to char array at +4
    }
    if (stateType == 1) {
        // state 1: obtain string from another function
        int* result = (int*)FUN_004da080();  // likely getStateNameForOne() - returns char*
        return (char*)result;
    }
    if (stateType == 2) {
        // state 2: return pointer at offset 0x14 (0x50 bytes from start)
        return (char*)(int*)thisState[0x14]; // treat as char* pointer stored at +0x50
    }
    // unknown state
    return "(unknown)";
}