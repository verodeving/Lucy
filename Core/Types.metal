#if !defined(LUCY_METAL_Core_Types)
#define LUCY_METAL_Core_Types
#if lucy_major_version == 0 and lucy_middle_version == 0 and lucy_minor_version == 1

namespace Lucy
{
    using u8 = uchar;
    
    using s8 = char;
    
    using u16 = ushort;

    using s16 = short;

    using f16 = half;

    using u32 = uint;

    using s32 = int;

    using f32 = float;

    using u64 = ulong;

    using s64 = long;

    class f64
    {
        class ieee754
        {
        public:
            bool sign : 1;
        
            u16 exponent : 11;

            u64 mantissa : 52;
        };

        union
        {
            ieee754 bf64{};

            u64 stub;
        };
    public:
        inline constexpr f64(){}

        inline constexpr f64(const f64& other) : stub(other.stub){}

        inline constexpr f64(f64&& other) : stub(other.stub)
        {
            other.stub = 0ull;
        }

        
    };
}

#endif
#endif