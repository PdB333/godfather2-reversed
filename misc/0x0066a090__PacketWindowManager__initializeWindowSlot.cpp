// FUNC_NAME: PacketWindowManager::initializeWindowSlot
int __thiscall PacketWindowManager::initializeWindowSlot(uint *slotIndex, int param3)
{
    uint slot = *slotIndex;
    void *tempBuffer;
    int result;
    int local_size;
    int temp_l;
    int iVar3;
    int iVar4;

    tempBuffer = _calloc(4, 0x40); // allocate temporary buffer (4 * 64 = 256 bytes)
    if (tempBuffer == nullptr) {
        return -2;
    }

    local_size = 0;
    temp_l = 0x40; // maybe initial capacity or size
    // Note: local_8 (undefined4) not used further

    result = packetWindowPreInit(); // FUN_00665ce0
    if (result != 0) {
        goto cleanup;
    }

    selectActiveWindow(slot - 1); // FUN_0066a4d0

    if (slot < 0x8000001) {
        // Small slot range: use direct window method
        result = directWindowSetup(&local_size, param3, &local_size, slot - 1); // FUN_0066c4d0
    } else {
        // Larger slot: use alternate window method
        result = alternateWindowSetup(&local_size, param3, &local_size); // FUN_00668ce0
    }

    if (result == 0) {
        iVar4 = slot + 1;
        selectActiveWindow(iVar4); // FUN_0066a4d0

        result = allocateSlotBuffer((slot + 1) * 0x1c); // FUN_00668920, 0x1c = 28 bytes per slot
        if (result == 0) {
            result = addPacketToWindow(&local_size, slotIndex, &local_size, iVar4); // FUN_0066c2f0
        }

        if (result == 0) {
            result = finalizeWindow(this, &local_size); // FUN_0066a780
        }

        if (result == 0) {
            iVar3 = getNextSequence(); // FUN_00665c00
            if (iVar3 == -1) {
                resetWindow(); // FUN_0066a550
                result = clearSlot(iVar4); // FUN_006687e0
                if (result != 0) goto cleanup;
                result = retransmitPackets(this); // FUN_006657c0
                if (result != 0) goto cleanup;
            }

            // Process all active slots until failure
            iVar4 = getNextActiveSlot(); // FUN_00665bd0
            while (iVar4 != -1 && (result = processSlot(this), result == 0)) { // FUN_0066c8d0
                iVar4 = getNextActiveSlot();
            }
        }
    }

cleanup:
    if (tempBuffer != nullptr) {
        _memset(tempBuffer, 0, local_size * 4); // clear portion of buffer
        _free(tempBuffer);
    }
    return result;
}