#ifndef PANS_SRC_LOGGER_BUFFER_H
#define PANS_SRC_LOGGER_BUFFER_H

#include <algorithm>
#include <array>
#include <cstring>
#include <cstddef>
#include <streambuf>
#include <string_view>
#include <vector>

namespace pans::detail
{
    
//std::stringstream 比较简单 但是获取的时候有点麻烦

template<std::size_t INLINE_CAPACITY>
class InlineBuffer
{
private:
    std::array<char,INLINE_CAPACITY> m_inlie{};
    std::vector<char> m_overflow;
    
public:
    InlineBuffer(){}

    ~InlineBuffer(){}
};




} // namespace pans::detail






#endif
