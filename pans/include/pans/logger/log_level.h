#ifndef PANS_INCLUDE_PANS_LOGGER_LOG_LEVEL_H
#define PANS_INCLUDE_PANS_LOGGER_LOG_LEVEL_H

#include <cstdint>
#include <string_view>

#include <pans/export.h>

namespace pans{

class LogLevel final
{
public:
    enum class Level : std::uint8_t
    {
        LOG_LV_DEBUG = 1,   //调试细节
        LOG_LV_INFO = 2,    //正常运行信息
        LOG_LV_WARN = 3,    //可能存在问题 但是程序继续执行
        LOG_LV_ERROR = 4,   //操作失败 或功能异常
        LOG_LV_FATAL = 5,   //严重故障
        LOG_LV_OFF = 6,     //关闭日志
    };

    [[nodiscard]] static std::string_view ToString(Level level) noexcept;
    [[nodiscard]] static LogLevel::Level FromString(std::string_view value) noexcept;
    
private:
   

};







}






#endif