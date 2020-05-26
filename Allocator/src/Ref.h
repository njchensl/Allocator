#pragma once

class IRef
{
public:
    virtual ~IRef()
    {
    }

    uint64_t GetHandle() const
    {
        return m_Handle;
    }

    void SetHandle(uint64_t handle)
    {
        m_Handle = handle;
    }

    virtual void Finalize() = 0;

protected:
    uint64_t m_Handle = 0;
};

