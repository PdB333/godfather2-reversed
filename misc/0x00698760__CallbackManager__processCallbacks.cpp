// FUNC_NAME: CallbackManager::processCallbacks
void CallbackManager::processCallbacks(void)
{
  undefined4 *puVar1;
  
  puVar1 = DAT_01129f8c;
  if (DAT_01129f8c != DAT_01129f90) {
    do {
      // Call each registered callback function via its vtable (offset +0x04)
      (**(code **)(*(int *)*puVar1 + 4))();
      puVar1 = puVar1 + 1;
    } while (puVar1 != DAT_01129f90);
  }
  return;
}