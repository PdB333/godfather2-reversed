// FUNC_NAME: SimManager::SimManager

void SimManager::SimManager(void)
{
  // Initialize base class (likely EARS::Object or similar)
  this->baseConstructor(); // FUN_00652ab0

  // Set vtable pointer to class's virtual function table
  // Offset 0x00: vtable pointer
  this->vtable = reinterpret_cast<int*>(0x00e42e68); // PTR_LAB_00e42e68

  // Zero-initialize a block of member fields.
  // Offsets are indices into a uint32 array (i.e., byte offset = index * 4).
  // These likely represent flags, counters, or pointers.
  this->field_0x73 = 0; // +0x1CC (uint32)
  this->field_0x74 = 0; // +0x1D0
  this->field_0x75 = 0; // +0x1D4
  this->field_0x76 = 0; // +0x1D8
  this->field_0x77 = 0; // +0x1DC
  this->field_0x78 = 0; // +0x1E0
  this->field_0x79 = 0; // +0x1E4
  this->field_0x7a = 0; // +0x1E8
  this->field_0x7c = 0; // +0x1F0
  this->field_0x7d = 0; // +0x1F4

  // Set a sentinel value (e.g., invalid ID/handle) - offset 0x7b = +0x1EC
  this->field_0x7b = -1;
}