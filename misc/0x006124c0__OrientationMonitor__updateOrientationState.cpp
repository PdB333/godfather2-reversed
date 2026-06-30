// FUNC_NAME: OrientationMonitor::updateOrientationState
// Function address: 0x006124c0
// Role: Updates a static last orientation (quaternion) and triggers a callback if any component changed.
// Uses SSE to compare new values with previous stored in global statics.
// The callback is invoked via a global listener object pointer (s_pOrientationListener) if the orientation changed.

#include <xmmintrin.h> // for _mm_movemask_ps

// Global statics for previous orientation (quaternion x,y,z,w)
static float s_lastOrientationX; // _DAT_011f6890
static float s_lastOrientationY; // fRam011f6894
static float s_lastOrientationZ; // fRam011f6898
static float s_lastOrientationW; // fRam011f689c

// Global pointer to an orientation listener object (e.g., camera controller)
static void* s_pOrientationListener; // DAT_012058e8

// Forward declaration of the callback function (address 0x0060add0)
void notifyOrientationChange(uint32_t context, int callbackFunc, float* pOrientation);

void __fastcall updateOrientationState(uint32_t unused1, uint32_t unused2, float* pNewOrientation)
{
    float newX = pNewOrientation[0];
    float newY = pNewOrientation[1];
    float newZ = pNewOrientation[2];
    float newW = pNewOrientation[3];

    // Build SSE comparison mask: each component compared to previous
    __m128 cmp = _mm_set_ps(newW, newZ, newY, newX);
    __m128 prev = _mm_set_ps(s_lastOrientationW, s_lastOrientationZ, s_lastOrientationY, s_lastOrientationX);
    __m128 eq = _mm_cmpeq_ps(cmp, prev);
    int mask = _mm_movemask_ps(eq); // bit 0 = x, bit1 = y, bit2 = z, bit3 = w

    // Update the static previous orientation
    s_lastOrientationX = newX;
    s_lastOrientationY = newY;
    s_lastOrientationZ = newZ;
    s_lastOrientationW = newW;

    // If any component changed (mask != 0xF) and listener exists, call callback
    if ((mask != 0xF) && (s_pOrientationListener != nullptr))
    {
        void* listener = s_pOrientationListener;
        uint32_t context = *(uint32_t*)((uint8_t*)listener + 0x14); // +0x14: context/identifier
        int callbackFunc = *(int*)((uint8_t*)listener + 0x74);      // +0x74: function pointer or index
        if (callbackFunc != 0)
        {
            notifyOrientationChange(context, callbackFunc, &s_lastOrientationX);
        }
    }
}