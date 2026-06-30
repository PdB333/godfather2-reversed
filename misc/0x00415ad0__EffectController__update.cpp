// FUNC_NAME: EffectController::update
// Function at 0x00415ad0
// Each frame: updates effect timer, handles state transitions, and calls related routines.

class EffectController {
public:
    // Vtable at +0x00
    // +0x0c: pointer to an object (e.g., scene node or material) whose vtable+0x60 returns a matrix
    // +0x31: flags byte (bit 1 = some flag)
    // +0x80: pointer to a target object (may be 0)
    // +0x84: pointer to some resource (maybe texture, shader, or null)
    // +0x98: total duration (float)
    // +0xa0: fade-out time (float)
    // +0xa4: counter (int, decremented when no target)
    // +0xa8: state flags (bit 0 = triggered state)
    // +0xac: elapsed time accumulator (float)
    // +0xb0: some value passed to the transform-related function (maybe color/alpha)
};

// Global frame delta time (in seconds)
extern float g_fDeltaTime; // DAT_012067e8
// Global flag (non-zero enables some effect part)
extern int g_bEnableEffect; // DAT_012233c4

// Forward declarations of called functions
void FUN_00416130(float matrix[4], float value);
void FUN_00415970(void); // finishEffect
void FUN_00415200(void); // removeEffect
void FUN_004df890(float ratio); // setFadeProgress
void FUN_00415880(void); // startFadeOut
void FUN_004df650(void); // stopEffect

void __fastcall EffectController_update(int thisPtr)
{
    // Step 1: If a resource exists and global flag is set, update transform
    if (*(int*)(thisPtr + 0x84) != 0 && g_bEnableEffect != 0)
    {
        // Get the object at +0x0c, call its virtual function at vtable+0x60 to retrieve a matrix pointer
        int obj = **(int**)(thisPtr + 0x0c);
        int vtable = *(int*)obj;
        auto getTransform = (float* (*)(void*))(*(int*)(vtable + 0x60));
        float* matrixPtr = getTransform((void*)obj); // Returns a pointer; we copy 4 floats from +0x30

        float matrix[4];
        matrix[0] = *(float*)(matrixPtr + 0x30);
        matrix[1] = *(float*)(matrixPtr + 0x34);
        matrix[2] = *(float*)(matrixPtr + 0x38);
        matrix[3] = *(float*)(matrixPtr + 0x3c);

        // Call a function with the matrix and the value at +0xb0 (e.g., alpha or color)
        FUN_00416130(matrix, *(float*)(thisPtr + 0xb0));
    }

    // Step 2: Normal update (bit 0 clear) vs triggered update (bit 0 set)
    if ((*(unsigned int*)(thisPtr + 0xa8) & 1) == 0)
    {
        // Normal update path
        if (*(int*)(thisPtr + 0x80) != 0)
        {
            float duration = *(float*)(thisPtr + 0x98);
            if (duration > 0.0f)
            {
                float elapsed = *(float*)(thisPtr + 0xac) + g_fDeltaTime;
                *(float*)(thisPtr + 0xac) = elapsed;

                if (duration <= elapsed)
                {
                    // Duration expired: finish and remove effect
                    FUN_00415970();
                    FUN_00415200();
                    return;
                }

                float fadeTime = *(float*)(thisPtr + 0xa0);
                if (fadeTime > 0.0f && (duration - fadeTime) < elapsed)
                {
                    // In fade-out region: compute progress (1 at start of fade, 0 at end)
                    float ratio = (duration - elapsed) / fadeTime;
                    FUN_004df890(ratio);
                }
            }
        }
    }
    else
    {
        // Triggered state: clear the bit
        *(unsigned int*)(thisPtr + 0xa8) &= 0xfffffffe;

        if (*(int*)(thisPtr + 0x80) == 0)
        {
            // No target: decrement counter (if not -1) and start fade-out
            if (*(int*)(thisPtr + 0xa4) != -1)
            {
                *(int*)(thisPtr + 0xa4) -= 1;
            }
            FUN_00415880();

            if ((*(unsigned char*)(thisPtr + 0x31) & 2) == 0)
            {
                FUN_004df650();
            }

            *(float*)(thisPtr + 0xac) = 0.0f;
            return;
        }
        // If target exists, do nothing extra (fall through to return)
    }
    return;
}