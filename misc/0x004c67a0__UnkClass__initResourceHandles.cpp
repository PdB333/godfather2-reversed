// FUNC_NAME: UnkClass::initResourceHandles
void __thiscall UnkClass::initResourceHandles(int this)
{
  // Store first handle from global resource manager (e.g., sound bank or texture)
  *(int *)(this + 0x10) = FUN_0060a380();
  
  // Store second handle from a specific resource identified by a global pointer (likely a string ID)
  *(int *)(this + 0x14) = FUN_0060a2e0(&PTR_DAT_0110a37c);
  
  // Finalize initialization (e.g., register this object with engine)
  FUN_006127d0();
  
  return;
}