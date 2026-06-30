// FUNC_NAME: TNLWindowSlot::constructor
// Address: 0x004d8c00
// Role: Initializes a window slot (part of TNL packet window) with zero sequence and calls base/init function.

// This is a constructor for a 32-slot packet window entry, used in TNL networking.
// Offset +0x14 likely holds the sequence number or acknowledgment flag.
// param_2 is a pointer to the parent window or manager that is passed to the initialization routine FUN_004da550.

int __thiscall TNLWindowSlot::constructor(TNLWindowSlot* this, void* parentWindow) {
    // Set the sequence/flag at offset +0x14 to 0 (likely start of window slot)
    this->field_0x14 = 0; // +0x14: sequence number or slot state

    // Call the base/parent init function with the parent window pointer
    FUN_004da550(parentWindow);

    return (int)this;
}