// FUNC_NAME: PackId
// 0x00540c60 - Packs three bit fields into a 32-bit identifier:
//   lowField (5 bits) -> bits 0-4
//   midField (5 bits) -> bits 5-9
//   highField (12 bits) -> bits 16-27 (bits 10-15 remain zero)
// Used for compact object/network identifiers throughout the game.
uint32_t PackId(uint32_t lowField, uint32_t midField, uint32_t highField)
{
    return ((highField & 0xFFF) << 11 | (midField & 0x1F)) << 5 | (lowField & 0x1F);
}