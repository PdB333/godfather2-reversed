// FUNC_NAME: EventScheduler::constructor
undefined4 * __thiscall EventScheduler::constructor(undefined4 *this, char *eventName, undefined4 param3, undefined4 param4, undefined4 param5)
{
  // Call base class constructor
  FUN_0064cc90();
  
  // Set vtable pointer
  *this = &PTR_LAB_00d6a744;
  
  // Copy event name (max 63 characters)
  _strncpy((char *)(this + 8), eventName, 0x3f);
  
  // Store parameters
  this[1] = param3;  // +0x04 - event type/ID
  this[3] = param4;  // +0x0C - trigger time/delay
  this[2] = param5;  // +0x08 - event data
  
  // Initialize linked list pointers
  this[4] = 0;  // +0x10 - next event
  this[5] = 0;  // +0x14 - prev event
  this[6] = 0;  // +0x18 - aux data 1
  this[7] = 0;  // +0x1C - aux data 2
  
  // Store global list head reference
  this[0x1c] = DAT_012059ec;  // +0x70 - previous head of event list
  DAT_012059ec = this;        // Update global event list head to this
  
  return this;
}