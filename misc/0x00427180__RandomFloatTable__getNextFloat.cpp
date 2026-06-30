// FUNC_NAME: RandomFloatTable::getNextFloat
float RandomFloatTable::getNextFloat()
{
    uint32_t index = kTableMask & sCurrentIndex;  // DAT_010c2678: mask for table size (power of 2 minus 1)
    sCurrentIndex++;                              // DAT_012054b4: current index into shuffled table
    return sFloatTable[index];                    // DAT_010c2680: pre-generated table of random floats
}