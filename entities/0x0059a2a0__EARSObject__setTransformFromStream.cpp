// FUNC_NAME: EARSObject::setTransformFromStream
void __fastcall EARSObject::setTransformFromStream(int this)
{
  int streamPtr;
  int objPtr;
  undefined1 *stackVar;
  undefined1 localTransform [28];
  
  streamPtr = *(int *)(this + 8);
  if (*(short *)(streamPtr + 2) != 0x28) {
    stackVar = (undefined1 *)0x59a2c4;
    (**(code **)(*DAT_01205590 + 4))(); // error handler
  }
  
  streamPtr = *(int *)(this + 8);
  // Read 4 bytes from stream and combine into a single value (likely a hash or ID)
  stackVar = (undefined1 *)
               (((*(int *)(streamPtr + 4) * 0x100 + *(int *)(streamPtr + 8)) * 0x100 + *(int *)(streamPtr + 0xc)
                ) * 0x100 + *(int *)(streamPtr + 0x10));
  
  objPtr = FUN_00599aa0(this); // findOrCreateObject
  if (objPtr == 0) {
    stackVar = (undefined1 *)0x59a2f9;
    (**(code **)(*DAT_01205590 + 4))(); // error handler
    return;
  }
  
  stackVar = localTransform;
  *(undefined4 *)(objPtr + 0x138) = *(undefined4 *)(streamPtr + 0x24); // copy some field to object +0x138
  
  // Read transform from stream (4 floats)
  (**(code **)(*DAT_012055a8 + 4))
            (*(undefined4 *)(streamPtr + 0x14), *(undefined4 *)(streamPtr + 0x18),
             *(undefined4 *)(streamPtr + 0x1c), *(undefined4 *)(streamPtr + 0x20));
  
  // Apply transform to object at offset +0xa0
  (**(code **)(*DAT_012055a8 + 0x28))(&stackVar, objPtr + 0xa0);
  
  // Set flag 0x40 on object at +0x7c (dirty/updated flag)
  *(uint *)(objPtr + 0x7c) = *(uint *)(objPtr + 0x7c) | 0x40;
  
  return;
}