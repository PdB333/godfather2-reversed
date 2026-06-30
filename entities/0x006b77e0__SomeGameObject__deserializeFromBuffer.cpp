// FUNC_NAME: SomeGameObject::deserializeFromBuffer
void __thiscall SomeGameObject::deserializeFromBuffer(int this, uint stream) {
  char loopCondition;
  int index;
  uint *bufferPtr;
  // Local buffer for unpacking a sub-struct (0x3C bytes)
  uint localStruct[15]; // Actually larger, but we only define up to needed
  // Use an array to avoid many local variables
  uint localBuffer[16]; // Starting at local_120

  beginRead(stream);
  readTag(stream, 0xb390b11a); // Sync tag A
  setReadFlag(1); // Set reading flag (maybe bit order)

  // Initialize localBuffer from buffer
  bufferPtr = getBufferPointer(localBuffer); // Gets pointer to start of buffer
  processBuffer(localBuffer); // Process header

  // Build the sub-struct from the buffer data
  localBuffer[0] = localBuffer[?]; // Actually copy from local_120 to local_160
  // Manually copy fields
  // The exact mapping: local_160 = local_120, etc.
  // We'll just assume a struct assignment
  // Actually, we'll define a struct to hold the data
  struct SubStruct {
    uint field_00;
    uint field_04;
    uint field_08;
    uint field_0C; // local_154 = 0
    uint field_10; // local_150
    uint field_14; // local_14c
    uint field_18; // local_148
    uint field_1C; // local_144 = 0
    uint field_20; // local_140
    uint field_24; // local_13c
    uint field_28; // local_138
    uint field_2C; // local_134 = 0
    uint field_30; // local_130
    uint field_34; // local_12c
    uint field_38; // local_128
    uint field_3C; // local_124 = g_constant
  } subStruct;

  // Fill from localBuffer (which is at local_120)
  subStruct.field_00 = localBuffer[0];  // local_120
  subStruct.field_04 = localBuffer[1];  // local_11c
  subStruct.field_08 = localBuffer[2];  // local_118
  subStruct.field_0C = 0;               // local_154
  subStruct.field_10 = localBuffer[3];  // local_110 (offset 0x10)
  subStruct.field_14 = localBuffer[4];  // local_10c
  subStruct.field_18 = localBuffer[5];  // local_108
  subStruct.field_1C = 0;               // local_144
  subStruct.field_20 = localBuffer[6];  // local_100
  subStruct.field_24 = localBuffer[7];  // local_fc
  subStruct.field_28 = localBuffer[8];  // local_f8
  subStruct.field_2C = 0;               // local_134
  subStruct.field_30 = localBuffer[9];  // local_f0
  subStruct.field_34 = localBuffer[10]; // local_ec
  subStruct.field_38 = localBuffer[11]; // local_e8
  subStruct.field_3C = g_constant;      // _DAT_00d5780c

  // Copy the sub-struct to the object at offset 0x60
  copySubStruct(&subStruct, this + 0x60);

  readTag(stream, 0x3782a961); // Sync tag B

  // Loop to read additional data
  loopCondition = isReadComplete();
  while (loopCondition == '\0') {
    getBufferPointer(); // Advance or refresh buffer pointer
    index = readIndex();
    if (index == 0) {
      bufferPtr = getBufferPointer();
      *(int *)(this + 0xa0) = *(int *)(bufferPtr + 8);
    } else if (index == 1) {
      bufferPtr = getBufferPointer();
      *(int *)(this + 0xa4) = *(int *)(bufferPtr + 8);
    }
    advanceRead();
    loopCondition = isReadComplete();
  }
}