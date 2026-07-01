// FUNC_NAME: EffectResourceDefinition::loadFromStream

void __thiscall EffectResourceDefinition::loadFromStream(EffectResourceDefinition* thisx, StreamReader* stream) {
  char isNotEnd;
  int tokenType;
  int* tokenData;
  const char* strPtr;
  int resIndex;
  float* floatArray;

  streamBeginRead(stream);
  streamReadMagic(stream, 0x324b32cb);  // Magic number for effect resource

  isNotEnd = streamIsAtEnd(stream);
  while (isNotEnd == '\0') {
    streamReadNextToken(stream);         // Prepare for next token
    tokenType = streamGetTokenType(stream);

    switch(tokenType) {
    case 0:   // String token - set texture name
      streamReadNextToken(stream);
      strPtr = streamReadString(stream);
      if (strPtr == (const char*)0x0) {
        strPtr = &DAT_0120546e; // Default empty string
      }
      thisx->textureNameIndex = streamLookupString(strPtr); // +0x50: texture resource index
      break;

    case 1:   // Int token - integer value 1
      tokenData = streamReadTokenData(stream);
      thisx->field_a0 = *(int*)(tokenData + 8);   // +0xa0
      break;

    case 2:   // Int token - integer value 2
      tokenData = streamReadTokenData(stream);
      thisx->field_a4 = *(int*)(tokenData + 8);   // +0xa4
      break;

    case 3:   // Int token - integer value 3
      tokenData = streamReadTokenData(stream);
      thisx->field_a8 = *(int*)(tokenData + 8);   // +0xa8
      break;

    case 4:   // Int token - integer value 4
      tokenData = streamReadTokenData(stream);
      thisx->field_ac = *(int*)(tokenData + 8);   // +0xac
      break;

    case 5:   // Int token - integer value 5
      tokenData = streamReadTokenData(stream);
      thisx->field_54 = *(int*)(tokenData + 8);   // +0x54
      break;

    case 6:   // Float array token - 4 floats
      streamReadNextToken(stream);
      floatArray = (float*)streamRead4Floats(stream);
      thisx->color[0] = floatArray[0];        // +0x84
      thisx->color[1] = floatArray[1];        // +0x88
      thisx->color[2] = floatArray[2];        // +0x8c
      thisx->color[3] = floatArray[3];        // +0x90
      break;

    case 8:   // String token - set name
      streamReadNextToken(stream);
      streamCopyString(thisx + 0x7c, stream); // +0x7c: name buffer
      break;

    case 9:   // Int token - integer value 6
      tokenData = streamReadTokenData(stream);
      thisx->field_b0 = *(int*)(tokenData + 8);   // +0xb0
      break;

    case 10:  // Int token - integer value 7
      tokenData = streamReadTokenData(stream);
      thisx->field_b4 = *(int*)(tokenData + 8);   // +0xb4
      break;
    }

    streamAdvanceToNextToken(stream);
    isNotEnd = streamIsAtEnd(stream);
  }

  finishLoading(thisx);
  return;
}