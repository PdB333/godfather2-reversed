// FUNC_NAME: CharacterComponent::CharacterComponent

void __thiscall CharacterComponent::CharacterComponent(void)
{
  // Call base class constructor (EARSBase or similar)
  // Address: 0x0046c590
  EARSBase::EARSBase(this);

  // Set virtual function table pointers
  // Vtable for CharacterComponent at offset 0
  *(void**)this = (void*)&VTable_CharacterComponent; // PTR_FUN_00e36c80

  // Second vtable pointer at offset 0x3C (15 ints from start)
  // Interface or secondary base class
  *(void**)((int)this + 0x3C) = (void*)&VTable_CharacterComponent_Interface1; // PTR_LAB_00e36ca0

  // Third vtable pointer at offset 0x48 (18 ints from start)
  *(void**)((int)this + 0x48) = (void*)&VTable_CharacterComponent_Interface2; // PTR_LAB_00e36cb0

  // Initialize fields
  // Offset 0x50: some pointer or integer (initially 0)
  *(int*)((int)this + 0x50) = 0;

  // Offset 0x54: 16-bit value (initially 0)
  *(short*)((int)this + 0x54) = 0;

  // Offset 0x56: 16-bit value (initially 0)
  *(short*)((int)this + 0x56) = 0;

  // Offset 0x58: integer (initially 0)
  *(int*)((int)this + 0x58) = 0;

  // Offset 0x5C: 16-bit value (initially 0)
  *(short*)((int)this + 0x5C) = 0;

  // Offset 0x5E: 16-bit value (initially 0)
  *(short*)((int)this + 0x5E) = 0;

  // Clear block of 8 integers from offset 0x60 to 0x7C
  // Likely an array of 8 state values or timers
  for (int i = 0; i < 8; i++) {
    *(int*)((int)this + 0x60 + i * 4) = 0;
  }

  // Offset 0x80: pointer to allocated memory (initially 0)
  *(int*)((int)this + 0x80) = 0;

  // Offset 0x84: some integer (initially 0)
  *(int*)((int)this + 0x84) = 0;

  // Offset 0x88: sentinel value -1 (e.g., invalid index, timer ID, or handle)
  *(int*)((int)this + 0x88) = -1;

  // Offset 0x8C: single byte (initially 0)
  *(char*)((int)this + 0x8C) = 0;

  // Defensive check: if pointer at offset 0x80 is non-null, free it and clear
  // (Possibly because this constructor can be called on already initialized memory)
  if (*(int*)((int)this + 0x80) != 0) {
    FUN_004daf90(*(void**)((int)this + 0x80)); // deallocate function
    *(int*)((int)this + 0x80) = 0;
  }
}