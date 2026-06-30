// FUNC_NAME: EARS::StreamManager::handleSequenceData
void __fastcall StreamManager::handleSequenceData(uint *this, char *data)
{
    uint flags;
    uint tempFlags;
    uint *dataPtr;
    undefined4 local_94;
    undefined4 local_90;
    undefined4 local_8c;
    undefined4 local_88;
    undefined1 auStack_78[4];
    undefined1 auStack_74[4];
    uint local_70[8];
    undefined1 auStack_50[76];

    if (data != (char *)0x0) {
        this[1] = (uint)data;
        // Check for "seqb" magic with version 4
        if ((((*data == 's') && (data[1] == 'e')) && (data[2] == 'q')) &&
           ((data[3] == 'b' && (*(int *)(data + 4) == 4)))) {
            // Set flags: bit 0 (0x01) and bit 5 (0x20) - sequence data received
            *this = *this | 0x21;
            // XOR based on some state at ESI+0x40
            tempFlags = (*(int *)(unaff_ESI + 0x40) * 2 ^ *this) & 2 ^ *this;
            *this = tempFlags;
            tempFlags = (*(uint *)(unaff_ESI + 0x40) ^ tempFlags) & 4 ^ tempFlags;
            *this = tempFlags;
            if ((tempFlags & 4) == 0) {
                // No pending data - call some handler
                dataPtr = this + 4;
                local_88 = 0x599469;
                (**(code **)(*DAT_012055a8 + 0x40))();
            }
            else {
                // Extract sequence data from offset 0x1c to 0x28
                local_88 = *(undefined4 *)(data + 0x28);
                dataPtr = local_70;
                local_8c = *(undefined4 *)(data + 0x24);
                local_90 = *(undefined4 *)(data + 0x20);
                local_94 = *(undefined4 *)(data + 0x1c);
                puStack_98 = (undefined1 *)0x5993e9;
                (**(code **)(*DAT_012055a8 + 4))();
                // Process the sequence data
                tempFlags = this[1];
                puStack_98 = auStack_74;
                (**(code **)(*DAT_012055a8 + 4))
                          (*(undefined4 *)(tempFlags + 0xc), *(undefined4 *)(tempFlags + 0x10),
                           *(undefined4 *)(tempFlags + 0x14), 0x3f800000);
                (**(code **)(*DAT_012055a8 + 0x60))(&puStack_98, auStack_78);
                (**(code **)(*DAT_012055a8 + 0x10))(auStack_74, auStack_50);
                (**(code **)(*DAT_012055a8 + 0x4c))(&local_88);
            }
            // Store some value from data + 0xb8
            this[2] = *(uint *)(this[1] + 0xb8);
            // Reset some counters
            this[0x14] = 0;
            this[0x15] = 0;
            FUN_00599720(0);
            // Clear bit 5 (0x20) - sequence data processed
            *this = *this & 0xffffffdf;
            // Check if some threshold is exceeded
            if (DAT_00e2b05c < *(float *)(unaff_ESI + 0x4c)) {
                FUN_00599720(*(float *)(unaff_ESI + 0x4c));
            }
            return;
        }
        // Invalid sequence data - call error handler
        dataPtr = (uint *)0x59937e;
        (**(code **)(*DAT_01205590 + 4))();
    }
    // Null data - call error handler
    dataPtr = (uint *)0x59938b;
    (**(code **)(*DAT_01205590 + 4))();
    return;
}