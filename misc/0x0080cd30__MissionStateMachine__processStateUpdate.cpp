// FUNC_NAME: MissionStateMachine::processStateUpdate
// Address: 0x0080cd30
// This function handles state transitions for a mission state machine.
// It checks the current state (param_5) and performs actions based on mission progress.
// The object at this+0x50 (param_1[0x14]) is the owner entity (e.g., Player or mission object).
// State IDs: 10,11,12,13,14,15,16,17 (mapped from param_5 - 10).

typedef void (__thiscall* VTableFunc1)(void*);
typedef int (__thiscall* VTableFunc2)(void*);
typedef void (__thiscall* VTableFunc3)(void*, int, int, int);
typedef void (__thiscall* VTableFunc4)(void*, int, int, int, float, float);

// Forward declarations (renamed from Ghidra names for clarity)
void playStateTransitionSound(unsigned char oldSubState); // FUN_0080c7f0
void setPlayerControlMode(int mode); // FUN_007ff050
bool isGamePaused(); // FUN_004ac260
void setMissionState(int state); // FUN_007f6420
void playMissionSuccessSound(); // FUN_007fd670
void stopMissionMusic(); // FUN_007fc9f0
void markObjectiveComplete(); // FUN_007f9690
int getPlayerVehicleIndex(); // FUN_00471610
void startCutscene(int* stackData, int zero); // FUN_00408a00
void setCinematicCamera(void* entity, int a, int b, int c, int d, int e); // FUN_00741e20 (simplified)
bool checkGlobalFlag(int flag); // FUN_00690150
bool isMissionAlreadyStarted(); // FUN_007f9710
void* getPlayerEntity(int a, int b); // FUN_006fbc40
void playMissionDialogue(unsigned int soundHash, int a, int b, int c); // FUN_007f96a0
void releasePlayerControl(); // FUN_006fbc70
void setMissionSubState(int state); // FUN_007f63e0
bool checkMissionCompletionConditions(); // FUN_007f7c00
bool isMissionActive(unsigned int missionHash); // FUN_0045eec0
void* checkNPCInteraction(void* entity, unsigned int interactionHash); // FUN_006bc8d0
void triggerDialog(void* npc, int param); // FUN_006f8d40
void cleanUp(); // FUN_0080c700
unsigned char defaultStateHandler(int param_2, int param_3, int param_4, int param_5, int param_6); // FUN_004ac700

// Extern for global pointer (from GTA or EARS engine)
extern int* g_GlobalData; // DAT_012233a0

bool __thiscall MissionStateMachine::processStateUpdate(int param_2, int param_3, int param_4, int state, int param_6)
{
    unsigned char oldSubState = *(unsigned char*)((int)this + 0x55); // m_prevSubState
    unsigned char result = 1; // default return value

    switch(state - 10) // Convert state ID to case index (10->0, 11->1, etc.)
    {
        case 0: // State 10: Enter initial state
        {
            *(unsigned char*)((int)this + 0x55) = 0; // m_subState = 0
            *(unsigned char*)((int)this + 0x54) = 1; // m_flag = true
            playStateTransitionSound(oldSubState);
            setPlayerControlMode(1);
            // Call virtual method on owner (vtable offset 0x164)
            ((VTableFunc1)(*(int*)(*(int*)((int)this + 0x50) + 0x164)))(*(void**)((int)this + 0x50));
            return 1;
        }
        case 1: // State 11: Mission processing
        {
            // Call virtual method on owner (vtable offset 0x164)
            ((VTableFunc1)(*(int*)(*(int*)((int)this + 0x50) + 0x164)))(*(void**)((int)this + 0x50));
            int missionId = *(int*)(*(int*)((int)this + 0x50) + 0x1010);
            
            // Check for specific mission sub-state (0x36)
            if (*(int*)(*(int*)((int)this + 0x50) + 0x1014) == 0x36)
            {
                if (!isGamePaused())
                {
                    setMissionState(6);
                    playMissionSuccessSound();
                    stopMissionMusic();
                    // Call virtual method on owner (vtable offset 0x198)
                    ((VTableFunc1)(*(int*)(*(int*)((int)this + 0x50) + 0x198)))(*(void**)((int)this + 0x50));
                    markObjectiveComplete();
                    
                    int* globalPtr = (int*)(g_GlobalData[1]); // Dereference global pointer
                    int vehicleIndex;
                    if (globalPtr == 0)
                        vehicleIndex = 0;
                    else
                        vehicleIndex = globalPtr - 0x1f30; // Adjust pointer
                    
                    // Call virtual method on owner (vtable offset 0x288) with (5, vehicleIndex, 0)
                    ((VTableFunc3)(*(int*)(*(int*)((int)this + 0x50) + 0x288)))(*(void**)((int)this + 0x50), 5, vehicleIndex, 0);
                    
                    *(unsigned int*)(*(int*)((int)this + 0x50) + 0x1b94) |= 0x40; // Set mission flag
                    
                    int playerVehicle = getPlayerVehicleIndex();
                    int timeout = ((VTableFunc2)(*(int*)(*(int*)((int)this + 0x50) + 0x28c)))(*(void**)((int)this + 0x50));
                    setCinematicCamera(*(void**)((int)this + 0x50), *(unsigned long long*)(playerVehicle + 0x30), *(int*)(playerVehicle + 0x38), 0, timeout);
                    
                    int stackVar = 0;
                    startCutscene(&stackVar, 0);
                    return 1;
                }
                
                if (!checkGlobalFlag(0x52))
                    return 1;
                    
                if (isMissionAlreadyStarted())
                    return 1;
                    
                // Start mission dialogue
                playMissionDialogue(0x95750bca, 0, (int)getPlayerEntity(0,0), 0);
                releasePlayerControl();
                setMissionState(0x52);
                setMissionSubState(0x53);
                return 1;
            }
            
            // For other missions
            if (isGamePaused())
                return 1;
                
            if (!checkMissionCompletionConditions())
                goto missionComplete;
                
            // Check mission IDs
            unsigned int missionHash;
            if (missionId == 0x54)
                missionHash = 0x30eedaf2;
            else if (missionId == 0x56)
                missionHash = 0x6a194d69;
            else if (missionId == 0x58)
                missionHash = 0x5ac3ec71;
            else if (missionId == 0x5a)
                missionHash = 0x93ee5ee8;
            else if (missionId == 0x2e)
            {
                if (isMissionActive(0xa209b0c5))
                    goto missionComplete;
                missionHash = 0xa209b0c5;
                goto checkActive;
            }
            else if (missionId == 0x52)
                missionHash = 0x8b5d9033;
            else
                return 1; // Unknown mission ID
                
            // Check if mission is active
            if (!isMissionActive(missionHash))
                return 1;
                
        missionComplete:
            setMissionState(6);
            playMissionSuccessSound();
            stopMissionMusic();
            // Call virtual method on owner (vtable offset 0x198)
            ((VTableFunc1)(*(int*)(*(int*)((int)this + 0x50) + 0x198)))(*(void**)((int)this + 0x50));
            return 1;
            
        checkActive:
            if (!isMissionActive(missionHash))
                return 1;
            goto missionComplete;
        }
        case 2: // State 12: Idle
        {
            break; // Returns 1
        }
        case 3: // State 13: Enter state with subState=1
        {
            *(unsigned char*)((int)this + 0x55) = 1; // m_subState = 1
            *(unsigned char*)((int)this + 0x54) = 1; // m_flag = true
            playStateTransitionSound(oldSubState);
            setPlayerControlMode(1);
            return 1;
        }
        case 4: // State 14
        case 7: // State 17
        {
            // Check for NPC interaction
            void* npc = checkNPCInteraction(*(void**)((int)this + 0x50), 0x369ac561);
            if (npc != 0 && !checkGlobalFlag(0x30))
            {
                triggerDialog(npc, 0);
                return 1;
            }
            break; // Returns 1
        }
        case 5: // State 15: Transition
        {
            if (*(unsigned char*)((int)this + 0x54) != 0) // m_flag
            {
                cleanUp();
                *(unsigned char*)((int)this + 0x54) = 0; // m_flag = false
                
                if (*(int*)((int)this + 0x50) != 0) // owner exists
                {
                    int somePtr = *(int*)(*(int*)((int)this + 0x50) + 0xff0);
                    if (somePtr != 0)
                    {
                        int* derivedObject = (int*)(somePtr - 0x48);
                        if (derivedObject != 0)
                        {
                            playMissionSuccessSound();
                            stopMissionMusic();
                            setMissionState(6);
                            // Call virtual method on derived object (vtable offset 0x290)
                            ((VTableFunc3)(*(int*)(*derivedObject + 0x290)))(derivedObject, 1, 4, 0);
                        }
                    }
                }
                
                playMissionSuccessSound();
                stopMissionMusic();
                setMissionState(6);
                // Call virtual method on owner (vtable offset 0x290) with (1,4,0)
                ((VTableFunc3)(*(int*)(*(int*)((int)this + 0x50) + 0x290)))(*(void**)((int)this + 0x50), 1, 4, 0);
                // Call virtual method on owner (vtable offset 0x198)
                ((VTableFunc1)(*(int*)(*(int*)((int)this + 0x50) + 0x198)))(*(void**)((int)this + 0x50));
                setMissionState(0x2f);
                return 1;
            }
            break; // Returns 1
        }
        case 6: // State 16: Action during state
        {
            if (*(unsigned char*)((int)this + 0x54) != 0 && // m_flag
                !someConditionCheck() && // FUN_007f47a0 (unknown, assumed external)
                *(unsigned char*)(*(int*)((int)this + 0x50) + 0x1b8c) == 0) // some entity flag
            {
                int vtable = *(int*)this;
                float paramA = 1.0f;
                float paramB = 1.0f;
                float paramC = 0.0f;
                int paramD = 1;
                int paramE = 1;
                int paramF = getSomeParameter(1); // FUN_0071fd90
                
                // Call virtual method on owner (vtable offset 0x2c)
                ((VTableFunc4)(*(int*)(*(int*)(*(int*)((int)this + 0x50)) + 0x2c)))(*(void**)((int)this + 0x50), paramF, paramD, paramE, paramC, paramA, paramB);
                return 1;
            }
            break; // Returns 1
        }
        default:
        {
            result = defaultStateHandler(param_2, param_3, param_4, state, param_6);
        }
    }
    return result;
}