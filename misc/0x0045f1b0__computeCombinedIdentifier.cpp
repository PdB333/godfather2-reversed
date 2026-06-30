// FUNC_NAME: computeCombinedIdentifier
uint __fastcall computeCombinedIdentifier(void* object, uint baseIdentifier) {
    uint result = baseIdentifier & 0xFFFFFF00; // Clear low byte; baseIdentifier passed in EAX
    if (*(int*)((char*)object + 0x218) != 0) { // +0x218: pointer to override component
        result = FUN_00573440(); // Get override value from component
    }
    return result;
}