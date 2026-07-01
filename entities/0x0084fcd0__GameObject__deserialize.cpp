// FUNC_NAME: GameObject::deserialize
void __thiscall GameObject::deserialize(void *stream)
{
  bool hasMore;
  int fieldType;
  int fieldData;
  int fieldPtr;

  // Initialize stream reading with magic number
  readStreamBegin(stream);
  readStreamMagic(stream, 0x6701e7a5);

  // Loop while there are field tokens remaining
  hasMore = hasMoreStreamData();
  while (!hasMore)
  {
    readNextFieldToken();           // advance to next field token
    fieldType = getCurrentFieldType();

    switch (fieldType)
    {
    case 0: // Type 0: set pointer at offset +0x50
      readNextFieldToken();         // read value token
      fieldData = readFieldValue();
      setPointerAtOffset(this + 0x50, fieldData);   // FUN_004089b0 – likely sets a pointer/string
      break;
    case 1: // Type 1: read and store (function call only)
      readNextFieldToken();
      fieldData = readFieldValue();
      processFieldValue(fieldData);                 // FUN_004d3d90 – stores in some global or other
      break;
    case 2: // Type 2: same as 1
      readNextFieldToken();
      fieldData = readFieldValue();
      processFieldValue(fieldData);
      break;
    case 3: // Type 3: set pointer at offset +0x58
      readNextFieldToken();
      fieldData = readFieldValue();
      setPointerAtOffset(this + 0x58, fieldData);   // FUN_00408980 – likely sets another pointer/string
      break;
    case 4: // Type 4: set integer at offset +0xa8
      fieldPtr = readNextFieldToken();               // returns pointer to token data
      *(int *)(this + 0xa8) = *(int *)(fieldPtr + 8); // read integer from token structure
      break;
    case 5: // Type 5: set flag bit 1 at +0x90
      fieldPtr = readNextFieldToken();
      if (*(int *)(fieldPtr + 8) == 0)
        *(unsigned int *)(this + 0x90) &= ~2;        // clear bit 1
      else
        *(unsigned int *)(this + 0x90) |= 2;         // set bit 1
      break;
    case 6: // Type 6: set flag bit 2 at +0x90
      fieldPtr = readNextFieldToken();
      if (*(int *)(fieldPtr + 8) == 0)
        *(unsigned int *)(this + 0x90) &= ~4;        // clear bit 2
      else
        *(unsigned int *)(this + 0x90) |= 4;         // set bit 2
      break;
    case 7: // Type 7: set flag bit 3 at +0x90
      fieldPtr = readNextFieldToken();
      if (*(int *)(fieldPtr + 8) == 0)
        *(unsigned int *)(this + 0x90) &= ~8;        // clear bit 3
      else
        *(unsigned int *)(this + 0x90) |= 8;         // set bit 3
      break;
    case 8: // Type 8: set integer at offset +0x94
      fieldPtr = readNextFieldToken();
      *(int *)(this + 0x94) = *(int *)(fieldPtr + 8);
      break;
    }

    readNextFieldEnd();              // advance past the field
    hasMore = hasMoreStreamData();   // check if more fields remain
  }
}