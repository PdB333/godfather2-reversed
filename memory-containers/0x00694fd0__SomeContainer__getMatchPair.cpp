// FUNC_NAME: SomeContainer::getMatchPair
// Address: 0x00694fd0
// This function retrieves a pair of values (this pointer + internal field or key) based on a comparison.
// It is likely part of a container or map class where each element has a key and a related value stored at +0x4.

void __thiscall getMatchPair(int thisPtr, int* outputPair, int param_3)
{
    // Convert the third parameter to an internal key/index using helper FUN_006948e0
    int key = convertToInternalKey(param_3); // FUN_006948e0

    // Assert if this is null
    if (thisPtr == 0) {
        assertionFailure(); // FUN_00b97aea
    }

    // Compare the key with the stored field at this+0x4
    if (key != *(int*)(thisPtr + 0x4)) {
        // Key does not match; attempt to validate key + 0xc
        int validationResult = validateIndex(key + 0xc); // FUN_004d4b20
        if (validationResult >= 0) {
            // Validation passed: return pair (thisPtr, key)
            outputPair[0] = thisPtr;
            outputPair[1] = key;
            return;
        }
    }

    // Default: return pair (thisPtr, value at this+0x4)
    outputPair[0] = thisPtr;
    outputPair[1] = *(int*)(thisPtr + 0x4);
}