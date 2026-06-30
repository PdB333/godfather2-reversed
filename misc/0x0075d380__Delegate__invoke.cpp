// FUNC_NAME: Delegate::invoke
void __thiscall Delegate::invoke(void *pArg)
{
  int (*legacyHandler)(int) = *(int (**)(int))(this + 0xD8); // function pointer for legacy callback
  void (*modernHandler)(int *) = *(void (**)(int *))(this + 0xEC); // modern callback that receives pointer to user data

  // Only proceed if at least one callback is set
  if (modernHandler != nullptr || legacyHandler != nullptr) {
    int arg;
    if (*(int *)((char *)pArg + 0x24) == 0) {
      arg = 0;
    } else {
      arg = *(int *)((char *)pArg + 0x24) - 0x48;
    }

    // Prefer modern handler; it receives a pointer to the user data (which is also the legacy function pointer)
    if (modernHandler != nullptr) {
      modernHandler((int *)(this + 0xD8));
      return;
    }

    // Otherwise, call the legacy handler with the computed argument
    legacyHandler(arg);
  }
}