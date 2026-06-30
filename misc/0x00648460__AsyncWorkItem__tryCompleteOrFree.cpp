// FUNC_NAME: AsyncWorkItem::tryCompleteOrFree
undefined4 __thiscall AsyncWorkItem::tryCompleteOrFree(LPVOID this, undefined4 param_2, char param_3)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  // Check if work is done (flag at +0xd) or if forced completion is requested (param_3) and work is cancelable (flag at +0xe)
  if ((*(char *)((int)this + 0xd) != '\0') ||
     ((param_3 != '\0' && (*(char *)((int)this + 0xe) != '\0')))) {
    // If there's a completion callback at +0x10, call it
    if (*(code **)((int)this + 0x10) != (code *)0x0) {
      (**(code **)((int)this + 0x10))
                (param_2,this,*(undefined4 *)((int)this + 8),  // +0x8 likely user data
                 *(undefined4 *)((int)this + 0x14));           // +0x14 likely callback context
      return 1;
    }
    // No callback, free the memory
    VirtualFree(this,0,0x8000);  // MEM_RELEASE
    uVar1 = 1;
  }
  return uVar1;
}