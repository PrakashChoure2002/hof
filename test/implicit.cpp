#include <fit/implicit.hpp>
#include "test.hpp"

template<class T>
struct auto_caster
{
    template<class U>
    T operator()(U x)
    {
        return T(x);
    }
};

template<class T>
struct auto_caster_noexcept
{
    template<class U>
    T operator()(U x) noexcept
    {
        return T(x);
    }
};

struct auto_caster_foo
{
    int i;
    explicit auto_caster_foo(int ip) : i(ip) {}

};
// TODO: Test template constraint on conversion operator
static constexpr fit::implicit<auto_caster> auto_cast = {};

FIT_TEST_CASE()
{
    float f = 1.5;
    int i = auto_cast(f);
    // auto_caster_foo x = 1;
    auto_caster_foo x = auto_cast(1);
    FIT_TEST_CHECK(1 == i);
    FIT_TEST_CHECK(1 == x.i);

}
#if FIT_HAS_NOEXCEPT_DEDUCTION
FIT_TEST_CASE()
{
    fit::implicit<auto_caster_noexcept> lauto_cast{};
    float f = 1.5;
    static_assert(noexcept(int(lauto_cast(f))), "noexcept implicit");
}
#endif
