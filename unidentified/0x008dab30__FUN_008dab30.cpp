// FUNC_NAME: SomeClass::resetSomeState
void __fastcall SomeClass::resetSomeState(int thisPtr)
{
  // Call virtual function at offset 0x28 from the object at thisPtr+0x58
  // This likely calls a method on a sub-object or interface
  (**(code **)(*(int *)(thisPtr + 0x58) + 0x28))(0x10);
  
  // Reset two fields to zero
  *(undefined4 *)(thisPtr + 400) = 0;   // +0x190 (400 decimal)
  *(undefined4 *)(thisPtr + 0x1ac) = 0; // +0x1AC
  return;
}