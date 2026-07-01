// FUNC_NAME: PropertyParser::parseProperties
void __thiscall PropertyParser::parseProperties(int thisPtr, undefined4 streamPtr)
{
  char hasMore;
  undefined4 typeCode;
  int valueNode;
  
  FUN_0046c710(streamPtr);                                              // initStream
  FUN_0043aff0(streamPtr, 0xe78a9a7e);                                  // setMagic
  hasMore = FUN_0043b120();                                             // hasMoreData
  while (hasMore == '\0') {
    FUN_0043b210();                                                     // advanceToNextKey
    typeCode = FUN_0043ab70();                                          // getKeyType
    switch(typeCode) {
    case 0:                                                             // int
      valueNode = FUN_0043b210();                                       // readValue
      *(undefined4 *)(thisPtr + 0x50) = *(undefined4 *)(valueNode + 8); // +0x50: someIntField
      break;
    case 1:                                                             // int
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x54) = *(undefined4 *)(valueNode + 8); // +0x54: anotherIntField
      break;
    case 2:                                                             // string
      FUN_0043b210();                                                   // discard key?
      typeCode = FUN_0043ab90();                                        // getStringValue
      FUN_004d3d90(typeCode);                                           // processString
      break;
    case 3:                                                             // int
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x68) = *(undefined4 *)(valueNode + 8); // +0x68
      break;
    case 4:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x6c) = *(undefined4 *)(valueNode + 8); // +0x6c
      break;
    case 5:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x70) = *(undefined4 *)(valueNode + 8); // +0x70
      break;
    case 6:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x74) = *(undefined4 *)(valueNode + 8); // +0x74
      break;
    case 7:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x98) = *(undefined4 *)(valueNode + 8); // +0x98
      break;
    case 8:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x9c) = *(undefined4 *)(valueNode + 8); // +0x9c
      break;
    case 9:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x78) = *(undefined4 *)(valueNode + 8); // +0x78
      break;
    case 10:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x80) = *(undefined4 *)(valueNode + 8); // +0x80
      break;
    case 0xb:
      valueNode = thisPtr + 0x88;
      FUN_0043b210(valueNode);                                          // read composite value into array
      FUN_0043ad80(valueNode);                                          // parseArray
      break;
    case 0xc:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x7c) = *(undefined4 *)(valueNode + 8); // +0x7c
      break;
    case 0xd:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x84) = *(undefined4 *)(valueNode + 8); // +0x84
      break;
    case 0xe:
      valueNode = thisPtr + 0x8c;
      FUN_0043b210(valueNode);
      FUN_0043ad80(valueNode);                                          // parseArray
      break;
    case 0xf:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x90) = *(undefined4 *)(valueNode + 8); // +0x90
      break;
    case 0x10:
      valueNode = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x94) = *(undefined4 *)(valueNode + 8); // +0x94
      break;
    }
    FUN_0043b1a0();                                                     // endKey
    hasMore = FUN_0043b120();                                           // checkMoreKeys
  }
  FUN_00815eb0(thisPtr);                                                // onParseComplete
  return;
}