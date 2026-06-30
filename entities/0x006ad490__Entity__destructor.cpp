// FUNC_NAME: Entity::destructor
void __fastcall Entity::destructor(Entity *this)
{
  // If the child pointer at offset +0x8 is non-null, free it
  if (this->m_child != 0) {
    // FUN_004daf90 is a deletion function (likely operator delete or specific destructor)
    FUN_004daf90(&this->m_child);
  }
  // Reset vtable pointer to the base class vtable (destructor guard)
  this->vtable = &s_baseVtable; // PTR_LAB_00e2f0c0
}