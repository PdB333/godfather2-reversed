// FUNC_NAME: TimerManager::updateTimers

// Address: 0x004dfdd0
// Role: Updates all active timers each frame, incrementing their tick counters and handling expired ones.
// Each timer has a pointer and a tick counter. When a timer fires, a 15-bit counter on the event is incremented.
// If no event is ready, the timer is removed with a reset flag (0x4000 for the first two, 0x8000 for the rest).

#include <cstdint>

// Forward declarations for helper functions used below
int* getNextExpiredTimer();           // Returns a pointer to an expired timer event, or 0 if none
void removeTimerAndReset(uint32_t* timerPtr, uint32_t resetFlag); // Removes the timer and possibly resets it

// Global timer state (offsets based on addresses in the binary)
static uint32_t* timerPtr1 = reinterpret_cast<uint32_t*>(0x012069d4);
static int32_t timerTick1 = *reinterpret_cast<int32_t*>(0x012069d8); // Actually _DAT_012069d8

static uint32_t* timerPtr2 = reinterpret_cast<uint32_t*>(0x012069ec);
static int32_t timerTick2 = *reinterpret_cast<int32_t*>(0x012069f0);

static uint32_t* timerPtr3 = reinterpret_cast<uint32_t*>(0x01206960);
static int32_t timerTick3 = *reinterpret_cast<int32_t*>(0x01206964);

static uint32_t* timerPtr4 = reinterpret_cast<uint32_t*>(0x01206980);
static int32_t timerTick4 = *reinterpret_cast<int32_t*>(0x01206984);

static uint32_t* timerPtr5 = reinterpret_cast<uint32_t*>(0x01206978);
static int32_t timerTick5 = *reinterpret_cast<int32_t*>(0x0120697c);

static uint32_t* timerPtr6 = reinterpret_cast<uint32_t*>(0x01206968);
static int32_t timerTick6 = *reinterpret_cast<int32_t*>(0x0120696c);

static uint32_t* timerPtr7 = reinterpret_cast<uint32_t*>(0x01206970);
static int32_t timerTick7 = *reinterpret_cast<int32_t*>(0x01206974);

void TimerManager::updateTimers()
{
    // Timer 1 (flag 0x4000)
    if (*timerPtr1 != 0) {
        timerTick1++;
        int* expired = getNextExpiredTimer();
        if (expired == nullptr) {
            removeTimerAndReset(timerPtr1, 0x4000);
        } else {
            // Increment the 15-bit tick counter at offset +0x14 of the timer event
            *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(expired) + 0x14) =
                (*reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(expired) + 0x14) + 1) & 0x7FFF;
        }
    }

    // Timer 2 (flag 0x4000)
    if (*timerPtr2 != 0) {
        timerTick2++;
        int* expired = getNextExpiredTimer();
        if (expired == nullptr) {
            removeTimerAndReset(timerPtr2, 0x4000);
        } else {
            *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(expired) + 0x14) =
                (*reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(expired) + 0x14) + 1) & 0x7FFF;
        }
    }

    // Timer 3–7 (flag 0x8000)
    for (int i = 3; i <= 7; i++) {
        uint32_t** timerPtr;
        int32_t* tickCounter;
        uint32_t flag = 0x8000;

        // Assign based on index (unrolled in original binary)
        switch (i) {
        case 3: timerPtr = &timerPtr3; tickCounter = &timerTick3; break;
        case 4: timerPtr = &timerPtr4; tickCounter = &timerTick4; break;
        case 5: timerPtr = &timerPtr5; tickCounter = &timerTick5; break;
        case 6: timerPtr = &timerPtr6; tickCounter = &timerTick6; break;
        case 7: timerPtr = &timerPtr7; tickCounter = &timerTick7; break;
        }

        if (*timerPtr != 0) {
            (*tickCounter)++;
            int* expired = getNextExpiredTimer();
            if (expired == nullptr) {
                removeTimerAndReset(*timerPtr, flag);
            } else {
                *reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(expired) + 0x14) =
                    (*reinterpret_cast<uint16_t*>(reinterpret_cast<uintptr_t>(expired) + 0x14) + 1) & 0x7FFF;
            }
        }
    }
}