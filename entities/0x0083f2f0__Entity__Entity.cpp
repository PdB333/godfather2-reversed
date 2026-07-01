// FUNC_NAME: Entity::Entity
void __fastcall Entity::Entity(Entity *this)
{
  // Set primary vtable pointer (base class 1) at offset 0x00
  this->vtable1 = &PTR_FUN_00d74438;
  // Set secondary vtable pointer (base class 2) at offset +0x3C (0xF * 4)
  *(void ***)((char *)this + 0x3C) = &PTR_LAB_00d74428;
  // Set tertiary vtable pointer (base class 3) at offset +0x48 (0x12 * 4) 
  *(void ***)((char *)this + 0x48) = &PTR_LAB_00d74424;
  // Call common initialization routine
  FUN_0083f0e0();
  return;
}