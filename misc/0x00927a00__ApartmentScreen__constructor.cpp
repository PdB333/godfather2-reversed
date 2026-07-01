// FUNC_NAME: ApartmentScreen::constructor
undefined4 * __fastcall ApartmentScreen::constructor(undefined4 *this)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar1 = this + 0xa8;
  this[1] = 1;
  this[2] = 0;
  *this = &PTR_FUN_00d87aa8; // vtable pointer
  iVar3 = 0xf;
  piVar2 = piVar1;
  do {
    *piVar2 = 0;
    *(undefined2 *)(piVar2 + 1) = 0;
    *(undefined2 *)((int)piVar2 + 6) = 0;
    piVar2 = piVar2 + 2;
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  this[0xca] = 0; // +0x328
  this[0xcb] = 0; // +0x32C
  this[0xcc] = 0; // +0x330
  *(undefined1 *)(this + 3) = 0;  // +0x0C
  *(undefined1 *)(this + 0x33) = 0; // +0xCC
  *(undefined1 *)(this + 0x35) = 0; // +0xD4
  *(undefined1 *)(this + 0x65) = 0; // +0x194
  *(undefined1 *)(this + 0x67) = 0; // +0x19C
  *(undefined1 *)(this + 0x97) = 0; // +0x25C
  this[0x9f] = 0; // +0x27C
  this[0x9e] = 0; // +0x278
  this[0x9d] = 0; // +0x274
  this[0x9c] = 0; // +0x270
  this[0xa3] = 0; // +0x28C
  this[0xa2] = 0; // +0x288
  this[0xa1] = 0; // +0x284
  this[0xa0] = 0; // +0x280
  this[0xa7] = 0; // +0x29C
  this[0xa6] = 0; // +0x298
  this[0xa5] = 0; // +0x294
  this[0xa4] = 0; // +0x290
  *(undefined1 *)(this + 0xc9) = 0; // +0x324
  *(undefined1 *)((int)this + 0x325) = 0;
  FUN_00408240(piVar1,"iMsgAptScreenShown"); // register message handler
  if (*piVar1 != 0) {
    FUN_00408900(this,piVar1,0x8000); // subscribe to message
  }
  piVar1 = this + 0xaa;
  FUN_00408240(piVar1,"iMsgAptScreenHidden"); // register message handler
  if (*piVar1 != 0) {
    FUN_00408900(this,piVar1,0x8000); // subscribe to message
  }
  this[200] = 2; // +0x320, initial state
  this[0xca] = 0; // +0x328
  this[0xcb] = 0; // +0x32C
  this[0xcc] = 0; // +0x330
  return this;
}