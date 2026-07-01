// FUNC_NAME: sendInternalEventMessage
void sendInternalEventMessage(void *targetObject) {
    vtable_type *vtable = (vtable_type *)getStaticVTable();
    InternalEvent event;
    event.type = 2;    // likely an event type constant
    event.size = 0x10; // size of the event structure (16 bytes)
    event.flags = 0;   // no flags

    // Call the first virtual function in the vtable, typically dispatchEvent
    vtable->dispatchEvent(targetObject, &event);
}