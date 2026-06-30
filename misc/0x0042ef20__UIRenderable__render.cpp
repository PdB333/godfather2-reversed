// FUNC_NAME: UIRenderable::render

// Reconstructed from Ghidra at 0x0042ef20
// This function appears to render a UI element with optional child elements,
// handling state transitions and music/sound updates based on flags and sub-state.

// Object layout (relative to this):
// +0x04: byte mState (1 = active/visible?)
// +0x06: byte mSubState (0 = normal, non-zero = alternate indexing)
// +0x07: byte mIndex (index into global music/texture tables)
// +0x08: byte mFlags (bit 0x10 = force music change flag)
// +0x26: char mImageIdA (first image/texture ID)
// +0x27: char mImageIdB (second image/texture ID)
// +0x30: int mPositionX (or float?)
// +0x34: int mPositionY (or float?)
// +0x3c: short mWidth
// +0x40: short mHeight
// +0x42: short mSomething (padding/alpha?)
// +0x50: int *mpInternalData (pointer used to derive additional index)
// +0x64: int mImageArray[?] (array of image IDs, indexed by mSubState)
// +0x6c: int *mpExtraImage (optional extra image ID pointer)

// Global pointers (hypothetical, must match):
extern void *g_pEngineCore;       // DAT_01205750
extern void *g_pVideoManager;     // DAT_012058e8
extern int g_currentMusicId;      // DAT_01205838
extern int g_musicTableA[];       // DAT_01164010 (indexed by mIndex*8)
extern int g_musicTableB[];       // DAT_01164014 (indexed by mIndex*8)
extern int g_someGlobalFlag;      // DAT_011da800
extern int g_someOtherFlag;       // DAT_011da804
extern int g_forceFlag;           // unaff_EBX high byte (maybe g_altRenderFlag)

void UIRenderable::render(void) {
    byte subState;
    byte index;
    bool useAltMusic;
    int *musicEntry;
    int altIndex;
    int imageId;

    // State check: only render if mState == 1
    if (*(char *)(this + 4) == 1) {
        // Obtain pointer from internal data
        musicEntry = *(int **)(this + 0x50);
        FUN_00459b30();  // unknown, maybe reset render state?

        // Determine alternate index for image array
        if (*(char *)(this + 6) == 0) {
            altIndex = 0;
        } else {
            altIndex = (uint)*(byte *)(musicEntry + 0x2d); // +0x2d offset in musicEntry struct
        }

        // Check force music change flag
        if ((*(byte *)(this + 8) & 0x10) != 0) {
            FUN_00459c20(&DAT_011f6ab0);  // push/pop some state?
        }

        // If sub-state is 0, handle input disabling?
        if (*(char *)(this + 6) == 0) {
            FUN_00613440(1);
            FUN_00613180();
        }

        // Get music/sound ID from global table using mIndex
        index = *(byte *)(this + 7);
        musicEntry = (int *)(&g_musicTableA + (uint)index * 2); // each entry is 8 bytes? Actually read as int from base+index*8, so g_musicTableA[index*2] (int array)
        // But the decompile does: &DAT_01164010 + (uint)*(byte *)(in_EAX + 7) * 8, so it points to a DWORD inside that 8-byte block.
        // We treat musicEntry as pointer to int at that address.
        int soundId = *musicEntry; // actually first int in 8-byte block

        useAltMusic = (index == 0xb); // seems to set a flag if index == 0xb

        if (g_currentMusicId != soundId) {
            // Call engine virtual function at offset 0x15c (likely setMusic or playSound)
            (*(void(__thiscall *)(void *, int))(*DAT_01205750 + 0x15c))(DAT_01205750, soundId);
            g_currentMusicId = soundId;
        }

        // Select image ID: use alternate index if applicable, else first element
        imageId = *(int *)(this + 100 + altIndex * 4); // offset 0x64
    } else {
        // mState != 1
        if ((*(byte *)(this + 8) & 0x10) == 0) {
            // Normal path: use second music table entry
            index = *(byte *)(this + 7);
            if ((index == 0xb) || (index == 0xc)) {
                useAltMusic = true;
            } else {
                useAltMusic = false;
            }
            musicEntry = (int *)(&g_musicTableB + (uint)index * 2);
            int soundId = *musicEntry;
        } else {
            // Force flag set: use first music table and push state
            FUN_00459c20(&DAT_011f6ab0);
            index = *(byte *)(this + 7);
            useAltMusic = (index == 0xb);
            musicEntry = (int *)(&g_musicTableA + (uint)index * 2);
            int soundId = *musicEntry;
        }

        if (g_currentMusicId != *musicEntry) {
            (*(void(__thiscall *)(void *, int))(*DAT_01205750 + 0x15c))(DAT_01205750, *musicEntry);
            g_currentMusicId = *musicEntry;
        }
        imageId = *(int *)(this + 100); // only first image
    }

    // Draw primary image
    FUN_0060c8d0(0, imageId, *(char *)(this + 0x26), 0, 0, 0, 1);

    // Draw optional secondary image (if pointer non-null)
    if (*(int *)(this + 0x6c) != 0) {
        FUN_0060c8d0(1, *(int *)(this + 0x6c), *(char *)(this + 0x27), 0, 0, 0, 1);
    }

    // Notify video manager of alt music state (maybe cursor or screen effect)
    (*(void(__thiscall *)(void *, bool))(*DAT_012058e8 + 0x38))(DAT_012058e8, useAltMusic);

    // Render rectangle/overlay with position, size, etc.
    FUN_0060cb70(
        *(short *)(this + 0x3c),   // width
        useAltMusic,                // bool (passed as int)
        *(int *)(this + 0x34),     // Y position
        *(int *)(this + 0x30),     // X position
        *(short *)(this + 0x40),   // height
        *(short *)(this + 0x42)    // unknown
    );

    // Post-render state management for secondary image
    if (*(int *)(this + 0x6c) != 0) {
        if (g_someGlobalFlag != 1) {
            (*(void(__thiscall *)(void *, int, int))(*DAT_01205750 + 0x198))(DAT_01205750, 1, 1);
            g_someGlobalFlag = 1;
        }
        if (g_someOtherFlag != 0) {
            (*(void(__thiscall *)(void *, int, int, int, int))(*DAT_01205750 + 400))(DAT_01205750, 1, 0, 0, 0);
            g_someOtherFlag = 0;
        }
    }

    // Force flag from global register (maybe set by earlier code)
    if ((char)((uint)unaff_EBX >> 0x18) != '\0') {
        FUN_00613570(1);
    }

    return;
}