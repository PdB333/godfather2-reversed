// FUNC_NAME: GameObject::destroy
void __thiscall GameObject::destroy(GameObject* thisPtr)
{
    int iVar1;
    
    // Check if already destroyed (bit 0 of flags at +0x34)
    if ((*(uint8*)(thisPtr + 0x34) & 1) == 0) {
        // Mark as destroying
        *(uint32*)(thisPtr + 0x34) |= 1;
        
        // Release sub-object stored at +0x16c (second arg 0)
        SubObject::release(*(void**)(thisPtr + 0x16c), 0);
        
        // The following condition appears dead due to flag being set above,
        // but in the original binary it may be an else-if or re-checked.
        // Possibly the flag is cleared by SubObject::release or other logic.
        if ((*(uint8*)(thisPtr + 0x34) & 1) == 0 &&          // re-check flag
            *(void**)(thisPtr + 0x40) != nullptr &&
            (iVar1 = Manager::isValid(*(void**)(thisPtr + 0x40)), iVar1 != 0) &&
            ((~(uint8)(*(uint32*)(iVar1 + 0x84) >> 5) & 1) != 0)) {
            return;  // Early exit if manager condition met
        }
        
        // Release another sub-object at +0x19c
        if (*(void**)(thisPtr + 0x19c) != nullptr) {
            Pointer::release(*(void**)(thisPtr + 0x19c));
            *(void**)(thisPtr + 0x19c) = nullptr;
        }
    }
    return;
}