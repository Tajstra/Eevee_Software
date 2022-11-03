#include <filesystem>
#include <cassert>
#include "logger_csv.h"

namespace test
{
LoggerCsv::LoggerCsv(std::string const name) : m_name(name)
{
    // std::filesystem::path const log_path = "logs";
    std::filesystem::create_directory("logs");
    m_csv_file.open("logs/log_" + name + ".csv");
}

LoggerCsv &
LoggerCsv::operator<<(std::string const & col_name)
{
    assert(!m_header_finished);
    m_csv_file << col_name << ",";
    col_num++;
    return *this;
}

// template <typename T>
// typename std::enable_if<std::is_arithmetic<T>::value, LoggerCsv &>::type
// LoggerCsv::operator<<(T const & signal)
// {
//     assert(col_num > 0u);
//     col_count++;
//     if (!m_header_finished)
//     {
//         m_header_finished = true;
//         m_csv_file << "\n";
//     }

//     m_csv_file << signal;

//     if (col_count >= col_num)
//     {
//         m_csv_file << "\n";
//         col_count = 0;
//     }
//     else
//     {
//         m_csv_file << ",";
//     }
//     return *this;
// }

LoggerCsv::~LoggerCsv()
{
    m_csv_file.close();
}

}   // namespace test
