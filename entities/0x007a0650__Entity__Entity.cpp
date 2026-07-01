// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(undefined4 *this, int allocFlag)
{
  undefined4 allocationResult;
  
  if (allocFlag == 0) {
    allocationResult = 0;
  } else {
    allocationResult = FUN_00481610();  // Memory allocation call
  }
  FUN_0064d390(1,1);                    // Debug/memory tracking? Parameters (1,1)
  *this = &PTR_LAB_00e317dc;           // Set base vtable pointer
  this[6] = 0;                         // +0x18: unknown field (maybe reference count or state)
  FUN_00454a10(allocationResult);       // Call base class constructor (likely Entity base)
  this[9] = 1;                         // +0x24: active flag? Set to 1
  *this = &PTR_LAB_00d6a904;           // Override with derived vtable pointer
  this[10] = &PTR_LAB_00d6a6c4;        // +0x28: secondary vtable or interface pointer
  this[0xc] = &LAB_0079b0f0;           // +0x30: function pointer (likely virtual override)
  this[0xd] = 0;                       // +0x34: unknown (maybe next pointer in list or null)
  this[5] = this + 10;                 // +0x14: self-referential pointer to offset 0x28 (list node next)
  return this;
}