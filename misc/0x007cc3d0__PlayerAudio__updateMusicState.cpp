// FUNC_NAME: PlayerAudio::updateMusicState

#include <cstdint>

// Forward declarations of called functions
extern float __stdcall FUN_0046fd30(void* ptr); // Get some float value (e.g., speed, timer)
extern void __stdcall FUN_007223b0(float value); // Adjust something based on the float
extern void __stdcall FUN_007f63e0(uint32_t id); // Play sound effect with ID
extern int __stdcall FUN_00625050(uint32_t id1, int param2); // Get object or manager
extern bool __stdcall FUN_00800b60(); // Check some condition (e.g., game paused, menu open)

// Globals (from .data section)
extern float DAT_00e44748; // Multiplier constant
extern float _DAT_00e52f90; // Threshold constant

// External constant (string/ID)
extern const char* DAT_00ca9bea; // Probably a sound bank or event name

class PlayerAudio {
public:
    // Offsets within this object
    float field_0x194;                          // +0x194: speed, timer, or intensity value
    void* field_0x1b4;                         // +0x1b4: pointer to AudioComponent subobject (base at -0x48)
    uint32_t flags;                            // +0x1d0: bit flags

    // Virtual table layout of the subobject at field_0x1b4
    struct AudioComponentVTable {
        // offset 0x10: (bool __thiscall)(uint32_t id, int* outResult)
        bool (__thiscall* queryState)(void* self, uint32_t id, int* outResult);
        // ... other virtual functions ...
        // offset 0x164: (void __thiscall)()
        void (__thiscall* triggerEvent)(void* self);
    };

    // Virtual table of the external manager (sound system)
    struct SoundManagerVTable {
        // offset 0x2c: (void __thiscall)(const char* event, int a, int b, int c, float d, float e)
        void (__thiscall* playEvent)(void* self, const char* eventName, int a, int b, int c, float volume, float pitch);
    };

    void updateMusicState() {
        AudioComponentVTable* audioVtbl = nullptr;
        if (field_0x1b4 != nullptr) {
            audioVtbl = reinterpret_cast<AudioComponentVTable*>(
                *reinterpret_cast<int*>(static_cast<char*>(field_0x1b4) - 0x48));
        }

        // Check if the audio component is in a "active" state (hash 0x369ac561)
        if (audioVtbl != nullptr) {
            int dummy;
            bool isActive = audioVtbl->queryState(static_cast<char*>(field_0x1b4) - 0x48, 0x369ac561, &dummy);
            if (isActive) {
                // Get the sound manager from global hash
                void* soundManager = reinterpret_cast<void*>(FUN_00625050(0x187b7e2b, 0));
                if (soundManager != nullptr && !FUN_00800b60()) {
                    float currentValue = FUN_0046fd30(&field_0x194); // e.g., speed or timer
                    float scaledValue = currentValue * DAT_00e44748;
                    if (_DAT_00e52f90 < __builtin_fabsf(scaledValue)) {
                        FUN_007223b0(scaledValue);
                        // Check bit 8 of flags at offset 0x23a (but in the context of audioVtbl object? Actually the code uses piVar2[0x23a] which we set to this, so it's this->something? Wait careful.
                        // In the decompiler, after the condition, piVar2 was set to (cVar1) ? this : 0. So piVar2 = this (PlayerAudio*). So piVar2[0x23a] accesses this[0x23a], i.e., *(uint*)((char*)this + 0x8e0). That might be a different field? The offset calculation: piVar2 is an int*, so piVar2[0x23a] = *(int*)((int*)piVar2 + 0x23a) = *(int*)((char*)piVar2 + 0x8e8). That's far beyond typical object size, probably incorrect. Let's re-evaluate.
                        // The decompiler might have mis-typed piVar2. Actually the code does:
                        // piVar2 = (int *)(-(uint)(cVar1 != '\0') & unaff_ESI);
                        // unaff_ESI is a leftover register; likely it was the original this pointer. So piVar2 becomes this when condition is true.
                        // Then it checks piVar2[0x23a]. But that would be at offset 0x8e8 from this. Possibly it's a typo or the decompiler used wrong pointer type. 
                        // We'll assume it's accessing a field of the audio component? Actually the object at field_0x1b4 - 0x48 is the audio component base. Its vtable offset 0x10 was called. The function then checks piVar2[0x23a] where piVar2 is this. That seems inconsistent. 
                        // There might be a misreading. Let's look at the original: 
                        // piVar2 = (int *)(-(uint)(cVar1 != '\0') & unaff_ESI);
                        // The unaff_ESI is actually the original this (param_1). So piVar2 = param_1 if cVar1 != 0 else 0.
                        // Then it checks ((uint)piVar2[0x23a] >> 8 & 1) == 0. That's (this->someFieldAtOffset0x8e8? too large.
                        // But note that param_1+0x1b4 is a pointer, and we subtract 0x48 to get audio component. The audio component might be a base class of PlayerAudio? Possibly PlayerAudio inherits from AudioComponent? Then the this pointer might be the same as the audio component? That could explain: if PlayerAudio inherits from AudioComponent, then the offset -0x48 might be to adjust to the base? Actually the code does:
                        // piVar2 = field_0x1b4 - 0x48. So it's getting parent of the field_0x1b4. That parent might be the PlayerAudio itself? Then piVar2 would be the same as this. That would make sense: field_0x1b4 is a pointer to a subobject (maybe the audio component derived class). The parent object (PlayerAudio) is at field_0x1b4 - 0x48 (sizeof something). So the audio component vtable is at that offset. Then piVar2 as used later is the same as this (since it's the parent object). So piVar2[0x23a] is actually this[0x23a] but offset 0x8e8 is still huge. Perhaps the array index is wrong? Could be piVar2[0x23a] is not an index but a field at offset 0x8e8? That seems too large. 
                        // Another possibility: unaff_ESI is actually the address of the audio component subobject, not this. Then piVar2 becomes audio component if condition is true. Then checking piVar2[0x23a] would be at offset 0x8e8 within the audio component. That is plausible given audio component might have large arrays.
                        // Given the ambiguity, we'll implement as the code suggests but with a comment.
                        // We'll treat piVar2 as the audio component base (the object that has the vtable).
                        // So we store the audio component pointer from earlier.
                        // Actually the correct reconstruction: after the virtual call, piVar2 is set to (cVar1) ? audioComponentBase : 0. So we have:
                        void* audioComponentBase = (isActive) ? static_cast<char*>(field_0x1b4) - 0x48 : nullptr;
                        // Then check audioComponentBase[0x23a]? We'll cast to uint32_t*.
                        uint32_t* fieldAtLargeOffset = reinterpret_cast<uint32_t*>(audioComponentBase) + 0x23a; // offset 0x8e8
                        if (audioComponentBase && (*fieldAtLargeOffset >> 8 & 1) == 0) {
                            FUN_007f63e0(0x48);
                            flags |= 0x4000;
                        }
                        // Then play sound using the sound manager
                        SoundManagerVTable* smVtbl = *reinterpret_cast<SoundManagerVTable**>(soundManager);
                        smVtbl->playEvent(soundManager, DAT_00ca9bea, 1, 1, 0, 1.0f, 1.0f);
                        flags |= 0x2000;
                        // Trigger event on the audio component
                        AudioComponentVTable* acVtbl = *reinterpret_cast<AudioComponentVTable**>(audioComponentBase);
                        acVtbl->triggerEvent(audioComponentBase);
                    }
                }
            }
        }
    }
};