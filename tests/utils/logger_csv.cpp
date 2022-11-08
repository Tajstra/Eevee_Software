#include <filesystem>
#include <cassert>
#include "logger_csv.h"

namespace test
{
LoggerCsv::LoggerCsv(std::string const name) : m_name(name)
{
    std::filesystem::create_directory("logs");
    m_csv_file.open("logs/log_" + name + ".csv");
}

LoggerCsv &
LoggerCsv::operator<<(std::string const & col_name)
{
    assert(!m_header_finished);
    m_csv_file << col_name << ";";
    col_num++;
    return *this;
}

LoggerCsv::~LoggerCsv()
{
    m_csv_file.close();
}

}   // namespace test
