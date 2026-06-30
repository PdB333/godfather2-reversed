// FUNC_NAME: NetStream::writeAbstractObject

void __thiscall NetStream::writeAbstractObject(void* this, void* object)
{
  uint* pBufferPtr;
  uint* alignedPtr;
  uint field1, field2, field3;
  uint flags;

  // Store the object reference in this stream at +0x24
  *(void**)((int)this + 0x24) = object;

  // Access global buffer pointer at DAT_01206880+0x14
  pBufferPtr = (uint*)(DAT_01206880 + 0x14);
  // Write the type descriptor pointer into the buffer
  **(int***)pBufferPtr = (int*)&PTR_LAB_01124c88;
  *pBufferPtr += 4;

  // Write the this pointer
  *(int*)(*pBufferPtr) = (int)this;
  // Align to 4-byte boundary (round up to next multiple of 4)
  alignedPtr = (uint*)((*pBufferPtr + 7) & 0xFFFFFFFC);
  *pBufferPtr = (uint)alignedPtr;

  // Write the object pointer
  *alignedPtr = (uint)object;
  *pBufferPtr += 4;

  // Check byte order flag at object+0x2c (bit 0x200)
  flags = *(ushort*)((int)object + 0x2c);
  if ((flags & 0x200) == 0) {
    // Little‑endian order
    field1 = *(uint*)((int)object + 0x24);
    field2 = *(uint*)((int)object + 0x20);
    field3 = *(uint*)((int)object + 0x28);
  } else {
    // Big‑endian order (swap offsets)
    field1 = *(uint*)((int)object + 0x20);
    field2 = *(uint*)((int)object + 0x28);
    field3 = *(uint*)((int)object + 0x24);
  }

  // Finalize the buffer entry
  FUN_0048ee40();

  // Store the extracted fields into this stream
  *(uint*)((int)this + 0x64) = field1;
  *(uint*)((int)this + 0x60) = field2;
  *(uint*)((int)this + 0x68) = field3;
}