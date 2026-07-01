// FUNC_NAME: SystemDisplay::setResolutionFromSystem
void __thiscall SystemDisplay::setResolutionFromSystem(SystemDisplay* this)
{
    // +0x8: width (float), +0xC: height (float)
    int displayModeIndex = GetCurrentDisplayModeIndex();  // returns mode index or handle
    DisplayModeInfo* modeInfo = GetDisplayModeInfo(displayModeIndex);
    // modeInfo has uint16 at +0x2 (width) and +0x4 (height)
    this->width = (float)modeInfo->width;
    this->height = (float)modeInfo->height;
}