//FUNC_NAME: Entity::Entity
// Constructor for Entity class (likely base for game objects)
// Sets up multiple vtable pointers and initializes subobject at offset 0x14
// Address: 0x0080b960

undefined4 * __thiscall Entity::Entity(undefined4 *this, byte allocFlag)
{
  // Set primary vtable at +0x0
  *this = &PTR_FUN_00d724cc;
  // Set secondary vtable at +0x3C (offset 0xF * 4)
  this[0xF] = &PTR_LAB_00d724bc;
  // Set tertiary vtable at +0x48 (offset 0x12 * 4)
  this[0x12] = &PTR_LAB_00d724b8;
  
  // Initialize subobject at offset +0x14 (likely a member like Animation or Animated)
  // Calls two initialization functions on that subobject
  FUN_004086d0(this + 0x14);  // Subobject constructor/init
  FUN_00408310(this + 0x14);  // Subobject additional init
  
  // Global initialization call (e.g., singleton or static manager)
  FUN_0046c640();
  
  // If allocFlag has bit 0 set, call operator delete with size 0x80 (128 bytes)
  // This is a common pattern for placement new constructors that free on failure
  if ((allocFlag & 1) != 0) {
    FUN_0043b960(this, 0x80);  // operator delete(this, 0x80)
  }
  
  return this;
}