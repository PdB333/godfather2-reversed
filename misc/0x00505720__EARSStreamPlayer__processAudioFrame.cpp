// FUNC_NAME: EARSStreamPlayer::processAudioFrame

void EARSStreamPlayer::processAudioFrame(int param_1)
{
    int *piVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    uint uVar4;
    int iVar5;
    int iVar6;
    undefined4 *manager; // unaff_ESI
    int *ediVar; // unaff_EDI

    FUN_00533cc0(); // criticalSectionEnter (lock)

    *manager = &PTR_FUN_00e37fe0; // set vtable or object pointer

    // Check if the stream is active (field at +0x0D)
    if (*(char *)(param_1 + 0x0D) == '\0') {
        // Set fields in the manager structure
        manager[9] = ediVar; // store some pointer
        manager[10] = 0;     // clear a field

        // Check if the pointer ediVar points to a valid resource (all zeros?)
        if ((*ediVar != 0 || ediVar[1] != 0) || (ediVar[2] != 0 || ediVar[3] != 0)) {
            // Get a resource index or ID
            uVar4 = FUN_004e9270(); // getAudioResourceIndex

            if (((uVar4 != 0) &&
                (((uVar4 != 0xffffffff && (uVar4 < 0x1000)) &&
                  (uVar4 * 0x38 != (uint)(-0x11a0f28)))) &&
                (piVar1 = *(int **)(&DAT_011a0f38 + uVar4 * 0x38), piVar1 != (int *)0x0)) {
                // Increment reference count of the resource
                *piVar1 = *piVar1 + 1;
            }
        }

        // Get values for the audio ring buffer update
        uVar2 = manager[1]; // some manager field
        uVar3 = *(undefined4 *)(param_1 + 8); // stream field at +0x08

        // Update the global audio ring buffer index and elements
        iVar5 = DAT_0119478c + -1;
        iVar6 = DAT_0119478c + 2;
        if (iVar5 < 0) {
            iVar5 = 0x13; // wrap to 19
        } else if (0x13 < iVar6) {
            iVar6 = DAT_0119478c + -0x12; // wrap around
        }

        // Add the values at two positions in the ring buffer
        (&DAT_01194790)[iVar5] = (&DAT_01194790)[iVar5] + (&DAT_01194790)[iVar6];
        DAT_0119478c = iVar5; // advance index

        // Call the main audio output function with many parameters
        FUN_005054a0(manager, *(undefined4 *)(manager[1] + 0x10),
                     CONCAT44(uVar2, ediVar), CONCAT44((&DAT_01194790)[iVar5], uVar3),
                     uVar4, manager[4], manager[5]);
    }
}