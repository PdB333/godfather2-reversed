// FUN_NAME: Component::initComponent
void __thiscall Component::initComponent(void *this, void *parentObject)
{
  // vtable pointer set to global table
  *(void**)this = (void*)0x00e41490;

  // Call various engine initialization routines
  callFunction00c9ec50();         // Unknown engine init
  callFunction00ab5fb0(0, 1);    // Set flag(s)

  // Zero out fields at offsets +0x84, +0x88, +0x90, +0x94 (word-sized)
  *(int*)((char*)this + 0x84) = 0;
  *(int*)((char*)this + 0x88) = 0;
  *(int*)((char*)this + 0x90) = 0;
  *(int*)((char*)this + 0x94) = 0;

  // Store parent object pointer at offset +0x08
  *(void**)((char*)this + 0x08) = parentObject;

  // Initialize sound/audio system
  callFunction00c9eac0();

  // Conditional call based on parent's field at +0x28
  if (*(int*)(*(int*)((char*)this + 0x08) + 0x28) == 0) {
    callFunction00ca3ee0();       // Some error/fallback
  }

  // Additional initialization calls
  int uVar1 = callFunction00ca8180();
  callFunction00c9ceb0(uVar1);

  if (*(int*)(*(int*)((char*)this + 0x08) + 0x28) == 0) {
    callFunction00ca3ee0();
  }

  uVar1 = callFunction00caa1c0();
  callFunction00c9ceb0(uVar1);
  uVar1 = callFunction00cd2a00();
  callFunction00ca3e90(uVar1);
  callFunction00c96910(uVar1);
  callFunction00c9eae0();

  // Store a global constant at offset +0x38
  *(int*)((char*)this + 0x38) = DAT_00e2b1a4;

  // Initialize many fields to zero
  *(int*)((char*)this + 0x04) = 0;     // offset +0x04
  *(int*)((char*)this + 0x28) = 0;     // offset +0x28
  *(int*)((char*)this + 0x2C) = 0;     // offset +0x2C
  *(int*)((char*)this + 0x30) = 0;     // offset +0x30
  *(int*)((char*)this + 0x34) = 0;     // offset +0x34
  *(int*)((char*)this + 0x9C) = 0;     // offset +0x9C
  *(char*)((char*)this + 0x24) = 0;    // byte at +0x24
  *(char*)((char*)this + 0x80) = 0;    // byte at +0x80
  *(int*)((char*)this + 0xA0) = 0;     // offset +0xA0
  *(int*)((char*)this + 0xA4) = 0;     // offset +0xA4
  *(int*)((char*)this + 0xA8) = 0;     // offset +0xA8
  *(int*)((char*)this + 0xAC) = 0;     // offset +0xAC
  *(char*)((char*)this + 0x0C) = 0;    // byte at +0x0C (originally unaff_ESI+0x30? Actually offset 0x30*4=0xC0 byte? Let's fix)

  // Re-analyzing byte assignments:
  // *(undefined1 *)(unaff_ESI + 9): unaff_ESI is int*, so (int*) + 9 = offset 0x24 -> byte set to 0 (already done)
  // *(undefined1 *)(unaff_ESI + 0x20): offset 0x80 -> byte set to 0
  // *(undefined1 *)(unaff_ESI + 0x30): offset 0xC0 -> byte set to 0
  *(char*)((char*)this + 0xC0) = 0;    // byte at +0xC0

  // Remaining zeros at offsets +0xBC, +0xB8, +0xB4, +0xB0
  *(int*)((char*)this + 0xBC) = 0;
  *(int*)((char*)this + 0xB8) = 0;
  *(int*)((char*)this + 0xB4) = 0;
  *(int*)((char*)this + 0xB0) = 0;
}