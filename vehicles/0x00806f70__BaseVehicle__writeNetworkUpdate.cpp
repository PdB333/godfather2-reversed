// FUNC_NAME: BaseVehicle::writeNetworkUpdate
uint __thiscall BaseVehicle::writeNetworkUpdate(void* bitstream, uint dirtyMask, float deltaTime)
{
    float fVar1;
    char cVar2;
    uint uVar3;
    int iVar5;
    float fVar6;
    float tempFloat;
    char local_8[8]; // Stack buffer for finalize

    fVar1 = deltaTime;

    // Write base class update first
    uVar3 = writeStandardUpdate(bitstream, dirtyMask, deltaTime);

    // Handle dirty bit 0: maybe vehicle type or global flag
    cVar2 = checkFlag(dirtyMask & 1);
    if (cVar2 != 0) {
        tempFloat = 0.0f;
        if (*(int*)(g_globals + 0x34) != -1) {
            tempFloat = *(float*)(*(int*)(*(int*)(g_globals + 0x28) + *(int*)(g_globals + 0x34) * 4) + 0x40);
        }
        writeDataToBitstream(0x20, &tempFloat);
    }

    // Handle dirty bit 4: some virtual call result
    cVar2 = checkFlag(dirtyMask >> 4 & 1);
    if (cVar2 != 0) {
        // Call virtual function at index 0x28 on the sub-object at offset 0x59c
        fVar6 = (**(float (__thiscall**)(void*))(*((int*)m_pSomeSubObject + 0x28)))();
        tempFloat = fVar6;
        writeDataToBitstream(0x20, &tempFloat);
    }

    // Handle dirty bit 5: write block of data (0x80 bytes)
    cVar2 = checkFlag(dirtyMask >> 5 & 1);
    if (cVar2 != 0) {
        writeDataToBitstream(0x80, &m_debugData); // Offset 0x888
    }

    // Handle dirty bit 6: write position (3 floats)
    cVar2 = checkFlag(dirtyMask >> 6 & 1);
    if (cVar2 != 0) {
        tempFloat = m_positionX; // 0x898
        writeDataToBitstream(0x20, &tempFloat);
        tempFloat = m_positionY; // 0x89c
        writeDataToBitstream(0x20, &tempFloat);
        tempFloat = m_positionZ; // 0x8a0
        writeDataToBitstream(0x20, &tempFloat);
    }

    // Handle dirty bit 7: write orientation and extended state
    cVar2 = checkFlag(dirtyMask >> 7 & 1);
    if (cVar2 != 0) {
        cVar2 = checkFlag(m_bSomeFlag != 0); // 0x7f0
        if (cVar2 != 0) {
            writeQuaternion(fVar1, &m_quaternion); // 0x7ec
        }
        tempFloat = m_extendedFloat0; // 0x1e9c
        writeDataToBitstream(0x20, &tempFloat);
        tempFloat = m_extendedFloat1; // 0x1ea0
        writeDataToBitstream(0x20, &tempFloat);
        tempFloat = m_extendedFloat2; // 0x1e88
        writeDataToBitstream(0x20, &tempFloat);
        // Call virtual function on base class at vtable index 0x2cc
        (**(void (__thiscall**)(void*))(*((int*)((char*)this - 0x58) + 0x2cc)))();
        // The negative offset is unusual; likely a different base pointer.
    }

    // Handle dirty bit 8 (0x100): special condition
    cVar2 = checkFlag((uint)(dirtyMask & 0x100));
    if ((cVar2 != 0) && (m_actionType != 0) && (m_actionType != 0x48)) { // 0x6f4
        cVar2 = checkSomeExternalCondition(); // FUN_00481660
        tempFloat = (float)(int)cVar2; // reinterpreted as int
        if (cVar2 == 0) {
            uVar3 |= 0x100;
        }
    }

    // Finalize writing if condition met
    cVar2 = checkFlag((uint)(tempFloat & 0xFFFFFF00)); // Upper bits used as flag
    if (cVar2 != 0) {
        iVar5 = m_actionType;
        if ((iVar5 == 0) || (iVar5 == 0x48)) {
            iVar5 = 0;
        } else {
            iVar5 = iVar5 + 0x10;
        }
        startWritingBuffer(iVar5); // FUN_004a8ec0
        finalizeWrite(fVar1, local_8); // FUN_004a9320
    }

    return uVar3;
}