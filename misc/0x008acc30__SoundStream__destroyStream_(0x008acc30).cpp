// FUNC_NAME: SoundStream::destroyStream (0x008acc30)

void __fastcall SoundStream::destroyStream(SoundStream *this)
{
  // Destroy embedded object at offset 0x34 (likely a StringBuffer or SubObject)
  FUN_008ab560(reinterpret_cast<int>(this) + 0x34);
  
  // Call virtual function through vtable[0] (at this+8, not standard offset zero)
  // Uses global format string pointer PTR_LAB_00e35c24 and stream property fields
  (*(void (__fastcall **)(void *, int, int, int, int, int, int, int, unsigned char)) \
    (*reinterpret_cast<int *>(reinterpret_cast<int>(this) + 8)))(
      &PTR_LAB_00e35c24,
      *(int *)(reinterpret_cast<int>(this) + 0x14),  // +0x14 field1
      *(int *)(reinterpret_cast<int>(this) + 0x18),  // +0x18 field2
      *(int *)(reinterpret_cast<int>(this) + 0x1c),  // +0x1c field3
      *(int *)(reinterpret_cast<int>(this) + 0x20),  // +0x20 field4
      *(int *)(reinterpret_cast<int>(this) + 0x24),  // +0x24 field5
      *(int *)(reinterpret_cast<int>(this) + 0x28),  // +0x28 field6
      *(int *)(reinterpret_cast<int>(this) + 0x2c),  // +0x2c field7
      *(unsigned char *)(reinterpret_cast<int>(this) + 0x30)); // +0x30 byte flag
}