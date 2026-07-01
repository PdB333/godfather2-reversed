// FUNC_NAME: Renderer::setVSync
void __thiscall Renderer::setVSync(int this, int enable, char applyImmediately)
{
  *(int *)(this + 0x44) = enable; // +0x44: m_vsyncEnabled
  if (applyImmediately != '\0') {
    FUN_0060e680(enable != 0); // likely D3DDevice::SetSwapInterval or similar
  }
  FUN_0069bf90("Window.VSync", enable); // store setting in config system
}