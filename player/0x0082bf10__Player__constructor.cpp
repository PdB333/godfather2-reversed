//FUNC_NAME: Player::constructor
undefined4 * __thiscall Player::constructor(undefined4 *this, byte allocFlag)
{
  int *allocatorVtable;

  // Set primary vtable (main class)
  *this = &PTR_FUN_00d737fc;

  // Call base class constructor (likely Sentient or Entity)
  Sentient::Sentient();

  // Set secondary vtable at offset 0x30 (multiple inheritance or interface)
  this[0xc] = &PTR_LAB_00e32854;

  // Call another initialization function (e.g., initComponents)
  Player::initComponents();

  // If allocFlag has bit 0 set, allocate memory for this object
  if ((allocFlag & 1) != 0) {
    // Get allocator vtable
    allocatorVtable = (int *)getAllocator();
    // Call allocate method (offset 4 in vtable) with size 0x160
    (**(code **)(*allocatorVtable + 4))(this, 0x160);
  }

  return this;
}