// FUNC_NAME: GodfatherGameManager::constructor (inferred from global instance storage)

undefined4 * __fastcall GodfatherGameManager::constructor(undefined4 *this)
{
  undefined4 *vtableBase;

  // this+4 is the base class vtable (likely multiple inheritance)
  vtableBase = this + 1;
  *vtableBase = &PTR_FUN_00e2f19c;     // set base vtable initially
  this[2] = 1;                         // initialize some field (e.g. m_initState)
  this[3] = 0;                         // initialize another field
  *this = &PTR_FUN_00e40788;          // set primary vtable
  *vtableBase = &PTR_LAB_00e4078c;     // override base vtable to final value
  _DAT_0122351c = this;                // store global singleton pointer

  // If a secondary object exists (likely a dependency), attach it
  if (DAT_012069c4 != 0) {
    FUN_00407e60(vtableBase, &DAT_012069c4); // attach to object at DAT_012069c4
  }

  return this;
}