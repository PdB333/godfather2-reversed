// FUNC_NAME: EntityData::loadFromStream
void __thiscall EntityData::loadFromStream(int this, undefined4 stream)
{
  char hasMore;
  int fieldType;
  int fieldData;

  // Initialize stream reader
  initStreamReader(stream);
  setStreamMode(stream, 0x484607f2);  // some mode constant

  hasMore = checkStreamEnd();
  while (hasMore == '\0') {
    advanceStream();
    fieldType = readFieldType();
    switch(fieldType) {
      case 0:
        advanceStream();
        fieldData = readFieldString();  // reads string identifier
        setStringField(this + 0x50, fieldData);  // +0x50: m_name or m_id
        break;
      case 1:
        fieldData = advanceStream();
        *(int *)(this + 0x58) = *(int *)(fieldData + 8);  // +0x58: m_field1
        break;
      case 2:
        fieldData = advanceStream();
        *(int *)(this + 0x5c) = *(int *)(fieldData + 8);  // +0x5c: m_field2
        break;
      case 3:
        fieldData = advanceStream();
        *(int *)(this + 0x6c) = *(int *)(fieldData + 8);  // +0x6c: m_field3
        break;
      case 4:
        fieldData = advanceStream();
        *(int *)(this + 0x60) = *(int *)(fieldData + 8);  // +0x60: m_field4
        break;
      case 5:
        fieldData = advanceStream();
        *(int *)(this + 100) = *(int *)(fieldData + 8);   // +0x64: m_field5
        break;
      case 6:
        fieldData = advanceStream();
        *(int *)(this + 0x68) = *(int *)(fieldData + 8);  // +0x68: m_field6
        break;
      case 7:
        fieldData = advanceStream();
        *(int *)(this + 0x70) = *(int *)(fieldData + 8);  // +0x70: m_field7
        break;
      case 8:
        fieldData = advanceStream();
        *(int *)(this + 0x74) = *(int *)(fieldData + 8);  // +0x74: m_field8
        break;
      case 9:
        fieldData = advanceStream();
        *(int *)(this + 0x78) = *(int *)(fieldData + 8);  // +0x78: m_field9
        break;
      case 10:
        fieldData = advanceStream();
        *(int *)(this + 0x7c) = *(int *)(fieldData + 8);  // +0x7c: m_field10
        break;
    }
    skipField();
    hasMore = checkStreamEnd();
  }
  return;
}