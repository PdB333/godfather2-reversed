// Xbox PDB: EARS::Modules::InGameVideoPlayer::StartVideo
// FUNC_NAME: FlashClipManager::duplicateClip

void FlashClipManager::duplicateClip(void)
{
  int charIndex;
  float *pXPos;
  bool isSpecialX;
  int tempInt;
  int basePath;
  float varX [2];
  char varName [16];
  char targetPath [64];
  char clipPath [68];
  
  // Increment duplicate counter
  *(int *)(this + 0x108) = *(int *)(this + 0x108) + 1;
  
  // Get character index in string buffer based on current counter
  charIndex = FUN_005cde50(*(undefined4 *)(this + 0x108));
  
  // Skip spaces in the source string (at +0x44) until end of string
  if (*(int *)(this + 0x108) != *(int *)(this + 0x104)) {
    while (*(char *)(this + 0x44 + charIndex) == ' ') {
      *(int *)(this + 0x108) = *(int *)(this + 0x108) + 1;
      charIndex = FUN_005cde50(*(undefined4 *)(this + 0x108));
      if (*(int *)(this + 0x108) == *(int *)(this + 0x104)) {
        return;
      }
    }
    
    // Build target path: base path + subpath at +0x84
    basePath = this + 0x84;  // +0x84: subpath string (e.g., "myClip")
    __snprintf(targetPath, 0x40, "%s/%s", this + 4, basePath);
    
    // Build new instance name: subpath + current counter
    __snprintf(clipPath, 0x40, "%s%d", basePath, *(undefined4 *)(this + 0x108));
    
    // Build depth string: 16000 + current counter
    __snprintf(varName, 0x10, "%d", *(int *)(this + 0x108) + 16000);
    
    // Call Flash's duplicateMovieClip(target, depth, newName)
    // Parameters: this, "duplicateMovieClip", 0, targetPath, 2, clipPath, varName
    // The '0' and '2' likely indicate parameter types (e.g., string, number)
    FUN_005a04a0("duplicateMovieClip", 0, targetPath, 2, clipPath, varName);
    
    // Set flags: clear bits 1 and 2? Actually: &6 (bits 1 and 2 cleared) then set bit 4
    *(uint *)(this + 0x10c) = *(uint *)(this + 0x10c) & 6 | 0x10;
    
    // Build full path for retrieving x position variable
    __snprintf(targetPath, 0x40, "%s/%s/%s", this + 4, basePath, this + 0xc4);
    
    // Copy source string (+0x44) to local buffer, then set character at current index to 'H'
    // This creates a variable name like "somePrefixH" (probably "x" property accessor?)
    _strncpy(clipPath, (char *)(this + 0x44), 0x40);
    clipPath[charIndex] = 'H';
    clipPath[charIndex + 1] = '\0';
    
    // Read a Flash variable value (type 1 = number?) into tempInt and varX
    FUN_005cff00(1, clipPath, &tempInt, varX);
    
    // Store current x offset from +0x110
    varX[0] = *(float *)(this + 0x110);
    pXPos = (float *)(this + 0x110);
    
    // Handle special constants: if x offset is a "special" value (NaN or infinity?)
    // DAT_00e4481c and DAT_00e44818 are global floats likely representing 0.0 / INF / NaN
    if ((varX[0] == DAT_00e4481c) || (varX[0] == DAT_00e44818)) {
      isSpecialX = FUN_005cffe0(this + 0x44, pXPos);
      if (isSpecialX == '\0') {
        *pXPos = 0.0;
      }
      else {
        // Scale if matching first constant
        if (varX[0] == DAT_00e4481c) {
          *pXPos = *pXPos * DAT_00e2cd54;
        }
        // Subtract the integer part read from Flash variable
        *pXPos = *pXPos - (float)tempInt;
      }
    }
    
    // Set the x position of the duplicated clip using Flash property assignment
    __snprintf(targetPath, 0x40, "%s/%s%d._x", this + 4, basePath, *(undefined4 *)(this + 0x108));
    FUN_0059ecb0(targetPath, (float)tempInt + *pXPos);
  }
  return;
}