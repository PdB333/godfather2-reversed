// FUNC_NAME: DebugLogEntry::DebugLogEntry

// Constructor for a debug log entry node, added to a global linked list.
// This is likely part of EA's engine debug/logging system.
// The string parameter is copied to a fixed-size buffer (63 chars + null).
// Offsets: +0x00: vtable pointer, +0x04: param3 (some int), +0x08: param5, +0x0C: param4, 
// +0x10-0x1C: next/prev links?, +0x20: name string (63 chars max), +0x70: next pointer in list

DebugLogEntry * __thiscall DebugLogEntry::DebugLogEntry(DebugLogEntry *this, char *name, int param3, int param4, int param5)
{
  // Call base class constructor
  Base::Base(this);
  
  // Set vtable to DebugLogEntry's virtual function table
  this->vtable = &DebugLogEntry_VTable;
  
  // Copy name into fixed buffer at offset +0x20 (32 bytes into object)
  _strncpy((char *)(this + 8), name, 0x3f); // this+8 is exactly at byte offset 0x20
  this->field_0x04 = param3;   // +0x04
  this->field_0x0C = param4;   // +0x0C
  this->field_0x08 = param5;   // +0x08
  this->field_0x10 = 0;        // +0x10
  this->field_0x14 = 0;        // +0x14
  this->field_0x18 = 0;        // +0x18
  this->field_0x1C = 0;        // +0x1C
  
  // Link into the global list (singleton head stored at DAT_012059ec)
  this->next = gDebugLogHead;   // +0x70 (offset 0x1c * 4 = 0x70)
  gDebugLogHead = this;
  
  return this;
}