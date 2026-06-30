// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::destroy(undefined4 *this)
{
  int *dataManager;
  uint flags;
  int result;
  undefined4 *localPtr;

  dataManager = (int *)this[0x17]; // +0x5C: pointer to some data manager (e.g., SimDataManager)
  *this = &PTR_LAB_00d63448; // Set vtable to derived class (or this class) – actually this is the derived class vtable?
  localPtr = this;

  FUN_007ff050(0); // Unknown cleanup (maybe input or controller shutdown)

  if ((this[0x1d] & 0x200) != 0) // +0x74 flags: bit 0x200 (maybe "initialized")
  {
    FUN_007f6420(1); // Debug log or subsystem shutdown (arg 1)
  }

  FUN_004612a0(); // Possibly deactivate some game system (e.g., audio)

  dataManager[0x7d6] = dataManager[0x7d6] & 0xefffffff; // Clear a flag in data manager at offset 0x1F58 (0x7D6*4 = 0x1F58)

  if ((this[0x1d] & 0x10000) != 0) // +0x74 flags: bit 0x10000
  {
    FUN_007f6420(99); // Debug log or subsystem shutdown (arg 99)
  }

  flags = this[0x1d]; // +0x74 flags

  if (((flags & 1) == 0) || (((flags & 0x2000) != 0 && ((flags & 0x40) == 0))))
  {
    if ((flags & 0x10) != 0 && (dataManager != 0 && (result = FUN_0043b870(DAT_0113105c), result != 0)))
    {
      FUN_009b2570(); // Some subsystem update/cleanup
    }

    FUN_00939860(dataManager, 1); // Possibly release/remove something from data manager
    if (((*(byte *)(this + 0x1d) & 0x20) != 0 && dataManager != 0) && (result = FUN_0043b870(DAT_01131064), result != 0))
    {
      FUN_009b3ae0(); // Another subsystem cleanup
    }
  }

  FUN_00939710(dataManager); // Update/cleanup data manager
  FUN_00939670(dataManager, this[0x1c]); // +0x70: some id or parameter

  if ((this[0x1e] != 0 && this[0x1e] != 0x48) && // +0x78: some handle or object ID
      (result = FUN_0043b870(DAT_0112af98), result != 0))
  {
    FUN_00789f00(0); // Subsystem shutdown
    if (((this[0x1d] & 0x40) != 0) && ((this[0x1d] & 0x200000) != 0)) // +0x74 flags: bits 0x40 and 0x200000
    {
      FUN_0073b4c0(); // Additional cleanup
      FUN_007894b0();
    }
  }

  if ((this[0x1d] & 0x8000) != 0) // +0x74 flags: bit 0x8000
  {
    (**(code **)(*dataManager + 0x290))(1, 1); // Virtual call on dataManager at offset 0x290
  }

  if (dataManager != 0)
  {
    localPtr = 0;
    (**(code **)(*(int *)this[0x17] + 0x10))(0xa0d329d6, &localPtr); // Virtual call on dataManager at offset 0x10, with a hash
  }

  FUN_004df590(); // Cleanup (maybe network or stream)
  if (dataManager != 0)
  {
    result = FUN_0043b870(DAT_01131018);
    if ((result != 0) && ((this[0x1d] & 0x1000) != 0)) // +0x74 flags: bit 0x1000
    {
      FUN_009ae900(0); // Subsystem release
    }
    result = FUN_0043b870(DAT_01131040);
    if (result != 0)
    {
      *(uint *)(result + 0x48) = *(uint *)(result + 0x48) & 0xfffffffd; // Clear bit 1 in that object
    }
  }

  if (this[0x2b] != 0) // +0xAC: pointer or handle (e.g., Lua state)
  {
    FUN_004daf90(this + 0x2b); // Release/destroy
  }

  if (this[0x29] != 0) // +0xA4: another handle
  {
    FUN_004daf90(this + 0x29);
  }

  result = this[0x26]; // +0x98: pointer to something
  if (result != 0)
  {
    *(undefined4 *)(result + 8) = 0; // Clear field at offset 8
    this[0x26] = 0;
  }

  if (this[0x1e] != 0) // +0x78: handle (cleanup again? but already above)
  {
    FUN_004daf90(this + 0x1e);
  }

  *this = &PTR_LAB_00d63090; // Switch vtable to base class (likely the parent destructor)

  if (this[0x1a] != 0) // +0x68: another handle
  {
    FUN_004daf90(this + 0x1a);
  }

  FUN_0080ea60(); // Final cleanup (maybe memory deallocation or base destructor)
  return;
}