// FUNC_NAME: LargeManager::~LargeManager
undefined4 * __thiscall LargeManager::~LargeManager(LargeManager *this, byte flags)
{
  // Set initial vtable (base class?)
  this->vtable = &PTR_FUN_00e3e78c;
  // Call base destructor / common cleanup
  FUN_005c0360();
  // Zero out fields at offsets +0xC and +0x8
  this->field_0xC = 0;
  this->field_0x8 = 0;
  // If the resource pointer at +0x4 is not null, release it
  if (this->m_pResource != NULL) {
    // Call release function through indirection: global->vtable[1] (offset 4)
    (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(this->m_pResource, 0);
  }
  // Nullify the resource pointer
  this->m_pResource = NULL;
  // Switch vtable to destroyed state (marks object as destroyed)
  this->vtable = &PTR_LAB_00e3e74c;
  // If the object was dynamically allocated (flags bit 0 set), delete it
  if ((flags & 1) != 0) {
    (*DAT_0119caf8)(this, 0xC20);
  }
  return reinterpret_cast<undefined4 *>(this);
}