// FUNC_NAME: Entity::~Entity
void __fastcall Entity::~Entity(Entity* this)
{
  SubObject* subObj = this->m_pSubObject; // +0x84
  // Set vtable to the current class's vtable (likely base class in debug destr)
  this->vtable = &Entity_vtable; // PTR_FUN_00d5f060
  this->field_8 = &Entity_staticField; // PTR_LAB_00d5f058

  if (subObj != 0) {
    releaseSubObject(subObj); // FUN_009e7530
    RefCountBlock* refBlock = *(RefCountBlock**)((uint8*)subObj + 0x10);
    if (refBlock->maxRefCount != 0) { // short at +4 (offset 4)
      refBlock->currentRefCount--; // short at +6
      if (refBlock->currentRefCount == 0) {
        // Call the ref block's destructor with argument 1
        ((void (__thiscall*)(RefCountBlock*, int))refBlock->vtable)(refBlock, 1);
      }
    }
    cleanupSubObjectAfterRelease(); // FUN_009f01a0
  }
  baseClassDestructor(); // FUN_00473a60
}