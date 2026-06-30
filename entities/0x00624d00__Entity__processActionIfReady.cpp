// FUNC_NAME: Entity::processActionIfReady
// Function address: 0x00624d00
// Role: Checks if action processing is not suspended and that an action pointer exists, then delegates processing to another function. Returns 1 if processed, 0 if not.

byte __fastcall Entity::processActionIfReady(Entity* this)
{
  // Flags at +0x14: bit 1 (0x02) = suspended/processing disabled?
  // Pointer at +0x18: action data block (could be a behavior, animation, etc.)
  byte result = 0;

  // Only process if not suspended (bit 1 clear) and there is a valid action pointer
  if (((this->flags & 0x02) == 0) && (this->actionPointer != 0)) {
    // Call the actual processing routine (address 0x00624f30)
    processAction(this);
    result = 1;
  }
  return result;
}