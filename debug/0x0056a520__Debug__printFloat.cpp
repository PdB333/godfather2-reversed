// FUNC_NAME: Debug::printFloat
void Debug::printFloat(float value)
{
  char buffer[15]; // +0x0
  char nullTerminator; // +0xF

  __snprintf(buffer, 0x10, "%f", (double)value);
  nullTerminator = 0;
  // Call to debug output function at vtable offset 0x14 (likely Debug::output or similar)
  // Parameters: 0x48445752 = "DW R" (maybe a debug channel tag), 0x48445350 = "DSP " (maybe "Debug String Print"), buffer
  (**(code **)(*DAT_012234e0 + 0x14))(0x48445752, 0x48445350, buffer);
}