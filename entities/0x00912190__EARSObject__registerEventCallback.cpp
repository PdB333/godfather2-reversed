// FUNC_NAME: EARSObject::registerEventCallback
void __fastcall EARSObject::registerEventCallback(int this)
{
  if (this != 0) {
    FUN_005c0d50(this + 0x14, &LAB_009120d0, 0); // +0x14 = eventCallbackList offset
    return;
  }
  FUN_005c0d50(0, &LAB_009120d0, 0);
  return;
}