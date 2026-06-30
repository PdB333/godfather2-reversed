// FUNC_NAME: hashChainGetPair
void hashChainGetPair(uint *node, uint *outLow, uint *outHigh)
{
    // Global constants (likely a hash seed or base values)
    ulonglong local_18 = DAT_0119cbf4;
    ulonglong local_10 = DAT_0119cbfc;
    ulonglong local_8 = DAT_0119cc04;

    // Traverse linked list (offset 0x54 = next pointer)
    while (node != nullptr) {
        FUN_005b4540(&local_18); // Process each node (hash combine?)
        node = (uint *)(node[0x15]); // node + 0x54 / 4 = index 0x15
    }

    // Write results to output parameters
    if (outLow != nullptr) {
        *outLow = (uint)(local_8 & 0xFFFFFFFF); // Lower 32 bits
    }
    if (outHigh != nullptr) {
        *outHigh = (uint)(local_8 >> 32); // Upper 32 bits
    }
}