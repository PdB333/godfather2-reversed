// Function at 0x00704730: Getter for a member pointer stored at offset 0xB0.
// FUNC_NAME: GameObject::getPointerB0
undefined4 __fastcall GameObject::getPointerB0(int thisPtr)
{
  // Retrieve the pointer stored at offset 0xB0 from the object
  return *(undefined4 *)(thisPtr + 0xb0);
}