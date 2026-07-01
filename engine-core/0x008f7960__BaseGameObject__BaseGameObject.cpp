// FUNC_NAME: BaseGameObject::BaseGameObject
// Constructor for a base game object with multiple inheritance (has secondary vtables at offsets 0x3C and 0x48)
// Called with an allocation flag (param_2 bit 0 indicates memory allocation needed)

undefined4 * __thiscall BaseGameObject::BaseGameObject(undefined4 *this, byte allocFlag)
{
  // Set primary vtable pointer (class own vtable)
  *this = &PTR_FUN_00d81288;  // VTABLE for BaseGameObject

  // Set secondary vtable pointer for first base interface (offset 0x3C = 15*4)
  this[0xf] = &PTR_LAB_00d81278;  // Secondary vtable 1 (e.g., INetObject or ISerializable)

  // Set secondary vtable pointer for second base interface (offset 0x48 = 18*4)
  this[0x12] = &PTR_LAB_00d81274;  // Secondary vtable 2 (e.g., ISimObject)

  // Construct sub-object at offset +0x18 (likely a SimObject or NetObject base)
  FUN_004086d0(this + 0x18);       // SubObject1::constructor (e.g., SimObject)

  // Construct sub-object at offset +0x18 again? Or offset +0x1a? Decompiler shows same offset then +0x1a.
  // Typically these would be for two different base sub-objects, but offsets are adjacent.
  // Possible that FUN_00408310 is a different constructor, and second call is for a sub-object at +0x1a (26 bytes).
  FUN_00408310(this + 0x18);       // SubObject2::constructor (e.g., NetObject?)
  FUN_00408310(this + 0x1a);       // SubObject2::constructor (again? or another sub-object at +0x1a? offset seems odd, maybe +0x1c)

  // Global initialization call (likely static initializer for some engine system)
  FUN_0046c640();                  // EARS system initialize?

  // If allocation flag indicates memory was externally allocated, call operator delete on failure??
  // Standard pattern: if (allocFlag & 1) -> call operator delete (size = 0xb4)
  if ((allocFlag & 1) != 0) {
    // This is typically a seperate function that frees memory using operator delete(size)
    // But here it's called with (this, size) - might be implementing "placement delete" or exception handling
    FUN_0043b960(this, 0xb4);     // operator delete(this, 0xb4)
  }

  return this;
}