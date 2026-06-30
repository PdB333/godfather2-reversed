// FUNC_NAME: SetDesktopWallpaperAndSettings
// Address: 0x0069d060
// Role: Sets desktop wallpaper and other system parameters (icon spacing, metrics) 
//          to game-preferred values. Conditionally applies wallpaper based on 
//          a check (likely fullscreen mode).

#include <windows.h>

void SetDesktopWallpaperAndSettings(void)
{
  UINT wallpaperPath;
  int conditionCheck;

  // DAT_01129fb4 likely holds a string pointer to a wallpaper image path (e.g., game logo).
  wallpaperPath = *(UINT*)0x01129fb4;

  // Check some condition (e.g., fullscreen mode). If true, skip wallpaper update.
  conditionCheck = SomeCheckFunction();  // FUN_006a17c0
  if (conditionCheck == 0) {
    // (0xb) = SPI_SETDESKWALLPAPER? Actually 0xb = 11. Possibly an older or custom code.
    // Set wallpaper to the path stored in DAT_01129fb4.
    SystemParametersInfoA(0xb,       // uiAction: set desktop wallpaper
                          wallpaperPath,
                          (PVOID)0x0, // no additional data
                          1);         // fWinIni: update user profile and broadcast
  }

  // (0x3b = 59) Possibly SPI_SETICONMETRICS or other desktop icon spacing.
  // Using 8-byte structure from DAT_00e50b44.
  SystemParametersInfoA(0x3b, 8, &DAT_00e50b44, 0);

  // (0x35 = 53) Possibly SPI_SETDESKPATTERN? Use 8-byte from DAT_00e50b4c.
  SystemParametersInfoA(0x35, 8, &DAT_00e50b4c, 0);

  // (0x33 = 51) Possibly SPI_SETWHEELSCROLLLINES? Use structure of size 0x18 = 24 bytes from DAT_00e50b54.
  SystemParametersInfoA(0x33, 0x18, &DAT_00e50b54, 0);

  // (0xf = 15) Possibly SPI_SETSCREENSAVEACTIVE or SPI_SETDESKPATTERN? 
  // Set an integer value from DAT_01129fb8.
  SystemParametersInfoA(0xf, *(UINT*)0x01129fb8, (PVOID)0x0, 0);

  return;
}

// Note: All global data references (DAT_*) are likely external arrays or structures.
// DAT_01129fb4, DAT_01129fb8 are DWORDs; DAT_00e50b44, 4c, 54 are byte arrays.