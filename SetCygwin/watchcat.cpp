#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <experimental/filesystem>

using namespace std;

namespace fs = experimental::filesystem;

vector<string> GetFiles();
vector<string> GetDirs();

int main()
{
    // 2 способ инициализации
    int v = 520;
    char ch {v}; // from c++11

    int n1 = 3;
    int n2 = 5;
 
    std::vector<int> v{0, 1, 2, 3, 4};
 
    auto result1 = std::find(std::begin(v), std::end(v), n1);
    auto result2 = std::find(std::begin(v), std::end(v), n2);
 
    if (result1 != std::end(v)) {
        std::cout << "v contains: " << n1 << '\n';
    } else {
        std::cout << "v does not contain: " << n1 << '\n';
    }
 
    if (result2 != std::end(v)) {
        std::cout << "v contains: " << n2 << '\n';
    } else {
        std::cout << "v does not contain: " << n2 << '\n';
    }
}

vector<string> GetDirectoryFiles(const fs::path & dir, const vector<string> & ext) 
{
    vector<string> files;
    for (auto & p: fs::recursive_directory_iterator(dir))
    {
        if(fs::is_regular_file(p))
        {
            // СТД Алгаритм
            if (ext.empty() || find(ext.begin(), ext.end(), p.path().extension().string()) != ext.end())
            {
                files.push_back(p.path().string());
            } 
        }
    }
    return files;
}