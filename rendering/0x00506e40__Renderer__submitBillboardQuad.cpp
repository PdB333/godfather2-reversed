// FUNC_NAME: Renderer::submitBillboardQuad
void submitBillboardQuad(float centerX, float centerY, float size, float scaleX, float scaleY) 
{
  float fVar1 = DAT_00e2b04c; // +0x? Viewport height or scale
  float fVar2 = DAT_00e2b1a4; // +0x? Viewport width or offset
  float fVar3 = DAT_01218e48; // +0x? Texture scale Y
  float fVar4 = DAT_01218e44; // +0x? Texture scale X
  float fVar5 = DAT_00e2cd54; // +0x? Z scaling factor

  // Push graphics state (likely matrix/transform)
  FUN_00b99fcb();
  FUN_00b99e20();

  float* vertexBuffer = (float*)FUN_0060cd00(5, 4, 0, 1, 0); // allocate 4 vertices, each 4 floats (x,y,z,w?)
  if (vertexBuffer != nullptr) {
    // Generate 4 corners of a billboard quad (rotated 2D rectangle)
    for (int i = 0; i < 4; i++) {
      float signX = (float)(int)(((i & 1) * 2) - 1);  // ±1 for corners
      float signY = (float)(int)((i & 2) - 1);         // ±1 for corners

      // Compute local offset: rotate by 90° increments using signX/signY
      float dx = signX * size * scaleX - signY * size * scaleY;
      float dy = signY * size * scaleY + signX * size * scaleX;

      // World-space corner position with center offset
      float worldX = dx + centerX;
      float worldY = dy + centerY;

      // Project to screen space (orthographic or billboard?)
      vertexBuffer[0] = (worldX * DAT_01218e44 * fVar1) - fVar2; // screen X
      vertexBuffer[1] = fVar2 - (worldY * fVar3 * fVar1);       // screen Y (inverted)
      vertexBuffer[2] = (signX + fVar2) * DAT_00e2cd54;          // depth/UV? 
      vertexBuffer[3] = (signY + fVar2) * DAT_00e2cd54;          // depth/UV?

      vertexBuffer += 4;
    }
    FUN_0060cde0(); // submit vertex buffer to renderer
  }
}