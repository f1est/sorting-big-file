/*
    Cортировка чисел формата double хранящихся в текстовом файле размером 1Гб 
    (файл генерируется программой 0_generate_double_digits.cpp)
*/

#include <iostream>    
#include <fstream>
#include <chrono>
#include <limits>    
#include <algorithm> 
#include <iterator> 

#include <string>    
#include <vector>   

#include <cstdio>

bool merge_sort(const std::string &file1, const std::string &file2, const std::string &result){ 

    std::ifstream sorted_1(file1);
    std::ifstream sorted_2(file2);
    
    if(!sorted_1.good() || !sorted_2.good())    
        return false;
    
    std::ofstream dst_file(result);
    double d_value1, d_value2;

    sorted_1.read(reinterpret_cast<char*>(&d_value1), sizeof(d_value1));
    sorted_2.read(reinterpret_cast<char*>(&d_value2), sizeof(d_value2));


    while (sorted_1.good() ||sorted_2.good()) {

        if(d_value1 <= d_value2) {
            dst_file.write(reinterpret_cast<char*>(&d_value1), sizeof(d_value1));
            sorted_1.read(reinterpret_cast<char*>(&d_value1), sizeof(d_value1));
        } 
        else{
            dst_file.write(reinterpret_cast<char*>(&d_value2), sizeof(d_value2));
            sorted_2.read(reinterpret_cast<char*>(&d_value2), sizeof(d_value2));
        }

        if(!sorted_1.good())
        {
            while(sorted_2.good()) {
                sorted_2.read(reinterpret_cast<char*>(&d_value2), sizeof(d_value2));
                dst_file.write(reinterpret_cast<char*>(&d_value2), sizeof(d_value2));
            }
            
            break;
        }

        if(!sorted_2.good())
        {
            while(sorted_1.good()) {
                sorted_1.read(reinterpret_cast<char*>(&d_value1), sizeof(d_value1));
                dst_file.write(reinterpret_cast<char*>(&d_value1), sizeof(d_value1));
            }
        }
    }

    dst_file.close();
    sorted_1.close();
    sorted_2.close();

    remove(file1.c_str());
    remove(file2.c_str());

    return true;
}

int main(int argc, char **argv) {
    
    if(argc < 3) {
        std::cout << "\n \t Please use this format: " << argv[0] << " unsorted_file sorted_file \n";
        exit(EXIT_FAILURE);
    }

    std::vector<double> arr;
    size_t num_of_piece = 0;
    size_t num_of_sort = 0;
    std::ifstream unsorted_file(argv[1]);

    typedef std::chrono::high_resolution_clock myclock;
    myclock::time_point end, duration;
    auto begin = end = myclock::now();

    while(unsorted_file.good()) {
        std::string line, tmp_file;

        for(size_t i = 0; i < 33000000/sizeof(double); i++) { // ограничиваем использование памяти 
//        for(size_t i = 0; i < 100000000/sizeof(double); i++) { // ограничиваем использование памяти 100Mb
            std::getline(unsorted_file, line);

            if(!line.empty())
                arr.push_back(std::stod(line));

            if(!unsorted_file.good()) break;
        }
        
        std::sort(arr.begin(), arr.end());

        tmp_file = "sorted_" + std::to_string(num_of_piece) +".bin";
        std::ofstream sorted(tmp_file);
        
        for ( auto &i : arr ) {
            sorted.write(reinterpret_cast<char*>(&i), sizeof(i)); // избавимся от лишних конвертаций сохранив в файл в бинарном виде
        }
        sorted.close();
    
        duration = myclock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(duration - end);
        end = duration;

        std::cout << "sorting time of sorted_" << num_of_piece << " is: " << elapsed_time.count()/60 << " minutes " << elapsed_time.count()%60 << " seconds\n";

        num_of_piece++;
        arr.clear();

    }

    unsorted_file.close();

    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    std::cout << "Total sorting time of pieces is: " << elapsed_time.count()/60 << " minutes " << elapsed_time.count()%60 << " seconds\n";
    std::cout << "\nStart merge sorting\n\n";
  
    for(; num_of_sort < num_of_piece; num_of_sort+=2, num_of_piece++) {

        if(!merge_sort("sorted_" + std::to_string(num_of_sort) +".bin", 
                        "sorted_" + std::to_string(num_of_sort+1) +".bin", 
                        "sorted_" + std::to_string(num_of_piece) +".bin"))
            break;
        
        duration = myclock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(duration - end);
        end = duration;

        std::cout << "merge sorting time of sorted_" << num_of_sort << " and sorted_" << num_of_sort+1 << " is: " << elapsed_time.count()/60 << " minutes " << elapsed_time.count()%60 << " seconds\n";
    }
        
    
    double d_value = 0.0;
    std::string sorted_bin_file = "sorted_" + std::to_string(num_of_sort) +".bin";
    std::ifstream read_bin_file(sorted_bin_file);
    std::ofstream sorted_file(argv[2]);

    read_bin_file.read(reinterpret_cast<char*>(&d_value), sizeof(d_value));
    while(read_bin_file.good()) {
        sorted_file << d_value << '\n';
        read_bin_file.read(reinterpret_cast<char*>(&d_value), sizeof(d_value));
    }
    read_bin_file.close();
    sorted_file.close();

    remove(sorted_bin_file.c_str());
    
    end = myclock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    std::cout << "\nTotal sorting time of is: " << elapsed_time.count()/60 << " minutes " << elapsed_time.count()%60 << " seconds\n";

    exit(EXIT_SUCCESS);
}


