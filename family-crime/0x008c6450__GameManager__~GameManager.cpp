// FUNC_NAME: GameManager::~GameManager
void __fastcall GameManager::~GameManager(GameManager* this)
{
    int iVar1;
    // Save and restore some state for nested destruction
    int savedState;

    // Set vtable to destructor vtable (likely for base class or cleanup)
    this->vtable = &PTR_FUN_00d7bcf8;
    // Pointers to other vtables for sub-objects? Possibly for virtual destructor chains.
    this->field_0x3C = &PTR_LAB_00d7bce8; // +0x3C = 0xF *4
    this->field_0x48 = &PTR_LAB_00d7bce4; // +0x48 = 0x12*4

    // Destroy base object or singleton references
    GLOBAL::baseShutdown(&DAT_0112fe38);  // FUN_004086d0
    GLOBAL::baseCleanup(&DAT_0112f940);   // FUN_00408310

    // Destroy some sub-system with argument 1 (maybe a flag)
    SubSystem::shutdown(1);               // FUN_008c63b0

    // Save and restore a global state for iteration?
    savedState = GlobalManager::getState(0); // FUN_0084ab30(0)
    // Clear two lists (or arrays) at offsets +0x114 and +0x108 (0x45*4, 0x42*4)
    DynamicList::clear(&this->list_0x114); // FUN_008be330(this+0x45)
    DynamicList::clear(&this->list_0x108); // FUN_008be330(this+0x42)
    GlobalManager::restoreState(savedState); // FUN_0084ab30(savedState)

    // Destroy a series of sub-objects (pairs of construct/destruct? Actually patterns show construct then destruct on the same address)
    // These are likely placement new/destroy for embedded members
    // The addresses are offsets from this: 0x7b,0x7d,0x7f,0x81,0x83,0x85,0x87,0x89
    // Each pair: first construct (FUN_004086d0) then destruct (FUN_00408310)
    // But in a destructor, we only need to destruct. However the decompiler shows both calls. Possibility: the first is a no-op or a different function? 
    // Since it's a destructor, we might only call destruct on each sub-object. But the code explicitly calls construct then destruct. Could be a bug in decompilation? 
    // Or maybe it's a pattern: construct on a temporary copy, then destruct? Unclear. We'll follow the exact sequence.
    // Actually, the sequence is:
    // FUN_004086d0(&DAT_012069c4);  // global sub-object?
    // then four sub-objects: construct, destruct, etc.
    // Let's assume these are initialization/finalization pairs for sub-objects that need to be properly destructed.
    // But since this is a destructor, we might be calling destructors on sub-objects that were previously constructed. The extra construct call might be a quirk of the decompiler (maybe they are overloaded functions). 
    // I'll name them as "initSubObject" and "destroySubObject" for clarity.

    // Destruct a global sub-object
    SubObject::destroy(&DAT_012069c4); // FUN_00408310 on DAT_012069c4? Actually order: FUN_004086d0(&DAT_012069c4); then later for each: FUN_004086d0(..), FUN_00408310(..). So first is construct on global, then for each of the following: construct then destruct.
    // For clarity, I'll write the exact sequence as in the decompiled.

    // For each of the 8 sub-objects (offsets 0x7b,0x7d,0x7f,0x81,0x83,0x85,0x87,0x89)
    // But note: the first two are called on param_1+0x7b and param_1+0x7d with both functions.
    // Then the later ones only call one of the two? Look: 
    // FUN_004086d0(param_1+0x7b); FUN_00408310(param_1+0x7b);
    // FUN_004086d0(param_1+0x7d); FUN_00408310(param_1+0x7d);
    // FUN_004086d0(param_1+0x7f); FUN_00408310(param_1+0x7f);
    // FUN_004086d0(param_1+0x81); FUN_00408310(param_1+0x81);
    // FUN_00408310(param_1+0x83); // only destruct
    // FUN_004086d0(param_1+0x85); FUN_00408310(param_1+0x85);
    // FUN_00408310(param_1+0x87); // only destruct
    // FUN_00408310(param_1+0x89); // only destruct
    // So some have both, some only destruct. This might be because some sub-objects need to be re-initialized before destruction? Or it's a pattern for clearing reference counts? Hard to say. I'll keep as is.

    // I'll create a macro or inline for each pair.

    // Actually, to keep code clean, I'll define helper functions based on the called addresses.
    // Let's assume FUN_004086d0 is "initSubObject" and FUN_00408310 is "destroySubObject".

    // Global sub-object init/destroy
    initSubObject(&DAT_012069c4);
    destroySubObject(&DAT_012069c4);

    // Sub-objects at offset 0x7b, 0x7d, 0x7f, 0x81
    initSubObject(&this->subObj_0x1EC); // +0x7b*4 = 0x1EC
    destroySubObject(&this->subObj_0x1EC);
    initSubObject(&this->subObj_0x1F4); // +0x7d*4 = 0x1F4
    destroySubObject(&this->subObj_0x1F4);
    initSubObject(&this->subObj_0x1FC); // +0x7f*4 = 0x1FC
    destroySubObject(&this->subObj_0x1FC);
    initSubObject(&this->subObj_0x204); // +0x81*4 = 0x204
    destroySubObject(&this->subObj_0x204);

    // Sub-object at 0x83 (0x20C) - only destroy
    destroySubObject(&this->subObj_0x20C);

    // Sub-objects at 0x85, 0x87, 0x89
    initSubObject(&this->subObj_0x214); // +0x85*4 = 0x214
    destroySubObject(&this->subObj_0x214);
    destroySubObject(&this->subObj_0x21C); // +0x87*4 = 0x21C
    destroySubObject(&this->subObj_0x224); // +0x89*4 = 0x224

    // Check if there's a dynamically allocated array at offset 0x8c (0x230)
    iVar1 = this->field_0x230; // param_1[0x8c]
    if (iVar1 != 0) {
        // Decrement some global counter
        GlobalCounter::decrement(); // FUN_008928f0
        // Free the memory
        Memory::free(iVar1);        // FUN_009c8eb0
    }

    // Access a global variable (singleton pointer)
    iVar1 = SingletonManager::gInstance; // DAT_01129904
    // Finalize this object
    this->finalize(); // FUN_008c71d0(this)
    // Release a COM interface or similar at offset 0x22 (0x88)
    Interface::release(this->field_0x88); // FUN_0043c200

    // Global singleton state check
    if (*(int*)(iVar1 + 0x28) == 1) {
        gGlobalFlag = 0; // DAT_0112f938 = 0;
    }

    // Free additional dynamically allocated members
    if (this->field_0x1A4 != 0) { // param_1[0x69] *4 = 0x1A4
        Memory::free(this->field_0x1A4); // FUN_009c8f10
    }
    if (this->field_0x18C != 0) { // param_1[99]? Wait 99*4 = 0x18C, but parameter index 99 is param_1[99] = 0x18C
        Memory::free(this->field_0x18C);
    }
    // Call some global cleanup
    GlobalCleanup::run(); // FUN_008c2020
    // Free more members
    if (this->field_0x124 != 0) { // param_1[0x49] = 0x124
        Memory::free(this->field_0x124);
    }
    iVar1 = this->field_0x114; // param_1[0x45] = 0x114
    if (iVar1 != 0) {
        Memory::free(iVar1);
    }
    if (this->field_0x108 != 0) { // param_1[0x42] = 0x108
        Memory::free(this->field_0x108);
    }

    // Call deletion functions via function pointers for owned objects
    DeleteObjectIfExist(this->field_0xBC, this->field_0xC8); // offsets 0x2f and 0x32: object at 0xBC (0x2f*4), method at 0xC8 (0x32*4)
    DeleteObjectIfExist(this->field_0xAC, this->field_0xB8); // 0x2b and 0x2e
    DeleteObjectIfExist(this->field_0x9C, this->field_0xA8); // 0x27 and 0x2a
    DeleteObjectIfExist(this->field_0x8C, this->field_0x98); // 0x23 and 0x26
    DeleteObjectIfExist(this->field_0x6C, this->field_0x78); // 0x1b and 0x1e

    // Final global cleanup
    FinalCleanup::execute(); // FUN_0046c640
}

// Inline helper for calling destructor function pointer
inline void DeleteObjectIfExist(void* obj, void* funcPtr) {
    if (obj != 0) {
        ((void(*)(void*))funcPtr)(obj);
    }
}