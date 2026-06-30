// FUNC_NAME: StreamManager::Initialize
void __thiscall StreamManager::Initialize(void *thisPtr)
{
  uint *vtablePtr;
  StreamBuffer buffer;
  
  // Set vtable pointer at offset 0x00
  *(uint **)thisPtr = &PTR_LAB_00e43124;
  
  // Initialize some flags/counters at offsets 0x04, 0x08
  *(int *)((char *)thisPtr + 4) = 0;
  *(int *)((char *)thisPtr + 8) = 0;
  
  // Initialize more state at offsets 0x18, 0x1C
  *(int *)((char *)thisPtr + 0x18) = 0;
  *(int *)((char *)thisPtr + 0x1C) = 0;
  
  // Prepare a local StreamBuffer descriptor on the stack
  buffer.vtablePtr = &PTR_LAB_00e42d64;
  buffer.field_4 = 0;
  buffer.field_8 = 0;
  buffer.bufferSize = 0x5dc;  // 1500 bytes (standard MTU)
  buffer.bufferPtr = (uint8_t *)malloc(0x5dc);
  buffer.flag = 1;  // ownership flag
  
  // Call sub-initialization functions
  SubInitialize1(thisPtr);
  SubInitialize2(thisPtr, &buffer);
  SubInitialize3();
}