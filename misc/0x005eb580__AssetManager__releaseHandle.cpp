// FUNC_NAME: AssetManager::releaseHandle
undefined1 __thiscall AssetManager::releaseHandle(void *this, AssetHandle *handle)
{
  int *resourcePtr;
  int resource;
  undefined1 result;
  void (*releaseFunc)(int);

  resourcePtr = (int *)(handle + 8);  // +0x8: pointer to the resource data
  resource = *resourcePtr;
  result = 0;
  if (resource != 0) {
    if (FUN_005ec890() == '\0') {
      releaseFunc = *(void (**)(int))(this + 0x81b8);  // +0x81b8: release callback function pointer
      if (releaseFunc != (void (*)(int))0x0) {
        releaseFunc(resource);
      }
      result = 1;
    }
    else {
      FUN_005efca0(resourcePtr);  // queue async deletion or similar
    }
  }
  *resourcePtr = 0;
  *(undefined4 *)(handle + 0xc) = 0;  // +0xC: reference count or state
  *(undefined4 *)(handle + 0x10) = 0; // +0x10: possibly a lock or flags
  return result;
}