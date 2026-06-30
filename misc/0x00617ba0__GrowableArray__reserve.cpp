// FUNC_NAME: GrowableArray::reserve
void GrowableArray::reserve(uint newCapacity)
{
  // param_1 is 'this', with layout:
  // +0x00: m_pData (pointer to array of elements, each 8 bytes)
  // +0x04: m_nCount (number of elements currently)
  // +0x08: m_nCapacity (allocated capacity)
  int *thisPtr = param_1;
  uint *countPtr = (uint *)(thisPtr + 1);
  uint *capPtr = (uint *)(thisPtr + 2);

  if (*capPtr >= newCapacity)
    return;

  // Allocate new array of 8-byte elements
  undefined4 *newData = (undefined4 *)FUN_009c8e80(newCapacity * 8);

  if (*thisPtr != 0)
  {
    uint idx = 0;
    undefined4 *dest = newData;
    if (*countPtr != 0)
    {
      do
      {
        undefined4 *src = (undefined4 *)(*thisPtr + idx * 8);
        // Copy first 4 bytes (key/ID)
        if (dest != (undefined4 *)0x0)
        {
          *dest = *src;
          // Initialize second 4 bytes (ref-counted pointer) to null, then call a function
          // FUN_006164e0 might be RefCountedHandle::setNull or similar
          dest[1] = 0;
          FUN_006164e0(dest + 1);
        }

        // Release the old reference in source
        int oldRef = src[1];
        if (oldRef != 0)
        {
          short *refCount = (short *)(oldRef + 8);
          *refCount = *refCount - 1;
          if (*refCount == 0)
          {
            FUN_00616dc0(oldRef); // destructor
            (**(code **)(*DAT_01205964 + 4))(oldRef, 0); // vtable delete
          }
          src[1] = 0;
        }

        idx++;
        dest += 2;
      } while (idx < *countPtr);
    }
    // Free old array
    FUN_009c8f10(*thisPtr);
  }

  *thisPtr = (int)newData;
  *capPtr = newCapacity;
}