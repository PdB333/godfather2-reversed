// FUNC_NAME: GameObject::GameObject
// Function address: 0x008aba80
// Role: Constructor for a base game object (likely part of EARS engine)
// Initializes vtable pointers, flags, and embedded sub-object pointer.

undefined4 * __thiscall GameObject::GameObject(GameObject *this, int createSubObject)
{
  undefined4 subObject;
  
  // If createSubObject is non-zero, allocate a sub-object via FUN_00481610
  if (createSubObject == 0) {
    subObject = 0;
  }
  else {
    subObject = FUN_00481610();  // Likely operator new or sub-object factory
  }
  
  // Call base class initialization (e.g., register class, set base vtable)
  FUN_0064d390(0, 1);  // Possibly BaseObject::init(0,1)
  
  // Set base class vtable pointer
  *this = &PTR_LAB_00e317dc;  // Base vtable
  
  // Initialize field at +0x18 to 0
  this[6] = 0;  // +0x18: some flag or pointer
  
  // Attach sub-object (if any) via FUN_00454a10
  FUN_00454a10(subObject);  // Possibly setSubObject(subObject)
  
  // Set flag at +0x24 to 1
  this[9] = 1;  // +0x24: e.g., m_isActive = 1
  
  // Override vtable with derived class vtable
  *this = &PTR_LAB_00d79ef0;  // Derived vtable
  
  // Set function pointers for virtual dispatch or callbacks
  this[10] = &PTR_FUN_00d79ed0;  // +0x28: function pointer (e.g., m_updateFunc)
  this[0xc] = &LAB_008a8a10;     // +0x30: another function pointer (e.g., m_handleEvent)
  
  // Initialize various fields to default values
  this[0xd] = 0;                 // +0x34: m_state = 0
  this[0x11] = 0;                // +0x44: m_counter = 0
  this[0x14] = 0;                // +0x50: m_flags = 0
  this[0xe] = &PTR_LAB_00e35c24; // +0x38: pointer to some static data
  this[0xf] = 0xffffffff;        // +0x3C: m_id1 = -1
  this[0x10] = 0xffffffff;       // +0x40: m_id2 = -1
  this[0x12] = 0xffffffff;       // +0x48: m_id3 = -1
  this[0x13] = 0xffffffff;       // +0x4C: m_id4 = -1
  this[0x15] = 0;                // +0x54: m_unknown1 = 0
  this[0x17] = 0;                // +0x5C: m_unknown2 = 0
  this[0x18] = 0;                // +0x60: m_unknown3 = 0
  this[0x19] = 0;                // +0x64: m_unknown4 = 0
  
  // Set embedded sub-object pointer: points to the function pointer array at +0x28
  this[5] = this + 10;           // +0x14: m_subObjectPtr = &this[10]
  
  return this;
}