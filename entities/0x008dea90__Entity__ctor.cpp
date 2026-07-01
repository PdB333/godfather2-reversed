// FUNC_NAME: Entity::ctor
// Function address: 0x008dea90
// Role: Constructor for Entity class (size 0x220 bytes, multiple inheritance with vtable pointers at offsets 0x00, 0x3C, 0x48, 0x50, 0x54, 0x58)
// allocFlag: byte parameter indicating whether to deallocate on failure (1 = call operator delete if construction fails after base construction)

undefined4 * __thiscall Entity::ctor(undefined4 *this, byte allocFlag)

{
  // Set vtable pointer at offset 0x00
  *this = &PTR_FUN_00d7ef20;
  
  // Set additional vtable pointers for multiple inheritance bases
  this[0xf] = &PTR_LAB_00d7ef10;  // +0x3C
  this[0x12] = &PTR_LAB_00d7ef0c; // +0x48
  this[0x14] = &PTR_LAB_00d7ef08; // +0x50
  this[0x15] = &PTR_LAB_00d7eea8; // +0x54
  this[0x16] = &PTR_LAB_00d7ee40; // +0x58
  
  // Call base class constructor (implicit this)
  FUN_008ded50();
  
  // If allocFlag & 1 is set, call deallocation function with size 0x220
  if ((allocFlag & 1) != 0) {
    FUN_0043b960(this, 0x220); // operator delete or free
  }
  
  return this;
}