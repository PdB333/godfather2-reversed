// FUNC_NAME: EARSObjectBase::~EARSObjectBase
void __fastcall EARSObjectBase::~EARSObjectBase(EARSObjectBase* this)
{
  // Offset 0x11C: m_arrayCount1 (int)
  int arrayCount1 = this->field_0x11C;
  if (arrayCount1 >= 0) {
    // Get thread-local storage for memory debugging/tracking
    TlsGetValue(DAT_01139810); // TLS slot index
    // Deallocate array at offset 0x114 (m_arrayData1) with tag 0x17
    FUN_00aa26e0(this->field_0x114, arrayCount1 * 4, 0x17);
  }
  // First vtable reassignment (likely derived class vtable)
  this->vtable = &PTR_LAB_00e3572c;
  // Offset 0x10: m_arrayCount2 (int)
  int arrayCount2 = this->field_0x10;
  if (arrayCount2 >= 0) {
    TlsGetValue(DAT_01139810);
    // Deallocate array at offset 0x8 (m_arrayData2) with tag 0x17
    FUN_00aa26e0(this->field_0x08, arrayCount2 << 4, 0x17); // 16 bytes per element
  }
  // Final vtable reassignment (likely base class vtable)
  this->vtable = &PTR_LAB_00dcf968;
}