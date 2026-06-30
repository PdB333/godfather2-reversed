// FUNC_NAME: UnknownClass::releaseChildObjects
void UnknownClass::releaseChildObjects(void)
{
    // Release first child object at +0x8
    int* child1 = *(int**)(this + 8);
    if (child1 != 0) {
        // Clear lowest bit (bit 0) of flags at +0xC
        *(uint*)(child1 + 0xc) &= 0x7ffffffe;
        // If bit 0x20000 is not set, set it and call cleanup function
        if ((*(uint*)(child1 + 0xc) & 0x20000) == 0) {
            *(uint*)(child1 + 0xc) |= 0x20000;
            FUN_0051b120(); // Likely a release/delete callback
        }
        // Clear bit 0x40000 (0xfffbffff = ~0x40000)
        *(uint*)(child1 + 0xc) &= 0xfffbffff;
        // If there is a pointer at +0x8 of child, zero it out
        if (*(int**)(child1 + 8) != 0) {
            **(int**)(child1 + 8) = 0;
            *(int**)(child1 + 8) = 0;
        }
    }

    // Release second child object at +0xC
    int* child2 = *(int**)(this + 0xc);
    if (child2 != 0) {
        *(uint*)(child2 + 0xc) &= 0x7ffffffe;
        if ((*(uint*)(child2 + 0xc) & 0x20000) == 0) {
            *(uint*)(child2 + 0xc) |= 0x20000;
            FUN_0051b120();
        }
        *(uint*)(child2 + 0xc) &= 0xfffbffff;
        if (*(int**)(child2 + 8) != 0) {
            **(int**)(child2 + 8) = 0;
            *(int**)(child2 + 8) = 0;
        }
    }
}