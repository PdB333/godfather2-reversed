// FUNC_NAME: UnknownClass::initDefaults

void __stdcall UnknownClass::initDefaults(UnknownClass *thisPtr)
{
  // Zero out all 15 dwords of the struct (60 bytes total)
  thisPtr->field_00 = 0;   // +0x00
  thisPtr->field_04 = 0;   // +0x04
  thisPtr->field_08 = 0;   // +0x08
  thisPtr->field_0C = 0;   // +0x0C
  thisPtr->field_10 = 0;   // +0x10
  thisPtr->field_14 = 0;   // +0x14
  thisPtr->field_18 = 0;   // +0x18
  thisPtr->field_1C = 0;   // +0x1C
  thisPtr->field_20 = 0;   // +0x20
  thisPtr->field_24 = 0;   // +0x24
  thisPtr->field_28 = 0;   // +0x28
  thisPtr->field_2C = 0;   // +0x2C
  thisPtr->field_30 = 0;   // +0x30
  // Set default enum values at offsets +0x34 and +0x38
  thisPtr->field_34 = 1;   // +0x34 (default state)
  thisPtr->field_38 = 2;   // +0x38 (default state)
}