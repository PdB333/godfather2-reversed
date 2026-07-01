// FUNC_NAME: DonControlGadget::setupFromConfig
void __thiscall DonControlGadget::setupFromConfig(int thisPtr, int* configData)
{
    // Call base class initialization (likely DonControlGadget base)
    FUN_0095ecd0();

    if (configData != nullptr) {
        // Process config data (likely copy or parse)
        FUN_008a33c0(configData);

        // Set flags and counters
        *(byte*)(thisPtr + 0x7a) = 1;   // +0x7a: some enabled flag
        *(int*)(thisPtr + 0x74) = 0;    // +0x74: counter or timer
        *(byte*)(thisPtr + 0x78) = 0;   // +0x78: flag
        *(byte*)(thisPtr + 0x79) = 0;   // +0x79: flag

        // If the "useDonFlow" flag is set (offset 0x4c), read DonFlow value from config
        if (*(byte*)(thisPtr + 0x4c) != 0) {
            uint donFlowValue = (**(code**)(*configData + 0x30))("DonFlow", 0); // vtable call at +0x30: getConfigValue
            if (donFlowValue < 8) {
                *(uint*)(thisPtr + 0x3c) = donFlowValue; // +0x3c: donFlowType
            }
        }

        // If global flag DAT_0112b9b4 is set, read MapHash and validate
        if (DAT_0112b9b4 != 0) {
            uint mapHash = (**(code**)(*configData + 0x30))("MapHash", 0); // vtable call
            *(uint*)(thisPtr + 0x10) = mapHash; // +0x10: mapHash

            if (DAT_0112b9b4 != 0) {
                // Validate mapHash via some lookup; if valid, store ESI pointer at +0x70
                char isValid = FUN_0095c8c0(mapHash, &stack0xfffffffc); // stack variable likely a reference
                if (isValid != 0) {
                    *(int*)(thisPtr + 0x70) = unaff_ESI; // +0x70: pointer to associated object (passed via ESI)
                }
            }
        }
    }
    return;
}