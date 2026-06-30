// FUNC_NAME: AptMovie::relocateFrameData

// Function address: 0x005b9560
// Purpose: Relocates frame data offsets within an AptMovie object by adding
// a delta offset to all internal pointers. Handles frame arrays, control
// structures, action streams, and frame label records.
// Called when copying frame data between memory buffers.

// Forward declarations for helper functions
extern void adjustActionStreamActions(int actionStream, int offset, int srcBase, int dstBase);
extern void insertFrameLabelAction(int frameLabelList, int labelOffset, uint* labelRecord);

// Assertion macro (simplified from the game's debug system)
#define APT_ASSERT(cond, msg) do { if (!(cond)) { __debugbreak(); } } while(0)

// Internal structures (based on decompiled offset accesses)
#pragma pack(push, 1)
struct AptFrame {
    int numControls;            // +0x00: number of controls in this frame
    int* controls;              // +0x04: pointer to array of control pointer offsets (each 4 bytes)
};

struct AptControl {
    int type;                   // +0x00: control type (1=action, 2=frameLabel, 3=placeObject2, 8=initAction)
};

struct AptActionControl {       // type 1
    int type;                   // +0x00 (1)
    int* aActionStream;         // +0x04: pointer to action stream offset
};

struct AptFrameLabelControl {   // type 2
    int type;                   // +0x00 (2)
    char* szLabel;              // +0x04: pointer to label string offset
};

struct AptPlaceObject2Control { // type 3
    int type;                   // +0x00 (3)
    // ... padding to 0x34 ...
    char* szName;               // +0x34: pointer to name string offset
    int* pActions;              // +0x3c: pointer to event actions structure offset
};

struct AptEventActions {
    int numEventActions;        // +0x00: number of event actions
    int* aEventActions;         // +0x04: pointer to array of event action offsets (each 0xC bytes)
};

struct AptEventAction {
    int* aActionStream;         // +0x00: pointer to action stream offset
    // +0x04, +0x08: possibly other fields (unused in this function)
};

struct AptInitActionControl {   // type 8
    int type;                   // +0x00 (8)
    // +0x04: unknown
    int* aActionStream;         // +0x08: pointer to action stream offset
};

struct AptFrameLabelRecord {    // 8 bytes allocated for FUN_005baa90 input
    int flags;                  // +0x00: upper bits set to 0x8007? TODO
    short unknown;              // +0x02
    int frameIndex;             // +0x04: frame index to label
};
#pragma pack(pop)

void AptMovie::relocateFrameData(int offset, int srcBase, int dstBase)
{
    // this->fields:
    // [0] -> numFrames (int)
    // [1] -> frames (AptFrame*)
    // [2] -> frameLabelList (void*) — must be null initially

    int* thisPtr = (int*)this;

    // Assert that frameLabelList is null (line 0x14)
    APT_ASSERT(thisPtr[2] == 0, "!phLabels");

    // Allocate a new frame label list (size 0x48 = 72 bytes)
    uint* labelList = (uint*)malloc(0x48);
    if (labelList) {
        labelList[0] = 2;          // Unknown constant
        labelList[1] = 0;          // Next pointer? Zeroed
        *(int**)(labelList + 2) = labelList + 4; // Circular pointer at offset+8
        labelList[4] = 0;          // Clear two qwords
        labelList[5] = 0;
        *(uint64*)(labelList + 6) = 0;
    }
    thisPtr[2] = (int)labelList;

    // Assert that frames pointer is within valid range (< 0xFFFFF)
    APT_ASSERT((uint)thisPtr[1] < 0xFFFFF, "(unsigned)(aFrames) < 0xfffff");

    // Offset the frames pointer itself
    if (thisPtr[1] != 0) {
        thisPtr[1] = thisPtr[1] + offset;
    }

    AptFrame* frames = (AptFrame*)thisPtr[1];
    int numFrames = thisPtr[0];

    for (int i = 0; i < numFrames; i++) {
        // For each frame, offset the controls pointer
        AptFrame* frame = &frames[i];
        APT_ASSERT((uint)frame->controls < 0xFFFFF, "(unsigned)(aFrames[i].apControls) < 0xfffff");

        if (frame->controls != 0) {
            frame->controls = (int*)((int)frame->controls + offset);
        }

        // Process each control in the frame
        for (int j = 0; j < frame->numControls; j++) {
            int* controlPtr = (int*)frame->controls[j]; // Original pointer
            if (controlPtr != 0) {
                // Apply offset to the control pointer itself
                frame->controls[j] = (int)((int)frame->controls[j] + offset);
                controlPtr = (int*)frame->controls[j]; // Update local reference
            }

            // Now process control contents based on type
            switch (controlPtr[0]) {
                case 1: { // Action control
                    AptActionControl* actionCtrl = (AptActionControl*)controlPtr;
                    APT_ASSERT((uint)actionCtrl->aActionStream < 0xFFFFF,
                        "(unsigned)(aFrames[i].apControls[j]->action.actions.aActionStream) < 0xfffff");
                    if (actionCtrl->aActionStream != 0) {
                        actionCtrl->aActionStream = (int*)((int)actionCtrl->aActionStream + offset);
                    }
                    adjustActionStreamActions((int)actionCtrl->aActionStream, offset, srcBase, dstBase);
                    break;
                }
                case 2: { // Frame label control
                    AptFrameLabelControl* labelCtrl = (AptFrameLabelControl*)controlPtr;
                    APT_ASSERT((uint)labelCtrl->szLabel < 0xFFFFF,
                        "(unsigned)(aFrames[i].apControls[j]->frameLabel.szLabel) < 0xfffff");
                    if (labelCtrl->szLabel != 0) {
                        labelCtrl->szLabel = (char*)((int)labelCtrl->szLabel + offset);
                    }
                    // Create a label record and insert into list
                    uint* labelRecord = (uint*)malloc(8);
                    if (labelRecord) {
                        labelRecord[0] = (labelRecord[0] & 0xFFFF8007) | 0x0007; // Set low bits and high bit?
                        *(short*)(labelRecord + 1) = 0;
                        labelRecord[0] |= 0x8000; // Set another bit
                        labelRecord[1] = i;       // Frame index
                    }
                    insertFrameLabelAction(thisPtr[2], (int)labelCtrl->szLabel, labelRecord);
                    break;
                }
                case 3: { // PlaceObject2 control
                    AptPlaceObject2Control* placeCtrl = (AptPlaceObject2Control*)controlPtr;
                    APT_ASSERT((uint)placeCtrl->szName < 0xFFFFF,
                        "(unsigned)(aFrames[i].apControls[j]->placeObject2.szName) < 0xfffff");
                    if (placeCtrl->szName != 0) {
                        placeCtrl->szName = (char*)((int)placeCtrl->szName + offset);
                    }
                    APT_ASSERT((uint)placeCtrl->pActions < 0xFFFFF,
                        "(unsigned)(aFrames[i].apControls[j]->placeObject2.pActions) < 0xfffff");
                    if (placeCtrl->pActions != 0) {
                        placeCtrl->pActions = (int*)((int)placeCtrl->pActions + offset);
                    }
                    // Process event actions within pActions
                    if (placeCtrl->pActions != 0) {
                        AptEventActions* eventActions = (AptEventActions*)placeCtrl->pActions;
                        APT_ASSERT((uint)eventActions->aEventActions < 0xFFFFF,
                            "(unsigned)(pActions->aEventActions) < 0xfffff");
                        if (eventActions->aEventActions != 0) {
                            eventActions->aEventActions = (int*)((int)eventActions->aEventActions + offset);
                        }
                        for (int k = 0; k < eventActions->numEventActions; k++) {
                            // Each event action entry is 0xC bytes
                            int* eventActionPtr = (int*)((int)eventActions->aEventActions + k * 0xC);
                            int* actionStreamOffset = (int*)*eventActionPtr; // Offset from eventAction base?
                            // Actually the structure: eventActions->aEventActions points to array of offsets to event action structs.
                            // Wait, the decompiled code does: iVar10 + 8 + piVar9[1] where piVar9 = pActions (AptEventActions).
                            // piVar9[1] = aEventActions pointer (already offset). Then iVar10 is k*0xC.
                            // So we access (aEventActions + k*0xC) which yields the action stream pointer.
                            // Let's re-derive: piVar9[1] = aEventActions offset array. For each k, offset = aEventActions[k*0xC/4]? Actually the code does:
                            // iVar11 = *(int *)(iVar10 + 8 + piVar9[1]);
                            // iVar10 = k*0xC.
                            // So base = piVar9[1] (address of array of offsets), then at base + 8 + k*0xC there is an int (action stream offset).
                            // That suggests the array elements are not just of size 0xC? Or maybe the structure has padding.
                            // For simplicity, we follow the decompiled logic explicitly.
                            // We'll just process the action stream pointer as found at that offset.
                            int* actionStreamBase = (int*)((int)eventActions->aEventActions + 8 + k * 0xC);
                            int actionStreamOffset = *actionStreamBase;
                            if (actionStreamOffset != 0) {
                                *actionStreamBase = actionStreamOffset + offset;
                            }
                            adjustActionStreamActions((int)*actionStreamBase, offset, srcBase, dstBase);
                        }
                    }
                    break;
                }
                case 8: { // Init action control
                    AptInitActionControl* initCtrl = (AptInitActionControl*)controlPtr;
                    APT_ASSERT((uint)initCtrl->aActionStream < 0xFFFFF,
                        "(unsigned)(aFrames[i].apControls[j]->initAction.actions.aActionStream) < 0xfffff");
                    if (initCtrl->aActionStream != 0) {
                        initCtrl->aActionStream = (int*)((int)initCtrl->aActionStream + offset);
                    }
                    adjustActionStreamActions((int)initCtrl->aActionStream, offset, srcBase, dstBase);
                    break;
                }
                default:
                    break;
            }
        }
    }
}