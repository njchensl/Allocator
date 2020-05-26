#include "Allocator.h"

#include <cassert>

static constexpr size_t sizeNursery = RoundUp<8>(1023);
static constexpr size_t sizeSurvivor = RoundUp<8>(16383);

void Allocator::Init()
{

    auto* ptr = (uint8_t*)malloc(sizeNursery);
    m_Base = ptr + sizeNursery;
    m_Stack = m_Base;
    m_Top = ptr;
    m_CurrentHandle = 1;

    // setup the suvivor spae
    m_ActiveRegion = 'A';
    auto* ptrSurviver = (uint8_t*)malloc(RoundUp<8>(sizeSurvivor));
    m_BaseA = ptrSurviver + sizeSurvivor;
    size_t sizeA = RoundUp<8, size_t>(sizeSurvivor / 2);
    size_t sizeB = sizeSurvivor - sizeA;
    m_BaseB = m_BaseA - sizeA;
    m_TopA = m_BaseB;
    m_TopB = m_TopA - sizeB;
    assert(m_TopB == ptrSurviver);
}

void Allocator::Defragment()
{
}

void Allocator::Delete(IRef& ref)
{
    ref.Finalize();
    m_Map.erase(ref.GetHandle());
}
