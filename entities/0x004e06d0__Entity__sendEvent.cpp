//FUNC_NAME: Entity::sendEvent
void Entity::sendEvent() {
    // Event parameters: code = 2, data = 0
    int eventParams[2];
    eventParams[0] = 2;
    eventParams[1] = 0;

    // Call virtual function pointer from global table (DAT_01194538)
    // This likely dispatches an event to the object's state machine or handler
    ((void (*)(Entity*, int*))DAT_01194538)(this, eventParams);
}