// FUNC_NAME: HUDWidget::processUIAction
int __thiscall HUDWidget::processUIAction(HUDWidget *this, int eventType, int data1, int data2) {
    char cVar1;
    int iVar2;

    // Early exit if engine is in certain state (e.g., loading screen)
    cVar1 = isEngineStateBlocking();
    if (cVar1 == '\0') {
        cVar1 = isInputAllowed();
        if (cVar1 == '\0' &&
            // Validate object integrity using sentinel pattern (EA debug markers)
            !((this->sentinel0 == 0xBADBABBA &&
               this->sentinel1 == 0xBEEFBEEF &&
               this->sentinel2 == 0xEAC15A55 &&
               this->sentinel3 == 0x91100911) ||
              (this->sentinel0 == 0 &&
               this->sentinel1 == 0 &&
               this->sentinel2 == 0 &&
               this->sentinel3 == 0))) {
            // Resolve action handler from internal dictionary
            iVar2 = findActionHandler(this, 0);  // offset unknown
            if (iVar2 != 0) {
                // Retrieve specific behavior object by signature 0x55859efa
                iVar2 = getBehaviorByID(iVar2, 0x55859efa);
                if (iVar2 != 0 && this->actionData != 0) {
                    // Validate behavior pointer
                    iVar2 = validateBehavior(iVar2);
                    if (iVar2 != 0) {
                        // Execute the action with parameters
                        cVar1 = executeAction(this->actionData, data1, (char)this->actionType, eventType, data2, 0, 0, 0);
                        if (cVar1 != '\0') {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}