#ifndef FUNDAMENTAL_ALGO_FILE_READER_H
#define FUNDAMENTAL_ALGO_FILE_READER_H
#include<iostream>
#include<fstream>

class file_reader
{
private:
    std::string _file_name;
    std::ifstream _file;
public:
    explicit file_reader(std::string& file_name): _file_name(std::move(file_name)) {}
    bool file_open(std::string const& _file_stream)
    {
        _file.open(_file_name);
        return  _file.is_open();
    }
    void file_reader_by_line(std::ifstream& opened_file)
    {
        std::string current_line;
        while(getline(opened_file, current_line))
        {

        }
    }
};

#endif //FUNDAMENTAL_ALGO_FILE_READER_H
