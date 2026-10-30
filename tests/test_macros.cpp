#include<pans/macros.h>
#include <iostream>
#include <limits>
#include <type_traits>

static_assert(sizeof(u8) == 1 && std::is_unsigned_v<u8>);
static_assert(sizeof(s8) == 1 && std::is_signed_v<s8>);
static_assert(sizeof(u16) == 2 && std::is_unsigned_v<u16>);
static_assert(sizeof(s16) == 2 && std::is_signed_v<s16>);
static_assert(sizeof(u32) == 4 && std::is_unsigned_v<u32>);
static_assert(sizeof(s32) == 4 && std::is_signed_v<s32>);
static_assert(sizeof(u64) == 8 && std::is_unsigned_v<u64>);
static_assert(sizeof(s64) == 8 && std::is_signed_v<s64>);
static_assert(INVALID8 == MAX_U8);
static_assert(INVALID16 == MAX_U16);
static_assert(INVALID32 == MAX_U32);
static_assert(INVALID64 == MAX_U64);
static_assert(MAX_U8 == std::numeric_limits<u8>::max());
static_assert(MAX_U16 == std::numeric_limits<u16>::max());
static_assert(MAX_U32 == std::numeric_limits<u32>::max());
static_assert(MAX_U64 == std::numeric_limits<u64>::max());

void test_types_and_constants()
{
    // 以下在运行时检查，本质上就是一个if语句判断混合assert的包装
    ASSERT_NOEFFECT(sizeof(u8) == 1 && std::is_unsigned_v<u8>);
    ASSERT_NOEFFECT(sizeof(s8) == 1 && std::is_signed_v<s8>);
    ASSERT_NOEFFECT(sizeof(u16) == 2 && std::is_unsigned_v<u16>);
    ASSERT_NOEFFECT(sizeof(s16) == 2 && std::is_signed_v<s16>);
    ASSERT_NOEFFECT(sizeof(u32) == 4 && std::is_unsigned_v<u32>);
    ASSERT_NOEFFECT(sizeof(s32) == 4 && std::is_signed_v<s32>);
    ASSERT_NOEFFECT(sizeof(u64) == 8 && std::is_unsigned_v<u64>);
    ASSERT_NOEFFECT(sizeof(s64) == 8 && std::is_signed_v<s64>);
    ASSERT_NOEFFECT(INVALID8 == MAX_U8);
    ASSERT_NOEFFECT(INVALID16 == MAX_U16);
    ASSERT_NOEFFECT(INVALID32 == MAX_U32);
    ASSERT_NOEFFECT(INVALID64 == MAX_U64);
    ASSERT_RETNONE(MAX_U8 == std::numeric_limits<u8>::max());
    ASSERT_RETNONE(MAX_U16 == std::numeric_limits<u16>::max());
    ASSERT_RETNONE2(MAX_U32 == std::numeric_limits<u32>::max(), "this is a test for ASSERT_RETNONE2 macro");
    ASSERT_RETNONE2(MAX_U64 == std::numeric_limits<u64>::max(), "this is a test for ASSERT_RETNONE2 macro");
}

[[nodiscard]] int test_assert_retval()
{
    ASSERT_RETVAL(false,-1);
    return 0;
}

[[nodiscard]] int test_assert_retval2()
{
    ASSERT_RETVAL2(false,-2,"this is retval2 test");
    return 0;
}

void test_macros()
{
    ASSERT_NOEFFECT2(true,"this should not trigger an assertion.");
    int n = 5;
    int i = 0;
    for(i=0;i<10;++i)
    {
        ASSERT_CONTINUE(i!=n);
        std::cout<<"AAA----"<<i<<std::endl;
    }
    std::cout<<"AAA----__________________________"<<i<<std::endl;

    for(i=0;i<10;++i)
    {
        ASSERT_CONTINUE2(i!=n,"this is ASSERT_CONTINUE2 "<<i);
        std::cout<<"BBB----"<<i<<std::endl;
    }
    std::cout<<"BBB----__________________________"<<i<<std::endl;

    for(i=0;i<10;++i)
    {
        ASSERT_BREAK(i!=n);
        std::cout<<"CCC----"<<i<<std::endl;
    }
    std::cout<<"CCC----__________________________"<<i<<std::endl;
    for(i=0;i<10;++i)
    {
        ASSERT_BREAK2(i!=n,"this is ASSERT_BREAK2 "<<i);
        std::cout<<"DDD----"<<i<<std::endl;
    }

    std::cout<<"DDD----__________________________"<<i<<std::endl;
    for(i=0;i<10;++i)
    {
        ASSERT_NOEFFECT(i!=n);
        std::cout<<"EEE----"<<i<<std::endl;
    }
    std::cout<<"EEE----__________________________"<<i<<std::endl;
    for(i=0;i<10;++i)
    {
        ASSERT_NOEFFECT2(i!=n,"this is ASSERT_NOEFFECT2 "<<i );
        std::cout<<"FFF----"<<i<<std::endl;
    }
    std::cout<<"FFF----__________________________"<<i<<std::endl;
    
}

int main()
{
#ifdef PANS_DEBUG
    std::cout << "This program is compiled in debug mode. Assert will terminate the program on failure." << std::endl;
#endif

#ifdef NDEBUG
    std::cout << "This program is compiled in release mode. Assert will do nothing on failure." << std::endl;
#endif

    test_types_and_constants();
    test_macros();
    int rev = test_assert_retval();
    std::cout<< " return val1 :"<<rev<<std::endl;
    int rev2 = test_assert_retval2();
    std::cout<< " return val2 :"<<rev2<<std::endl;

    return EXIT_SUCCESS;
}