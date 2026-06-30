// FUNC_NAME: ResourceHolder::release
// Function at 0x00486740: Cleans up a resource holder by releasing the managed pointer and zeroing fields.
// Offsets: +0x00 managed pointer, +0x04 usage count or handle, +0x08 some other state
void __thiscall ResourceHolder::release(undefined4 *this)
{
  this[1] = 0;                                  // +0x04 reset count/state
  FUN_009c8f10(this[0]);                        // +0x00 release the managed object
  this[0] = 0;                                  // +0x00 null pointer
  this[2] = 0;                                  // +0x08 clear other state
  return;
}