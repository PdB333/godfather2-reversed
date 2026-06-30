// FUNC_NAME: EnvironmentManager::setNightMode
// Address: 0x0049cf80
// This function updates the patch state for all environment objects (size 0xB0 each)
// based on a given boolean flag. It toggles between two visibility/patch modes:
// - isNight == false: set patch flag 0x400 (bit 10), clear 0x200 (bit 9)
// - isNight == true : set patch flag 0x200 (bit 9), clear 0x400 (bit 10)
// The current night mode is stored in this+0xB2 (bit 1).

void __thiscall EnvironmentManager::setNightMode(void* this, bool isNight)
{
  // this+0xB2: single byte containing state flags (bit 1 = night mode)
  byte currentNightFlag = (*(byte*)((int)this + 0xB2) >> 1) & 1;

  if ((byte)isNight != currentNightFlag)
  {
    // Manager structure pointed by this+0xA0
    int manager = *(int*)((int)this + 0xA0);

    // manager+0x50: base pointer to array of environment objects (size 0xB0 each)
    int base = *(int*)(manager + 0x50);

    // manager+0x34: count of objects in the array
    int count = *(int*)(manager + 0x34);

    int end = base + count * 0xB0;

    for (int current = base; current != end; current += 0xB0)
    {
      uint flags = *(uint*)(current + 8);
      if (!isNight)
      {
        // Clear bit 9 (0x200), set bit 10 (0x400)
        flags = (flags & 0xFFFFFDFF) | 0x400;
      }
      else
      {
        // Clear bit 10 (0x400), set bit 9 (0x200)
        flags = (flags & 0xFFFFFBFF) | 0x200;
      }
      *(uint*)(current + 8) = flags;
    }

    // Update the night mode flag in this+0xB2
    // Clear bit 1, then set it to isNight
    *(byte*)((int)this + 0xB2) =
         (*(byte*)((int)this + 0xB2) & 0xFD) | ((byte)isNight << 1);
  }
}