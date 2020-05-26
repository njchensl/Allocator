#pragma once

#include <forward_list>
#include <map>
#include <vector>
#include <queue>


#include "InternalRef.h"
#include "Ref.h"
#include "RefImpl.h"

template <int V, typename T>
static constexpr T RoundUp(T val)
{
    if (val % V != 0)
    {
        val = (val / V + 1) * V;
    }
    return val;
}

class Allocator
{
public:
    static void Init();

    template <typename T, typename ... Args>
    static Ref<T> New(Args&& ... args)
    {
        size_t size = sizeof(T);
        size = RoundUp<8>(size);

        m_Stack -= size;
        new(m_Stack) T(std::forward<Args>(args)...);

        Ref<T> ref;
        ref.SetHandle(m_CurrentHandle);
        m_Map[m_CurrentHandle] = {m_Stack};
        m_CurrentHandle++;

        return ref;
    }

    static void Defragment();

    static void Delete(IRef& ref);

    static InternalRef GetInternalRef(uint64_t handle)
    {
        return m_Map[handle];
    }

private:
    // nursery space
    inline static uint8_t* m_Base;
    inline static uint8_t* m_Stack;
    inline static uint8_t* m_Top;
    inline static uint64_t m_CurrentHandle;
    // surviver space
    inline static char m_ActiveRegion;
    // A
    inline static uint8_t* m_BaseA;
    inline static uint8_t* m_StackA;
    inline static uint8_t* m_TopA;
    // B
    inline static uint8_t* m_BaseB;
    inline static uint8_t* m_StackB;
    inline static uint8_t* m_TopB;

    inline static std::map<uint64_t, InternalRef> m_Map;
};

inline InternalRef GetInternalRef(uint64_t handle)
{
    return Allocator::GetInternalRef(handle);
}
