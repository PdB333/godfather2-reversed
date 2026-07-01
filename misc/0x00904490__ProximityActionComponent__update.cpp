// FUNC_NAME: ProximityActionComponent::update

// Reconstructed from Ghidra decompile at 0x00904490
// Likely part of EA EARS engine, The Godfather 2 (2008)

typedef unsigned int uint;
typedef unsigned char byte;

// External globals
extern float gCurrentTime; // DAT_01205228 - global frame time

// Forward declarations of called functions (inferred)
void* __fastcall getComponentByHash(void* component, uint hash); // FUN_00446100 - returns a pointer to a component from a container
void __fastcall debugOutput(uint value); // FUN_0044b210 - debug/log function
void* __fastcall getTargetTransform(); // FUN_00471610 - returns pointer to a transform (position) of some target, e.g., player or enemy
void __fastcall pushAction(void* action, int actionType, uint actionParam, int unk3, int unk4); // FUN_00440590 - triggers an action
void __fastcall deactivateEvent(void* event); // FUN_004088c0 - decrement reference count or deactivate a timer/event

class ProximityActionComponent {
public:
    // Offset: +0x3c - event/timer handle (used in deactivation)
    // +0x50 - component container 1 (e.g., list of child actions)
    // +0x60 - component container 2
    // +0x70 - state A (0 or 0x48 = inactive)
    // +0x78 - state B (0 or 0x48 = inactive)
    // +0x90 - near action pointer (closest distance)
    // +0x98 - far action pointer (farthest distance)
    // +0xa0 - medium action pointer (intermediate distance)
    // +0xa8 - min distance threshold for near zone
    // +0xac - max distance threshold (boundary between medium and far)
    // +0xb0 - current zone index (0=near, 1=medium, 2=far)
    // +0xb4 - action parameter (hash or ID)
    // +0xb8 - cooldown time between actions
    // +0xbc - action counter (decremented each call; triggers deactivation when <= 0)
    // +0xc0 - last action timestamp (set to current time when action triggered)
    // +0xc4 - flags (bit 2: allow zone change)

    void __thiscall update() {
        float currentTime = gCurrentTime;
        float lastActionTime = *(float*)((char*)this + 0xc0);
        
        // Check if cooldown period has passed
        if (lastActionTime < 0.0f || *(float*)((char*)this + 0xb8) <= currentTime - lastActionTime) {
            // Evaluate states A and B
            if ((*(int*)((char*)this + 0x70) == 0 || *(int*)((char*)this + 0x70) == 0x48) &&
                getComponentByHash((char*)this + 0x50, 0) != nullptr) {
                uint result = 0;
                byte bResult = ((uint (__thiscall*)(void*, uint, uint*))(*(void***)getComponentByHash((char*)this + 0x50, 0))[4])(
                    0x38523fc3, &result); // hash constant: likely a string hash for "check distance"
                if (bResult) {
                    debugOutput(result);
                }
            }
            if ((*(int*)((char*)this + 0x78) == 0 || *(int*)((char*)this + 0x78) == 0x48) &&
                getComponentByHash((char*)this + 0x60, 0) != nullptr) {
                uint result = 0;
                byte bResult = ((uint (__thiscall*)(void*, uint, uint*))(*(void***)getComponentByHash((char*)this + 0x60, 0))[4])(
                    0x38523fc3, &result);
                if (bResult) {
                    debugOutput(result);
                }
            }
            
            // If both states are active (not 0 or 0x48)
            if (*(int*)((char*)this + 0x70) != 0 && *(int*)((char*)this + 0x70) != 0x48 &&
                *(int*)((char*)this + 0x78) != 0 && *(int*)((char*)this + 0x78) != 0x48) {
                
                // Get positions of two targets
                void* target1 = getTargetTransform();
                void* target2 = getTargetTransform();
                // Offsets 0x30, 0x34, 0x38 are x,y,z in transform
                float dx = *(float*)((char*)target2 + 0x30) - *(float*)((char*)target1 + 0x30);
                float dy = *(float*)((char*)target2 + 0x34) - *(float*)((char*)target1 + 0x34);
                float dz = *(float*)((char*)target2 + 0x38) - *(float*)((char*)target1 + 0x38);
                float distSq = dx*dx + dy*dy + dz*dz;
                
                int newZoneIndex;
                void* actionPtr;
                if (distSq <= *(float*)((char*)this + 0xac)) {
                    if (distSq < *(float*)((char*)this + 0xa8)) {
                        // Near zone
                        actionPtr = (void*)((char*)this + 0x90);
                        newZoneIndex = 0;
                    } else {
                        // Medium zone
                        actionPtr = (void*)((char*)this + 0xa0);
                        newZoneIndex = 1;
                    }
                } else {
                    // Far zone
                    actionPtr = (void*)((char*)this + 0x98);
                    newZoneIndex = 2;
                }
                
                bool bTriggerAction = true;
                if ((*(byte*)((char*)this + 0xc4) & 2) != 0) { // Check flag
                    if (newZoneIndex == *(int*)((char*)this + 0xb0)) {
                        bTriggerAction = false; // Zone unchanged
                    } else {
                        *(int*)((char*)this + 0xb0) = newZoneIndex; // Update zone
                    }
                }
                
                // Reset cooldown timer
                *(float*)((char*)this + 0xc0) = currentTime;
                
                if (actionPtr != nullptr && bTriggerAction) {
                    pushAction(actionPtr, 0, *(uint*)((char*)this + 0xb4), 0, 0);
                    // Decrement action counter; if <=0, deactivate the event at +0x3c
                    int counter = *(int*)((char*)this + 0xbc);
                    if (counter > 0) {
                        *(int*)((char*)this + 0xbc) = counter - 1;
                        if (counter - 1 < 1) {
                            deactivateEvent((char*)this + 0x3c);
                        }
                    }
                }
            }
        }
        // else: cooldown not expired, skip
    }
};