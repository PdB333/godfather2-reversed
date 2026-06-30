:// FUNC_NAME: InputManager::processControllerMappings
void __thiscall InputManager::processControllerMappings(int *this, void *pControllerState, uint controllerCount)
{
    int iVar1;
    uint uVar2;
    int iVar3;
    int *pMapping;
    int iVar5;
    void *puVar6;
    uint currentIndex;
    int local_120[4]; // Actually might be float[4], 16 bytes
    char local_110[64];
    char local_90[64];
    char local_d0[64];
    char local_50[76]; // Note: 76 bytes, not 64

    int dataOffset = 0;
    if (this[1] != 0) {
        // Precompute response curves from controller state and number of controllers
        FUN_0066d310(pControllerState, local_120, local_90, local_110, local_d0, local_50, controllerCount);
        currentIndex = 0;
        iVar1 = (**(code **)(*this + 0x10))(); // Virtual function: GetNumberOfMappings()
        if (iVar1 != 0) {
            pMapping = this + 4; // Pointer to array of mapping entries (5 ints each)
            do {
                iVar1 = pMapping[1]; // Mapping entry field 1
                if (iVar1 != 0) {  // Check if mapping is valid
                    if (currentIndex < controllerCount) {
                        // Apply mapping with precomputed curves
                        FUN_0060aa90(this[1], pMapping[-1], local_120[currentIndex]);
                        FUN_0060add0(this[1], *pMapping, local_110 + dataOffset);
                        FUN_0060add0(this[1], pMapping[1], local_90 + dataOffset);
                        FUN_0060add0(this[1], pMapping[2], local_d0 + dataOffset);
                        iVar1 = pMapping[3];
                        iVar5 = this[1];
                        puVar6 = local_50 + dataOffset;
                    }
                    else {
                        puVar6 = &DAT_01225dc0; // Global fallback data
                        iVar5 = this[1];
                    }
                    FUN_0060add0(iVar5, iVar1, puVar6);
                }
                currentIndex++;
                dataOffset += 0x10; // Each curve chunk is 16 bytes
                pMapping += 5; // Each mapping entry is 5 ints (20 bytes)
                uVar2 = (**(code **)(*this + 0x10))(); // Re-get count in case set changed?
            } while (currentIndex < uVar2);
        }
    }
    return;
}