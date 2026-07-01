// FUNC_NAME: GodfatherGameManager::cleanup
void __fastcall GodfatherGameManager::cleanup(GodfatherGameManager* this)
{
    char cVar1;
    uint uVar2;

    // Set vtable pointers for sub-objects (likely initialization, but in cleanup? Possibly re-initialization for shutdown)
    this->field_0 = &PTR_FUN_00d6b350; // +0x00: vtable pointer
    this->field_0x3c = &PTR_LAB_00d6b340; // +0x3c (0xf * 4)
    this->field_0x48 = &PTR_LAB_00d6b33c; // +0x48 (0x12 * 4)
    this->field_0x50 = &PTR_LAB_00d6b338; // +0x50 (0x14 * 4)
    this->field_0x54 = &PTR_LAB_00d6b2d8; // +0x54 (0x15 * 4)
    this->field_0x58 = &PTR_LAB_00d6b270; // +0x58 (0x16 * 4)
    this->field_0x390 = &PTR_LAB_00d6b24c; // +0x390 (0xe4 * 4)
    this->field_0x394 = &PTR_FUN_00d6b238; // +0x394 (0xe5 * 4)
    this->field_0x3a0 = &PTR_LAB_00d6b230; // +0x3a0 (0xe8 * 4)
    this->field_0x1f30 = &PTR_LAB_00d6b218; // +0x1f30 (0x7cc * 4)

    // Free resources if pointers are non-null
    if (this->field_0x315c != 0) { // +0x315c (0xc57 * 4)
        FUN_004df600(); // likely memoryDeallocate or similar
    }
    if (this->field_0x2b80 != 0) { // +0x2b80 (0xae0 * 4)
        FUN_004df600();
    }
    this->field_0x24a4 = this->field_0x24a4 & 0xffffbfff; // +0x24a4 (0x929 * 4): clear a flag

    // Initialize two sub-systems with 'this' as parameter (likely sound or something)
    FUN_008f67c0(0, this);
    FUN_008f67c0(10, this);
    FUN_008938b0(0);

    // Check some global condition (e.g., if we are in a certain mode)
    cVar1 = FUN_00481620();
    if (cVar1 != '\0') {
        FUN_007f9340(0, 0);
        DAT_0112b220 = 0;
        FUN_009c8f10(DAT_0112b21c);
        DAT_0112b21c = 0;
        _DAT_0112b224 = 0;
    }

    // Destroy a series of global objects (likely singletons)
    FUN_004086d0(&DAT_0112a5e0); // destructor / cleanup
    FUN_004086d0(&DAT_0120ea74);
    FUN_004086d0(&DAT_0120e978);
    // ... many similar pairs of destroy then release
    FUN_004086d0(&DAT_0112b914);
    FUN_00408310(&DAT_0112b914);
    // ... (continued)
    // Pattern: for each global, call FUN_004086d0 then FUN_00408310 (destroy + release)
    // We'll list them all with explicit offsets for readability

    // Shorthand for repeated pattern: destroy then release a global object
    #define DESTROY_AND_RELEASE(addr) do { FUN_004086d0(addr); FUN_00408310(addr); } while(0)

    DESTROY_AND_RELEASE(&DAT_0112b914);
    DESTROY_AND_RELEASE(&DAT_0112b51c);
    DESTROY_AND_RELEASE(&DAT_0112b374);
    DESTROY_AND_RELEASE(&DAT_0112b20c);
    DESTROY_AND_RELEASE(&DAT_0112b66c);
    DESTROY_AND_RELEASE(&DAT_0112f4b4);
    DESTROY_AND_RELEASE(&DAT_0112b90c);
    // ... additional release-only calls
    FUN_00408310(&DAT_0112b554);
    FUN_00408310(&DAT_0112b52c);
    FUN_00408310(&DAT_0112b37c);
    FUN_00408310(&DAT_0112b54c);
    DESTROY_AND_RELEASE(&DAT_0112b2b4);
    DESTROY_AND_RELEASE(&DAT_0112dd00);
    FUN_00408310(&DAT_0112b6fc);
    FUN_00408310(&DAT_0112b904);
    FUN_00408310(&DAT_0112b384);
    DESTROY_AND_RELEASE(&DAT_0112b214);
    DESTROY_AND_RELEASE(&DAT_0112b2a4);
    DESTROY_AND_RELEASE(&DAT_0112b534);
    DESTROY_AND_RELEASE(&DAT_0112b41c);
    DESTROY_AND_RELEASE(&DAT_0112b544);
    // Check if another global is present and set flag
    cVar1 = FUN_00402080(&DAT_01129a98);
    if (cVar1 != '\0') {
        DAT_00e50fb5 = 1;
    }
    DESTROY_AND_RELEASE(&DAT_01129a98);
    DESTROY_AND_RELEASE(&DAT_01129aa0);
    DESTROY_AND_RELEASE(&DAT_0112b56c);
    DESTROY_AND_RELEASE(&DAT_0112b39c);
    FUN_00408310(&DAT_0112b564);
    DESTROY_AND_RELEASE(&DAT_01206970);
    FUN_00408310(&DAT_0112b18c);
    FUN_00408310(&DAT_0112b29c);
    DESTROY_AND_RELEASE(&DAT_0112b364);
    DESTROY_AND_RELEASE(&DAT_0112b6f4);
    DESTROY_AND_RELEASE(&DAT_0112b34c);
    DESTROY_AND_RELEASE(&DAT_0112b704);
    DESTROY_AND_RELEASE(&DAT_0112b784);
    DESTROY_AND_RELEASE(&DAT_0112b2c4);
    DESTROY_AND_RELEASE(&DAT_0112b804);
    // Now destroy member sub-object arrays (offsets from this)
    // These appear to be small objects at offsets 0xa3c, 0xa3e, 0xa40 (each 4 bytes? but using 4-byte offset)
    // Actually param_1 + 0xa3c is pointer arithmetic on uint*, so it's (this + 0xa3c) which is offset in bytes = 0xa3c * 4 = 0x28F0
    DESTROY_AND_RELEASE(this + 0xa3c); // at +0x28f0
    DESTROY_AND_RELEASE(this + 0xa3e); // at +0x28f8
    DESTROY_AND_RELEASE(this + 0xa40); // at +0x2900
    DESTROY_AND_RELEASE(&DAT_0112b524);

    // Handle state member
    if (this->field_0x2498 != 0x12) { // +0x2498 (0x926 * 4)
        FUN_00464a10(*(undefined1*)(this + 0x926)); // treat as byte? weird cast
    }
    FUN_00440020(this + 0x7cc); // +0x1f30, some sub-object cleanup
    FUN_00625030(); // global cleanup
    FUN_0079d560(0);
    // Release many member fields (likely an array of pointers)
    #define RELEASE_OFFSET(off) FUN_00408310(this + (off))
    RELEASE_OFFSET(0xba7);
    RELEASE_OFFSET(0xba9);
    RELEASE_OFFSET(0xbad);
    RELEASE_OFFSET(0xbab);
    RELEASE_OFFSET(0xbaf);
    RELEASE_OFFSET(0xbb1);
    RELEASE_OFFSET(0xbb3);
    RELEASE_OFFSET(0xbb5);
    RELEASE_OFFSET(2999); //  0xbb7
    RELEASE_OFFSET(0xbb9);
    RELEASE_OFFSET(0xbbb);
    RELEASE_OFFSET(0xbbd);
    RELEASE_OFFSET(0xbbf);
    RELEASE_OFFSET(0xbc1);
    RELEASE_OFFSET(0xbc3);
    RELEASE_OFFSET(0xbc5);
    RELEASE_OFFSET(0xbc7);
    RELEASE_OFFSET(0xbc9);
    RELEASE_OFFSET(0xbcb);
    RELEASE_OFFSET(0xbcd);
    RELEASE_OFFSET(0xbcf);
    RELEASE_OFFSET(0xbd1);
    RELEASE_OFFSET(0xbd3);
    RELEASE_OFFSET(0xbd5);
    RELEASE_OFFSET(0xbd7);
    RELEASE_OFFSET(0xbd9);
    RELEASE_OFFSET(0xbdb);
    RELEASE_OFFSET(0xbdd);
    RELEASE_OFFSET(0xbdf);
    RELEASE_OFFSET(0xbe1);
    RELEASE_OFFSET(0xbe3);
    RELEASE_OFFSET(0xbe5);
    RELEASE_OFFSET(0xbe7);
    RELEASE_OFFSET(0xbe9);
    RELEASE_OFFSET(0xbeb);
    RELEASE_OFFSET(0xbed);
    RELEASE_OFFSET(0xbef);
    RELEASE_OFFSET(0xbf1);
    RELEASE_OFFSET(0xbf3);
    RELEASE_OFFSET(0xbf5);
    RELEASE_OFFSET(0xbf7);
    RELEASE_OFFSET(0xbf9);
    RELEASE_OFFSET(0xbfb);
    RELEASE_OFFSET(0xbfd);
    RELEASE_OFFSET(0xbff);
    RELEASE_OFFSET(0xc01);
    RELEASE_OFFSET(0xc03);
    RELEASE_OFFSET(0xc05);
    RELEASE_OFFSET(0xc07);
    RELEASE_OFFSET(0xc09);
    RELEASE_OFFSET(0xc0b);
    RELEASE_OFFSET(0xc0d);
    RELEASE_OFFSET(0xc0f);
    RELEASE_OFFSET(0xc11);
    RELEASE_OFFSET(0xc13);
    RELEASE_OFFSET(0xc15);
    RELEASE_OFFSET(0xc17);
    #undef RELEASE_OFFSET

    DESTROY_AND_RELEASE(&DAT_0113109c);

    // Handle a managed object (possibly network stream)
    if (this->field_0x2c70 != 0) { // +0x2c70 (0xb1c * 4)
        FUN_005e6820(this->field_0x2c70, 0, 0);
        FUN_005e6660(this->field_0x2c70);
        this->field_0x2c70 = 0;
        *((uint8_t*)(this + 0xb1d)) = 0; // clear byte
    }

    // Call virtual destructor on some object
    if (this->field_0x24a8 != 0) { // +0x24a8 (0x92a * 4)
        (*(code**)*(uint32_t**)this->field_0x24a8)[0x01](1); // call method at vtable index 1
    }

    // Handle timer or sequence manager
    uVar2 = FUN_00424c90(this->field_0x2494); // +0x2494 (0x925 * 4)
    if (uVar2 < 4) {
        FUN_00424ee0(this->field_0x2494, this + 0xb24);
        FUN_00424ee0(this->field_0x2494, this + 0xb44);
        FUN_00424ee0(this->field_0x2494, this + 0xb64);
    }

    // Release member pointer with some function
    if (this->field_0x2918 != 0) { // +0x2918 (0xa46 * 4)
        FUN_004035f0(this->field_0x2918, 0x1ff, this + 0xf); // param: pointer, size, array?
    }

    // Clean up multiple sub-objects via FUN_004daf90 (likely a release/destroy function)
    #define CLEANUP_MEMBER(offset) do { if (this->field_##offset != 0) FUN_004daf90(this + (offset)); } while(0)
    CLEANUP_MEMBER(0xc70);
    CLEANUP_MEMBER(0xc6e);
    CLEANUP_MEMBER(0xc6c);
    CLEANUP_MEMBER(0xc6a);
    CLEANUP_MEMBER(0xc5d);
    #undef CLEANUP_MEMBER

    // Nullify pointers and clear associated data
    if (this->field_0x315c != 0) { // +0x315c (0xc57 * 4)
        *((uint32_t*)(this->field_0x315c + 8)) = 0;
        this->field_0x315c = 0;
    }
    if (this->field_0x3148 != 0) { // +0x3148 (0xc52 * 4)
        *((uint32_t*)(this->field_0x3148 + 8)) = 0;
        this->field_0x3148 = 0;
    }
    if (this->field_0x3104 != 0) { // +0x3104 (0xc41 * 4)
        FUN_004daf90(this + 0xc41);
    }
    FUN_0084e3e0(); // global cleanup
    if (this->field_0x30c0 != 0) { // +0x30c0 (0xc30 * 4)
        FUN_004daf90(this + 0xc30);
    }
    this->field_0x30b0 = &PTR_LAB_00e39ea4; // +0x30b0 (0xc2c * 4): set vtable? 
    if (this->field_0x30a4 != 0) { // +0x30a4 (0xc29 * 4)
        FUN_004daf90(this + 0xc29);
    }
    if (this->field_0x3064 != 0) { // +0x3064 (0xc19 * 4)
        FUN_004daf90(this + 0xc19);
    }
    if (this->field_0x2e24 != 0) { // +0x2e24 (0xb89 * 4)
        FUN_004daf90(this + 0xb89);
    }

    // Three calls to same cleanup function (maybe clearing a stack?)
    FUN_006d9d30();
    FUN_006d9d30();
    FUN_006d9d30();

    if (this->field_0x2b80 != 0) { // +0x2b80 (0xae0 * 4)
        *((uint32_t*)(this->field_0x2b80 + 8)) = 0;
        this->field_0x2b80 = 0;
    }
    FUN_00897170(); // global cleanup
    FUN_007981e0();
    FUN_007dc190();

    // More member cleanup
    if (this->field_0x2528 != 0) { // +0x2528 (0x94a * 4)
        FUN_004daf90(this + 0x94a);
    }
    if (this->field_0x24fc != 0) { // +0x24fc (0x93f * 4)
        FUN_004daf90(this + 0x93f);
    }
    this->field_0x24c4 = &PTR_LAB_00d60cdc; // +0x24c4 (0x931 * 4): set vtable
    if (this->field_0x24bc != 0) { // +0x24bc (0x92f * 4)
        FUN_004daf90(this + 0x92f);
    }
    if (this->field_0x24b4 != 0) { // +0x24b4 (0x92d * 4)
        FUN_004daf90(this + 0x92d);
    }
    if (this->field_0x24ac != 0) { // +0x24ac (0x92b * 4)
        FUN_004daf90(this + 0x92b);
    }
    if (this->field_0x2190 != 0) { // +0x2190 (0x864 * 4)
        FUN_004daf90(this + 0x864);
    }

    FUN_004aee30(); // final global cleanup
    FUN_008079c0();
    return;
}