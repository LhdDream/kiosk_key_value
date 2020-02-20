//
// Created by kiosk on 19-11-3.
//
#include "read_buffer.h"

bool read_buffer::Find_Value(const char *name, int len) {
    m_iter = m_block->newItear(name, len);
    if (m_iter->Seek(m_key)) {
        m_value = m_iter->Value();
        return true;
    }
    return false;
}

void read_buffer::Get_Vector(std::vector<uint32_t> &index, const std::string &off) {
    std::string temp;
    for (size_t i = 0; i < off.size() / 4; i++) {
        temp.resize(5, '\0');
        std::copy(off.begin() + i * 4, off.begin() + (i + 1) * 4, temp.begin());
        index.emplace_back(DecodeInt32(temp.data()));
    }
}

//偏移量进行加载
bool read_buffer::Read_Offset(const char *data, size_t len) {
    uint32_t size = DecodeInt32(data + len - sizeof(uint32_t));
    //得到所有偏移量的长度
    std::string altogether;
    altogether.resize(size * sizeof(uint32_t));
    std::copy(data + len - sizeof(uint32_t) - size * sizeof(uint32_t) - 2, data + len - sizeof(uint32_t),
              altogether.begin());
    auto it = altogether.find('\r');
    std::string temp1, temp2;
    temp1.resize(it);
    temp2.resize(altogether.end() - altogether.begin() - it);
    std::copy(altogether.begin(), altogether.begin() + it - 1, temp1.begin());
    std::copy(altogether.begin() + it + 1, altogether.end() - 1, temp2.begin());
    Get_Vector(m_data_index, temp1);
    Get_Vector(m_fifter_index, temp2);
    size_t fifter_size = 0;
    size_t index_fif = m_fifter_index.size() - 1;
    while (fifter_size <= index_fif) {
        m_fifter.resize(m_fifter_index[fifter_size + 1] - m_fifter_index[fifter_size]);
        std::copy(data + len - (size + 1) * sizeof(uint32_t) - 2 - m_fifter_index[index_fif] +
                  m_fifter_index[fifter_size],
                  data + len - (size + 1) * sizeof(uint32_t) - 2 - m_fifter_index[index_fif] +
                  m_fifter_index[fifter_size + 1], m_fifter.begin());
        m_fif = std::make_unique<fifter>();
        m_fif->SplitString(m_fifter);
        if (m_fif->Match(m_key)) {
            break;
        }
        fifter_size++;
    }
    if (fifter_size <= index_fif) {
        m_buffer.resize(m_data_index[fifter_size + 1] - m_data_index[fifter_size]);
        std::copy(data + len - (size + 1) * sizeof(uint32_t) - m_fifter_index[index_fif] -
                  m_data_index[m_data_index.size() - 1] - 2 + m_data_index[fifter_size],
                  data + len - 2 - (size + 1) * sizeof(uint32_t) - m_fifter_index[index_fif] -
                  m_data_index[m_data_index.size() - 1] + m_data_index[fifter_size + 1], m_buffer.begin());
        return true;
    }
    return false;
}

bool read_buffer::Read_File() {
    try {
        int len = 0;
        while (m_id >= 0) {
            m_filename = "." + std::to_string(m_id) + options::GetOptions().GetFilename();
            fd = open(m_filename.c_str(), O_RDONLY | O_CLOEXEC | O_DIRECT, 0666);
            if (fd == -1) {
                m_id--;//查看下一个文件是不是存在
                continue;
            }
            struct stat st{};
            auto r = fstat(fd, &st);
            if (r == -1) {
                close(fd);
                return false;
            }
            len = st.st_size;
            auto re_buffer = reinterpret_cast<const char *> (mmap(nullptr, len, PROT_READ,
                                                                  MAP_SHARED | MAP_POPULATE | MAP_NONBLOCK, fd, 0));

            if (re_buffer == nullptr) {
                throw std::invalid_argument(strerror(errno));
            }
            std::string real_buffer;
            snappy::Uncompress(re_buffer, len, &real_buffer);
            if (!Read_Offset(real_buffer.data(), real_buffer.size())) {
                break;
            }
            m_block = std::make_unique<Block>();
            if (Find_Value(m_buffer.data(), m_buffer.length())) {
                m_id = options::GetOptions().Id();
                break;
            }
            m_id--;
        }
        m_block.release(); // 对象生命周期的问题
        return m_id == options::GetOptions().Id();;
    } catch (std::invalid_argument &e) {
        puts(e.what());
    }
}
