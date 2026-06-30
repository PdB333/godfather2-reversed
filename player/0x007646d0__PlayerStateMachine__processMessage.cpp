// FUNC_NAME: PlayerStateMachine::processMessage
uint8_t __thiscall PlayerStateMachine::processMessage(int *this, uint32_t unk1, float dt, uint32_t unk2, int32_t messageId, uint32_t unk3)
{
    uint8_t result = 1;
    int32_t adjustedMsg = messageId - 10;
    switch (adjustedMsg) {
        case 0: {
            // messageId = 10: presumably start or play something
            void *somePtr = (void *)this[0x38]; // +0xE0: pointer to animation controller or similar
            // call virtual function at offset 0x2c (likely setSpeed or playAnimation)
            (*(void (**)(void *, int32_t, int32_t, int32_t, int32_t, float, float))(* (int *)somePtr + 0x2c))(somePtr, 1, 0, 0, 0, 1.0f, 1.0f);
            return 1;
        }
        default:
            result = handleDefaultMessage(unk1, dt, unk2, messageId, unk3); // FUN_004ac700
            break;
        case 2: {
            // messageId = 12
            this[0x1f] = (int32_t)globalSomeFloat; // DAT_00d5779c
            updateInternalTimer(); // FUN_00763df0
            return 1;
        }
        case 3: {
            // messageId = 13
            int vtable = *(int *)this;
            uint32_t obj = createSomeObject(1, 0, 1, 1.0f, 1.0f); // FUN_00763c30
            (*(void (**)(uint32_t))(* (int *)obj + 0x2c))(obj);
            // note: the call seems to pass only 'obj' but original code had uVar4 = return and then used it as this.
            // The original call was (**(code **)(iVar1 + 0x2c))(uVar4);
            // So we call the function with obj as this.
            return 1;
        }
        case 4: {
            // messageId = 14: update logic with accumulators
            processTimeStep(dt); // FUN_007642b0
            float accumulator = getAccumulator(&this[0x32]); // FUN_004702b0, offset +0xC8
            if (globalAccumThreshold < accumulator) { // DAT_00d5ef84 < fVar5
                adjustAccumulator(&this[0x32], (float)this[0x2a] * dt, 0); // FUN_00470130
            }
            uint32_t res = createSomeObject(); // FUN_00763c30 no args
            bool isActive = checkActivity(res); // FUN_0045eec0
            if (!isActive) {
                // call virtual at offset 0x2c on res with parameters 1,0,0,0,1.0,1.0
                (*(void (**)(uint32_t, int32_t, int32_t, int32_t, int32_t, float, float))(* (int *)res + 0x2c))(res, 1, 0, 0, 0, 1.0f, 1.0f);
                return 1;
            }
            break;
        }
        case 5: {
            // messageId = 15
            this[0x37] = 3; // +0xDC state variable
            playAnimation(dt); // FUN_007641c0
            return 1;
        }
        case 6:
            // messageId = 16: no action
            break;
        case 7: {
            // messageId = 17
            if ((this[0x3a] >> 5 & 1) != 0) { // bit 5 of +0xE8
                playSoundEffect(0x80); // FUN_004abcc0
                return 1;
            }
            break;
        }
        case 8: {
            // messageId = 18
            playSoundEffect(0x4000); // FUN_004abdd0
            return 1;
        }
    }
    return result;
}