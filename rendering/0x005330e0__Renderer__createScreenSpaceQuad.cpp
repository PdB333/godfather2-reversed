// FUNC_NAME: Renderer::createScreenSpaceQuad
void Renderer::createScreenSpaceQuad(float x, float y, float width, float height, float depth, char isFullscreen)
{
  float *vertexBuffer;
  float screenWidth;
  float screenHeight;
  
  if (isFullscreen == '\0') {
    vertexBuffer = (float *)allocateMemory(0xd,4,0,1,0);
    if (vertexBuffer != (float *)0x0) {
      screenHeight = DAT_00e44564 - x;
      vertexBuffer[3] = depth;
      vertexBuffer[7] = depth;
      *vertexBuffer = screenHeight;
      vertexBuffer[1] = screenHeight;
      vertexBuffer[2] = y;
      vertexBuffer[4] = x;
      vertexBuffer[5] = screenHeight;
      vertexBuffer[6] = y + width;
      vertexBuffer[8] = x;
      vertexBuffer[9] = x;
      vertexBuffer[10] = y + width;
      vertexBuffer[0xb] = depth + height;
      vertexBuffer[0xc] = screenHeight;
      vertexBuffer[0xd] = x;
      vertexBuffer[0xe] = y;
      vertexBuffer[0xf] = depth + height;
      submitVertexBuffer();
      return;
    }
  }
  else {
    vertexBuffer = (float *)allocateMemory(0xd,4,0,1,0);
    screenWidth = DAT_00e2b1a4;
    if (vertexBuffer != (float *)0x0) {
      screenHeight = DAT_00e44564 - x;
      vertexBuffer[3] = depth;
      vertexBuffer[9] = depth;
      *vertexBuffer = screenHeight;
      vertexBuffer[1] = screenHeight;
      vertexBuffer[2] = y;
      vertexBuffer[4] = 0.0;
      vertexBuffer[5] = 0.0;
      vertexBuffer[6] = x;
      vertexBuffer[7] = screenHeight;
      vertexBuffer[8] = y + width;
      vertexBuffer[10] = screenWidth;
      vertexBuffer[0xb] = 0.0;
      vertexBuffer[0xc] = x;
      vertexBuffer[0xd] = x;
      vertexBuffer[0xe] = y + width;
      vertexBuffer[0xf] = depth + height;
      vertexBuffer[0x10] = screenWidth;
      vertexBuffer[0x11] = screenWidth;
      vertexBuffer[0x12] = screenHeight;
      vertexBuffer[0x13] = x;
      vertexBuffer[0x14] = y;
      vertexBuffer[0x15] = depth + height;
      vertexBuffer[0x16] = 0.0;
      vertexBuffer[0x17] = screenWidth;
      submitVertexBuffer();
      return;
    }
  }
  return;
}