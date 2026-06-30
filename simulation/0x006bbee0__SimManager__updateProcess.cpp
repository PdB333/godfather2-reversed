// FUNC_NAME: SimManager::updateProcess
// Function at 0x006bbee0
// This function updates the simulation process list with phase-based processing
// based on bitfield flags and an accumulator.

void SimManager::updateProcess()
{
    char cVar1;
    byte bVar2;
    byte bVar3;
    int iVar4;
    int local_40;
    int local_3c;
    int local_38;
    undefined4 local_34;
    undefined4 local_30;
    int local_2c;
    int local_28;
    int local_24;
    undefined4 local_20;
    undefined4 local_1c;
    undefined4 local_18;
    int local_14;
    int local_10;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;

    // Ensure process data block exists; allocate if null
    if (m_processData == 0) {
        createProcessData(); // FUN_006bb070
    }

    preUpdate(); // FUN_006bacb0
    preProcessList(); // FUN_006bba40

    // Check if process data is valid, simulation is active, and updates are enabled
    if (((m_processData == 0) || (iVar4 = isSimulationActive(), iVar4 != 0)) ||
        (cVar1 = isUpdateEnabled(), cVar1 == '\0')) {
        goto LAB_006bc07c;
    }

    // If bit 3 in flags is set, perform type checks on sub-objects
    if ((m_flags & 0x08) != 0) {
        iVar4 = *(int *)(m_processData + 0xfc);
        if (iVar4 == 0) {
            goto LAB_006bc07c;
        }
        // Both pointers at +0x14 and +0x18 must be non-null and have class ID 0x637b907
        if (((*(int *)(iVar4 + 0x14) == 0) ||
             (*(int *)(*(int *)(iVar4 + 0x14) + 0x54) != 0x637b907)) ||
            ((*(int *)(iVar4 + 0x18) == 0 ||
              (*(int *)(*(int *)(iVar4 + 0x18) + 0x54) != 0x637b907)))) {
            goto LAB_006bc07c;
        }
    }

    iVar4 = m_processData;
    // Update frame counter if condition met
    if ((iVar4 != 0) && ((m_flags & 0x01) != 0) &&
        (m_frameCounter < *(uint *)(iVar4 + 0xac))) {
        m_frameCounter = *(uint *)(iVar4 + 0xac);
    }

    // Prepare locals for list processing (may be used as arguments to processListItem)
    local_38 = iVar4 + 0xa8;             // start of some array in process data
    local_3c = this;
    local_34 = getCurrentTime();          // FUN_006ba3c0
    local_24 = iVar4 + 0x84;             // start of flags in process data
    local_20 = 0xffffffff;
    local_c = 0xffffffff;
    local_40 = m_listHead;                // +0x60
    local_10 = iVar4 + 0x9c;             // some offset in process data
    local_30 = 0;
    local_2c = 0;                         // accumulator for processed items
    local_1c = 0;
    local_18 = 0;
    local_8 = 0;
    local_4 = 0;

    bVar2 = 1;                           // continue flag
    local_28 = this;
    local_14 = this;

    // Process list in three phases (bits 0,1,2 control each phase)
    while ((local_40 != 0) && (bVar2 != 0)) {
        bVar2 = 0;
        if ((m_flags & 0x01) != 0) {      // bit 0
            bVar2 = processListItem(&local_40); // FUN_006bbde0
        }
        if ((m_flags & 0x02) != 0) {      // bit 1
            bVar3 = processListItem(&local_40);
            bVar2 = bVar2 | bVar3;
        }
        if ((m_flags & 0x04) != 0) {      // bit 2
            bVar3 = processListItem(&local_40);
            bVar2 = bVar2 | bVar3;
        }
    }

    m_totalProcessed += local_2c;         // +0x94, accumulated from processListItem?

LAB_006bc07c:
    postUpdate();                         // FUN_006badb0
    return;
}