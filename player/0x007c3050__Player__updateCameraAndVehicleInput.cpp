// FUNC_NAME: Player::updateCameraAndVehicleInput
void __fastcall Player::updateCameraAndVehicleInput(int thisPtr)
{
    char bEnterKey;
    int *pInputMgr; // pointer to InputManager singleton
    int pEntity;
    int playerData;
    int iVar4;
    int vehiclePtr;
    int cameraPtr;
    float posX, posY, posZ; // camera position or offset
    float dummy0, dummy1, dummy2; // for vector manipulation

    // +0x58: pointer to player-specific data (camera/vehicle info)
    playerData = *(int *)(thisPtr + 0x58);

    pInputMgr = (int *)InputManager::getInstance();
    bEnterKey = InputManager::isEnterVehicleKeyDown();

    if (bEnterKey != '\0') {
        // get the entity/character the player is currently controlling
        pEntity = Entity::getCurrentControlledEntity();
        if (pEntity == 0) {
            pInputMgr = (int *)0x0;
        }
        else {
            // convert entity pointer to player data address (offset -0x58)
            pInputMgr = (int *)(pEntity - 0x58);
        }
        // set a flag in player data to indicate entering vehicle mode
        *(unsigned char *)(playerData + 0x23ac) = 1; // +0x23ac: m_bEnteringVehicle
    }

    if (pInputMgr != (int *)0x0) {
        // get main camera data (position, orientation)
        cameraPtr = CameraManager::getMainCamera();
        // read camera fields: +0x30 double for x? Actually double, then split into two floats
        posX = (float)*(double *)(cameraPtr + 0x30); // double -> float
        posY = (float)((unsigned long long)*(double *)(cameraPtr + 0x30) >> 32); // upper 32 bits of double
        posZ = *(float *)(cameraPtr + 0x38); // third component

        // get current vehicle (if any)
        vehiclePtr = VehicleManager::getCurrentVehicle();

        // check if we are driving a boat or plane and vehicle exists
        if ((vehiclePtr != 0) && (*(int *)(thisPtr + 0x78) == 3 || *(int *)(thisPtr + 0x78) == 2)) {
            // set a flag on vehicle to indicate camera is following
            *(unsigned int *)(vehiclePtr + 0x1a4) |= 4; // +0x1a4: m_cameraFollowFlag
            // get vehicle's camera angle (yaw)
            int defaultAngle = *(int *)(vehiclePtr + 0x1ac);
            // check if we are near a vehicle exit trigger (e.g., boat or plane)
            if (*(char *)((int)pInputMgr + 0x1ad) == 0x1a) { // exit boat trigger
                Vehicle::exitVehicle(vehiclePtr);
            }
            else if (*(char *)((int)pInputMgr + 0x1ad) == 0x1b) { // exit plane trigger
                Vehicle::exitVehicle(vehiclePtr);
            }
        }
        else {
            // update camera for foot / car mode (reset to default)
            Camera::updateFloorCamera();
        }

        // read camera velocity / offset from camera component
        posX += (float)*(double *)(cameraPtr + 0x20) * DAT_00d5c454; // maybe sensitivity factor
        // y component has additional offset
        posY += (float)*(double *)(cameraPtr + 0x24) * DAT_00d5c454 + DAT_00d5f18c;
        posZ += (float)*(double *)(cameraPtr + 0x28) * DAT_00d5c454;

        // call a virtual function on the input manager to apply camera update
        (**(code **)(*pInputMgr + 0x19c))(&posX, defaultAngle); // vtable index 103 -> applyCameraInput

        // check for another input (e.g., exit vehicle key)
        bEnterKey = InputManager::isExitVehicleKeyDown(); // supposed name
        if (bEnterKey != '\0') {
            // queue an action on the input manager
            InputManager::queueAction(pInputMgr + 0x16, 0x13); // some action ID
        }
    }
}