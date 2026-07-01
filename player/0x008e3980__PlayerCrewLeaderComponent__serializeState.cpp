// FUNC_NAME: PlayerCrewLeaderComponent::serializeState
// Function at 0x008e3980 - serializes crew leader state into a buffer (for network or save)
// Uses __thiscall, this = param_1, outBuffer = param_2

void __thiscall PlayerCrewLeaderComponent::serializeState(uint* this, uint* outBuffer)
{
    char cVar1;
    int* piVar2;
    int* piVar3;
    uint uVar4;
    int iVar5;
    undefined8* puVar6;
    uint* puVar7;
    uint* puVar8;
    int loopIndex; // local_c[0]
    int local_1; // local_c[1] - reused
    int local_2; // local_c[2] - reused

    // Copy position and base state (offsets 0x20-0x28 are Vector3, 0x84 is likely a scalar)
    outBuffer[0] = *(uint*)(this + 0x20); // position x
    outBuffer[1] = *(uint*)(this + 0x24); // position y
    outBuffer[2] = *(uint*)(this + 0x28); // position z
    outBuffer[3] = *(uint*)(this + 0x2c); // rotation or other
    outBuffer[4] = *(uint*)(this + 0x84); // e.g., health or state flag

    loopIndex = 0;
    puVar7 = (uint*)(this + 0xC0); // pointer to first crew slot data (each slot size 0x5C)
    puVar8 = outBuffer + 8;         // output offset for first slot (buffer[8..17] per slot)

    do {
        // Clear the output slot (10 uint32 = 40 bytes)
        puVar8[1] = 0;
        *puVar8 = 0;
        puVar8[-1] = 0;
        puVar8[-2] = 0;
        puVar8[2] = 0;
        puVar8[6] = 0;
        puVar8[3] = 0;
        puVar8[4] = 0;
        puVar8[5] = 0;

        // Clear bit 2 (0x4) of slot flags at slot offset 0x0
        *puVar7 = *puVar7 & 0xfffffffb;
        // Store flags in output at puVar8[-3] (which is outBuffer[5] for first slot, etc.)
        puVar8[-3] = *puVar7;

        // Call some lookup function on slot's data (offset -0x38 bytes from slot start? puVar7 + -0xe)
        // FUN_00446100 likely gets a pointer to an entity/game object from an ID
        piVar2 = (int*)FUN_00446100(puVar7 + -0xe, 0);
        if (piVar2 != (int*)0x0) {
            local_1 = 0;
            // Call vtable method at offset 0x10 on the entity - seems to check a tag/type
            cVar1 = (**(code**)(*piVar2 + 0x10))(0x254cce9, &local_1);
            loopIndex = 0; // Reset loopIndex to reuse
            // piVar3 derived from flag test - probably pointer to something
            piVar3 = (int*)(-(uint)(cVar1 != '\0') & (uint)this);
            cVar1 = (**(code**)(*piVar2 + 0x10))(0x43c8ec5b, &loopIndex);
            uVar4 = -(uint)(cVar1 != '\0') & (uint)local_2; // local_2 was set by above call?
            if (piVar3 == (int*)0x0) {
                if (uVar4 != 0) {
                    // Copy from child object's offset 0x180
                    puVar8[2] = *(uint*)(uVar4 + 0x180);
                }
            }
            else {
                // Call vtable method at offset 0x160 to get some sub-object (e.g., mountable)
                iVar5 = (**(code**)(*piVar3 + 0x160))();
                // Copy position from that sub-object (offsets 0x20-0x2C)
                puVar8[-2] = *(uint*)(iVar5 + 0x20);
                puVar8[-1] = *(uint*)(iVar5 + 0x24);
                *puVar8 = *(uint*)(iVar5 + 0x28);
                puVar8[1] = *(uint*)(iVar5 + 0x2c);

                if ((loopIndex == 1) || (loopIndex == 2)) {
                    // Get global time or timestamp from FUN_00790cd0()
                    puVar6 = (undefined8*)FUN_00790cd0();
                    // Copy a double (8 bytes) into output[3] and [4]
                    *(undefined8*)(puVar8 + 3) = *puVar6;
                    puVar8[5] = *(uint*)(puVar6 + 1); // copy another int
                    // Check flag bit 1 (0x2) in the slot's flags (stored earlier)
                    if ((*(byte*)(puVar8 + -3) & 2) != 0) {
                        // Copy from slot's sub-sub-object (puVar7[5] = slot+0x14) + 0x38
                        puVar8[6] = *(uint*)(puVar7[5] + 0x38);
                    }
                }
            }
        }
        loopIndex = loopIndex + 1;
        puVar8 = puVar8 + 10; // advance to next output slot (40 bytes)
        puVar7 = puVar7 + 0x17; // advance to next slot (0x17*4 = 0x5C bytes)
    } while (loopIndex < 3);

    // Copy additional state beyond the 3 slots
    outBuffer[0x23] = *(uint*)(this + 0x1A8); // e.g., current crew size or something
    outBuffer[0x28] = *(uint*)(this + 0x1CC); // e.g., reputation or time
    outBuffer[0x29] = *(uint*)(this + 0x1D0);
    outBuffer[0x2A] = *(uint*)(this + 0x1D4);
    outBuffer[0x2B] = *(uint*)(this + 0x1D8);

    // Handle optional sub-object at offset 0x1C4 (maybe a weapon slot)
    iVar5 = *(int*)(this + 0x1C4);
    if ((iVar5 != 0) && (iVar5 != 0x48)) {
        if (iVar5 != 0) {
            iVar5 = iVar5 - 0x48; // convert to offset? unique mapping
        }
        // Copy position from that sub-object (offsets 0x20-0x2C)
        outBuffer[0x24] = *(uint*)(iVar5 + 0x20);
        outBuffer[0x25] = *(uint*)(iVar5 + 0x24);
        outBuffer[0x26] = *(uint*)(iVar5 + 0x28);
        outBuffer[0x27] = *(uint*)(iVar5 + 0x2C);
        return;
    }
    // If no valid sub-object, zero out those output slots
    outBuffer[0x26] = 0;
    outBuffer[0x25] = 0;
    outBuffer[0x24] = 0;
    outBuffer[0x27] = 0;
    return;
}