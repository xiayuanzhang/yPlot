// MESSAGE PID support class

#pragma once

namespace mavlink {
namespace yplot {
namespace msg {

/**
 * @brief PID message
 *
 * user cmd
 */
struct PID : mavlink::Message {
    static constexpr msgid_t MSG_ID = 4;
    static constexpr size_t LENGTH = 32;
    static constexpr size_t MIN_LENGTH = 32;
    static constexpr uint8_t CRC_EXTRA = 130;
    static constexpr auto NAME = "PID";


    std::array<uint8_t, 20> pidName; /*<  pidName */
    float p; /*<  p */
    float i; /*<  i */
    float d; /*<  d */


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
        ss << "  pidName: [" << to_string(pidName) << "]" << std::endl;
        ss << "  p: " << p << std::endl;
        ss << "  i: " << i << std::endl;
        ss << "  d: " << d << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << p;                             // offset: 0
        map << i;                             // offset: 4
        map << d;                             // offset: 8
        map << pidName;                       // offset: 12
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> p;                             // offset: 0
        map >> i;                             // offset: 4
        map >> d;                             // offset: 8
        map >> pidName;                       // offset: 12
    }
};

} // namespace msg
} // namespace yplot
} // namespace mavlink
