//
// Created by kiosk on 2020/2/5.
//
#include "Log.h"


#include <fstream>
#include <iostream>
#include <stdexcept>

class Logger::Impl {
public:

    Impl();

    ~Impl();


    std::ostringstream &info();


    static void init(const std::string &filename, bool append);

    void flush();

    std::ostringstream &getStream();

    void clear();

private:

    static std::ofstream m_fout;

    std::ostringstream m_oss;

    static std::string name;
};




std::ofstream Logger::Impl::m_fout{};

std::string Logger::Impl::name;

// Default streams



Logger::Impl::Impl() {

}

Logger::Impl::~Impl() {

    if (Impl::m_fout.is_open()) {
        Impl::m_fout.flush();
    }
}


std::ostringstream &Logger::Impl::getStream() {

    return m_oss;
}


void Logger::Impl::flush() {

    if (m_oss.str().empty()) {
        return;
    }
    Impl::m_fout << m_oss.str()  ;
    m_fout.flush();
    m_oss.str("");
}

void Logger::Impl::init(const std::string &filename, bool append) {
    if (!filename.empty()) {
        name = filename;
        Impl::m_fout.open(filename, append ? std::ofstream::out | std::ofstream::app  : std::ofstream::out);
        if (!Impl::m_fout.is_open()) {
            throw std::runtime_error("ERROR!!: Couldn't open '" + filename + "' for write.\n");
        }
    }
}

std::ostringstream &Logger::Impl::info() {
    return getStream();
}

Logger::Logger()
        : m_impl(std::make_unique< Logger::Impl>()) {
}

void Logger::init(const std::string &filename, bool append) {
    Impl::init(filename, append);
}


std::ostringstream &Logger::info() {
    return m_impl->info();
}

Logger::~Logger() = default;

void Logger::flunsh() {
    m_impl->flush();
}

void Logger::clear() {
    m_impl->clear();
}

void Logger::Impl::clear() {
    m_fout.close();
    Impl::m_fout.open(name, std::ofstream::out | std::ofstream::app );
}