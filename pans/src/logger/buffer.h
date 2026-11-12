#ifndef PANS_SRC_LOGGER_BUFFER_H
#define PANS_SRC_LOGGER_BUFFER_H

#include <algorithm>
#include <array>
#include <cstring>
#include <cstddef>
#include <streambuf>
#include <string_view>
#include <vector>

//日志缓冲区
namespace pans::detail//pans 下的 detail空间
{
    
//std::stringstream 比较简单 但是获取的时候有点麻烦

template<std::size_t INLINE_CAPACITY>//
class InlineBuffer
{
private:
    std::array<char,INLINE_CAPACITY> m_inline{}; //栈上小缓冲
    std::vector<char> m_overflow;               //堆上溢出缓冲
    std::size_t m_size = 0;                     //当前写入字节数
    
public:

    void append(const char * data,std::size_t size)
    {
        if(size == 0)
        {
            return;
        }
        //内联缓冲够用
        if(m_overflow.empty() && m_size + size <= INLINE_CAPACITY)
        {
            std::memcpy(m_inline.data() + m_size,data,size);
            m_size +=size;
            return;
        }
        //内联缓冲不够用
        if(m_overflow.empty())
        {
            const std::size_t required_capacity = m_size + size;
            m_overflow.reserve(std::max(INLINE_CAPACITY*2,required_capacity));
            m_overflow.insert(m_overflow.end(),m_inline.data(),m_inline.data()+m_size);
        }
        //已经在使用内联缓冲
        m_overflow.insert(m_overflow.end(),data,data+size);
        m_size=m_overflow.size();
    }

    void append(std::string_view value)
    {
        append(value.data(),value.size());
    }

    void append(char value)
    {
        append(&value,1);
    }

    [[nodiscard]] const char* data() const noexcept//返回保存的日志的起始位置地址
    {
        return m_overflow.empty()?m_inline.data():m_overflow.data();
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        return m_size;
    }
    //指向已有数据的视图
    [[nodiscard]] std::string_view view() const noexcept
    {
        return {data(),size()};
    }
};

//接收 streambuf 的写入请求
template<std::size_t INLINE_CAPACITY>//
class SmmallStreamBuffer final :public std::streambuf//继续使用流式输入接口
{
private:
    InlineBuffer<INLINE_CAPACITY>& m_buffer;
public:
   explicit SmmallStreamBuffer(InlineBuffer<INLINE_CAPACITY>& buffer) noexcept : m_buffer(buffer)
   {}
protected:
    //重写streambuf的两个方法
    std::streamsize xsputn(const char* data,std::streamsize size) override 
    {
        if(size <= 0)
        {
            return 0;
        }
        m_buffer.append(data,static_cast<std::size_t>(size));//size要转为无符号
        return size;
    }
    int_type overflow(int_type character) override
    {
        if(traits_type::eq_int_type(character,traits_type::eof()))
        {
            return traits_type::not_eof(character);
        }
        m_buffer.append(traits_type::to_char_type(character));
        return character;
    }

};





} // namespace pans::detail






#endif
