// FUNC_NAME: ResourceManager::findOrLoadAsset
// Function address: 0x005ae7e0
// Role: Central resource loading/dispatch function that attempts to find an asset
//       by various methods (hash, type-specific loaders) based on request parameters.
//       param_5 points to an AssetRequest struct with string at offset +8.
//       param_7 acts as a flag (0 = eager load, nonzero = try existing/cached first).
//       param_2 and param_3 likely represent a range (e.g., container iterators) for
//       batch lookup. Returns a resource handle (uint*).

extern uint* g_nullResourceHandle; // DAT_0119cbbc – sentinel null handle

// Extern helper functions (guessed names based on context)
extern uint* hashLookup(const char* name); // FUN_005bc230
extern uint* allocateResource(int size, const char* name); // FUN_005bb050
extern int getResourceManagerCount(); // FUN_005b1b90
extern bool checkAssetType1(); // FUN_0059c5c0
extern void enterAssetType1Mode(); // FUN_0059c3b0
extern bool checkAssetType2(); // FUN_0059c500
extern uint* convertStringToHandle(uint* data); // FUN_0059c450
extern uint* processConvertedHandle(uint* converted, uint* data); // FUN_005ab7b0
extern bool checkAssetType3(); // FUN_005a8030
extern void enterAssetType3Mode(); // FUN_005a78b0
extern uint* loadFromStream3(uint* data); // FUN_005bb610
extern bool checkAssetType4(); // FUN_005abcb0
extern void enterAssetType4Mode(); // FUN_005abb50
extern bool checkAssetType5(); // FUN_005a3c40
extern void enterAssetType5Mode(); // FUN_005a3a40
extern void appendLengthString(); // FUN_005a3a40 (actually string concat with "length"?)
extern uint* handleLengthString(uint* data); // FUN_005b8800 – returns handle for "length" type
extern bool checkAssetType6(); // FUN_005a80f0
extern void enterAssetType6Mode(); // FUN_005a7950
extern uint* loadFromStream6(); // FUN_005ac170
extern bool checkAssetType7(); // FUN_005a7eb0
extern void enterAssetType7Mode(); // FUN_005a7580
extern uint* loadFromStream7(); // FUN_005bbd50
extern bool checkAssetType8(); // FUN_005a3fc0
extern uint* loadFromStream8(uint* data, const char* name); // FUN_005b77c0
extern uint* fallbackLoadResource(uint* start, int unknown, uint param6, int param7, int finalFlag); // FUN_005aea60 – recursive fallback

struct AssetRequest {
    int someCount;   // +0x00
    int pad[1];      // +0x04
    const char* name; // +0x08
};

// Reconstructed function
uint* ResourceManager::findOrLoadAsset(int thisPtr, uint* param_2, uint* param_3, int param_4, AssetRequest* request, uint param_6, int param_7) {
    uint* foundHandle = nullptr;
    const char* assetName = nullptr;
    uint* tempHandle = nullptr;

    // If we have a valid element to look up and an existing handle is not already found,
    // try a hash-based lookup using the asset name from request.
    if (param_2 != param_3 && param_3 != nullptr) {
        foundHandle = hashLookup(request->name); // FUN_005bc230
    }

    // param_7 == 0: eager loading path – try to load if not found via hash
    if (param_7 == 0) {
        if (foundHandle == nullptr) {
            // If there is an in_EAX (likely a previous result) and the resource manager
            // still has room (field at +0x604 > 0), allocate a new resource.
            // (In_EAX is not explicitly defined in the signature; it may come from the caller.)
            int in_EAX; // assumed register variable
            if (in_EAX != 0 && *(int*)(thisPtr + 0x604) > 0) {
                int resourceSize = request->name ? (*(int*)(request->name)) : 0; // not exactly, but kept logic similar
                // Actually piVar1[2] is request->name; the original uses a size argument from some function.
                // We'll approximate: allocate a resource with size from a helper.
                int sizeFromHelper = FUN_005b1b90(); // get some allocation size
                foundHandle = allocateResource(sizeFromHelper + 4, request->name); // FUN_005bb050
            }
        } else {
            // If param_3 is not null, jump to the type-checking chain.
            if (param_3 != nullptr) {
                goto typeCheckChain;
            }
        }
    } else {
        // param_7 != 0: try to avoid loading if possible, but still try hash lookup first.
        if (foundHandle == nullptr && *(int*)(thisPtr + 0x604) > 0) {
            int sizeFromHelper = FUN_005b1b90();
            tempHandle = allocateResource(sizeFromHelper + 4, request->name);
            if (tempHandle != nullptr) {
                return tempHandle;
            }
            foundHandle = nullptr;
        }
        if (param_3 == nullptr) {
            goto afterTypeCheck; // if no element to check, skip the type chain
        }
        // Check a first asset type
        if (checkAssetType1(0)) { // FUN_0059c5c0(0)
            enterAssetType1Mode(); // FUN_0059c3b0
            if (checkAssetType8()) { // FUN_005a3fc0
                int nameLen = request->name ? strlen(request->name) : 0;
                enterAssetType1Mode(); // another call
                enterAssetType5Mode(); // FUN_005a3f20
                foundHandle = loadFromStream8(param_3, request->name); // FUN_005b77c0
                if (foundHandle != nullptr) {
                    return foundHandle;
                }
            }
            // If type8 not available, continue to normal type chain
        }
        // ... (the original code falls through to type check chain label)
    }

typeCheckChain:
    // Only if param_3 is non-null and request->someCount > 0 and certain bit test passes
    if (param_3 != nullptr && request->someCount > 0 && ((*param_3 >> 0xf) & 1) == 0) {
        // Series of asset type checks
        if (!checkAssetType1(0)) { // first type
            // type 1 false -> try type2
            if (!checkAssetType2()) { // FUN_0059c500
                // type2 false -> try type3
                if (!checkAssetType3()) { // FUN_005a8030
                    // type3 false -> try type4
                    if (!checkAssetType4()) { // FUN_005abcb0
                        // type4 false -> try type5
                        if (!checkAssetType5()) { // FUN_005a3c40
                            // type5 false -> try type6
                            if (!checkAssetType6()) { // FUN_005a80f0
                                // type6 false -> try type7
                                if (!checkAssetType7()) { // FUN_005a7eb0
                                    goto afterTypeCheck; // none matched
                                }
                                // type7 true
                                enterAssetType7Mode(); // FUN_005a7580
                                tempHandle = loadFromStream7(); // FUN_005bbd50
                            } else {
                                // type6 true
                                enterAssetType6Mode(); // FUN_005a7950
                                tempHandle = loadFromStream6(); // FUN_005ac170
                            }
                        } else {
                            // type5 true
                            const char* nameStr = request->name;
                            enterAssetType5Mode(); // FUN_005a3a40
                            if (__stricmp(nameStr, "length") == 0) {
                                tempHandle = handleLengthString(param_3); // FUN_005b8800
                            } else {
                                tempHandle = g_nullResourceHandle; // DAT_0119cbbc
                            }
                        }
                    } else {
                        // type4 true
                        enterAssetType4Mode(); // FUN_005abb50
                        goto afterTypeCheck; // note: in original, after this it jumps to another branch
                    }
                } else {
                    // type3 true
                    enterAssetType3Mode(); // FUN_005a78b0
                    tempHandle = loadFromStream3(param_3); // FUN_005bb610
                }
            } else {
                // type2 true
                uint* converted = convertStringToHandle(param_3); // FUN_0059c450
                tempHandle = processConvertedHandle(converted, param_3); // FUN_005ab7b0
            }
        } else {
            // type1 true
            const char* nameStr = request->name;
            enterAssetType1Mode(); // FUN_0059c3b0
            enterAssetType5Mode(); // FUN_005a3f20
            tempHandle = loadFromStream8(param_3, nameStr); // FUN_005b77c0
        }
        if (tempHandle != nullptr) {
            return tempHandle;
        }
    }

afterTypeCheck:
    // If we have a param_3 element, decide what to return.
    if (param_3 != nullptr) {
        if (request->someCount == 0) {
            return param_3; // return the element itself as handle
        }
        if (foundHandle != nullptr) {
            return foundHandle;
        }
    }

    // Fallback: if param_4 is 0, return the global null handle.
    if (param_4 == 0) {
        return g_nullResourceHandle;
    }

    // Otherwise, call a fallback loader (possibly recursive).
    return fallbackLoadResource(param_2, 0, param_6, param_7, 1); // FUN_005aea60
}