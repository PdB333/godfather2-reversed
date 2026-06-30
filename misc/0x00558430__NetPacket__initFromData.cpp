// FUNC_NAME: NetPacket::initFromData
void NetPacket::initFromData(NetPacket *this, undefined8 *inputData) {
  int heapHandle;
  int firstBlock;
  int secondBlock;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *unaff_EDI; // This is actually 'this' pointer stored in EDI from caller
  
  // Get thread-local heap handle (probably TLS for memory allocator)
  TlsGetValue(DAT_01139810);
  
  // Allocate first block (0x50 bytes) with tag 0x27
  firstBlock = FUN_00aa2680(0x50,0x27);
  *(undefined2 *)(firstBlock + 4) = 0x50; // Store block size at offset +4
  
  // Get pointer from some helper (e.g., getRefCountedPointer)
  puVar2 = (undefined4 *)FUN_00557810(*unaff_EDI, unaff_EDI[8]);
  
  // Copy two 8-byte fields from inputData into the object
  *(undefined8 *)(unaff_EDI + 2) = *inputData;           // Copy first 8 bytes (e.g., sequence/ack)
  *(undefined8 *)(unaff_EDI + 4) = inputData[1];         // Copy next 8 bytes (e.g., extra data)
  unaff_EDI[6] = *(undefined4 *)(inputData + 2);         // Copy 4-byte field (e.g., command ID)
  
  // Get TLS heap again (maybe for second allocation)
  TlsGetValue(DAT_01139810);
  
  // Allocate second block (0x160 bytes) with tag 0x31 (payload buffer)
  secondBlock = FUN_00aa2680(0x160,0x31);
  *(undefined2 *)(secondBlock + 4) = 0x160; // Store size at offset +4
  
  // Register/attach the second block to the first block (or to the object)
  uVar3 = FUN_009f0c70(puVar2, &DAT_011397d0, (uint)(unaff_EDI + 2) >> 2 | 0x40000000);
  unaff_EDI[7] = uVar3; // Store resulting handle/pointer
  
  // Decrement reference count of puVar2 (if it's a ref-counted object)
  if ((*(short *)(puVar2 + 1) != 0) &&   // Check if ref count > 0
      (*(short *)((int)puVar2 + 6) = *(short *)((int)puVar2 + 6) + -1, // Decrement at offset +6
       *(short *)((int)puVar2 + 6) == 0)) {
    // If ref count reached 0, call destructor callback
    (**(code **)*puVar2)(1); // Call function pointer stored at first word (vtable or destructor)
  }
  
  // Save the initial word of the object for registration
  uVar3 = *unaff_EDI;
  
  // Perform global registration of this packet
  FUN_0043b490(); // (e.g., check for leaks, or prepare global state)
  
  // Register the object with two IDs (0x2001 and 0x2002)
  FUN_009f01f0(0x2001, uVar3, 0);  // Register packet handle
  FUN_009f01f0(0x2002, unaff_EDI, 0); // Register full object pointer
  
  return;
}