// FUNC_NAME: Entity::resetEntity
undefined4 * __fastcall Entity::resetEntity(undefined4 *this)
// Address: 0x00604be0
// Resets the entity's state: sets a flag/parent to zero (first 4 bytes)
// and clears the entire remaining data block (0x1010 bytes = 4112 bytes)
{
  *this = 0;
  _memset(this + 1, 0, 0x1010);
  return this;
}