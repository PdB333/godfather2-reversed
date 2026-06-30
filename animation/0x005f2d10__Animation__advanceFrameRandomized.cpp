// FUNC_NAME: Animation::advanceFrameRandomized

// Decompiled from address 0x005f2d10
// Advances a frame counter with optional randomization and wraps modulo max frames.

class AnimationData {
public:
    byte type;           // +0x00 (not used in this function? Actually offset 0x1)
    byte maxFrame;       // +0x02
    byte currentFrame;   // +0x04 (synced with Animation's m_currentFrame)
    // ... other fields
};

class Animation {
public:
    AnimationData* m_pAnimData; // +0x8
    byte m_currentFrame;        // +0x66
    // ... other fields
};

// Global random state and table (from EA EARS engine)
extern uint g_randomState;          // DAT_012054b4
extern uint g_randomMask;           // DAT_010c2678
extern float g_randomBase;          // DAT_00e2cd54
extern float g_randomTable[256];    // DAT_010c2680

void __thiscall Animation::advanceFrameRandomized(void) {
    if (this == 0) {
        return;
    }

    AnimationData* animData = this->m_pAnimData;
    byte maxFrame = animData->maxFrame;

    if (maxFrame < 2) {
        this->m_currentFrame = 0;
        return;
    }

    if (maxFrame == 0) {
        return;
    }

    byte newFrame;
    if (animData->type < 4) {
        uint index = g_randomMask & g_randomState;
        g_randomState = g_randomState + 1;
        // Randomize frame around base range
        float fVar = ((float)maxFrame - g_randomBase - g_randomBase) * g_randomTable[index] + g_randomBase;
        newFrame = (byte)(int)fVar;

        byte compareFrame;
        if (animData->type == 2) {
            compareFrame = this->m_currentFrame;
        } else if (animData->type == 3) {
            compareFrame = animData->currentFrame;
        } else {
            goto updateFrame;
        }

        if (newFrame == compareFrame) {
            // Frame matches, no change? Actually then we do nothing and fall through to increment?
            // The original logic: if they are equal, we still proceed to increment newFrame? 
            // Actually the original: if bVar4 != bVar2 goto LAB_005f2d91; So if equal, it does NOT goto label,
            // meaning it continues? No, it falls through to the code after the if... else? Let's re-analyze.
            // Original decompiled:
            // if (bVar4 != bVar2) goto LAB_005f2d91;
            // else then it goes to bVar4 = bVar4 + 1; LAB_005f2d91: ...
            // So if equal, it increments bVar4 by 1; if not equal, it goes directly to label (no increment).
            // So we need to replicate that.
        }
        // If not equal, skip increment; but we need to separate.
        // Actually the original: 
        // if (bVar4 != bVar2) goto LAB_005f2d91; // skip increment if not equal
        // bVar4 = bVar4 + 1;                     // increment if equal
        // LAB_005f2d91:
        // ...
        // So we implement: if (newFrame == compareFrame) newFrame = newFrame + 1; else nothing.
        if (animData->type == 2 || animData->type == 3) {
            if (newFrame == compareFrame) {
                newFrame = newFrame + 1;
            }
        }
    } else {
        newFrame = this->m_currentFrame;
    }

updateFrame:
    // Wrap modulo
    if (maxFrame <= newFrame) {
        newFrame = newFrame - maxFrame;
    }

    this->m_currentFrame = newFrame;
    animData->currentFrame = newFrame;
}