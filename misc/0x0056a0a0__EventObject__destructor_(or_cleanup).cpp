// FUNC_NAME: EventObject::destructor (or cleanup)
void __fastcall EventObject::destructor(class EventObject *this)
{
  // Set vtable to base class (likely to prevent virtual calls during destruction)
  this->vtable = &PTR_FUN_00e3ab30;

  // +0x334: Handle to a Windows event/synchronization object
  if (this->hEvent != (HANDLE)0x0) {
    CloseHandle(this->hEvent);
    this->hEvent = 0;

    // +0x33C: Pointer to event data (allocated memory)
    // FUN_009c8f10 is likely a deallocation function (e.g., free or operator delete)
    FUN_009c8f10(this->eventData);
    this->eventData = 0;

    // +0x338: Event state flag/other integer field
    this->eventState = 0;
  }

  // Call base class destructor or common cleanup (likely releases other resources)
  FUN_00569190();
}