// FUNC_NAME: getParentNpc
// Function at 0x00800a90: Given a component pointer (this), retrieves the parent NPC if its active flag is set.
// Offsets: +0x74c = pointer to parent NPC's child component pointer (or offset), +0x1a8 = active flag (char)
int __fastcall getParentNpc(void* component) {
    int* parentPtr = *(int**)((char*)component + 0x74c); // +0x74c: pointer to parent's child component or sentinel
    if (parentPtr != 0 && (int)parentPtr != 0x48) {      // 0x48 is sentinel meaning no valid parent
        int* parentBase = (int*)((char*)parentPtr - 0x48); // Subtract 0x48 to get base address of parent
        if (*(char*)((char*)parentBase + 0x1a8) == 1) {   // +0x1a8: active flag (1 = alive/active)
            return (int)parentBase;
        }
    }
    return 0;
}