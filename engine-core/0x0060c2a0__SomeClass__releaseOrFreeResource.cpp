// FUNC_NAME: SomeClass::releaseOrFreeResource
void SomeClass::releaseOrFreeResource(void)
{
  // unaff_ESI points to 'this' object
  // +0x1C (index 7): resource pointer
  // +0x24 (index 9): some integer parameter
  // +0x20 (index 8): another integer parameter
  // +0x28 (index 10): byte flag
  
  FUN_0060be80(this->field_1C, this->field_24);
  
  if (this->field_00 != 0) {
    // Call a virtual function at vtable+4 (likely release or destroy)
    (**(code **)(*DAT_01205868 + 4))(this->field_1C, this->field_20);
    this->field_1C = 0;
    *(byte *)(&this->field_28) = 1;  // Set flag to indicate resource is freed
  }
}