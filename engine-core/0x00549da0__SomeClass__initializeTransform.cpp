// FUNC_NAME: SomeClass::initializeTransform
void __fastcall SomeClass::initializeTransform(int thisPtr)
{
  undefined4 temp[3];
  
  // Call virtual function at vtable offset 0xa4 (likely getWorldMatrix or similar)
  (**(code **)(**(int **)(thisPtr + 0x10c) + 0xa4))(temp);
  
  // Set transform data at offset 0x40 to point to offset 0x110
  *(int *)(thisPtr + 0x40) = thisPtr + 0x110;
  
  // Copy transform components
  *(undefined4 *)(thisPtr + 0x44) = unaff_ESI;  // +0x44: rotation/translation component
  *(undefined4 *)(thisPtr + 0x48) = temp[0];     // +0x48: scale/translation component
  *(undefined4 *)(thisPtr + 0x4c) = DAT_00e2b1a4; // +0x4c: global constant (likely identity or zero)
}