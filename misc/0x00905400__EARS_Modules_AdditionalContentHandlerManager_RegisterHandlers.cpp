// Xbox PDB: EARS_Modules_AdditionalContentHandlerManager_RegisterHandlers
// FUNC_NAME: GodfatherGameManager::reset
void __fastcall GodfatherGameManager::reset(int thisPtr)
{
  // Call base class constructor or reset routine (vtable dispatch at offset 0x8)
  (**(code **)(*DAT_012233c0 + 8))();

  // String operation - likely setting game mode/state name (vtable offset 0x2c)
  (**(code **)(*(int *)DAT_012233c0[8] + 0x2c))("GODFATHER2");

  // Reset four subsystems, each 0x214 bytes apart
  // +0x04: subsystem 1
  // +0x218: subsystem 2
  // +0x43c: subsystem 3
  // +0x65c: subsystem 4
  FUN_00564ce0(thisPtr + 4);
  FUN_00564ce0(thisPtr + 0x218);
  FUN_00564ce0(thisPtr + 0x43c);
  FUN_00564ce0(thisPtr + 0x65c);

  // Release/dereference a pointer at +0x87c
  FUN_00564eb0(*(undefined4 *)(thisPtr + 0x87c));

  return;
}