// FUNC_NAME: EventProcessor::processEvents

// Represents an object that processes pending events from a bitmask
struct EventProcessor {
    void* vtable;                     // +0x00
    int unknown1;                     // +0x04
    int* pendingEventBitmask;         // +0x08  // pointer to array of uint32 bits (size = (maxEvents+31)/32)
    int context;                      // +0x0C  // passed to event handlers
    int numEvents;                    // +0x10  // total number of possible events
    int currentIndex;                 // +0x14  // index being processed (or total to process)
    int someCounter;                  // +0x18
    int sentinel;                     // +0x1C  // often DAT_00e2b1a4
};

// Structure pointed to by pendingEventBitmask (offset +0x08)
// Likely a collection of event handlers or a queue state
struct EventState {
    byte stateFlags;                  // +0x04
    // based on stateFlags & 0xff < 10 => use array at +0x24, else use +0x2c
    int handlerArray1[?];             // +0x24
    int handlerArray2[?];             // +0x2c
};

// Forward declarations of called subroutines
void processInitialEvent(int context);
void processPendingBit(int context);
void finishProcessing(void* obj);           // takes *this

void processDelayedInitialEvent(int context);
void processDelayedPendingBit(int context);
void finishDelayedProcessing(void* obj);

int __thiscall FUN_00580380(EventProcessor* this) {
    int iVar1;
    int iVar4;
    int* piVar3;
    int sentinel = DAT_00e2b1a4;  // global constant

    iVar1 = this->numEvents;
    // Check if the bit for iVar1 (which is the count? Likely the current index) is clear in the bitmask
    uint32* bitArray = *(uint32**)this->pendingEventBitmask;  // actually this->pendingEventBitmask is itself a pointer to int array
    // Correction: this->pendingEventBitmask is already the pointer to the bitmask array
    // So check (bitArray[iVar1 >> 5] & (1 << (iVar1 & 0x1f))) == 0
    if ((*(uint32*)(*(int*)this->pendingEventBitmask + (iVar1 >> 5) * 4) & (1 << (iVar1 & 0x1f))) == 0) {
        // Bit not set: initialize the object
        // Reset the whole structure to zero, then set sentinel
        this->vtable = 0;           // cleared
        this->unknown1 = 0;
        this->pendingEventBitmask = 0;
        this->context = sentinel;
        this->currentIndex = 0;
        this->numEvents = 0;
        this->someCounter = 0;
        this->sentinel = sentinel;
        return 1;
    }

    // Bit is set: proceed to process events
    iVar4 = (int)this->unknown1;  // Treat as pointer to EventState
    EventState* state = (EventState*)iVar4;
    if ((state->stateFlags & 0xFF) < 10) {
        piVar3 = (int*)(state->handlerArray1);
    } else {
        piVar3 = (int*)(state->handlerArray2);
    }

    if (*piVar3 == 0) {
        // first branch: handler is null? but check piVar3[3] (short)
        if ((short)piVar3[3] != 0) {
            processInitialEvent(this->context);
            // Process all bits from 0 to iVar1-1
            int idx = 0;
            if (0 < iVar1) {
                do {
                    if ((*(uint32*)(*(int*)this->pendingEventBitmask + (idx >> 5) * 4) & (1 << (idx & 0x1f))) != 0) {
                        processPendingBit(0);
                    }
                    idx++;
                } while (idx < iVar1);
            }
            finishProcessing(this->vtable);
            return 1;
        }
    } else {
        // second branch: handler non-null, but similar check on other structure
        int stateBase;
        if ((state->stateFlags & 0xFF) < 10) {
            stateBase = (int)(state->handlerArray1);
        } else {
            stateBase = (int)(state->handlerArray2);
        }
        if (*(short*)(stateBase + 0x24) != 0) {  // piVar3[3] becomes offset 12, but here offset 0x24 from stateBase
            processDelayedInitialEvent(this->context);
            int idx = 0;
            if (0 < iVar1) {
                do {
                    if ((*(uint32*)(*(int*)this->pendingEventBitmask + (idx >> 5) * 4) & (1 << (idx & 0x1f))) != 0) {
                        processDelayedPendingBit(0);
                    }
                    idx++;
                } while (idx < iVar1);
            }
            finishDelayedProcessing(this->vtable);
            return 1;
        }
    }
    return 0;
}