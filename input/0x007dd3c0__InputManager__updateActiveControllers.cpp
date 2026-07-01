// FUNC_NAME: InputManager::updateActiveControllers

void __thiscall InputManager::updateActiveControllers(void)
{
    /*** Fields of 'this' ***/
    // +0x10: byte m_stateDirty (set to 1 at start)
    // +0x14: uint m_previousInputFlags
    // +0x1c: uint m_currentInputFlags (bit 23 = camera shake, bit 5 = weapon trigger)
    // +0x20: uint m_extraInputFlags (bit 10 = action event)

    struct ControllerNode {
        ControllerData* data;    // +0x00
        ControllerNode* next;   // +0x04
    };

    ControllerData* data;
    bool cutsceneActive;
    uint changedFlag;
    uint tempIndex;
    int* pEntity;
    uint weaponCount;
    int weaponIndex;
    uint shakeResult;
    float shakeValue;
    int* pCamera;

    // Mark state as dirty
    this->m_stateDirty = 1;

    // Get linked list of active controllers
    ControllerNode* node = *(ControllerNode**) GetActiveControllerList(1); // FUN_0043c2c0
    while (node != nullptr) {
        data = node->data;
        cutsceneActive = IsCutsceneActive(); // FUN_00481640

        if (!cutsceneActive) {
            // --- Rumble / vibration update ---
            changedFlag = (this->m_currentInputFlags >> 2) & 1;
            if (changedFlag != ((this->m_previousInputFlags >> 2) & 1)) {
                if (changedFlag == 0)
                    data->rumbleFlags &= ~0x40;   // +0x820
                else
                    data->rumbleFlags |= 0x40;
            }

            // --- Weapon / gadget fire handling ---
            if ((this->m_currentInputFlags & bit5_WeaponTrigger) &&
                (data->weaponArray != 0)) {
                pEntity = (int*) *(data->weaponArray + 0x10); // +0x10 = weapon count/array head
                if (pEntity != nullptr && *pEntity != 0) {
                    weaponCount = *pEntity;
                    for (weaponIndex = 0; weaponIndex < weaponCount; ++weaponIndex) {
                        int weaponObj = GetWeaponObject(weaponIndex); // FUN_00704110
                        if (weaponObj != 0 && *(char*)(weaponObj + 0x1a8) == 1) {
                            uint weaponData = GetWeaponData(); // FUN_00701360
                            ApplyWeaponModifiers(weaponData);  // FUN_00701ff0
                            FireWeapon(*(uint*)(weaponObj + 0x32c)); // FUN_00701290
                        }
                    }
                }
            }

            // --- Camera shake / rumble effect ---
            if (this->m_currentInputFlags & bit23_CameraShake) {
                shakeValue = (data->vfptr->GetShakeIntensity)(); // +0xc0
                if (shakeValue > 0.0f) {
                    pCamera = (int*) GetGlobalCameraManager(); // FUN_0043b870, DAT_01131018
                    shakeResult = (*pCamera)->GetShakeAmount(); // vtable+0x2c
                    (*pCamera)->ApplyShake(shakeResult);        // vtable+0x3c
                } else {
                    // fallback: create a small shake effect
                    uint dummy = 0;
                    uint shakeHandle = CreateShakeEffect(1, 0, 0); // FUN_00471610
                    PlayShakeEffect(shakeHandle, 1, 0, 0);        // FUN_0079e3c0
                }
            }

            // --- Action event (e.g. sound/effect) ---
            if ((this->m_extraInputFlags & bit10_ActionEvent) &&
                data != nullptr &&
                data->someActionId != 0 &&
                data->someActionId != 0x48) {
                PlayActionEvent(g_soundManager, 4); // FUN_008c09a0, DAT_00d61ae8
            }
        }

        node = node->next;
    }

    // Clear processed flags
    this->m_currentInputFlags &= ~bit23_CameraShake;
    this->m_extraInputFlags   &= ~0x40;
    this->m_currentInputFlags &= ~bit5_WeaponTrigger;
}