// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(undefined4 *this)
{
  *this = &PTR_FUN_00d88f28;
  this[4] = &PTR_LAB_00d88f00;
  this[0x13] = &PTR_LAB_00d88efc;
  this[0x14] = &PTR_LAB_00d88eec;
  FUN_00408310(&DAT_0113050c); // likely release some global resource
  FUN_009c8f10(this[0x4b]); // release pointer at +0x12C
  FUN_009c8f10(this[0x4c]); // release pointer at +0x130
  FUN_009c8f10(this[0x4d]); // release pointer at +0x134
  FUN_009c8f10(this[0x4e]); // release pointer at +0x138
  FUN_009c8f10(this[0x4f]); // release pointer at +0x13C
  FUN_009c8f10(this[0x56]); // release pointer at +0x158
  FUN_009c8f10(this[0x57]); // release pointer at +0x15C
  FUN_009c8f10(this[0x52]); // release pointer at +0x148
  if ((undefined4 *)this[0x5b] != (undefined4 *)0x0) { // +0x16C
    (*(code *)**(undefined4 **)this[0x5b])(1); // call vtable method with arg 1
  }
  FUN_004086d0(&DAT_012069b4); // release global resource
  FUN_004086d0(&DAT_012069c4); // release global resource
  if (this[0x42] != 0) { // +0x108
    (*(code *)this[0x45])(this[0x42]); // call function pointer with arg
  }
  if (this[0x3f] != 0) { // +0xFC
    FUN_009c8f10(this[0x3f]);
  }
  if (this[0x3c] != 0) { // +0xF0
    FUN_009c8f10(this[0x3c]);
  }
  if (this[0x37] != 0) { // +0xDC
    FUN_009c8f10(this[0x37]);
  }
  if (this[0x34] != 0) { // +0xD0
    FUN_009c8f10(this[0x34]);
  }
  FUN_005c16e0(); // shutdown subsystem
  if (this[0x17] != 0) { // +0x5C
    FUN_009c8f10(this[0x17]);
  }
  FUN_004083d0(); // final cleanup
  this[0x13] = &PTR_LAB_00d88ee8; // update vtable pointer at +0x4C
  DAT_0112ebb4 = 0; // clear global flag
  FUN_005c16e0(); // second shutdown call
  return;
}