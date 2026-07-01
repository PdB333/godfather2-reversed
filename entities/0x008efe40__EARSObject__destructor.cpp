// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(int this)
{
  undefined1 local_8 [8];
  
  // Call the base destructor or cleanup function
  FUN_008ee740(local_8, this, **(undefined4 **)(this + 4), this, *(undefined4 **)(this + 4));
  
  // Release the object at +0x04
  FUN_009c8eb0(*(undefined4 *)(this + 4));
  
  // Clear pointers
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0;
  
  return;
}