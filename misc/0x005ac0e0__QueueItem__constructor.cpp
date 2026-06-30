// FUNC_NAME: QueueItem::constructor
void __thiscall QueueItem::constructor(void *this)

{
  char cVar1;
  uint *puVar2;
  uint uVar3;
  
  *(uint *)this = *(uint *)this & 0xffff801a | 0x1a;
  *(undefined2 *)((int)this + 2) = 0;
  *(uint *)this = *(uint *)this | 0x8000;
  *(undefined2 *)((uint *)this + 1) = 4;
  *(undefined2 *)((int)this + 6) = 0;
  *(uint *)((int)this + 8) = (uint)((uint *)this + 3);  // +0x8: data pointer
  _memset((uint *)this + 3,0,0x40);  // Zero out 64-byte data buffer
  cVar1 = FUN_0059c5c0(0);  // IsInputActive?
  if (cVar1 != '\0') {
    puVar2 = (uint *)FUN_0059c3b0();  // GetControllerState
    uVar3 = *puVar2 & 0x7fff;
    if (((*puVar2 & 0x8000) != 0) && ((uVar3 == 0xd || (uVar3 == 0x12)))) {
      uVar3 = FUN_0059c3b0();
      *(uint *)((int)this + 0x4c) = uVar3;  // +0x4c: storedControllerState
      FUN_0059c690();  // ClearInputBuffer
      return;
    }
  }
  *(uint *)((int)this + 0x4c) = 0;  // Clear stored state
  return;
}