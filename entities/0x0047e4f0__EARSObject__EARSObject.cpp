// FUNC_NAME: EARSObject::EARSObject
// Address: 0x0047e4f0
// Role: Constructor for EARSObject with optional auto-registration flag
// param_2 (byte): bit0 = 1  => call vtable function at offset 4 (e.g., registerWithManager)
// DAT_01223410 is likely g_engine or a global manager vtable base

undefined4 __thiscall EARSObject::EARSObject(byte allocateFlag)
{
  // Base class constructor (possibly assigns vtable, initializes base members)
  this->EARSObject_baseInit();   // actually calls FUN_0047e550

  // If the allocate flag indicates heap allocation (bit0 set), call the
  // second virtual function from the manager's vtable (offset +4).
  // Typically used to register the object with a manager or allocate resources.
  if ((allocateFlag & 1) != 0) {
    // *(int**)DAT_01223410  => manager object vtable pointer
    // +0x2d4                 => offset to a sub-vtable or function table
    // *(int*) (that + 0x2d4) => address of a vtable
    // +4                     => second virtual function (index 1)
    (*(void (__thiscall **)(EARSObject *, int))(
        **(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
  }
  return this;
}