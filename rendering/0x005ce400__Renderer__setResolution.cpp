// FUNC_NAME: Renderer::setResolution
void __fastcall Renderer::setResolution(int param_1, int param_2, int param_3, int param_4)
{
  // Check if resolution actually changed (param_1=width, param_2=height, param_4=bitDepth?)
  if (((param_4 != DAT_012056b4) || (param_2 != DAT_012056b8)) || (param_1 != DAT_00f17624)) {
    // Compute aspect ratio based on some global value (likely screen width / height)
    DAT_01222214 = DAT_00e2b1a4 / (float)param_4;  // +0x14: aspect ratio X?
    DAT_012056b4 = param_4;  // Store new bit depth
    DAT_01222218 = DAT_00e2b1a4 / (float)param_2;  // +0x18: aspect ratio Y?
    DAT_00f17624 = param_1;  // Store new width
    DAT_012056b8 = param_2;  // Store new height
    
    // Call to set up the new resolution (likely device reset)
    FUN_005db5c0(param_1);
    
    // If the renderer has a device context (param_3 + 0x18 != 0)
    if (*(int *)(param_3 + 0x18) != 0) {
      // Reset some state (likely clear render targets)
      FUN_005d0b90();
      *(undefined4 *)(param_3 + 0x30) = 0;  // +0x30: some flag
      return;
    }
    
    // If no device context, reset stored values
    DAT_012056b4 = 0;
    DAT_012056b8 = 0;
  }
  return;
}