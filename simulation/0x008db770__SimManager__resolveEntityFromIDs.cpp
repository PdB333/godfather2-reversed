// FUNC_NAME: SimManager::resolveEntityFromIDs
void __thiscall SimManager::resolveEntityFromIDs(int thisPtr, uint32_t* idPair) {
    int nodePtr = FUN_004544a0(*idPair, idPair[1]); // lookup node from two IDs
    if (nodePtr != 0) {
        *(int*)(thisPtr + 0x138) = nodePtr - 0x58; // store parent object (adjust from node offset)
    }
}