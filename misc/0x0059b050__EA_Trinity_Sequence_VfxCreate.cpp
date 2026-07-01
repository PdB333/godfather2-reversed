// Xbox PDB: EA::Trinity::Sequence::VfxCreate
// FUNC_NAME: VFXManager::createVFXInstance
void __fastcall VFXManager::createVFXInstance(int this)
{
    int vfxDefIndex;
    int freeSlotIndex;
    int slotIndex;
    int *vfxInstance;
    uint uVar5;

    // Check if VFX definition index is valid (100 = invalid/end marker)
    if (*(short *)(*(int *)(this + 8) + 2) != 100) {
        (**(code **)(*DAT_01205590 + 4))(); // Assert or error handler
    }

    vfxDefIndex = *(int *)(this + 8); // +0x8: VFX definition pointer
    freeSlotIndex = *(int *)(this + 0x1bc); // +0x1BC: VFX slot manager
    slotIndex = *(int *)(freeSlotIndex + 0x34); // +0x34: Current free slot index

    if (slotIndex != -1) {
        // Mark slot as used by setting to next free slot
        *(undefined4 *)(freeSlotIndex + 0x34) = *(undefined4 *)(*(int *)(freeSlotIndex + 0x30) + slotIndex * 4);
        // Mark old slot as -2 (invalid/freed)
        *(undefined4 *)(*(int *)(freeSlotIndex + 0x30) + slotIndex * 4) = 0xfffffffe;
    }

    // Store slot index in VFX instance array (offset +0x9C from this, indexed by byte at this+0x9A)
    *(char *)(*(byte *)(this + 0x9a) + 0x9c + this) = (char)slotIndex;

    if (*(char *)(*(byte *)(this + 0x9a) + 0x9c + this) == -1) {
        (**(code **)(*DAT_01205590 + 8))
                  (DAT_01205590,
                   "The Trinity create new vfx index has exceeded the allocated array boundaries. Make sure VFX are being freed properly during the IGC!"
                  );
    }

    uVar5 = (uint)*(byte *)(*(byte *)(this + 0x9a) + 0x9c + this);
    freeSlotIndex = *(int *)(this + 0x1bc);

    // Verify slot is actually free (-2 marker)
    if (*(int *)(*(int *)(freeSlotIndex + 0x30) + uVar5 * 4) != -2) {
        (**(code **)(*DAT_01205590 + 4))(); // Assert
    }

    vfxInstance = *(int **)(*(int *)(freeSlotIndex + 0x2c) + uVar5 * 4); // +0x2C: VFX instance array
    if (vfxInstance != (int *)0x0) {
        // Call virtual function at vtable+4 to initialize VFX instance
        (**(code **)(*vfxInstance + 4))
                  (this, *(undefined4 *)(vfxDefIndex + 4), vfxDefIndex + 8, vfxDefIndex + 0x18, vfxDefIndex + 0x58);
        
        if (*(byte *)(this + 0x9a) == 0) {
            vfxInstance[0x1b] = 0; // +0x6C: Some state/flag
            *(char *)(this + 0x9a) = *(char *)(this + 0x9a) + 1;
            return;
        }

        // Handle additional VFX instances (linked list chain)
        freeSlotIndex = *(int *)(this + 0x1bc);
        uVar5 = (uint)*(byte *)(*(byte *)(this + 0x9a) + 0x9b + this);
        if (*(int *)(*(int *)(freeSlotIndex + 0x30) + uVar5 * 4) != -2) {
            (**(code **)(*DAT_01205590 + 4))(); // Assert
        }
        vfxInstance[0x1b] = *(int *)(*(int *)(freeSlotIndex + 0x2c) + uVar5 * 4); // Link to next instance
        *(char *)(this + 0x9a) = *(char *)(this + 0x9a) + 1;
        return;
    }

    // Error: VFX instance is null
    (**(code **)(*DAT_01205590 + 4))(); // Assert
    return;
}