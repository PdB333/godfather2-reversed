// FUNC_NAME: NetPacketAllocator::allocatePacket
// Address: 0x00533e70
// This function allocates a network packet from a pool. It checks pool limits, calls a virtual factory method, and updates counters.

class NetPacketAllocator {
public:
    // +0x10: pointer to pool array (array of PoolEntry at +0x30, each 0x24 bytes)
    // Method: allocatePacket(classPool* pool, int poolIndex)
    // Returns pointer to allocated packet or null.
    void* allocatePacket(int pool, int poolIndex) {
        int* poolEntry;          // piVar3
        uint allocResult;        // uVar4
        int checkResult;         // iVar6
        int* localEntry;         // iVar2
        void* allocatedPtr;      // puVar5
        struct {
            int manager;          // param_1
            int pool;             // param_2
            int poolIndex;        // param_3
            char statusFirstByte;
            char statusSecondByte;
        } allocParams;

        poolEntry = *(int**)(pool + 8);
        if (*(int*)(pool + 0xc) != 0 && poolEntry != 0) {
            localEntry = (int*)(*(int*)(manager + 0x10) + 0x30 + poolIndex * 0x24);
            // Check if pool slot is available: either max count is 0 or current count < max,
            // and overall pool flags allow allocation, and overall current count < max.
            if ((*(short*)(localEntry + 3) == 0 || *(short*)(localEntry + 3) < *(short*)(localEntry + 4)) &&
                ((poolEntry[3] & 0x80000000) == 0 && (uint)poolEntry[5] < (uint)poolEntry[6])) {
                
                allocResult = FUN_00533b40();  // Memory allocation function
                checkResult = 0;
                if (allocResult != 0 && (allocResult < 0x40000000 && (checkResult = FUN_004e06d0(allocResult), checkResult == 0))) {
                    return 0;  // Allocation failed or flag cleared
                }

                // Prepare parameters for virtual construction call
                allocParams.manager = manager;
                allocParams.pool = pool;
                allocParams.poolIndex = poolIndex;
                allocParams.statusFirstByte = 0;
                allocParams.statusSecondByte = 0;

                // Virtual call on poolEntry's vtable at offset 0xc
                allocatedPtr = (void*)(**(int(__thiscall***)(void*, int))(*poolEntry + 0xc))(&allocParams, checkResult);

                if ((char)allocParams.pool != '\0') {  // First byte of pool (status)
                    if (allocatedPtr != 0) {
                        (**(void(__thiscall***)(void*, int))allocatedPtr)(0);  // Destructor?? (called with 0)
                    }
                    allocatedPtr = 0;
                }

                if (allocParams.pool == 0) {  // Second byte check? Actually local_c._1_1_ is second byte.
                    // Wait: the code checks local_c._1_1_ == '\0'. Since local_c is pool (int),
                    // this checks if the second byte of pool is zero.
                    // But we have allocParams.pool, which is an int. We need to extract second byte.
                    // To correctly reconstruct, we treat pool as a 4-byte status field.
                    // The virtual call might write a two-byte status into the first two bytes of pool.
                    // We'll handle it with bitwise operations.
                    // For reconstruction, we'll assume the virtual call modifies the status bytes.
                }

                // Reinterpret the status bytes from pool (which is int)
                // The decompiled code:
                // if (local_c._1_1_ == '\0') {
                //    ... success path
                // } else { puVar5 = 0; }
                // We'll implement accordingly.
                // Since we can't directly access bytes easily, we'll cast.
                char* statusBytes = (char*)&allocParams.pool;
                if (statusBytes[1] == '\0') {
                    if ((char)allocParams.pool == '\0') {
                        // Success: update counters and return allocatedPtr
                        if (*(short*)(localEntry + 3) != 0) {
                            // Update some global state (thread-local)
                            uint* globalFlags = (uint*)(*(int*)(*(int*)(__readfsdword(0x2c) + 8) + 4);  // unaff_FS_OFFSET + 0x2c likely __readfsdword(0x2c)
                            // Modify flags at offset based on allocatedPtr
                            uint* flags = (uint*)(globalFlags[8] + *((uint*)allocatedPtr + 4));
                            *flags |= 0x10000000;
                            *(short*)(localEntry + 4) = *(short*)(localEntry + 4) + 1;  // Increment count at +0xe
                        }
                        poolEntry[5]++;  // Increment overall count
                        return allocatedPtr;
                    }
                } else {
                    allocatedPtr = 0;
                }

                if (checkResult != 0) {
                    FUN_004e0700();  // Cleanup function
                }
                return allocatedPtr;
            }
        }
        return 0;
    }
};

// Note: Some details are approximate due to decompilation ambiguity.
// The original code uses FS segment for thread-local storage; reconstructed as __readfsdword.