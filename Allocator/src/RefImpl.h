#pragma once
#include "Ref.h"

extern InternalRef GetInternalRef(uint64_t handle);

template <typename T>
class Ref : public IRef
{
public:
    Ref()
    {
    }

    ~Ref() override
    {
    }

    void Finalize() override
    {
        Get()->~T();
    }

    T* Get() const
    {
        return operator->();
    }

    T* operator->() const
    {
        return (T*)GetInternalRef(m_Handle).Pointer;
    }

    friend bool operator==(const Ref& lhs, const Ref& rhs)
    {
        return lhs.m_Handle == rhs.m_Handle;
    }

    friend bool operator!=(const Ref& lhs, const Ref& rhs)
    {
        return !(lhs == rhs);
    }
};

template <typename T>
Ref<T> RefCast(const IRef& ref)
{
    return *(Ref<T>*)&ref;
}
