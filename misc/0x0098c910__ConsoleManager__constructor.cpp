// FUNC_NAME: ConsoleManager::constructor
undefined4 * __fastcall ConsoleManager::constructor(undefined4 *this)

{
  undefined8 *puVar1;
  UINT blinkTime;
  
  // Call base class constructor
  FUN_005bf9b0();
  
  // Initialize vtable pointer and member variables
  this[0x13] = &PTR_FUN_00e2f19c;  // +0x4C - vtable pointer
  this[0x14] = 1;                   // +0x50 - console active flag
  this[0x15] = 0;                   // +0x54 - some state
  this[0x16] = &PTR_LAB_00d916b0;  // +0x58 - vtable pointer
  
  // Store global singleton pointer
  DAT_0112a044 = this;              // Global console manager instance
  
  // Initialize more vtable pointers
  *this = &PTR_FUN_00d916f8;        // +0x00 - primary vtable
  this[4] = &PTR_LAB_00d916d0;      // +0x10 - secondary vtable
  this[0x13] = &PTR_LAB_00d916c0;   // +0x4C - vtable pointer
  this[0x16] = &PTR_LAB_00d916bc;   // +0x58 - vtable pointer
  this[0x17] = 0;                   // +0x5C - some pointer
  this[0x48] = 0;                   // +0x120 - some value
  
  // Initialize string/list related fields
  *(undefined1 *)(this + 0x80) = 0; // +0x200 - string buffer start
  this[0x81] = 0;                   // +0x204 - string length
  this[0x82] = 0;                   // +0x208 - string capacity
  this[0x83] = 0;                   // +0x20C - some value
  this[0x84] = 0;                   // +0x210 - caret blink time
  
  // Initialize linked list (circular doubly linked list)
  puVar1 = (undefined8 *)(this + 0x86);  // +0x218 - list head
  *puVar1 = 0;                      // Initialize first element
  *(undefined8 *)(this + 0x88) = 0; // +0x220 - next pointer
  *(undefined8 **)puVar1 = puVar1;  // Self-referencing circular list
  this[0x87] = puVar1;              // +0x21C - list pointer
  this[0x88] = 0;                   // +0x220 - list size
  
  // Initialize more fields
  *(undefined1 *)(this + 0x89) = 0; // +0x224 - some flag
  this[0x8a] = 0;                   // +0x228 - some value
  this[0x8c] = 0;                   // +0x230 - some value
  this[0x8d] = 0;                   // +0x234 - some value
  this[0x8e] = 0;                   // +0x238 - some value
  this[0x90] = 0;                   // +0x240 - some value
  this[0x91] = 0;                   // +0x244 - some value
  this[0x92] = 0;                   // +0x248 - some value
  this[0x94] = 0;                   // +0x250 - some value
  this[0x95] = 0;                   // +0x254 - some value
  this[0x96] = 0;                   // +0x258 - some value
  this[0x98] = 0;                   // +0x260 - some value
  this[0x99] = 0;                   // +0x264 - some value
  this[0x9a] = 0;                   // +0x268 - some value
  this[0x9b] = 0;                   // +0x26C - some value
  this[0x9c] = 0;                   // +0x270 - some value
  
  // Initialize some more fields
  this[0x4f] = 0;                   // +0x13C - some value
  this[0x4e] = 0;                   // +0x138 - some value
  this[0x4d] = 0;                   // +0x134 - some value
  this[0x4c] = 0;                   // +0x130 - some value
  
  // Get system caret blink time for console cursor
  blinkTime = GetCaretBlinkTime();
  if (blinkTime == 0xffffffff) {
    this[0x84] = 0xffffffff;        // +0x210 - default caret blink time
    return this;
  }
  this[0x84] = blinkTime;           // +0x210 - store system caret blink time
  return this;
}