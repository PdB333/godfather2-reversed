// FUNC_NAME: GameCondition::evaluate
// Function address: 0x006ebff0
// Role: Central condition evaluator for game logic. Takes a condition ID and parameters, returns boolean.
// Called from many condition-specific functions (e.g., 0x006ecf70, 0x006ed0a0, etc.)

#include <cstdint>

// Forward declarations of called functions (these would be declared properly in headers)
extern "C" {
    uint32_t FUN_0043b870();                // global state initializer?
    uint32_t FUN_0078af40();                // input related?
    uint32_t FUN_0078b010();                // input related?
    uint32_t FUN_0071f820();                // time/event function?
    uint32_t FUN_0071fa00();                // time/event function?
    uint32_t FUN_0071fa50();                // time/event function?
    uint32_t FUN_00898330(int32_t index);   // get some attribute/skill level?
    uint32_t FUN_007e80c0();                // returns bool (byte)
    uint32_t FUN_006eb670();                // returns uint (maybe time or distance)
    uint32_t FUN_006ebfb0();                // another condition check (returns pointer)
    int32_t  FUN_0072f370();                // returns int (maybe bool or count)
    uint32_t FUN_00730210();                // returns uint (maybe bool)
    uint32_t FUN_007f7c50();                // returns bool
    uint32_t FUN_00690150();                // returns bool
    int32_t  FUN_006bc8b0(int32_t param);   // returns pointer to object (given offset)
    uint32_t FUN_006eb940();                // returns bool
    uint32_t FUN_006eb8b0();                // returns bool
    uint32_t FUN_00782ce0();                // returns bool
    uint32_t FUN_0072ff30(int32_t param);   // returns uint (maybe bool)
    int32_t  FUN_006ad7f0(int32_t param);   // returns pointer to something (maybe character)
    int32_t  FUN_009a9460();                // returns pointer
    int32_t  FUN_00705ab0();                // returns int (maybe state)
    int32_t  FUN_007049a0();                // returns int (maybe bool)
    uint32_t FUN_00736300();                // returns uint (maybe bool)
    int32_t  FUN_007351c0();                // returns int (maybe state)
    uint32_t FUN_006eb790();                // returns bool
    uint32_t FUN_0090b180();                // returns bool
    int32_t  FUN_006ebfd0();                // returns int
    uint32_t FUN_008bf540();                // returns uint (maybe current time)
    int32_t  FUN_008e62c0();                // returns pointer
    int32_t  FUN_0077dd80();                // returns int (maybe count)
    void     FUN_0045ca00(void*);           // UI debug function
    void     FUN_0045c400(void*, void*);    // UI debug function
    void     FUN_0045cac0(void*);           // UI debug function
    uint32_t FUN_007cc340();                // returns bool
}

// Global data references
extern uint32_t DAT_01205224;               // some global timer
extern uint32_t DAT_012233a0;               // some global pointer? (used as array of pointers)
extern uint32_t DAT_0112ff88[7];            // debug arrays (size based on usage)
extern uint32_t DAT_0112ffb4;              // etc.

uint32_t GameCondition::evaluate(
    [[maybe_unused]] uint32_t unused_param,  // possible 'this'? not used
    int32_t conditionID,
    int32_t* conditionParams          // array of two ints: [sourceOffset, targetOffset?]
)
{
    uint32_t result = false;  // bVar3

    // Early exit if conditionParams is null or contains zero or sentinel value 0x48
    if (conditionParams == nullptr ||
        *conditionParams == 0 || *conditionParams == 0x48 ||
        conditionParams[2] == 0 || conditionParams[2] == 0x48)
    {
        goto exit;
    }

    int32_t baseOffset;
    int32_t baseOffset2;   // iVar8 and iVar4 in original

    if (conditionParams[2] == 0)
    {
        baseOffset = 0;
        baseOffset2 = 0;
    }
    else
    {
        baseOffset = conditionParams[2] - 0x48;
        if (baseOffset == 0)
        {
            baseOffset = 0;
            baseOffset2 = 0;
        }
        else
        {
            // debug source line tracking
            int32_t debugSourceLine = 0x6ec046;
            baseOffset2 = FUN_0043b870();
        }
    }

    // debug data
    void* debugData = reinterpret_cast<void*>(baseOffset); // puStack_4c

    switch (conditionID)
    {
    case 0:  // Skill/Attribute check 0?
    case 2:
        if (baseOffset2 != 0)
        {
            // debugSourceLine = 0x6ec077;
            result = FUN_0078af40();
        }
        break;

    case 1:  // Skill/Attribute check 1?
        if (baseOffset2 != 0)
        {
            // debugSourceLine = 0x6ec090;
            result = FUN_0078b010();
        }
        break;

    case 5:  // Check if something is ready?
        if (*conditionParams == 0)
        {
            // debugSourceLine = 1; debugData = nullptr;
            result = FUN_0071f820();
        }
        else
        {
            // debugData = (void*)(*conditionParams - 0x48); debugSourceLine = 1;
            result = FUN_0071f820();
        }
        break;

    case 9:  // Check distance between two objects?
        if (*conditionParams != 0 && *conditionParams != 0x48)
        {
            // debugSourceLine = 0x6ec1e7;
            int32_t ptr = FUN_006ebfb0();   // get some object
            if (ptr != 0)
            {
                float distance = *reinterpret_cast<float*>(ptr + 0x100);
                // debugSourceLine = 1; debugData = (void*)0x6ec204;
                int32_t threshold = FUN_0072f370();
                result = (threshold <= static_cast<int32_t>(distance));
            }
        }
        break;

    case 10:  // Check something else?
        // debugSourceLine = 0x6ec21e;
        result = FUN_0071fa00();
        break;

    // Cases 0xc to 0x12: Check something indexed from 0 to 6 (maybe player skill levels)
    case 0xc:
        result = FUN_00898330(0);
        break;
    case 0xd:
        result = FUN_00898330(1);
        break;
    case 0xe:
        result = FUN_00898330(2);
        break;
    case 0xf:
        result = FUN_00898330(3);
        break;
    case 0x10:
        result = FUN_00898330(4);
        break;
    case 0x11:
        result = FUN_00898330(5);
        break;
    case 0x12:
        result = FUN_00898330(6);
        break;

    case 0x21:  // Some timed event?
        // debugSourceLine = 0x6ec14d;
        result = FUN_0071fa50();
        break;

    case 0x25:  // Check if player is in certain state?
        // debugSourceLine = 0x6ec162;
        {
            uint32_t flag = FUN_007e80c0();
            if (flag != 0) goto case_0x32;  // fallthrough to case 0x32
        }
        break;

    case 0x2b:  // Check a bit flag on an object?
        // return (*(uint32_t*)(*(int32_t*)(baseOffset + 0x2124) + 0x20) >> 2) & 1;
        {
            int32_t objectPtr = *reinterpret_cast<int32_t*>(baseOffset + 0x2124);
            result = (*reinterpret_cast<uint32_t*>(objectPtr + 0x20) >> 2) & 1;
        }
        break;

    case 0x2f:  // Some other check?
        // debugSourceLine = 0x6ec283;
        result = FUN_00730210();
        break;

    case 0x32:  // Check if a counter has elapsed?
case_0x32:
        // debugSourceLine = 100; debugData = (void*)0x6ec171;
        {
            uint32_t value = FUN_006eb670();
            if (value < *reinterpret_cast<uint32_t*>(baseOffset + 0x1f64))
            {
                result = 1;
            }
        }
        break;

    case 0x33:  // Check time since event?
        // debugSourceLine = 0x6ec197;
        {
            uint32_t flag = FUN_007e80c0();
            if (flag != 0 &&
                DAT_01205224 < *reinterpret_cast<uint32_t*>(baseOffset + 0x205c) + 60000U &&
                *reinterpret_cast<uint32_t*>(baseOffset + 0x205c) != 0)
            {
                result = 1;
            }
        }
        break;

    case 0x34:  // Check two conditions?
        // debugSourceLine = 0x6ec2a1;
        {
            uint32_t flag1 = FUN_007f7c50();
            if (flag1)
            {
                result = 1;
            }
            else
            {
                // debugSourceLine = 0x32; debugData = (void*)0x6ec2b2;
                uint32_t flag2 = FUN_00690150();
                if (flag2)
                {
                    result = 1;
                }
                else
                {
                    result = 0;
                }
            }
        }
        break;

    case 0x35:  // Check object state?
        {
            int32_t offset;
            if (conditionParams[2] == 0)
                offset = 0;
            else
                offset = conditionParams[2] - 0x48;
            // debugData = (void*)0x6ec2da;
            int32_t obj = FUN_006bc8b0(offset);
            if (obj != 0)
            {
                // debugSourceLine = 0x6ec2ec;
                uint32_t flag = FUN_006eb940();
                if (flag)
                {
                    result = 1;
                }
            }
        }
        break;

    case 0x36:  // Check a range?
        {
            int32_t param;
            if (*conditionParams == 0)
            {
                param = 0;
                // debugData = (void*)0x6ec35f;
                result = FUN_0072ff30(param);
            }
            else
            {
                param = *conditionParams - 0x48;
                // debugData = (void*)0x6ec34b;
                result = FUN_0072ff30(param);
            }
        }
        break;

    case 0x37:
    case 0x3c:
        // debugSourceLine = 1; debugData = (void*)0x6ec372;
        FUN_0072f370();
        result = 1;
        break;

    case 0x38:
    case 0x3d:
        // debugSourceLine = 1; debugData = (void*)0x6ec387;
        {
            int32_t val = FUN_0072f370();
            result = (val == 0);
        }
        break;

    case 0x3b:
        result = 0;
        break;

    case 0x42:  // Check character and crew?
        {
            int32_t sourcePtr;
            if (*conditionParams == 0)
                sourcePtr = 0;
            else
                sourcePtr = *conditionParams - 0x48;
            // debugData = (void*)0x6ec3a9;
            int32_t obj = FUN_006ad7f0(sourcePtr);
            if (obj == 0)
            {
                result = 0;
            }
            else if ((*reinterpret_cast<uint8_t*>(obj + 100) & 1) == 0)
            {
                result = 0;
            }
            else
            {
                // debugSourceLine = 0x6ec3c5;
                int32_t crew = FUN_009a9460();
                if (crew == 0)
                    result = 0;
                else
                    result = 1;
            }
        }
        break;

    case 0x43:  // Check vehicle state?
        {
            int32_t target;
            if (*conditionParams == 0)
                target = 0;
            else
                target = *conditionParams - 0x48;
            if (*reinterpret_cast<int32_t*>(target + 0x24a8) != 0)
            {
                // debugSourceLine = 7; debugData = (void*)0x6ec3fb;
                int32_t state = FUN_00705ab0();
                if (state != 0)
                {
                    // debugData = (void*)0x6ec40f;
                    int32_t flag = FUN_007049a0();
                    result = (flag != 0);
                }
            }
        }
        break;

    case 0x45:
        result = 1;
        break;

    case 0x46:  // Check building?
        {
            int32_t offset;
            if (conditionParams[2] == 0)
                offset = 0;
            else
                offset = conditionParams[2] - 0x48;
            // debugData = (void*)0x6ec314;
            int32_t building = FUN_006eb8b0(offset);
            if (building != 0)
            {
                // debugSourceLine = 0x6ec326;
                uint32_t flag = FUN_00782ce0();
                if (flag)
                {
                    result = 1;
                }
            }
        }
        break;

    case 0x48:  // Some generic check?
        // debugSourceLine = 0x6ec425;
        result = FUN_00736300();
        break;

    case 0x4a:  // Complex condition with character and crew
        {
            int32_t offset;
            if (conditionParams[2] == 0)
                offset = 0;
            else
                offset = conditionParams[2] - 0x48;
            // debugData = (void*)0x6ec443;
            int32_t obj = FUN_006bc8b0(offset);
            if (obj != 0 && (*reinterpret_cast<uint8_t*>(obj + 0x45) & 1) != 0)
            {
                // debugSourceLine = 0x6ec465;
                int32_t state = FUN_007351c0();
                // debugData = (void*)0x6ec46d;
                uint32_t flag = FUN_006eb790();
                if (flag == 0)
                {
                    // debugSourceLine = 0x6ec47c;
                    uint32_t otherFlag = FUN_0090b180();
                    if (otherFlag)
                    {
                        result = 1;
                    }
                }
            }
        }
        break;

    case 0x4c:  // Check character and target?
        {
            int32_t sourceVal = *conditionParams;
            // debugSourceLine = 0x6ec4a2;
            int32_t sourceObj = FUN_006ebfd0();
            int32_t sourcePtr;
            if (sourceVal == 0)
                sourcePtr = 0;
            else
                sourcePtr = sourceVal - 0x48;
            // debugData = (void*)0x6ec4b7;
            int32_t obj = FUN_006ad7f0(sourcePtr);
            int32_t targetVal = conditionParams[2];
            int32_t targetPtr;
            if (targetVal == 0)
                targetPtr = 0;
            else
                targetPtr = targetVal - 0x48;
            // debugData = (void*)0x6ec4d0;
            int32_t targetObj = FUN_006bc8b0(targetPtr);
            if (obj != 0 && sourceObj != 0)
            {
                uint32_t objData = *reinterpret_cast<uint32_t*>(obj + 0x34);
                // debugSourceLine = 0x6ec4fd;
                uint32_t currentTime = FUN_008bf540();
                if (currentTime < objData &&
                    (*reinterpret_cast<uint8_t*>(obj + 100) & 1) != 0 &&
                    targetObj != 0)
                {
                    // debugSourceLine = 0x6ec520;
                    uint32_t flag = FUN_006eb940();
                    if (flag == 0)
                    {
                        // debugSourceLine = 0x6ec52f;
                        int32_t state = FUN_007351c0();
                        // debugData = (void*)0x6ec539;
                        uint32_t otherFlag = FUN_006eb790();
                        if (otherFlag)
                        {
                            result = 1;
                        }
                    }
                }
            }
        }
        break;

    case 0x4e:  // Check some object state
        // debugSourceLine = 0x6ec554;
        {
            int32_t state = FUN_007351c0();
            if (state != 0)
            {
                // debugData = (void*)0x6ec568;
                int32_t obj = FUN_008e62c0();
                if (obj != 0 && *reinterpret_cast<char*>(obj + 0x1a4) != '\0')
                {
                    result = 1;
                }
            }
        }
        break;

    case 0x4f:
    case 0x50:
    case 0x51:
        // debugSourceLine = 0x6ec594;
        {
            int32_t count = FUN_0077dd80();
            result = (conditionID - 0x4f <= count - 1);
        }
        break;

    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
        // Debug rendering condition? Sets up UI data arrays.
        {
            // Local pointers to global debug arrays
            void* dbg0 = &DAT_0112ff88[0];   // local_20
            void* dbg1 = &DAT_0112ffb4;      // local_1c
            void* dbg2 = &DAT_0112ffbc;      // local_18
            void* dbg3 = &DAT_0112ffa4;      // local_14
            void* dbg4 = &DAT_0112ffc4;      // local_10
            void* dbg5 = &DAT_0112ffac;      // local_c
            void* dbg6 = &DAT_0112ff94;      // local_8
            void* dbg7 = &DAT_0112ff9c;      // local_4

            int32_t* basePtr = *reinterpret_cast<int32_t**>(DAT_012233a0 + 4);
            int32_t offset;
            if (basePtr == nullptr)
                offset = 0;
            else
                offset = *basePtr - 0x1f30;

            // debugData = (void*)0x6ec60b;
            FUN_0045ca00(&offset);  // pass pointer to offset?
            // Use conditionID to index into local array of pointers
            void* target = reinterpret_cast<void**>(&dbg0)[conditionID - 0x52];
            // debugData = local_2c (a char[12] buffer);
            char buffer[12];
            FUN_0045c400(target, buffer);
            // debugSourceLine = 0x6ec62b;
            FUN_0045cac0(target);
            result = 0;
        }
        break;

    case 0x5b:
        // debugSourceLine = 0x6ec63a;
        result = FUN_007cc340();
        break;

    default:
        break;
    }

exit:
    return result;
}