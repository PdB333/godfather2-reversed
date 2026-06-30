// FUNC_NAME: EARSObject::queryInterface

int __fastcall EARSObject::queryInterface(void *this) {
  // this points to an EARSObject with fields at:
  // +0x10C: ClassID (128-bit unique identifier for the object type) - 4 ints
  // +0x80: Interface data (pointer + additional info, 36 bytes total)
  
  int *classId = (int *)((char *)this + 0x10C);
  
  // Check if class ID is non-zero AND not equal to the specific interface GUID
  // {0xBABDB9BA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911}
  int interfaceGuid[4] = {0xBABDB9BA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911};
  
  if ((classId[0] != 0 || classId[1] != 0 || classId[2] != 0 || classId[3] != 0) &&
      !(classId[0] == interfaceGuid[0] && classId[1] == interfaceGuid[1] &&
        classId[2] == interfaceGuid[2] && classId[3] == interfaceGuid[3])) {
    
    // Object is not of the target interface type; attempt to retrieve the interface
    // via a factory or global lookup function
    int *factoryResult = (int *)FUN_00446100((int *)((char *)this + 0x10C), 0);
    
    if (factoryResult != nullptr) {
      int localArray[2];           // +0xFFFFFFB8 (stack)
      void *stackBuf = localArray; // used as temporary buffer
      localArray[0] = 0;
      
      // Virtual call: can we convert to the interface? (vtable+0x10, hash 0x8a859764)
      bool canConvert = (**(code (__stdcall **)(int, uint))(*factoryResult + 0x10))(0, 0x8a859764);
      
      if (canConvert && stackBuf != nullptr) {
        // Virtual call: create the interface instance (vtable+4)
        (**(code (__stdcall **)(void *, void *))(*factoryResult + 4))(stackBuf, &localArray);
        
        // Copy the interface data into the object at offset +0x80
        // Structure at +0x80:
        // +0x80: pointer/reference (8 bytes)
        // +0x88: int element
        // +0x90: another 8-byte field
        // +0x98: 4-byte field
        // +0xA0: 8-byte field
        // +0xA8: 4-byte field
        // Total 36 bytes, with possible gaps at +0x8C and +0x9C
        char *ifaceData = (char *)this + 0x80;
        *(uint8_t *)(ifaceData + 0x00) = *(uint8_t *)((char *)stackBuf + 0x00);
        *(uint8_t *)(ifaceData + 0x08) = *(uint8_t *)((char *)stackBuf + 0x08);
        *(uint8_t *)(ifaceData + 0x10) = *(uint8_t *)((char *)stackBuf + 0x10);
        *(uint8_t *)(ifaceData + 0x18) = *(uint8_t *)((char *)stackBuf + 0x18);
        *(uint8_t *)(ifaceData + 0x20) = *(uint8_t *)((char *)stackBuf + 0x20);
        *(uint8_t *)(ifaceData + 0x28) = *(uint8_t *)((char *)stackBuf + 0x28);
        
        // Copy the local array element (first int) to offset +0x88
        *(int *)(ifaceData + 0x08) = localArray[0];
        
        // Call a self-assignment/initialisation function on the interface data
        FUN_0043a2a0(ifaceData, ifaceData);
      }
    }
  }
  
  // Return pointer to the interface data area
  return (int)((char *)this + 0x80);
}