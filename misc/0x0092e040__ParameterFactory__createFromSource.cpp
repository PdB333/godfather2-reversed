// FUNC_NAME: ParameterFactory::createFromSource
// Function address: 0x0092e040
// Creates a new ParameterData object from a source block, looking up mapped values and a string ID.

ParameterData* __thiscall ParameterFactory::createFromSource(void* this, SourceBlock* source) {
  ParameterData* newParam = nullptr;
  short valShort;
  int* tableEntry;
  uint idx;
  uint hashResult;
  StringManager* strMgr;
  char* strPtr;

  // Validate input: source must be non-null and have the valid flag set (bit 0 at offset 0x0C)
  if ((source != nullptr) && ((source->flags & 1) != 0)) {
    // Allocate a new ParameterData object of size 0x28 (40 bytes)
    newParam = (ParameterData*)allocateMemory(0x28);
    if (newParam != nullptr) {
      // Zero-initialize all fields except those set later
      newParam->field_00 = nullptr;
      newParam->field_04 = nullptr;
      newParam->field_08 = nullptr;
      newParam->field_0C = nullptr;  // indices 0-3
      newParam->field_14 = nullptr;  // index 5 (offset 0x14)
      newParam->field_18 = nullptr;  // index 6
      newParam->field_1C = nullptr;  // index 7
      newParam->field_20 = nullptr;  // index 8
      newParam->field_24 = nullptr;  // index 9
      // Note: field_10 (index 4) is left uninitialized; will be set later

      // Convert source's internal ID to a hash and then to a string (likely debug/name)
      hashResult = convertToHash(source);
      convertHashToString(hashResult);

      // Copy the first 32-bit value from the source block into offset 0x14
      newParam->sourceValue = source->baseValue;

      // Search the mapping table at (this+0x5c) for an entry whose first value matches source->key
      idx = 0;
      if (this->tableCount != 0) {
        tableEntry = this->mappingTable;
        do {
          if (*tableEntry == source->key) {
            // Found: copy the two subsequent values from the table entry into the new parameter
            newParam->mappedValue1 = *(undefined4*)(idx * 12 + 4 + this->mappingTable);
            newParam->mappedValue2 = *(undefined4*)(idx * 12 + 8 + this->mappingTable);
            goto LAB_0092e0f2;
          }
          idx++;
          tableEntry += 3;  // each entry is 12 bytes (3 ints)
        } while (idx < this->tableCount);
      }

      // If not found in table and an alternative computation method exists
      if (this->alternativeMethod != 0) {
        // Compute mapped values using external functions on the source key
        valShort = FUN_008a6350(source->key);  // likely convertKeyToIntEx
        newParam->mappedValue1 = (int)valShort;
        valShort = FUN_008a6370(source->key);  // likely convertKeyToIntEx2
        newParam->mappedValue2 = (int)valShort;
      }

LAB_0092e0f2:
      // Obtain a string manager singleton and look up a string for the parameter's first field
      strMgr = (StringManager*)FUN_00ad8d40();  // likely StringManager::instance()
      if (strMgr != nullptr) {
        strMgr = (StringManager*)(**(code**)(*(int*)strMgr + 0x48))();  // virtual call to get string table
        strPtr = (char*)newParam->field_00;
        if (strPtr == nullptr) {
          strPtr = &DAT_0120546e;  // default string (likely empty or placeholder)
        }
        // Look up the string in the table and store the result at offset 0x10
        newParam->stringId = (**(code**)(*(int*)strMgr + 0x1c))(strPtr);
      }
    }
  }
  return newParam;
}