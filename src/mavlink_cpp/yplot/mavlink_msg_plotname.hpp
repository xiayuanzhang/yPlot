// MESSAGE PLOTNAME support class

#pragma once

namespace mavlink {
namespace yplot {
namespace msg {

/**
 * @brief PLOTNAME message
 *
 * the serial plot data
 */
struct PLOTNAME : mavlink::Message {
    static constexpr msgid_t MSG_ID = 2;
    static constexpr size_t LENGTH = 180;
    static constexpr size_t MIN_LENGTH = 180;
    static constexpr uint8_t CRC_EXTRA = 179;
    static constexpr auto NAME = "PLOTNAME";


    std::array<char, 15> plotName0; /*<  serial plot name */
    std::array<char, 15> plotName1; /*<  serial plot name */
    std::array<char, 15> plotName2; /*<  serial plot name */
    std::array<char, 15> plotName3; /*<  serial plot name */
    std::array<char, 15> plotName4; /*<  serial plot name */
    std::array<char, 15> plotName5; /*<  serial plot name */
    std::array<char, 15> plotName6; /*<  serial plot name */
    std::array<char, 15> plotName7; /*<  serial plot name */
    std::array<char, 15> plotName8; /*<  serial plot name */
    std::array<char, 15> plotName9; /*<  serial plot name */
    std::array<char, 15> plotName10; /*<  serial plot name */
    std::array<char, 15> plotName11; /*<  serial plot name */


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
        ss << "  plotName0: \"" << to_string(plotName0) << "\"" << std::endl;
        ss << "  plotName1: \"" << to_string(plotName1) << "\"" << std::endl;
        ss << "  plotName2: \"" << to_string(plotName2) << "\"" << std::endl;
        ss << "  plotName3: \"" << to_string(plotName3) << "\"" << std::endl;
        ss << "  plotName4: \"" << to_string(plotName4) << "\"" << std::endl;
        ss << "  plotName5: \"" << to_string(plotName5) << "\"" << std::endl;
        ss << "  plotName6: \"" << to_string(plotName6) << "\"" << std::endl;
        ss << "  plotName7: \"" << to_string(plotName7) << "\"" << std::endl;
        ss << "  plotName8: \"" << to_string(plotName8) << "\"" << std::endl;
        ss << "  plotName9: \"" << to_string(plotName9) << "\"" << std::endl;
        ss << "  plotName10: \"" << to_string(plotName10) << "\"" << std::endl;
        ss << "  plotName11: \"" << to_string(plotName11) << "\"" << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << plotName0;                     // offset: 0
        map << plotName1;                     // offset: 15
        map << plotName2;                     // offset: 30
        map << plotName3;                     // offset: 45
        map << plotName4;                     // offset: 60
        map << plotName5;                     // offset: 75
        map << plotName6;                     // offset: 90
        map << plotName7;                     // offset: 105
        map << plotName8;                     // offset: 120
        map << plotName9;                     // offset: 135
        map << plotName10;                    // offset: 150
        map << plotName11;                    // offset: 165
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> plotName0;                     // offset: 0
        map >> plotName1;                     // offset: 15
        map >> plotName2;                     // offset: 30
        map >> plotName3;                     // offset: 45
        map >> plotName4;                     // offset: 60
        map >> plotName5;                     // offset: 75
        map >> plotName6;                     // offset: 90
        map >> plotName7;                     // offset: 105
        map >> plotName8;                     // offset: 120
        map >> plotName9;                     // offset: 135
        map >> plotName10;                    // offset: 150
        map >> plotName11;                    // offset: 165
    }
};

} // namespace msg
} // namespace yplot
} // namespace mavlink
