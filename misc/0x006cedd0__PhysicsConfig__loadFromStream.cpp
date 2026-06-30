// FUNC_NAME: PhysicsConfig::loadFromStream
void PhysicsConfig::loadFromStream(void *stream)
{
  float fVar1;
  char isDone;
  int caseId;
  int value;
  void *dataPtr;
  char tempBuffer[12];
  float x, y, z, w; // from first chunk
  float temp;

  // Begin reading chunk with ID 0xb390b11a (first block)
  beginRead(stream);
  readChunkHeader(stream, 0xb390b11a);
  readVersion(1);
  isDone = isChunkFinished(stream);
  if (isDone == '\0') {
    // Read string/identifier into tempBuffer
    readData(stream, tempBuffer); // reads some data (maybe a length-prefixed string)
    readString(stream, tempBuffer); // reads actual string? or another buffer?
    // Parse the string into three floats (e.g., for position or rotation)
    parseStringToFloats(tempBuffer, &x, &y, &z);
    this->field80 = x;
    this->field84 = y;
    this->field88 = z;
    this->field8c = _zeroConstant;  // another value, maybe w
    this->field60 = _zeroConstant;  // initialize remaining fields
    this->field64 = _zeroConstant;
    this->field68 = _zeroConstant;
    this->field6c = _zeroConstant;
  }

  // Begin second chunk
  readChunkHeader(stream, 0xac728727);
  isDone = isChunkFinished(stream);
  while (isDone == '\0') {
    readData(stream); // skip maybe some header?
    caseId = readCaseID(stream);
    switch(caseId) {
    case 0:
      dataPtr = readNextData(stream);
      this->field90 = *(float *)((char *)dataPtr + 8) * _scaleFactor;
      break;
    case 1:
      dataPtr = readNextData(stream);
      this->fieldA0 = *(float *)((char *)dataPtr + 8) * _scaleFactor;
      break;
    case 2:
      dataPtr = readNextData(stream);
      this->fieldA4 = *(float *)((char *)dataPtr + 8) * _scaleFactor;
      break;
    case 3:
      dataPtr = readNextData(stream);
      this->fieldB0 = *(float *)((char *)dataPtr + 8) * _scaleFactor;
      break;
    case 4:
      readNextData(stream);
      value = readInteger(stream);
      setBoolField(&this->fieldB4, value);
      break;
    case 5:
      readNextData(stream);
      value = readInteger(stream);
      setBoolField(&this->fieldBC, value);
      break;
    case 6:
      dataPtr = readNextData(stream);
      this->fieldA8 = *(float *)((char *)dataPtr + 8) * _scaleFactor;
      break;
    case 7:
      dataPtr = readNextData(stream);
      this->fieldAC = *(float *)((char *)dataPtr + 8) * _scaleFactor;
      break;
    }
    advanceOrPopChunk(stream);
    isDone = isChunkFinished(stream);
  }

  // Clamp or swap if needed based on an epsilon?
  temp = this->fieldA8;
  if (_epsilon1 < (float)((uint)temp & _mask) || _epsilon1 < (float)(*(uint *)&this->fieldAC & _mask)) {
    this->fieldA8 = this->field84 - this->fieldAC;
    this->fieldAC = this->field84 - temp;
  }
}

/*
 Notes:
 - _zeroConstant: likely 0.0f (value from DAT_00d5780c)
 - _scaleFactor: global DAT_00e445c8 (e.g., 0.01)
 - _epsilon1: DAT_00e44598 (a threshold)
 - _mask: DAT_00e44680 (bitmask to extract something)
 - The helper functions correspond to EARS binary stream reading:
   beginRead, readChunkHeader, readVersion, isChunkFinished, readData/readNextData,
   readCaseID, readInteger, setBoolField, advanceOrPopChunk, parseStringToFloats.
*/