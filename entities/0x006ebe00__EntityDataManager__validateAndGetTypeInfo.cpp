// FUNC_NAME: EntityDataManager::validateAndGetTypeInfo

// Reconstructed from Ghidra at 0x006ebe00
// This function validates that an object data structure has non-zero, non-null type fields
// and retrieves a byte of info from a type table indexed by subType and baseType.
//
// param_1: pointer to an integer holding the base type ID (index used as *param_1 - 0x0C)
// param_2: pointer to a data structure with:
//   +0x00: base type field
//   +0x08: sub type field
//
// Returns a byte (0 if validation fails, otherwise result of getTypeInfo)

byte EntityDataManager::validateAndGetTypeInfo(int* baseTypeIdPtr, int* objectDataPtr) {
    byte result = 0; // default failure return

    // Check pointer validity and type fields not zero and not the exclusion value 0x48
    if (baseTypeIdPtr != nullptr && objectDataPtr != nullptr) {
        int baseField = *objectDataPtr;          // +0x00
        int subField = objectDataPtr[2];         // +0x08 (index 2)

        if (baseField != 0 && baseField != 0x48 &&
            subField != 0 && subField != 0x48) {
            // In practice subField cannot be 0 here due to above condition,
            // but the disassembly shows a dead branch: if (subField == 0) iVar2 = 0;
            int subTypeIndex = subField - 0x48; // subtract base offset to get index
            int baseTypeIndex = *baseTypeIdPtr - 0x0C; // subtract base offset to get index
            result = getTypeInfo(subTypeIndex, baseTypeIndex); // FUN_00898330
        }
    }
    return result;
}