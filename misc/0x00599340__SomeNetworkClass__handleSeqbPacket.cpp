// FUNC_NAME: SomeNetworkClass::handleSeqbPacket
void __fastcall SomeNetworkClass::handleSeqbPacket(void* thisPtr, char* packetData)
{
  // thisPtr is passed in EAX, packetData in EDX (fastcall convention)
  uint* flagsPtr = (uint*)thisPtr; // Pointer to the flags/state uint at offset 0
  uint flags = *flagsPtr;
  uint uVar1;

  if (packetData == (char*)0x0) {
    goto fail;
  }

  // Store the packet data pointer at this+4
  *(char**)(thisPtr + 4) = packetData;

  // Check if packet begins with "seqb" and length field (at offset 4) equals 4
  if ((packetData[0] == 's') && (packetData[1] == 'e') && (packetData[2] == 'q') && (packetData[3] == 'b') &&
      (*(int*)(packetData + 4) == 4)) {
    
    // Set bit 0 and bit 5 (0x21) in flags
    *flagsPtr = flags | 0x21;

    // Bit manipulation: toggle bits based on some global state
    uVar1 = (*(int*)(g_globalStruct + 0x40) * 2 ^ *flagsPtr) & 2 ^ *flagsPtr;
    *flagsPtr = uVar1;
    uVar1 = (*(uint*)(g_globalStruct + 0x40) ^ uVar1) & 4 ^ uVar1;
    *flagsPtr = uVar1;

    if ((uVar1 & 4) == 0) {
      // Branch A: call vfunc 0x40 on engine object
      uint* pStackArg = (uint*)((char*)flagsPtr + 16); // flagsPtr + 4 words = offset 0x10? Actually flagsPtr[4]? This is unclear.
      uint localVar = 0x599469; // address for debug? Or a parameter?
      (**(code**)(*DAT_012055a8 + 0x40))(); // call engine->vfunc(0x40)
    }
    else {
      // Branch B: copy 4 dwords from packetData+0x1c to local stack
      uint localArray[8]; // at local_70
      localArray[0] = *(uint*)(packetData + 0x1c);
      localArray[1] = *(uint*)(packetData + 0x20);
      localArray[2] = *(uint*)(packetData + 0x24);
      localArray[3] = *(uint*)(packetData + 0x28);

      // Call vfunc 4 on engine
      (**(code**)(*DAT_012055a8 + 4))();

      // Read back the stored pointer
      uint storedPtr = *(uint*)(thisPtr + 4);
      puStack_98 = (undefined1*)0x5993e9; // debug marker
      (**(code**)(*DAT_012055a8 + 4))(*(undefined4*)(storedPtr + 0xc), *(undefined4*)(storedPtr + 0x10),
                                       *(undefined4*)(storedPtr + 0x14), 0x3f800000); // call with 4 params

      // More vfunc calls: 0x60, 0x10, 0x4c
      (**(code**)(*DAT_012055a8 + 0x60))(&puStack_98, auStack_78);
      (**(code**)(*DAT_012055a8 + 0x10))(auStack_74, auStack_50);
      (**(code**)(*DAT_012055a8 + 0x4c))(&localArray);
    }

    // Store value from packet at offset 0xb8 into this+8
    *(uint*)(thisPtr + 8) = *(uint*)(*(char**)(thisPtr + 4) + 0xb8);

    // Reset two fields at this+0x50 and this+0x54? Actually index 0x14 and 0x15 from *flagsPtr base
    // flagsPtr points to the beginning of the object, so indices are relative to that.
    *(uint*)(thisPtr + 0x50) = 0;  // index 0x14 * 4 = 0x50
    *(uint*)(thisPtr + 0x54) = 0;  // index 0x15 * 4 = 0x54

    // Call external function with parameter 0
    FUN_00599720(0);

    // Clear bit 5 (0x20) from flags
    *flagsPtr = *flagsPtr & 0xffffffdf;

    // Compare with a global float at g_globalStruct+0x4c
    if (DAT_00e2b05c < *(float*)(g_globalStruct + 0x4c)) {
      FUN_00599720(*(float*)(g_globalStruct + 0x4c));
    }

    return;
  }

fail:
  // Error path: call vfunc 4 on another engine object
  (**(code**)(*DAT_01205590 + 4))();
  return;
}