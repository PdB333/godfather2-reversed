// FUNC_NAME: ObjectDataLoader::loadFromStream
void __thiscall ObjectDataLoader::loadFromStream(int thisPtr, undefined4 stream)
{
  char loadComplete;
  undefined4 subCode;
  int subObject;
  undefined4 *dataArray;
  
  FUN_0046c710(stream);  // streamBeginRead
  FUN_0043aff0(stream, 0xc825af20); // streamCheckMagic (likely version/type tag)
  
  loadComplete = FUN_0043b120(); // streamIsEmpty
  while (loadComplete == '\0') {
    FUN_0043b210(); // streamReadNode (descend into child)
    subCode = FUN_0043ab70(); // streamGetNodeType
    
    switch(subCode) {
    case 0: // string property
      FUN_0043b210(); // streamReadNode
      subCode = FUN_0043ab90(); // streamGetNodeValue
      FUN_004089b0(thisPtr + 0x58, subCode); // setStringProperty (offset +0x58)
      break;
      
    case 1: // another string property
      FUN_0043b210();
      subCode = FUN_0043ab90();
      FUN_004089b0(thisPtr + 0x60, subCode); // setStringProperty (offset +0x60)
      break;
      
    case 2: // integer property
      FUN_0043b210();
      subCode = FUN_0043ab90(); // streamGetIntValue
      FUN_00408980(thisPtr + 0x68, subCode); // setIntProperty (offset +0x68)
      break;
      
    case 3: // boolean flag
      subObject = FUN_0043b210(); // streamReadNode
      if (*(char *)(subObject + 8) != '\0') {
        *(uint *)(thisPtr + 0x94) = *(uint *)(thisPtr + 0x94) | 1; // set bit flag at +0x94
        FUN_00408680(&DAT_0120e93c); // debugLogMessage
      }
      break;
      
    case 4: // float property with scaling
      subObject = FUN_0043b210();
      *(float *)(thisPtr + 0x70) = *(float *)(subObject + 8) * DAT_00d5ef84; // scaled float at +0x70
      break;
      
    case 5: // direct float property
      subObject = FUN_0043b210();
      *(undefined4 *)(thisPtr + 0x74) = *(undefined4 *)(subObject + 8); // float at +0x74
      break;
      
    case 6: // vector/quaternion property (4 floats)
      FUN_0043b210();
      dataArray = (undefined4 *)FUN_0043abc0(); // streamGetArrayData
      *(undefined4 *)(thisPtr + 0x78) = *dataArray;
      *(undefined4 *)(thisPtr + 0x7c) = dataArray[1];
      *(undefined4 *)(thisPtr + 0x80) = dataArray[2];
      *(undefined4 *)(thisPtr + 0x84) = dataArray[3];
      // Store 4 floats at +0x78, +0x7C, +0x80, +0x84
    }
    
    FUN_0043b1a0(); // streamPopNode
    loadComplete = FUN_0043b120(); // streamIsEmpty
  }
  
  return;
}