// MESSAGE TEST_TYPES support class

#pragma once

namespace mavlink {
namespace test {
namespace msg {

/**
 * @brief TEST_TYPES message
 *
 * Test all field types
 */
struct TEST_TYPES : mavlink::Message {
    static constexpr msgid_t MSG_ID = 17000;
    static constexpr size_t LENGTH = 179;
    static constexpr size_t MIN_LENGTH = 179;
    static constexpr uint8_t CRC_EXTRA = 103;
    static constexpr auto NAME = "TEST_TYPES";


    char c; /*<  char */
    std::array<char, 10> s; /*<  string */
    uint8_t u8; /*<  uint8_t */
    uint16_t u16; /*<  uint16_t */
    uint32_t u32; /*<  uint32_t */
    uint64_t u64; /*<  uint64_t */
    int8_t s8; /*<  int8_t */
    int16_t s16; /*<  int16_t */
    int32_t s32; /*<  int32_t */
    int64_t s64; /*<  int64_t */
    float f; /*<  float */
    double d; /*<  double */
    std::array<uint8_t, 3> u8_array; /*<  uint8_t_array */
    std::array<uint16_t, 3> u16_array; /*<  uint16_t_array */
    std::array<uint32_t, 3> u32_array; /*<  uint32_t_array */
    std::array<uint64_t, 3> u64_array; /*<  uint64_t_array */
    std::array<int8_t, 3> s8_array; /*<  int8_t_array */
    std::array<int16_t, 3> s16_array; /*<  int16_t_array */
    std::array<int32_t, 3> s32_array; /*<  int32_t_array */
    std::array<int64_t, 3> s64_array; /*<  int64_t_array */
    std::array<float, 3> f_array; /*<  float_array */
    std::array<double, 3> d_array; /*<  double_array */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  c: " << +c << std::endl;
        ss << "  s: \"" << to_string(s) << "\"" << std::endl;
        ss << "  u8: " << +u8 << std::endl;
        ss << "  u16: " << u16 << std::endl;
        ss << "  u32: " << u32 << std::endl;
        ss << "  u64: " << u64 << std::endl;
        ss << "  s8: " << +s8 << std::endl;
        ss << "  s16: " << s16 << std::endl;
        ss << "  s32: " << s32 << std::endl;
        ss << "  s64: " << s64 << std::endl;
        ss << "  f: " << f << std::endl;
        ss << "  d: " << d << std::endl;
        ss << "  u8_array: [" << to_string(u8_array) << "]" << std::endl;
        ss << "  u16_array: [" << to_string(u16_array) << "]" << std::endl;
        ss << "  u32_array: [" << to_string(u32_array) << "]" << std::endl;
        ss << "  u64_array: [" << to_string(u64_array) << "]" << std::endl;
        ss << "  s8_array: [" << to_string(s8_array) << "]" << std::endl;
        ss << "  s16_array: [" << to_string(s16_array) << "]" << std::endl;
        ss << "  s32_array: [" << to_string(s32_array) << "]" << std::endl;
        ss << "  s64_array: [" << to_string(s64_array) << "]" << std::endl;
        ss << "  f_array: [" << to_string(f_array) << "]" << std::endl;
        ss << "  d_array: [" << to_string(d_array) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << u64;                           // offset: 0
        map << s64;                           // offset: 8
        map << d;                             // offset: 16
        map << u64_array;                     // offset: 24
        map << s64_array;                     // offset: 48
        map << d_array;                       // offset: 72
        map << u32;                           // offset: 96
        map << s32;                           // offset: 100
        map << f;                             // offset: 104
        map << u32_array;                     // offset: 108
        map << s32_array;                     // offset: 120
        map << f_array;                       // offset: 132
        map << u16;                           // offset: 144
        map << s16;                           // offset: 146
        map << u16_array;                     // offset: 148
        map << s16_array;                     // offset: 154
        map << c;                             // offset: 160
        map << s;                             // offset: 161
        map << u8;                            // offset: 171
        map << s8;                            // offset: 172
        map << u8_array;                      // offset: 173
        map << s8_array;                      // offset: 176
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> u64;                           // offset: 0
        map >> s64;                           // offset: 8
        map >> d;                             // offset: 16
        map >> u64_array;                     // offset: 24
        map >> s64_array;                     // offset: 48
        map >> d_array;                       // offset: 72
        map >> u32;                           // offset: 96
        map >> s32;                           // offset: 100
        map >> f;                             // offset: 104
        map >> u32_array;                     // offset: 108
        map >> s32_array;                     // offset: 120
        map >> f_array;                       // offset: 132
        map >> u16;                           // offset: 144
        map >> s16;                           // offset: 146
        map >> u16_array;                     // offset: 148
        map >> s16_array;                     // offset: 154
        map >> c;                             // offset: 160
        map >> s;                             // offset: 161
        map >> u8;                            // offset: 171
        map >> s8;                            // offset: 172
        map >> u8_array;                      // offset: 173
        map >> s8_array;                      // offset: 176
    }
};

} // namespace msg
} // namespace test
} // namespace mavlink
