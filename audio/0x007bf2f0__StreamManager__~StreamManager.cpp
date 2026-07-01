// FUNC_NAME: StreamManager::~StreamManager
void __fastcall StreamManager::~StreamManager(StreamManager* this)
{
  // iVar1 = this->someInternalPointer at offset +0x58 (0x16 * 4)
  int internalPtr = *(int*)((char*)this + 0x58);
  
  // Set vtable to derived class vtable (likely for cleanup)
  *(void**)this = (void*)0x00d6e1a8;
  
  // Release stream resources of types 0xc and 0xd
  FUN_007f6420(0xc);
  FUN_007f6420(0xd);
  
  // Check mode at offset +0x74 (0x1d * 4)
  if (*(int*)((char*)this + 0x74) == 2) {
    FUN_007fb9b0(0, _DAT_00d6e184); // Mode 2: pass 0
  } else if (*(int*)((char*)this + 0x74) == 1) {
    FUN_007fb9b0(1, _DAT_00d6e184); // Mode 1: pass 1
  }
  // else skip (mode other than 1 or 2)
  
  // Perform additional cleanup
  FUN_007f7e40();
  
  // Clear a flag/size field at internalPtr + 0x24a0
  *(int*)(internalPtr + 0x24a0) &= 0x7fffffff;
  
  // Switch vtable to base class vtable
  *(void**)this = (void*)0x00d6b95c;
  
  // Call base class destructor
  FUN_0080ea60();
}