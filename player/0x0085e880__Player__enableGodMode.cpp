// FUNC_NAME: Player::enableGodMode
void __fastcall Player::enableGodMode(int thisPtr)
{
  // Check if the god mode flag (bit 0x8000) is already set at offset +0xC88
  if ((*(uint *)(thisPtr + 0xC88) | 0x8000) != *(uint *)(thisPtr + 0xC88)) {
    // Call a virtual function at vtable offset 0x28 (likely a notification/event handler)
    // with parameter 0x10 (probably a flag or event ID)
    (**(code **)(*(int *)(thisPtr + 0x58) + 0x28))(0x10);
    // Set the god mode flag at offset +0xC88
    *(uint *)(thisPtr + 0xC88) = *(uint *)(thisPtr + 0xC88) | 0x8000;
  }
}