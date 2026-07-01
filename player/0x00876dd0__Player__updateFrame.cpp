// FUNC_NAME: Player::updateFrame
void __thiscall Player::updateFrame(int *this, int *someGlobalPtr) // someGlobalPtr might be passed in EDI
{
    char isActive;
    int iVar2;
    int *effectPtr;
    uint effectIndex;
    float speed;
    float timeScale;
    float maxSpeed;
    float ratio;

    isActive = (**(code **)(*this + 0x198))(); // virtual call: isActive()
    if (isActive != 0) {
        if (this[0x1f0] != 0) { // offset +0x7C0: some bool/flag
            FUN_0085adb0(); // likely resetInput() or clearState()
        }
        FUN_0055be50(DAT_012067e8, (uint)this[0x322] >> 0x12 & 0xffffff01); // offset +0xC88: some flags, bit18+ mask
        FUN_00880b80(this); // unknown update function
        if (this[0xaf] != 0) { // offset +0x2BC: m_effectCount
            effectIndex = 0;
            do {
                effectPtr = (int *)(this[0xae] + effectIndex * 8); // offset +0x2B8: m_effects array
                if ((*effectPtr != 0) && (*effectPtr != 0x48)) {
                    int *baseObj = *effectPtr;
                    if (baseObj == 0) {
                        baseObj = 0;
                    }
                    else {
                        baseObj = (int *)((int)baseObj - 0x48); // subtract header size
                    }
                    if ((*(int *)((int)baseObj + 0x68) != 0) && (*(int *)((int)baseObj + 0x68) != 0x48)) {
                        // update each effect
                        (**(code **)(*baseObj + 0x88))(); // virtual call: update()
                    }
                }
                effectIndex++;
            } while (effectIndex < (uint)this[0xaf]);
        }
        if (((uint)this[0x322] >> 2 & 1) != 0) { // bit 1 of flags at +0xC88
            if (DAT_011299a8 != 0) {
                speed = (float)(**(code **)(*this + 0x1a8))(); // virtual getSpeed()
                FUN_008d1c30(speed); // apply speed to camera shake
                FUN_008d1c10(0);
                timeScale = (float)(**(code **)(*this + 0xc4))(); // virtual getTimeScale() or similar
                if (timeScale <= DAT_00e44598) {
                    ratio = 1.0f;
                }
                else {
                    maxSpeed = (float)(**(code **)(*this + 0xc0))(); // virtual getMaxSpeed()
                    ratio = maxSpeed / timeScale;
                }
                FUN_008d1c70(ratio); // apply ratio to camera shake
            }
            int *cameraMgr = (int *)(**(code **)(*this + 0x1e4))(); // virtual getCameraManager()
            float outputFloat = 0.0f;
            char result = (**(code **)(*cameraMgr + 0x10))(0x383225a1, &outputFloat); // virtual lookupParam(hash, &value)
            if ((result != 0) && (someGlobalPtr != 0) &&
               ((*(uint *)((int)someGlobalPtr + 0x249c) >> 0x1a & 1) != 0)) {
                FUN_00546730(&outputFloat); // apply some effect
                outputFloat = outputFloat * DAT_00d5833c;
                FUN_005466c0(&outputFloat);
            }
        }
    }
}