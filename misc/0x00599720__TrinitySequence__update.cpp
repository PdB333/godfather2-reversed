// FUNC_NAME: TrinitySequence::update

void TrinitySequence::update(float deltaTime)
{
    if (this->currentOp != nullptr) {
        this->accumulatedTime += deltaTime;
        bool continueProcessing = true;
        do {
            ushort* opPtr = this->currentOp;
            ushort opcode = *opPtr;
            if (opcode == 0x100) {
                // Wait operation: subtract deltaTime from accumulated time
                if (opPtr[1] != 4) {
                    // Assert: operation size mismatch
                    (**(code**)(*DAT_01205590 + 4))();
                }
                this->accumulatedTime -= deltaTime;
                FUN_005994c0(0, deltaTime);
                return;
            }
            if (opcode == 0x101) {
                // Wait for duration operation
                if (opPtr[1] != 8) {
                    (**(code**)(*DAT_01205590 + 4))();
                }
                float duration = *(float*)(this->currentOp + 4);
                float newTimer = this->waitTimer + deltaTime;
                this->waitTimer = newTimer;
                if (newTimer < duration) break;
                if (DAT_00e2b05c < newTimer - duration) {
                    // Overshoot beyond threshold: process exact remaining time first
                    FUN_00599940(duration - (newTimer - deltaTime)); // fVar1 - fVar2
                    deltaTime = newTimer - duration;
                }
                this->waitTimer = 0.0f;
            }
            else if (opcode == 0x102) {
                // Call function operation
                if (opPtr[1] != 0x18) {
                    (**(code**)(*DAT_01205590 + 4))();
                }
                int* opData = (int*)(this->currentOp + 4);
                // Combine four 32-bit values into a single ID (big-endian concatenation)
                int combinedID = ((opData[0] * 0x100 + opData[1]) * 0x100 + opData[2]) * 0x100 + opData[3];
                int targetObj = FUN_00599aa0(this, combinedID);
                if (targetObj == 0) {
                    (**(code**)(*DAT_01205590 + 4))();
                    return;
                }
                if (opData[4] == 0) {
                    // Check flag 0x20 at offset +0x7c
                    continueProcessing = ((*(byte*)(targetObj + 0x7c) & 0x20) != 0x20);
                }
                else if (opData[4] == 1) {
                    // Check flag 0x800 at offset +0x7c
                    continueProcessing = (*(uint*)(targetObj + 0x7c) & 0x800) == 0x800;
                }
                if (!continueProcessing) break;
            }
            else {
                // Dispatch to opcode handler table (41 entries)
                int tableIndex = 0;
                do {
                    if (DAT_00e2bce0[tableIndex * 2] == opcode) {
                        (*(code*)(PTR_FUN_00e2bce4[tableIndex * 2]))();
                        break;
                    }
                    tableIndex++;
                } while (tableIndex < 0x29);
            }
            // Advance to next operation
            int nextOpOffset = *(ushort*)(this->currentOp + 2);
            if (nextOpOffset == 0) {
                // Error: operation size is zero
                (**(code**)(*DAT_01205590 + 8))(DAT_01205590, "Trinity sequence [%s] operation size is %d", this->name + 0x30, 0);
                break;
            }
            this->currentOp = (ushort*)((int)this->currentOp + nextOpOffset);
        } while (continueProcessing);
        FUN_00599940(deltaTime);
    }
}