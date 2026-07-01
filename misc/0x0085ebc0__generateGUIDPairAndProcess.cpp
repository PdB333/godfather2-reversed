// FUNC_NAME: generateGUIDPairAndProcess
// Function address: 0x0085ebc0
// This function generates two 12-byte GUIDs (or similar identifiers) and processes them with a global constant.
// param_1 is unused (possibly a this pointer in a member function context, but not used here).
// param_2 is likely an input parameter (e.g., a string or identifier) passed to the processing function.

void generateGUIDPairAndProcess(uint param_1, uint param_2)
{
    byte guidA[12]; // +0x00: First 12-byte GUID buffer
    byte guidB[12]; // +0x00: Second 12-byte GUID buffer

    // Generate two GUIDs (likely from some internal state or random)
    FUN_00875190(guidA, guidB); // 0x00875190: GenerateGUIDPair(guidA, guidB)

    // Process the GUIDs with param_2 and a global constant (e.g., a key or format string)
    FUN_004a0cd0(guidA, guidB, param_2, &DAT_00d75690); // 0x004a0cd0: ProcessGUIDPair(guidA, guidB, param_2, globalConstant)
}