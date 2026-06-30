// FUNC_NAME: createGameObject
// Function at 0x006838a0 - Allocates a game object of size 0x160 and initializes it.

int __thiscall createGameObject(void* thisPtr, int someParam) {
    // Stack struct passed as creation info to the allocator
    struct CreationInfo {
        int type;    // +0x0 - set to 2
        int flags;   // +0x4 - set to 0x10
        int padding; // +0x8 - set to 0
    } creationInfo;

    creationInfo.type = 2;
    creationInfo.flags = 0x10;
    creationInfo.padding = 0;

    // Allocate memory/object of size 0x160 (352 bytes)
    int success = FUN_0043b980(0x160, &creationInfo, someParam);
    if (success != 0) {
        // If allocation succeeded, call initialization on the object (thisPtr)
        return FUN_006fc6a0(thisPtr);
    }
    return 0;
}