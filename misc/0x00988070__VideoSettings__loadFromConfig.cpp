// FUNC_NAME: VideoSettings::loadFromConfig
void __fastcall VideoSettings::loadFromConfig(VideoSettings* this)
{
  int width;
  int height;
  int hz;

  sendCloseSelectionEvent("CloseSelection", 0, nullptr, 0);
  resetGamma();
  clearVideoMode();
  setVSync(0, 1);
  width = configGetInt("Window.Width", 0x400);
  this->mWidth = width;               // +0x114
  height = configGetInt("Window.Height", 0x300);
  this->mHeight = height;             // +0x110
  hz = configGetInt("Window.Hz", 0x3c);
  this->mRefreshRate = hz;            // +0x118
  applyVideoSettings();
  if (this->mIsFullscreen != '\0') {  // +0x10d
    toggleFullscreen();
  }
  this->mResolutionsListLoaded = 0;   // +0x10e
  return;
}