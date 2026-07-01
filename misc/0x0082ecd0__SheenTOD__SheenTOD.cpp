// FUNC_NAME: SheenTOD::SheenTOD
// Address: 0x0082ecd0
// Constructor for SheenTOD (time-of-day rendering manager) - initializes vtable, globals, and allocates sub-buffer.

SheenTOD *__fastcall SheenTOD::SheenTOD(SheenTOD *this)
{
  int tmp[3]; // local_20: scratch array used for message registration
  void (*cleanupFunc)(int); // local_14: cleanup callback from message registration

  // Initialize many fields to zero
  this->field_0x04 = 0;   // +0x04
  this->field_0x08 = 0;   // +0x08
  this->field_0x0c = 0;   // +0x0c
  this->field_0x10 = 0;   // +0x10
  this->field_0x14 = 0;   // +0x14
  this->field_0x18 = 0;   // +0x18
  this->field_0x1c = 0;   // +0x1c

  // Byte at +0x20 set to 1 (boolean flag?)
  *(byte *)(&this->field_0x20) = 1;
  this->vtable = (void **)&PTR_FUN_00d737d8; // +0x00: virtual function table

  this->field_0x24 = 1;   // +0x24

  // Call global initialization (likely sets up static TOD data)
  SheenTOD::staticInit(); // FUN_008334a0

  // Copy global DAT_00d5780c to two adjacent fields
  int globalVal = _DAT_00d5780c;
  this->field_0x7c = globalVal; // +0x7c
  this->field_0x80 = globalVal; // +0x80

  // Set pointer at +0x30 to another vtable (likely sub-object or callback table)
  this->field_0x30 = (void *)&PTR_LAB_00d736c0;

  this->field_0x84 = 0; // +0x84

  // Copy 4 globals into consecutive fields (maybe color RGBA?)
  this->field_0x90 = _DAT_00d735f0;  // +0x90
  this->field_0x94 = _UNK_00d735f4;  // +0x94
  this->field_0x98 = _UNK_00d735f8;  // +0x98
  this->field_0x9c = _UNK_00d735fc;  // +0x9c

  // Set another callback pointer and initial value 0
  this->field_0xa0 = (void *)&PTR_FUN_00d737d4; // +0xa0
  this->field_0xa4 = 0; // +0xa4

  // Allocate 64 bytes for internal buffer (maybe a blend state or shader data)
  void *buffer = (void *)FUN_009c8e80(0x40);
  this->field_0xa8 = buffer; // +0xa8
  this->field_0xac = 0; // +0xac
  this->field_0xb0 = 0x10; // +0xb0: initial size/count

  // Register a message type "SheenTODMessage" with a sequence string
  tmp[0] = 0;
  tmp[1] = 0;
  tmp[2] = 0;
  cleanupFunc = NULL;
  FUN_004d4ad0(tmp, &DAT_00e2f0b0, "SheenTODMessage", "Sequence");
  FUN_004d3e20(tmp);

  // Resolve a string from field_0x10 or use default, then store hash at +0x0c
  const char *str = (const char *)this->field_0x10; // +0x10
  if (str == NULL) {
    str = (const char *)&DAT_0120546e; // default string literal (probably a path or name)
  }
  this->field_0x0c = FUN_004dafd0(str); // +0x0c: some integer handle/hash

  // Cleanup the temporary message registration structure if needed
  if (tmp[0] != 0) {
    cleanupFunc(tmp[0]);
  }

  return this;
}