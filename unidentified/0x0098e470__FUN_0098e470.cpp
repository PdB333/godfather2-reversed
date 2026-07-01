// FUNC_NAME: UnknownClass::destructorOrShutdown
void __fastcall UnknownClass::destructorOrShutdown(unknown *this)
{
  this->vtable = &PTR_FUN_00d91920;
  this->field4 = &PTR_LAB_00d918fc;
  this->field13 = &PTR_LAB_00d918f8;
  FUN_0098e380(); // likely: releaseSubObjects or similar
  FUN_0098e270(); // likely: cleanupInternal
  if (this->field18 != 0) {
    (*(code *)this->field1b)(this->field18); // call destructor via vtable on child object at +0x18
  }
  if (this->field14 != 0) {
    (*(code *)this->field17)(this->field14); // call destructor via vtable on child object at +0x14
  }
  this->field13 = &PTR_LAB_00d91774;
  DAT_01129890 = 0; // likely: global flag or reference count
  FUN_005c16e0(); // likely: common cleanup or memory manager update
  return;
}