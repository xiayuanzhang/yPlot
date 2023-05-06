// MESSAGE USER support class

#pragma once

namespace mavlink {
namespace yplot {
namespace msg {

/**
 * @brief USER message
 *
 * user cmd
 */
struct USER : mavlink::Message {
    static constexpr msgid_t MSG_ID = 3;
    static constexpr size_t LENGTH = 255;
    static constexpr size_t MIN_LENGTH = 255;
    static constexpr uint8_t CRC_EXTRA = 202;
    static constexpr auto NAME = "USER";


    std::array<uint8_t, 255> userData; /*<  cmd */


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
        ss << "  userData: [" << to_string(userData) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << userData;                      // offset: 0
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> userData;                      // offset: 0
    }
};

} // namespace msg
} // namespace yplot
} // namespace mavlink
