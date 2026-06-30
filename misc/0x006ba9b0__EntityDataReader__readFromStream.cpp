// FUNC_NAME: EntityDataReader::readFromStream
// Function address: 0x006ba9b0
// Role: Deserializes property flags and an array of key-value pairs from a binary stream.
// Likely reads component/entity configuration data.

void __thiscall EntityDataReader::readFromStream(void *pStream)
{
  uint tag;
  uint idx;
  uint *pArrayElement;
  uint temp;
  
  // Initialize stream/reader context
  Reader::beginRead(pStream);
  // Validate magic/signature (0xb965931c likely a FourCC or version hash)
  Reader::checkSignature(pStream, 0xb965931c);
  
  // Loop until end of data
  while (!Reader::isEnd(pStream))
  {
    // Advance to next element? Actually pattern: first advance then get tag? 
    // The decompiled shows: FUN_0043b210() (getCurrentElement) then FUN_0043ab70() (getTag).
    // But the loop structure: while not end, get tag, switch, then advance.
    // The calls to FUN_0043b210 inside cases get the current element pointer.
    // The overall flow: after reading tag, we get the element and process.
    // So we need to restructure: We have getCurrentElement returning pointer to the current element block.
    // Better to read tag first, then fetch element data.
    
    // Actually from code: 
    // cVar2 = FUN_0043b120(); while (cVar2 == '\0') { FUN_0043b210(); uVar3 = FUN_0043ab70(); ... FUN_0043b1a0(); cVar2 = ... }
    // The initial FUN_0043b210() before the switch is called but not used? 
    // It might be an "advance to next" or "get current" that is discarded.
    // But for correctness, we follow the decompiled order: call getCurrentElement first (result unused?), then getTag.
    // I'll model it as: advance to next element? Actually the call to FUN_0043b210 is inside the loop before getTag; it returns a pointer that is used only in switch cases.
    // So it's "getCurrentElement". We need to store it for switch.
    void* pElement = Reader::getCurrentElement(pStream);
    tag = Reader::getTag(pStream);
    
    switch(tag) {
      // Bit 0 of flags field (offset 0x84) - sets/clears based on element's data at +8
      case 0:
        if (*(int*)((int)pElement + 8) == 0) {
          *(uint*)((int)this + 0x84) &= 0xfffffffe;  // clear bit 0
        } else {
          *(uint*)((int)this + 0x84) |= 1;            // set bit 0
        }
        break;
      
      // Bit 1 of flags field
      case 1:
        if (*(int*)((int)pElement + 8) == 0) {
          *(uint*)((int)this + 0x84) &= 0xfffffffd;  // clear bit 1
        } else {
          *(uint*)((int)this + 0x84) |= 2;            // set bit 1
        }
        break;
      
      // Bit 2 of flags field
      case 2:
        if (*(int*)((int)pElement + 8) == 0) {
          *(uint*)((int)this + 0x84) &= 0xfffffffb;  // clear bit 2
        } else {
          *(uint*)((int)this + 0x84) |= 4;            // set bit 2
        }
        break;
      
      // OR entire value from element's data into flags
      case 3:
        *(uint*)((int)this + 0x84) |= *(uint*)((int)pElement + 8);
        break;
      
      // Tags >3: handle array elements at offset 0xb8 (10 elements, 12 bytes each)
      default:
        if (tag > 3) {
          idx = (tag - 4) >> 1;
          if (idx < 10) {
            pArrayElement = (uint*)((int)this + 0xb8 + idx * 0xc);
            if ((tag & 1) == 0) {
              // Tag even: copy uint from element's data to array element's first field (offset 0)
              *pArrayElement = *(uint*)((int)pElement + 8);
            } else {
              // Tag odd: copy string from reader to array element's second field (offset 4)
              Reader::getCurrentElement(pStream);  // This seems redundant? But per decompiled it's called again.
              uint strHandle = Reader::getString(pStream);
              StringUtils::assign((char*)(pArrayElement + 1), strHandle);  // +0x4 from array base
            }
          }
        }
        break;
    }
    
    // Advance to next element in stream
    Reader::advance(pStream);
  }
  
  return;
}