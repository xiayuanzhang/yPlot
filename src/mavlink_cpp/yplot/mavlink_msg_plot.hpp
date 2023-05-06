// MESSAGE PLOT support class

#pragma once

namespace mavlink {
namespace yplot {
namespace msg {

/**
 * @brief PLOT message
 *
 * the serial plot data
 */
struct PLOT : mavlink::Message {
    static constexpr msgid_t MSG_ID = 1;
    static constexpr size_t LENGTH = 49;
    static constexpr size_t MIN_LENGTH = 49;
    static constexpr uint8_t CRC_EXTRA = 52;
    static constexpr auto NAME = "PLOT";


    int8_t plotNum; /*<  serial plot num  */
    std::array<float, 12> plot; /*<  serial plot */


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
        ss << "  plotNum: " << +plotNum << std::endl;
        ss << "  plot: [" << to_string(plot) << "]" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << plot;                          // offset: 0
        map << plotNum;                       // offset: 48
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> plot;                          // offset: 0
        map >> plotNum;                       // offset: 48
    }
};

} // namespace msg
} // namespace yplot
} // namespace mavlink
