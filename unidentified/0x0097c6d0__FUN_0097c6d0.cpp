// FUNC_NAME: SomeClass::notifyAllListeners
void __thiscall notifyAllListeners(int this, undefined4 param_2)
{
  uint i;
  
  i = 0;
  if (*(int *)(this + 0xdc) != 0) {
    do {
      // Call listener's virtual function at vtable+0x14 (likely onEvent or handleNotification)
      (**(code **)(**(int **)(*(int *)(this + 0xd8) + i * 4) + 0x14))(param_2);
      i = i + 1;
    } while (i < *(uint *)(this + 0xdc));
  }
  return;
}