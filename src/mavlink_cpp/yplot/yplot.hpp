/** @file
 *	@brief MAVLink comm protocol generated from yplot.xml
 *	@see http://mavlink.org
 */

#pragma once

#include <array>
#include <cstdint>
#include <sstream>

#ifndef MAVLINK_STX
#define MAVLINK_STX 253
#endif

#include "../message.hpp"

namespace mavlink {
namespace yplot {

/**
 * Array of msg_entry needed for @p mavlink_parse_char() (through @p mavlink_get_msg_entry())
 */
constexpr std::array<mavlink_msg_entry_t, 4> MESSAGE_ENTRIES {{ {1, 52, 49, 49, 0, 0, 0}, {2, 179, 180, 180, 0, 0, 0}, {3, 202, 255, 255, 0, 0, 0}, {4, 130, 32, 32, 0, 0, 0} }};

//! MAVLINK VERSION
constexpr auto MAVLINK_VERSION = 3;


// ENUM DEFINITIONS


/** @brief used to indicate whether the line is valid */
enum class PLOT_ISVALID
{
    INVALID=0, /* the ch is invalid | */
    VALID=1, /* the ch is valid | */
};

//! PLOT_ISVALID ENUM_END
constexpr auto PLOT_ISVALID_ENUM_END = 2;


} // namespace yplot
} // namespace mavlink

// MESSAGE DEFINITIONS
#include "./mavlink_msg_plot.hpp"
#include "./mavlink_msg_plotname.hpp"
#include "./mavlink_msg_user.hpp"
#include "./mavlink_msg_pid.hpp"

// base include

