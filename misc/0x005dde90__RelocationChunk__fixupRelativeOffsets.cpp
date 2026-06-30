// FUNC_NAME: RelocationChunk::fixupRelativeOffsets
uint __thiscall RelocationChunk::fixupRelativeOffsets(int this, uint originalBase)
{
    uint uVar2;
    uint uVar3;
    int iVar1;

    uVar2 = originalBase & 0xffffff00;
    // Check if this chunk is of type 0xf
    if (*(int*)(this + 0x20) == 0xf) {
        // If relocation has not been applied yet
        if ((*(byte*)(this + 0x24) & 1) == 0) {
            // Adjust first list head pointer (relative to this)
            if (*(int*)(this + 0x2c) != 0) {
                *(int*)(this + 0x2c) = *(int*)(this + 0x2c) + this;
            }
            // Adjust second list head pointer
            if (*(int*)(this + 0x34) != 0) {
                *(int*)(this + 0x34) = *(int*)(this + 0x34) + this;
            }
            // First list: iterate over items, adjust their internal pointer at +0x28
            iVar1 = *(int*)(this + 0x2c);
            if ((iVar1 != 0) && (uVar2 = 0, *(int*)(this + 0x28) != 0)) {
                do {
                    if (*(int*)(iVar1 + 0x28) != 0) {
                        *(int*)(iVar1 + 0x28) = *(int*)(iVar1 + 0x28) + iVar1;
                    }
                    iVar1 = *(int*)(iVar1 + 0x28); // next item (already absolute after adjustment?)
                    uVar2 = uVar2 + 1;
                } while (uVar2 < *(uint*)(this + 0x28));
            }
            // Second list: iterate over items, adjust their internal pointer at +0x1c
            uVar2 = *(uint*)(this + 0x34);
            if ((uVar2 != 0) && (uVar3 = 0, *(int*)(this + 0x30) != 0)) {
                do {
                    if (*(int*)(uVar2 + 0x1c) != 0) {
                        *(int*)(uVar2 + 0x1c) = *(int*)(uVar2 + 0x1c) + uVar2;
                    }
                    uVar2 = *(uint*)(uVar2 + 0x1c);
                    uVar3 = uVar3 + 1;
                } while (uVar3 < *(uint*)(this + 0x30));
            }
            // Mark relocation as applied
            *(uint*)(this + 0x24) = *(uint*)(this + 0x24) | 1;
        }
        // Return base with low byte set to 1 (relocation done)
        uVar2 = (originalBase & 0xffffff00) | 1;
    }
    return uVar2;
}