// FUNC_NAME: NetSession::initialize
void __thiscall NetSession::initialize(int this)
{
  GUID localGuid;
  int subInitResult; // eax
  int singletonPtr; // eax
  int callbackResult; // eax

  *(int *)(this + 0x8c) = 0; // m_bInitialized

  localGuid = DAT_0112ddc4; // session GUID constant
  FUN_00408a00(&localGuid, 0); // likely generates a unique session GUID

  subInitResult = FUN_00850620(this + 0x3c); // probably sub-object init, returns handle
  *(int *)(this + 0x80) = subInitResult; // m_subObjectHandle

  singletonPtr = FUN_009c9730(); // get session manager singleton
  // vtable offset 0x1c -> register callback
  callbackResult = (*(code **)(*(int *)singletonPtr + 0x1c))(0, this + 0xa4);
  *(int *)(this + 0xa0) = callbackResult; // m_callbackId

  if (*(int *)(this + 0x80) != 0) // if sub-object init succeeded
  {
    *(int *)(this + 0x84) = 7; // m_state = 7 (active)
    return;
  }

  FUN_008502b0(); // error/shutdown handler
}