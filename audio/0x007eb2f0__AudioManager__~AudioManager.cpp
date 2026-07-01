// FUNC_NAME: AudioManager::~AudioManager
void __fastcall AudioManager::~AudioManager(void* thisPtr)
{
  int someFlag;
  char cVar2;
  void* pSubsystem1;
  void* pSubsystem2;

  someFlag = *(int*)((char*)thisPtr + 0x58); // offset 0x16 * 4 = 0x58
  *(int*)thisPtr = &PTR_LAB_00d6ff20; // set vtable to derived class vtable (or intermediate)

  // Release subsystem 1 (offset 0x7C = 0x1F*4)
  pSubsystem1 = (void*)getSubsystemManager1(); // FUN_007ab150 returns a manager pointer
  (**(code**)(*(int*)pSubsystem1 + 4))(*(void**)((char*)thisPtr + 0x7C)); // virtual call at vtable+4 (destructor/release)

  // Release subsystem 2 (offset 0x78 = 0x1E*4)
  pSubsystem2 = (void*)getSubsystemManager2(); // FUN_007ab130
  (**(code**)(*(int*)pSubsystem2 + 4))(*(void**)((char*)thisPtr + 0x78));

  // Possibly decrease reference counts for specific indices
  decReferenceCount(0x17); // FUN_007f6420(0x17)
  decReferenceCount(0x14); // FUN_007f6420(0x14)

  // Unregister a global resource manager
  unregisterGlobalResource(&DAT_00d6fee0); // FUN_007f89d0(&DAT_00d6fee0)

  cVar2 = isGameModeActive(); // FUN_00481640
  if ((cVar2 != '\0') && (cVar2 = isAudioEnabled(), cVar2 != '\0') && (someFlag != 0))
  {
    void* pAudioComponent = getAudioComponentFromGlobal(*(int*)&DAT_01131018); // FUN_0043b870
    if (pAudioComponent != (void*)0x0)
    {
      // Clear a bit (0x20000) in flags field at offset +0x18 (piVar3[6] => offset 24)
      *(int*)((char*)pAudioComponent + 0x18) &= 0xfffdffff; // clear bit 0x20000
      // Call virtual function at vtable+0x3C with argument 1.0f (set volume?)
      (**(code**)(*(int*)pAudioComponent + 0x3C))(0x3f800000); // 1.0f
      // Set the bit back
      *(int*)((char*)pAudioComponent + 0x18) |= 0x20000;
    }
  }

  // Release a handle into a pool if valid (offset 0x80 = 0x20*4)
  if (*(int*)((char*)thisPtr + 0x80) != -1)
  {
    releaseHandle(*(int*)((char*)thisPtr + 0x80)); // FUN_0090dff0
    *(int*)((char*)thisPtr + 0x80) = -1;
  }

  // Additional cleanup
  cleanupSomething(); // FUN_007faca0

  // Restore base class vtable before calling base destructor
  *(int*)thisPtr = &PTR_LAB_00d6b95c;
  callBaseDestructor(); // FUN_0080ea60

  return;
}