// FUNC_NAME: ActionHandler::processInputEvent
void __thiscall ActionHandler::processInputEvent(int this, void *eventData)
{
  char isTriggered;

  // Update input state (static/global)
  InputSystem::updateInputState();

  // Check the first binding slot (offset +0x1c)
  isTriggered = InputBinding::wasTriggered(this + 0x1c, eventData);
  if (isTriggered != '\0') {
    // Execute primary action for this handler (action ID at +0x10)
    InputSystem::executePrimaryAction(*(int *)(this + 0x10), eventData);
    return;
  }

  // Check the second binding slot (offset +0x28)
  isTriggered = InputBinding::wasTriggered(this + 0x28, eventData);
  if (isTriggered != '\0') {
    // Execute secondary action for this handler
    InputSystem::executeSecondaryAction(*(int *)(this + 0x10), eventData);
  }
}