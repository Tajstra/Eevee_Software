#include <string>
#include <fstream>
#include <type_traits>

#pragma once

namespace test
{

class LoggerCsv
{
public:
    LoggerCsv(std::string const name);

    LoggerCsv &
    operator<<(std::string const & col_name);

    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, LoggerCsv &>::type
    operator<<(T const & signal)
    {
        assert(col_num > 0u);
        col_count++;
        if (!m_header_finished)
        {
            m_header_finished = true;
            m_csv_file << "\n";
        }

        m_csv_file << signal << ';';

        if (col_count >= col_num)
        {
            m_csv_file << "\n";
            col_count = 0;
        }

        return *this;
    }

    ~LoggerCsv();

private:
    std::string const m_name;
    std::ofstream     m_csv_file {};
    bool              m_header_finished {};
    unsigned          col_num {};
    unsigned          col_count {};
};

}   // namespace test