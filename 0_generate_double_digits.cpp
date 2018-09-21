/*
    генератор не отсортированного 1Гб файла с числами формата double
*/

#include <iostream>     // std::cout
#include <fstream>
#include <limits>       // std::numeric_limits
#include <random>
#include <chrono>

#define FILENAME "unsorted_double.txt"


int main () {
    int size_of_file = 0;
    double lower_bound = std::numeric_limits<double>::min(); // минимальное значение double
    double upper_bound = std::numeric_limits<double>::max(); // максимальное значение double
    double a_random_double = 0;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(lower_bound, upper_bound);

    typedef std::chrono::high_resolution_clock myclock;
    auto begin = myclock::now();
    auto duration = myclock::now() - begin;
    unsigned seed = duration.count() * 1024;

    generator.seed(seed);

    std::ofstream fout("unsorted_double.txt"); // создаём объект класса ofstream для записи и связываем его с файлом unsorted_double.txt

    while(size_of_file < 1024*1024*1024) { // наполняем файл пока он меньше 1Gb
        a_random_double = distribution(generator);
        fout << a_random_double << '\n'; // запись строки в файл
        size_of_file = fout.tellp();
    }
 
    auto end = myclock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end - begin);

    std::cout << "filling time is: " << elapsed_time.count()/60 << " minutes " << elapsed_time.count()%60 << " seconds\n";
    std::cout << "\n name of file is: " << FILENAME << "\n";
    std::cout << "\n size of file is: " << size_of_file << "\n\n\n";
    
    fout.close(); 
    return 0;
}
