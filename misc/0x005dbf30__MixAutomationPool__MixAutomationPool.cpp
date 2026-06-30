// FUNC_NAME: MixAutomationPool::MixAutomationPool
void __thiscall MixAutomationPool::MixAutomationPool(MixAutomationPool *this)
{
  // Set vtable pointer at offset 0x00
  *(void **)this = (void *)PTR_FUN_00e3f2e0;
  // Clear fields at offsets 0x04, 0x08, 0x0C
  this->field_0x04 = 0;
  this->field_0x08 = 0;
  this->field_0x0C = 0;
  // Set field at offset 0x14 (index 5) to global pool list head (DAT_012054b8)
  this->field_0x14 = (int)DAT_012054b8;
  // Store this pool pointer globally (DAT_01223508)
  DAT_01223508 = (int)this;
  // Set name string at offset 0x18 (index 6)
  this->field_0x18 = (int)"MixAutomationPool";
  // Update global pool list head to point to field at offset 0x10 (index 4)
  DAT_012054b8 = (int)&this->field_0x10;
  // Clear fields at offsets 0x1C, 0x20, 0x24 (indices 7,8,9)
  this->field_0x1C = 0;
  this->field_0x20 = 0;
  this->field_0x24 = 0;
  // Set max elements / capacity at offset 0x28 (index 10)
  this->maxElements = 200; // +0x28
  // Clear field at offset 0x2C (index 11)
  this->field_0x2C = 0;
  // Set element stride at offset 0x30 (index 12) to 4
  this->elementStride = 4; // +0x30
  // Set field at offset 0x34 (index 13) to 1
  this->field_0x34 = 1;
  // Set two fields at offsets 0x3C (index 15) and 0x38 (index 14) to 0x68 (104)
  this->field_0x3C = 0x68; // +0x3C
  this->field_0x38 = 0x68; // +0x38
  // Clear fields at offsets 0x40 (index 16) and 0x44 (index 17)
  this->field_0x40 = 0;
  this->field_0x44 = 0;
  // Set sub-vtable at offset 0x10 (index 4) – this is the same field that DAT_012054b8 points to
  this->field_0x10 = (int)&PTR_FUN_00e3f2e8;
  // Call additional initialization routine
  FUN_005de200();
}