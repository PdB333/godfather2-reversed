// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x006d1310
// Role: Constructor for the GodfatherGameManager singleton. Sets up multiple vtable pointers
//       and stores the instance globally at DAT_0112a874 (likely g_pGameManager).
void __fastcall GodfatherGameManager::GodfatherGameManager(void* thisPtr)
{
    // Call base class constructor (likely EARS::Framework::Object or similar)
    reinterpret_cast<void (__fastcall*)(void*)>(0x004737b0)(thisPtr);

    // Initialize secondary vtable at offset +0x58 (then later overwritten)
    *reinterpret_cast<void**>(reinterpret_cast<char*>(thisPtr) + 0x58) = reinterpret_cast<void*>(0x00d5f2f0);

    // Store the global instance pointer
    g_pGameManager = thisPtr; // DAT_0112a874

    // Set the primary vtable at offset 0x00
    *reinterpret_cast<void**>(thisPtr) = reinterpret_cast<void*>(0x00d5f32c);

    // Set additional vtable pointers at class-specific offsets
    *reinterpret_cast<void**>(reinterpret_cast<char*>(thisPtr) + 0x3C) = reinterpret_cast<void*>(0x00d5f31c); // +0x3C
    *reinterpret_cast<void**>(reinterpret_cast<char*>(thisPtr) + 0x48) = reinterpret_cast<void*>(0x00d5f318); // +0x48
    *reinterpret_cast<void**>(reinterpret_cast<char*>(thisPtr) + 0x50) = reinterpret_cast<void*>(0x00d5f314); // +0x50

    // Overwrite the secondary vtable at +0x58 with the final pointer
    *reinterpret_cast<void**>(reinterpret_cast<char*>(thisPtr) + 0x58) = reinterpret_cast<void*>(0x00d5f310);
}