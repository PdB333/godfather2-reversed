// FUNC_NAME: GameObject::unregisterSubObjects
void __fastcall GameObject::unregisterSubObjects(GameObject* this) {
    // Clear the "isActive" flag at +0x484
    this->activeFlag = 0; // +0x484

    // Unregister up to 4 sub-objects stored at offsets +0x710, +0x714, +0x718, +0x71c
    int subObject = this->subObject1; // +0x710
    if (subObject != 0) {
        uint* listPtr = (uint*)(gGlobalSystem + 0x14); // DAT_01206880 + 0x14
        **(void***)(gGlobalSystem + 0x14) = &PTR_LAB_01124690; // Write type tag
        *listPtr = *listPtr + 4; // Advance to next slot
        *(int*)*listPtr = subObject;    // Store sub-object pointer
        *listPtr = *listPtr + 4; // Advance
        *(int*)*listPtr = this + 0x54; // Store offset to parent container
        *listPtr = *listPtr + 4; // Advance
        *(char*)*listPtr = 1;         // Mark as pending removal (count?)
        *listPtr = (*listPtr + 4) & 0xFFFFFFFC; // Align to 4 bytes
    }
    subObject = this->subObject2; // +0x714
    if (subObject != 0) {
        // Same pattern for second sub-object
        uint* listPtr = (uint*)(gGlobalSystem + 0x14);
        **(void***)(gGlobalSystem + 0x14) = &PTR_LAB_01124690;
        *listPtr = *listPtr + 4;
        *(int*)*listPtr = subObject;
        *listPtr = *listPtr + 4;
        *(int*)*listPtr = this + 0x54;
        *listPtr = *listPtr + 4;
        *(char*)*listPtr = 1;
        *listPtr = (*listPtr + 4) & 0xFFFFFFFC;
    }
    subObject = this->subObject3; // +0x718
    if (subObject != 0) {
        // Same pattern
        uint* listPtr = (uint*)(gGlobalSystem + 0x14);
        **(void***)(gGlobalSystem + 0x14) = &PTR_LAB_01124690;
        *listPtr = *listPtr + 4;
        *(int*)*listPtr = subObject;
        *listPtr = *listPtr + 4;
        *(int*)*listPtr = this + 0x54;
        *listPtr = *listPtr + 4;
        *(char*)*listPtr = 1;
        *listPtr = (*listPtr + 4) & 0xFFFFFFFC;
    }
    subObject = this->subObject4; // +0x71c
    if (subObject != 0) {
        // Same pattern
        uint* listPtr = (uint*)(gGlobalSystem + 0x14);
        **(void***)(gGlobalSystem + 0x14) = &PTR_LAB_01124690;
        *listPtr = *listPtr + 4;
        *(int*)*listPtr = subObject;
        *listPtr = *listPtr + 4;
        *(int*)*listPtr = this + 0x54;
        *listPtr = *listPtr + 4;
        *(char*)*listPtr = 1;
        *listPtr = (*listPtr + 4) & 0xFFFFFFFC;
    }
}