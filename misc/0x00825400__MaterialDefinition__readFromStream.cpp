// FUNC_NAME: MaterialDefinition::readFromStream
void __thiscall MaterialDefinition::readFromStream(int thisPtr, uint streamHandle)
{
  float colorScale;
  uint tempValue;
  char readerHasMoreData;
  int tokenType;
  int dataPtr;
  float *colorDest;
  uint *valueRef;

  tempValue = streamHandle;
  materialFileOpen(streamHandle);                                   // init stream
  materialFileInitReader(tempValue, 0xd904c420);                    // magic number for material format
  readerHasMoreData = readerIsAtEnd();
  while (readerHasMoreData == '\0') {
    readerAdvanceToken();                                           // skip to next? Actually this seems called later, but here it's called inside loop
    tokenType = readerGetTokenType();
    switch(tokenType) {
    case 0:                                                         // diffuse color (RGB)
      valueRef = &tempValue;
      readerGetData(valueRef);                                      // read 32-bit packed color into tempValue
      readerProcessValue(valueRef);                                 // convert endianness? or decode
      colorScale = g_colorScaleFactor;                              // DAT_00e44640 = 1/255.0f
      *(float *)(thisPtr + 0x60) = (float)(tempValue & 0xff) * g_colorScaleFactor;       // R
      *(float *)(thisPtr + 0x64) = (float)((tempValue >> 8) & 0xff) * colorScale;        // G
      *(float *)(thisPtr + 0x68) = (float)((tempValue >> 16) & 0xff) * colorScale;       // B
      break;
    case 1:                                                         // diffuse texture reference
      dataPtr = readerGetData();
      *(int *)(thisPtr + 0x6c) = *(int *)(dataPtr + 8);            // get offset 8 from object (e.g., texture handle)
      break;
    case 2:                                                         // specular color (RGB)
      valueRef = &tempValue;
      readerGetData(valueRef);
      readerProcessValue(valueRef);
      colorScale = g_colorScaleFactor;
      *(float *)(thisPtr + 0x70) = (float)(tempValue & 0xff) * g_colorScaleFactor;       // R
      *(float *)(thisPtr + 0x74) = (float)((tempValue >> 8) & 0xff) * colorScale;        // G
      *(float *)(thisPtr + 0x78) = (float)((tempValue >> 16) & 0xff) * colorScale;       // B
      break;
    case 3:                                                         // specular texture reference
      dataPtr = readerGetData();
      *(int *)(thisPtr + 0x7c) = *(int *)(dataPtr + 8);
      break;
    case 4:                                                         // additional texture slot 0
      dataPtr = readerGetData();
      *(int *)(thisPtr + 0x50) = *(int *)(dataPtr + 8);
      break;
    case 5:                                                         // additional texture slot 1
      dataPtr = readerGetData();
      *(int *)(thisPtr + 0x54) = *(int *)(dataPtr + 8);
      break;
    case 6:                                                         // additional texture slot 2
      dataPtr = readerGetData();
      *(int *)(thisPtr + 0x58) = *(int *)(dataPtr + 8);
      break;
    case 7:                                                         // additional texture slot 3
      dataPtr = readerGetData();
      *(int *)(thisPtr + 0x5c) = *(int *)(dataPtr + 8);
      break;
    }
    readerFinalizeToken();                                          // prepare for next token
    readerHasMoreData = readerIsAtEnd();
  }
  return;
}