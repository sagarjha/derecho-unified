#include "PersistLog.hpp"
#include "util.hpp"
#include "utils/logger.hpp"

namespace persistent {

PersistLog::PersistLog(const std::string &name) noexcept(true) : m_sName(name) {
}

PersistLog::~PersistLog() noexcept(true) {
}

#ifndef NDEBUG
void PersistLog::dump_hidx() {
    dbg_default_trace("number of entry in hidx:{}.log_len={}.", hidx.size(), getLength());
    for(auto itr = hidx.cbegin(); itr != hidx.cend(); itr++) {
        dbg_default_trace("hlc({0},{1})->idx({2})", itr->hlc.m_rtc_us, itr->hlc.m_logic, itr->log_idx);
    }
}
#endif  //NDEBUG
}
