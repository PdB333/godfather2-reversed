// FUNC_NAME: SomeClass::updateSomething
void __fastcall SomeClass::updateSomething(int this)
{
  char cVar1;
  int *piVar2;
  int *unaff_EBX;
  int iVar3;
  undefined ***local_44;
  undefined1 uStack_40;
  int aiStack_3c [4];
  undefined **ppuStack_2c;
  undefined4 uStack_28;
  int *piStack_24;
  int iStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 uStack_10;
  float fStack_c;
  
  // Check if the float at +0xB8 is less than or equal to a global value, and not equal
  if (*(float *)(this + 0xb8) <= DAT_01205228 && DAT_01205228 != *(float *)(this + 0xb8)) {
    // Get pointer from +0x50, then dereference +0x70 from that
    iVar3 = *(int *)(*(int *)(this + 0x50) + 0x70);
    if ((iVar3 != 0) && (piVar2 = (int *)(iVar3 + -0x48), piVar2 != (int *)0x0)) {
      local_44 = (undefined ***)0x0;
      // Call virtual function at vtable+0x10 with a hash and local_44
      cVar1 = (**(code **)(*piVar2 + 0x10))(0xa5975eb2,&local_44);
      if ((cVar1 != '\0') && (unaff_EBX != (int *)0x0)) {
        // Call virtual function at vtable+0x1E4 on unaff_EBX
        piVar2 = (int *)(**(code **)(*unaff_EBX + 0x1e4))();
      }
      // Initialize stack variables
      uStack_14 = 0;
      uStack_18 = 0;
      uStack_1c = 0;
      ppuStack_2c = &PTR_FUN_00d5dbbc;
      piStack_24 = (int *)0x0;
      iStack_20 = 0;
      uStack_10 = 0;
      fStack_c = DAT_01205228;
      uStack_28 = 0x88886a27;
      if ((piVar2 != (int *)0x0) && (piVar2 + 0x12 != (int *)0x0)) {
        iStack_20 = piVar2[0x13];
        piVar2[0x13] = (int)&piStack_24;
        piStack_24 = piVar2 + 0x12;
      }
      local_44 = &ppuStack_2c;
      uStack_40 = 0;
      aiStack_3c[0] = 0;
      aiStack_3c[1] = 0;
      aiStack_3c[2] = 0;
      aiStack_3c[3] = 0;
      // Call function with array and size 4
      cVar1 = FUN_00543390(aiStack_3c,4);
      if (cVar1 != '\0') {
        iVar3 = 0;
        do {
          if (aiStack_3c[iVar3] != 0) {
            // Call function with stack offset, element+0x3C, and 0
            FUN_00408bf0(&stack0xffffffb8,aiStack_3c[iVar3] + 0x3c,0);
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < 4);
      }
      // Clean up linked list
      if (piStack_24 != (int *)0x0) {
        FUN_004daf90(&piStack_24);
      }
    }
    // Update the float at +0xB8 with global value plus another global
    *(float *)(this + 0xb8) = DAT_01205228 + _DAT_00d75f64;
  }
  return;
}