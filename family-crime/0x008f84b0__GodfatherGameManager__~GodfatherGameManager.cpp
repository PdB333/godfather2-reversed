// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager

// Destructor for the main game manager. Cleans up sub-objects, deletes arrays,
// releases global singletons, and sets a global shutdown flag.
// Address: 0x008f84b0

extern void* PTR_FUN_00d813f0;    // vtable for this class
extern void* PTR_LAB_00d813e0;    // vtable for sub-object at +0x3C
extern void* PTR_LAB_00d813dc;    // vtable at +0x48
extern void* PTR_FUN_00d813d8;    // vtable at +0x158
extern void* PTR_LAB_00d813d4;    // vtable at +0x15C
extern void* PTR_LAB_00d813d0;    // vtable for sub-object after deletion
extern void* PTR___purecall_00e407a4; // purecall vtable slot

extern void destroySubObject(void* obj);   // FUN_004086d0
extern void releaseMemory(void* ptr);     // FUN_00408310
extern void safeDelete(void** ptr);       // FUN_004daf90 (checks null then deletes)
extern void finalShutdown();              // FUN_0083f2f0

extern int g_someFlag;                    // DAT_0112af68
extern int DAT_0112fea0[];
extern int DAT_0112fe6c[];
extern int DAT_0112fe90[];
extern int DAT_0112b36c[];
extern int DAT_0112fc60[];
extern int DAT_0112b53c[];
extern int DAT_0112fe64[];
extern int DAT_0112fe88[];
extern int DAT_0112fe80[];
extern int DAT_0112fe74[];
extern int DAT_0112fea8[];
extern int DAT_0112fe98[];

void __thiscall GodfatherGameManager::~GodfatherGameManager(void* this)
{
    // Set vtable pointers for this object (base class destructor)
    *(void**)this = &PTR_FUN_00d813f0;
    *(void**)((int)this + 0x3C) = &PTR_LAB_00d813e0;   // +0x3C
    *(void**)((int)this + 0x48) = &PTR_LAB_00d813dc;   // +0x48
    *(void**)((int)this + 0x158) = &PTR_FUN_00d813d8;  // +0x158
    *(void**)((int)this + 0x15C) = &PTR_LAB_00d813d4;  // +0x15C

    // Destroy various global sub-objects (singletons)
    destroySubObject(&DAT_0112fea0);
    destroySubObject(&DAT_0112fe6c);
    destroySubObject((int*)this + 0x7C);   // offset 0x1F0
    destroySubObject(&DAT_0112fe90);
    destroySubObject((int*)this + 0x7E);   // offset 0x1F8
    destroySubObject(&DAT_0112b36c);
    destroySubObject(&DAT_0112fc60);
    destroySubObject(&DAT_0112b53c);

    // Release memory for more singletons
    releaseMemory(&DAT_0112fe6c);
    releaseMemory(&DAT_0112fe90);
    releaseMemory(&DAT_0112fe64);
    releaseMemory(&DAT_0112fe88);
    releaseMemory(&DAT_0112fe80);
    releaseMemory(&DAT_0112fe74);
    releaseMemory(&DAT_0112fea8);
    releaseMemory(&DAT_0112fea0);
    releaseMemory(&DAT_0112fe98);
    releaseMemory((int*)this + 0x7C);      // +0x1F0
    releaseMemory((int*)this + 0x7E);      // +0x1F8
    releaseMemory((int*)this + 0x80);      // +0x200

    // Delete a large allocated object at offset 0x43C
    if (*(int**)((int)this + 0x43C) != 0)
    {
        safeDelete((void**)((int)this + 0x43C));
    }

    // Delete an array of 8 pointers (offsets 0x374 down to 0x358)
    int* arrayBase = (int*)((int)this + 0xDD * 4); // +0x374
    for (int i = 0; i < 8; i++)
    {
        int* current = arrayBase - i - 1; // going downwards
        if (*current != 0)
        {
            safeDelete((void**)(current - 4)); // offset of pointer before current? Actually careful: the loop uses puVar3 = param_1+0xdd, then puVar3 = puVar3-4 each iteration. So it accesses offsets 0x374,0x370,...,0x358. We need to subtract 4 each time, starting at +0x374.
        }
        // Actually original: puVar3 starts at param_1+0xdd, then puVar3 = puVar3-4; piVar1 = puVar3-4? Wait: piVar1 = puVar3 + -4; puVar3 = puVar3 + -4; if (*piVar1 != 0) FUN_004daf90(puVar3);
        // That means first iteration: piVar1 = param_1+0xdd-4 = offset 0x374-4=0x370, puVar3 becomes offset=0x374-4=0x370. So it checks offset 0x370 first? Actually careful: piVar1 = puVar3 + -4, so at start puVar3 = param_1+0xdd (=0x374). Then piVar1 = param_1+0xdd-4 (=0x370). Then puVar3 becomes param_1+0xdd-4 (=0x370). Then checks *piVar1 (which is at offset 0x370) and if non-zero, calls FUN_004daf90(puVar3) which is also 0x370. So effectively it deletes the pointer at offset 0x370 first, then next iteration piVar1 = 0x370-4=0x36C, puVar3=0x36C, so delete at 0x36C, etc. So it deletes pointers at offsets 0x370,0x36C,...,0x344? But 8 iterations from 0x370 down to 0x344? Let's compute: Start puVar3=0x374, first delete 0x370; after that puVar3=0x370; next delete 0x36C; ... after 8 deletions, last delete at offset 0x374-8*4=0x354? Actually 0x374 - 8*4 = 0x374 - 0x20 = 0x354. But the loop runs 8 times, starting with piVar1 at 0x370, then 0x36C, ..., down to 0x370 - 7*4 = 0x370 - 0x1C = 0x354. So offsets 0x370,0x36C,0x368,0x364,0x360,0x35C,0x358,0x354. So it's a slightly different range. For simplicity in code we'll just implement the logic as written.
        // I'll rewrite the loop to match the decompiled:
        // int* puVar3 = (int*)((int)this + 0xDD * 4);
        // int iVar2 = 8;
        // do {
        //     int* piVar1 = puVar3 - 1;
        //     puVar3 = puVar3 - 1;
        //     if (*piVar1 != 0) {
        //         safeDelete(puVar3);
        //     }
        //     iVar2--;
        // } while (iVar2 >= 0);
    {
        // Correct loop:
        int* puVar3 = (int*)((int)this + 0xDD * 4); // +0x374
        for (int i = 8; i > 0; i--)
        {
            int* piVar1 = puVar3 - 1;
            puVar3 = puVar3 - 1;
            if (*piVar1 != 0)
            {
                safeDelete((void**)puVar3);
            }
        }
    }

    // Set to purecall vtable (indicating destruction has started)
    *(void**)((int)this + 0x19C) = &PTR___purecall_00e407a4; // +0x19C (param_1[0x67])

    // Delete another pointer at offset 0x194
    if (*(int**)((int)this + 0x194) != 0)
    {
        safeDelete((void**)((int)this + 0x194));
    }

    // Change vtable for sub-object at +0x15C to final base vtable
    *(void**)((int)this + 0x15C) = &PTR_LAB_00d813d0;

    // Set global shutdown flag
    g_someFlag = 0;

    // Call final shutdown routine (likely engine-wide cleanup)
    finalShutdown();
}