//
// Created by kiosk on 2020/2/9.
//
#include "sstable.h"

void sstable::UnmemtableAdd(
    const std::map<std::string, std::string, std::less<>, MemoryPool<std::pair<std::string, std::string>>>& value) {
    for (const auto& it : value) {
        m_block->Add(it.first, it.second);
    }
    m_buffer.append(m_block->Finish());
    m_data_index.emplace_back(m_buffer.size());
    m_fifter_buffer += m_block->To_Fif();  // fiter 过滤器
    m_fifter_index.emplace_back(m_fifter_buffer.size());
    m_block->Reset();
}

bool sstable::Get(const std::string& key_, std::string& value) {
    m_read->Set_Key(key_);
    auto it = m_read->Read_File();
    if (it) {
        value = m_read->Value();
        return true;
    }
    return false;
}

void sstable::Offset(std::vector<uint32_t>& index) {
    char bufs[4];
    for (const auto& it : index) {
        bzero(bufs, sizeof(bufs));
        EncodeInt32(bufs, it);
        m_offset.append(bufs, sizeof(bufs));
    }
    m_offset += '\r';
}

void sstable::Reset() {
    m_fifter_buffer.clear();
    m_buffer.clear();
    m_data_index.clear();
    m_fifter_index.clear();
    m_offset.clear();
    m_data_index.emplace_back(0);
    m_fifter_index.emplace_back(0);
}

void sstable::Write_NameFile() {
    m_buffer += m_fifter_buffer;
    Offset(m_data_index);
    Offset(m_fifter_index);
    char bufs[4];
    bzero(bufs, sizeof(bufs));
    EncodeInt32(bufs, m_data_index.size() + m_fifter_index.size());
    m_offset.append(bufs, sizeof(bufs));
    m_buffer.append(m_offset);
    std::stringstream filename;
    filename << '.';
    filename << options::GetOptions().Id();
    filename << options::GetOptions().GetFilename();
    m_write = std::make_unique<write_file>(filename.str());
    std::string real_buffer;
    snappy::Compress(m_buffer.data(), m_buffer.size(), &real_buffer);
    m_write->writeFile(real_buffer.data(), real_buffer.size());
    options::GetOptions().AddId();
    Reset();
}