// FUNC_NAME: deserializeFieldsFromStream
// Function at 0x0088e040: Reads a sequence of typed elements from a binary stream and sets fields at offsets +0x50 and +0x58 of the object.
void __thiscall deserializeFieldsFromStream(void *this, void *stream)
{
  char isEnd;
  int elementType;
  unsigned int elementValue;
  void *rawData;

  // Initialize stream reading (e.g., push buffer or validate)
  streamBeginRead(stream);
  // Set a key/magic number for stream integrity (0x38e83f04)
  streamSetKey(stream, 0x38e83f04);

  // Process elements until the stream ends
  isEnd = streamIsEnd(stream);
  while (isEnd == 0) {
    streamReadElement(stream);          // Advance to next element header
    elementType = streamGetType(stream);

    if (elementType == 0) {
      // Type 0: read a value and store at this+0x50
      streamReadElement(stream);        // Move to value payload
      elementValue = streamGetValue(stream);
      // Direct assignment (original called a setter-like function)
      *(unsigned int *)((char *)this + 0x50) = elementValue;
    }
    else if (elementType == 1) {
      // Type 1: read a pointer to another structure, copy field at offset 8 into this+0x58
      rawData = (void *)streamReadElement(stream); // Returns pointer to data
      *(unsigned int *)((char *)this + 0x58) = *(unsigned int *)((char *)rawData + 8);
    }
    streamEndElement(stream);           // End current element
    isEnd = streamIsEnd(stream);        // Check for more elements
  }
}