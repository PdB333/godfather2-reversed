// FUNC_NAME: Entity::constructor

undefined4 * __thiscall Entity::constructor(Entity *this, int param_2)
{
  undefined4 uVar1;
  
  // Determine handle based on parameter (0 = no allocation, non-zero = allocate)
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = allocateHandle();  // FUN_00481610 - likely allocates a handle
  }
  
  // Static initialization (e.g., reference counting or logging)
  staticInit(1, 1);  // FUN_0064d390
  
  // Set base vtable pointer (first base class)
  this->vtableBase = &vtable_BaseEntity;  // PTR_LAB_00e317dc
  
  // Initialize field at offset 0x18 (6 * 4) to 0
  this->m_flags = 0;  // +0x18
  
  // Associate handle with this entity
  setHandle(uVar1);  // FUN_00454a10
  
  // Set state to 2 (e.g., initial state)
  this->m_state = 2;  // +0x24 (9 * 4)
  
  // Overwrite vtable with derived class vtable
  this->vtable = &vtable_Entity;  // PTR_LAB_00d784dc
  
  // Set second vtable pointer (possibly for another base)
  this->vtableSecond = &vtable_SecondBase;  // PTR_LAB_00d77dc8, +0x28 (10 * 4)
  
  // Set function pointer (e.g., creation callback)
  this->m_pOnCreate = &Entity::onCreate;  // LAB_0089a1c0, +0x30 (0xc * 4)
  
  // Initialize field to 0
  this->m_unknown = 0;  // +0x34 (0xd * 4)
  
  // Set pointer to subobject at offset 0x28 (10 * 4) relative to this
  // This often appears in MSVC multiple inheritance to point to a virtual base
  this->m_pSubObject = &this->vtableSecond;  // +0x14 (5 * 4) = this + 0x28
  
  return this;
}