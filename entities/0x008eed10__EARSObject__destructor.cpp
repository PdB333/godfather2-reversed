// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(int this)
{
  undefined1 local_8 [8];
  
  // Call the actual destructor implementation
  FUN_008ee420(local_8, this, **(undefined4 **)(this + 4), this, *(undefined4 **)(this + 4));
  
  // Release the object's vtable/type info reference
  FUN_009c8eb0(*(undefined4 *)(this + 4));
  
  // Clear the vtable pointer and type info
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0;
  
  return;
}