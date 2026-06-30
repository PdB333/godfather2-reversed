// FUNC_NAME: MissionObjective::activateObjective

// 0x006f66f0 - MissionObjective activation logic. Checks if already active, optionally marks complete, then initializes from mission data.
// Fields:
//   +0x23 (0x8C): byte flags (bit 2 set on activation)
//   +0x25-0x28 (0x94-0xA0): array of 4 pointers to sub-objectives
//   +0x36 (0xD8): some source field copied to +0x1e
//   +0x39 (0xE4): activation state (0=inactive, 1=active, 2=completed)
//   +0x3a (0xE8): completion state (set to 2)
//   +0x3b (0xEC): milestone count?
//   +0x3d (0xF4): flags (bit0=activated, bit1=subobjective state, bit2=completed by data)
//   +0x1e (0x78): destination field (likely time or index)
//   +0xf (0x3C): data buffer for copying (size 0x8000)

#include <cstdint>

// Forward declarations for external functions
extern void* FUN_0043b870(uint32_t handle);
extern void FUN_0043a750(void* ptr);
extern void FUN_006f17c0(void* subObjArray);
extern void FUN_006ccd30(void* unknown);
extern uint32_t FUN_006f62b0(void* missionData);
extern void FUN_00408900(void* dest, void* src, uint32_t size);

// External globals
extern uint32_t DAT_0112a9fc;   // Some global handle (e.g., AudioManager)
extern uint32_t DAT_012069c4;   // Data pointer source
extern void* DAT_012233a0;      // Probably singleton SimManager or MissionManager

class MissionObjective
{
public:
    // Virtual table offsets:
    // +0x1c: bool isComplete() const;
    // +0x24: void setComplete(bool);
    // +0x2c: void update();

    uint8_t   flags_0x23;        // +0x23 (0x8C): bit 2 = activated
    void*     subObj[4];         // +0x25 (0x94) to +0x28 (0xA0)
    uint32_t  sourceField_0x36;  // +0x36 (0xD8)
    int32_t   state_0x39;        // +0x39 (0xE4): 0=inactive, 1=active, 2=completed
    int32_t   completionState_0x3a; // +0x3a (0xE8)
    int32_t   milestoneCount_0x3b;  // +0x3b (0xEC)
    uint32_t  flags_0x3d;        // +0x3d (0xF4): bit0, bit1, bit2
    uint32_t  destField_0x1e;    // +0x1e (0x78)
    // +0xf (0x3C): buffer[0x2000] (size 0x8000)
    uint8_t   dataBuffer[0x2000]; // At offset 0x3C

    // Vtable pointer is at offset 0
    // The following calls invoke vtable functions:
    // (*(code **)(*this + 0x1c))() 
    // (*(code **)(*this + 0x24))(1)
    // (*(code **)(*this + 0x2c))()
    // We'll call them via member function pointers or direct calls.

    bool isComplete() const
    {
        return (*(bool (__thiscall *)(const MissionObjective*))((uint32_t*)this)[0x1c/4])(this);
    }
    void setComplete(bool val)
    {
        (*(void (__thiscall *)(MissionObjective*, bool))((uint32_t*)this)[0x24/4])(this, val);
    }
    void update()
    {
        (*(void (__thiscall *)(MissionObjective*))((uint32_t*)this)[0x2c/4])(this);
    }
};

// Reconstructed function
int __thiscall MissionObjective::activateObjective(MissionObjective* thisObj, void* missionData)
{
    bool bResult = false;
    uint32_t iVar2 = 0;

    // If already active (completionState_0x3a != 0), handle completion/update
    if (thisObj->completionState_0x3a != 0)
    {
        if (thisObj->isComplete())
        {
            thisObj->setComplete(true);
        }
        thisObj->update();
    }

    // Get global singleton pointer (likely SimManager) and adjust
    int* globalPtr = *(int**)((char*)DAT_012233a0 + 4);
    int iVar5;
    if (globalPtr == nullptr)
    {
        iVar5 = 0;
    }
    else
    {
        iVar5 = *globalPtr - 0x1f30; // Offset to some inner object
    }

    // Activation condition: not already active, global valid, mission data provided
    if ((thisObj->state_0x39 == 0) && (iVar5 != 0) && (missionData != nullptr))
    {
        // Get audio manager from global handle
        iVar2 = (uint32_t)FUN_0043b870(DAT_0112a9fc);
        void* audioMgr = (void*)iVar2;

        // If any sub-objective is active and bit1 of flags is clear, stop/clear them
        if ((thisObj->subObj[0] != nullptr || thisObj->subObj[1] != nullptr ||
             thisObj->subObj[2] != nullptr || thisObj->subObj[3] != nullptr) &&
            ((thisObj->flags_0x3d >> 1) & 1) == 0)
        {
            FUN_0043a750((char*)audioMgr + 0xb0); // Likely stop objective sound
            FUN_006f17c0(thisObj->subObj);        // Reset or deactivate sub-objectives
            thisObj->flags_0x3d |= 2;             // Set bit 1
        }

        thisObj->milestoneCount_0x3b = 0;

        // Call twice (maybe start/stop sound or event)
        FUN_006ccd30((void*)iVar5);
        FUN_006ccd30((void*)iVar5);

        thisObj->flags_0x3d |= 1;              // Set bit 0 (activated)
        thisObj->destField_0x1e = thisObj->sourceField_0x36; // Copy source to dest
        thisObj->flags_0x23 |= 4;              // Set bit 2

        // Determine completion state from data
        if (*(char*)((char*)missionData + 0x99) == '\0')
        {
            thisObj->state_0x39 = 2;            // Completed
            thisObj->flags_0x3d |= 4;           // Set bit 2
        }
        else
        {
            thisObj->state_0x39 = 1;            // Active
            thisObj->flags_0x3d &= ~4;          // Clear bit 2
        }

        // Call mission start handler
        FUN_006f62b0(missionData);
        thisObj->completionState_0x3a = 2;

        // Copy additional data if available
        if (DAT_012069c4 != 0)
        {
            FUN_00408900(thisObj->dataBuffer, (void*)DAT_012069c4, 0x8000);
        }

        bResult = true;
    }

    // Weird return side effect on flags (decompiler artifact; just return bool)
    // uint32_t uVar3 = ((iVar2 >> 8) << 8) | (thisObj->flags_0x23 ^ (uint8_t)bResult) & 0xFF;
    // thisObj->flags_0x23 = (uint8_t)(uVar3 & 0xFF) ^ (uint8_t)uVar3? Not essential.
    
    return bResult ? 1 : 0;
}