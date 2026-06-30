// FUNC_NAME: InputManager::mapActionToSlotId
int mapActionToSlotId(int actionId)
{
  switch(actionId) {
    case 0x2a: // Action: Accelerate (forward?)
      return 2; // Slot 2
    case 0x2b: // Action: Brake/reverse
      return 0; // Slot 0
    default:
      return 0xe; // Default slot for unknown action
    case 0x2d: // Action: Steer left
      return 1; // Slot 1
    case 0x2f: // Action: Steer right
      return 3; // Slot 3
    case 0x3c: // Action: Handbrake
      return 8; // Slot 8
    case 0x3e: // Action: Horn/hazards
      return 10; // Slot 10
    case 0x5e: // Action: Exit vehicle
      return 4; // Slot 4
    case 0x101: // Action: Look behind
      return 0xc; // Slot 12
    case 0x10f: // Action: Cinematic camera
      return 0xd; // Slot 13
    case 0x117: // Action: Weapon fire
      return 5; // Slot 5
    case 0x119: // Action: Reload
      return 7; // Slot 7
    case 0x11a: // Action: Switch weapon
      return 0xb; // Slot 11
    case 0x11b: // Action: Aim/target
      return 9; // Slot 9
    case 0x11c: // Action: Cower/cover
      return 6; // Slot 6
  }
}