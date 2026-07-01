// Xbox PDB: EARS_Apt_UIFamilyMemberInfo_ShowNotEnoughMoneyPopup
// FUNC_NAME: GodfatherGameManager::createAttributeCannotAffordWidget
// Address: 0x0092bdd0
// Allocates and initializes a UI widget for the "cannot afford attribute" message.

void GodfatherGameManager::createAttributeCannotAffordWidget(void)
{
  int widgetPtr;

  // Allocate memory for widget object (size 0xF0 = 240 bytes).
  widgetPtr = FUN_009c8e50(0xf0);
  if (widgetPtr == 0) {
    widgetPtr = 0;
  }
  else {
    // Initialize the widget (argument 0 probably indicates default state).
    widgetPtr = FUN_00982280(0);
  }

  // Set the display text via localization key.
  FUN_00981eb0("$attribute_cannot_afford");
  
  // Configure widget fields:
  // +0x0C: State/type? Set to 3 (maybe enum value for "cannot afford").
  *(int *)(widgetPtr + 0xc) = 3;
  // +0x20: Some identifier/hash (0x510c352b appears to be a constant ID).
  *(uint32_t *)(widgetPtr + 0x20) = 0x510c352b;
  // +0x14: Callback function pointer (points to handler for this widget).
  *(void (**)(void))(widgetPtr + 0x14) = FUN_0092abc0;

  // Finalize/push widget into the UI stack (probably updates layout or show).
  FUN_00982e10();

  return;
}