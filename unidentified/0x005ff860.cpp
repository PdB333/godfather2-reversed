// FUN_005ff860: SequenceManager::activateSequence

#include <cstdint>

// Forward declarations of called functions (addresses given in decompile)
void __fastcall FUN_00600a40(int32_t* a, int32_t* b, int32_t c, int32_t d, int32_t e);
void __fastcall FUN_005f7ba0(int32_t* a);
void __fastcall FUN_005f5bb0();

class SequenceManager {
public:
    struct SequenceContext {
        int32_t  m_baseData;          // +0x00 (offset *0)
        int32_t  m_field04;           // +0x04 (offset *1)
        int32_t  m_field08;           // +0x08 (offset *2)
        // ... other fields up to offset 0x7C
        int32_t  m_startNode;         // +0x7C (offset *0x1F)
        int32_t  m_endNode;           // +0x84 (offset *0x21)
        int32_t  m_currentNode;       // +0x88 (offset *0x22)
        int32_t  m_field90;           // +0x90 (offset *0x24)
    };

    static void __fastcall activateSequence(SequenceContext* ctx);
};

void __fastcall SequenceManager::activateSequence(SequenceContext* ctx)
{
    // Only proceed if both start and end nodes exist
    if (ctx->m_startNode != 0 && ctx->m_endNode != 0)
    {
        // Build a temporary node on the stack to insert into the active list
        int32_t tempBase    = ctx->m_baseData;       // local_c
        int32_t tempCurNode = ctx->m_currentNode;    // local_18
        int32_t tempField8  = ctx->m_field08;        // local_8
        int32_t tempField4  = ctx->m_field04;        // local_4

        // Save old next pointer of current node and redirect it to our stack variable
        int32_t oldNext = 0;  // local_14
        if (tempCurNode != 0)
        {
            oldNext = *(int32_t*)(tempCurNode + 4);           // save +4 offset
            *(int32_t**)(tempCurNode + 4) = &tempCurNode;     // point to local_18
        }

        int32_t tempField90 = ctx->m_field90;                 // local_10
        int32_t tempStart   = ctx->m_startNode;               // local_24

        // Save old prev pointer of start node and redirect it to our stack variable
        int32_t oldPrev = 0;  // local_20
        if (tempStart != 0)
        {
            oldPrev = *(int32_t*)(tempStart + 4);             // save +4 offset
            *(int32_t**)(tempStart + 4) = &tempStart;         // point to local_24
        }

        int32_t tempEnd = ctx->m_endNode;                     // local_1c

        // Call processing functions with the temporary nodes
        FUN_00600a40(&tempStart, &tempBase, 0, 0, 0);
        FUN_005f7ba0(&tempCurNode);
        FUN_005f5bb0();
        FUN_005f5bb0();

        // Note: The old saved next/prev pointers (oldNext, oldPrev) are not restored.
        // This suggests the temporary node is consumed or becomes part of the active list.
    }
}