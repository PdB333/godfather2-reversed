// FUNC_NAME: NPCListComponent::populateFlagArrayFromList
void __thiscall NPCListComponent::populateFlagArrayFromList(NPCListComponent* this) {
    // counter at +0x78 (uint) - only run once when zero
    if (*(int*)((char*)this + 0x78) == 0) {
        // linked list head at +0x1c (Node*)
        for (Node* node = *(Node**)((char*)this + 0x1c); node != 0; node = *(Node**)((char*)node + 0x1c)) {
            // extract bit 2 from node flags (+0x14) and store as byte in array at +0x7c
            *(unsigned char*)((char*)this + 0x7c + *(int*)((char*)this + 0x78)) =
                (unsigned char)((*(unsigned int*)((char*)node + 0x14) >> 2) & 1);
            // increment counter
            *(int*)((char*)this + 0x78) = *(int*)((char*)this + 0x78) + 1;
            // call yield/processing function (0x00624ca0) with argument 0
            FUN_00624ca0(0);
        }
    }
}