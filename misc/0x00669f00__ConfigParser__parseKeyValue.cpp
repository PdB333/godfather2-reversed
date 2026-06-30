// FUNC_NAME: ConfigParser::parseKeyValue
int ConfigParser::parseKeyValue(char *inputStr, uint maxLen)
{
  char *pcVar1;
  int iVar2;
  char cVar3;
  int *this; // unaff_EDI - points to config parser state struct
  int iVar4;
  
  iVar2 = maxLen;
  if (0x40 < (int)maxLen) {
    return -3; // Error: key too long
  }
  
  // Check for negative sign prefix
  cVar3 = *inputStr;
  if (cVar3 == '-') {
    inputStr = inputStr + 1;
  }
  
  // Store sign flag (0 = positive, 1 = negative)
  maxLen = (uint)(cVar3 == '-');
  
  // Initialize state: clear current value and array
  this[2] = 0; // +0x08: currentValue
  *this = 0;   // +0x00: valueCount
  _memset((void *)this[3], 0, this[1] * 4); // +0x0C: valueArray, +0x04: arraySize
  
  cVar3 = *inputStr;
  while (cVar3 != '\0') {
    // Convert to uppercase if within base64 range
    if (iVar2 < 0x24) {
      iVar4 = _toupper((int)cVar3);
      cVar3 = (char)iVar4;
    }
    
    // Find character in base64 alphabet
    iVar4 = 0;
    do {
      if (cVar3 == "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/"[iVar4]) break;
      if (cVar3 == "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/"[iVar4 + 1]) {
        iVar4 = iVar4 + 1;
        break;
      }
      if (cVar3 == "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/"[iVar4 + 2]) {
        iVar4 = iVar4 + 2;
        break;
      }
      if (cVar3 == "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/"[iVar4 + 3]) {
        iVar4 = iVar4 + 3;
        break;
      }
      iVar4 = iVar4 + 4;
    } while (iVar4 < 0x40);
    
    if (iVar2 <= iVar4) break; // Exceeded max length
    
    // Process the character through two helper functions
    iVar4 = FUN_00668f50(); // Likely processCharacter or decodeValue
    if (iVar4 != 0) {
      return iVar4;
    }
    iVar4 = FUN_00665820(); // Likely accumulateValue or storeResult
    if (iVar4 != 0) {
      return iVar4;
    }
    
    pcVar1 = inputStr + 1;
    inputStr = inputStr + 1;
    cVar3 = *pcVar1;
  }
  
  // If we have values, store the sign
  if (*this != 0) {
    this[2] = maxLen; // +0x08: store sign flag
  }
  
  return 0; // Success
}