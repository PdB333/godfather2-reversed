// FUNC_NAME: ObjectEntry::init
// Address: 0x0069ad30
// Role: Initializes a dynamically-allocated ObjectEntry (intrusive linked list node) with a string copy and a type flag.

undefined4 * __thiscall ObjectEntry::init(undefined4 *this, undefined4 *source, int id, int type, int *someStruct)
{
  undefined8 *listSelf;
  undefined4 *dst;
  undefined2 *strSrc;
  undefined4 *src;
  int unused_local;
  code *unused_cb;

  // Clear first two fields
  this[1] = 0;                      // +0x04: some pointer/flag
  *(byte *)(this + 2) = 0;          // +0x08: byte field

  // Initialize intrusive doubly-linked list (self-pointing)
  listSelf = (undefined8 *)(this + 3); // +0x0C: list node pointer
  *listSelf = 0;                     // zero the 8-byte pointer
  *(undefined8 *)(this + 5) = 0;    // +0x14: next? (also 8 bytes)
  *(undefined8 **)listSelf = listSelf; // prev = self
  this[4] = (int)listSelf;          // +0x10: next = self

  // Store ID and clear more fields
  this[9] = id;                     // +0x24: resource/object ID
  this[5] = 0;                      // +0x14: already zero
  *(byte *)(this + 6) = 0;          // +0x18: byte
  this[7] = 0;                      // +0x1C: integer

  // Set vtable
  *this = (int)&PTR_FUN_00d5ceb0;   // +0x00: vtable

  // Determine type flag
  // type == 0 or type != 1 => flag = 0x80000002; only type == 1 => flag = 0x80000001
  if ((type == 0) || (type != 1)) {
    this[10] = 0x80000002;          // +0x28: type/state flag
  } else {
    this[10] = 0x80000001;
  }

  // Clear more fields
  dst = this + 11;                  // +0x2C
  *dst = 0;                         // +0x2C: pointer
  this[13] = 0;                     // +0x34: integer
  this[12] = 0;                     // +0x30: integer

  // Copy a string from source or from a singleton pointer
  if (*(int *)(someStruct + 4) == 0) {
    // someStruct->field_4 == 0 indicates source string is valid
    if (dst != source) {
      strSrc = (undefined2 *)*source;  // dereference source to get wchar_t*
      if (strSrc == (undefined2 *)0x0) {
        strSrc = &DAT_00e2df14;        // fallback empty string
      }
      FUN_004dbb10(strSrc, 0, source[1]); // wcsncpy? (dest, flags? , maxlen)
      return this;
    }
  } else {
    src = (undefined4 *)FUN_006984f0(); // get singleton manager/string table
    if (dst != src) {
      strSrc = (undefined2 *)*src;
      if (strSrc == (undefined2 *)0x0) {
        strSrc = &DAT_00e2df14;
      }
      FUN_004dbb10(strSrc, 0, src[1]);
    }
    // The following appears to be a decompilation artifact; the local variables are likely
    // used for cleanup or error handling in the original code.
    if (unused_local != 0) {
      (*unused_cb)(unused_local);
    }
    FUN_004dd3c0();
  }
  return this;
}