// FUNC_NAME: GhostEntity::flushStateUpdate (EARS ghost replication - writes pending state changes to a global buffer queue)

void __fastcall GhostEntity::flushStateUpdate(GhostEntity *this) {
    // +0x130: pointer to a manager/owner object (e.g., GhostManager)
    int *manager = (int *)this->field_0x130;
    if (manager != nullptr) {
        // Call virtual function at vtable offset 0x24 (index 9) on manager
        (*(code **)(*manager + 0x24))();
    }

    // +0x00: vtable of this
    // Call virtual function at vtable offset 0x104 (index 0x41) – likely "writeStateToBuffer"
    (*(code **)(*this + 0x104))(this->m_stateBuffer); // local_20 of size 28

    // +0x170: flag indicating if object is dirty (bool)
    // +0x164: pointer to a packet or command list
    if (this->field_0x170 == 0 && this->field_0x164 != 0) {
        // Global buffer system (used to queue dirty ghost commands for the network layer)
        // Address stored at DAT_01206880 + 0x14 is a pointer to the current write position
        uint *writePos = (uint *)(DAT_01206880 + 0x14);
        **(int **)(DAT_01206880 + 0x14) = (int *)&PTR_LAB_0110ba94; // Write a known signature
        *writePos = *writePos + 4; // Advance write pointer
        *(int **)*writePos = (int *)((int *)this + 0x54); // Write pointer to this +0x54 (e.g., object ID or transform)
        *writePos = *writePos + 4; // Advance
        *(unsigned char *)*writePos = 1; // Write a flag byte (likely "dirty" or "active")
        *writePos = *writePos + 4 & 0xfffffffc; // Align to 4-byte boundary
    }
}