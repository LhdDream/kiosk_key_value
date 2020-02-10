//
// Created by kiosk on 19-9-12.
//

#ifndef MY_SIMPLE_STORAGE_OPTIONS_H
#define MY_SIMPLE_STORAGE_OPTIONS_H


constexpr static const long long  m_number = 16 * 4 * 1024 * 1024;

class options
{
public:
    long long  Get_Lru_Number() const
    {
        return m_lru_number;
    }
    long long  Write() const
    {
        return m_write_buf;
    }
    long long  Block() const
    {
        return m_block_size;
    }
    long long Id() const {
        return id;
    }
    void AddId(){
        id = id+1;
    }
    static  options & GetOptions(){
        static  options cp;
        return cp;
    }
    void AddWrite(){
        m_write_buf = m_write_buf << 1;
    }
    void AddBlock(){
        m_block_size = m_block_size << 1;
    }
    void SetFilename(const std::string& filename){
        name = filename;
    }
    std::string GetFilename() const {
        return name;
    }
protected:
    options () = default;
private:
    long long  m_write_buf =  16 * 1024; //  设置写缓冲区的大小
    long long  m_block_size =  8 * 1024; // 设置每一块的内容的大小
    //test 8k and 16k
    long long m_lru_number = 1024000;//lru_中存储多少条数据
    long long  id = 1;
    std::string name = "";
};


#endif //MY_REDIES_OPTIONS_H
