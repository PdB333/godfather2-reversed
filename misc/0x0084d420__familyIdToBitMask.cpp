// FUNC_NAME: familyIdToBitMask
// Converts a family ID (1-10) to a bitmask for bitfield operations.
// Mapping: ID 1->0x01, 2->0x02, 3->0x04, 4->0x10, 5/6/7->0x08, 8->0x40, 9->0x80, 10->0x100, others 0.
unsigned int familyIdToBitMask(int familyId)
{
    switch(familyId)
    {
    case 1:  return 0x1;
    case 2:  return 0x2;
    case 3:  return 0x4;
    case 4:  return 0x10;
    case 5:
    case 6:
    case 7:  return 0x8;
    case 8:  return 0x40;
    case 9:  return 0x80;
    case 10: return 0x100;
    default: return 0;
    }
}