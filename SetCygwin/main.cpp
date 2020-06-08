#include <iostream>
#include <fstream>
#include <algorithm>
#include <experimental/filesystem>

using namespace std;

namespace fs = experimental::filesystem;

void DiskInfo(string path);
vector<string> GetDirectoryFiles(const fs::path & dir, const vector<string> & ext);
void Example();
void CreateDir();
void RemoveDir();
void FormatPath();
void GetFile();

int main()
{  
    string cur_p = fs::current_path().generic_string();
    // DiskInfo(cur_p);
    // FormatPath();
    // CreateDir();
    // RemoveDir();
    // Example();
    GetFile();
}

void DiskInfo(string path) 
{
    cout << "current_path - ," << path << endl;
    cout << endl;

    auto root_p = fs::path("c:/");
    auto space = fs::space(root_p);

    cout << "Total      : " << space.capacity/1024/1024/1024 << "GB" << endl;
    cout << "Free       : " << space.free/1024/1024/1024 << "GB" << endl;
    cout << "Available  : " << space.available/1024/1024/1024 << "GB" << endl;
    cout << endl;
}

void FormatPath() 
{
    fs::path aPath { "./path/to/file.txt" };
    cout << "Path to file : " << aPath << endl;
    cout << "Parent path : " << aPath.parent_path() << endl;
    cout << "Filename : " << aPath.filename() << endl;
    cout << "Extension : " << aPath.extension() << endl;
    cout << endl;

    cout << "Separator in my OS " << fs::path::preferred_separator << endl;
    cout << endl;

    fs::path root{ "/" };
    fs::path dir{ "dev/db/" };
    fs::path db{ "database.db" };

    fs::path pathToDb = root / dir / db;
    cout << pathToDb << endl;
    cout << endl;
}

void CreateDir() 
{
    auto cur_p = fs::current_path();
    fs::create_directory("tmp");
    fs::create_directories(cur_p / "tmp\\" / "a\\");
    fs::create_directories(cur_p / "tmp\\b");  
    fs::create_directories(cur_p / "tmp\\b" / "bb" / "bbb");
}

void RemoveDir() 
{
    auto cur_p = fs::current_path();
    fs::remove(cur_p / "tmp\\b" / "bb" / "bbb");
    fs::remove_all(cur_p / "tmp");
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

void Example() 
{
    auto res_dir = fs::current_path();    
    res_dir = res_dir / "res" / "pics";
    fs::create_directories(res_dir);

    vector<string> res_files =
    {
        ".\\res\\pics\\file.png",
        ".\\res\\pics\\file.jpg",
        ".\\res\\pics\\file.info"
    };

    for (auto &f: res_files)
        ofstream(f) << "data";
    
    auto print_files = [] (const auto &aVector)
    {
        for(auto &f: aVector)
            cout << f << endl;
        cout << endl;
    };

    cout << "JPG filter" << endl;
    auto files = GetDirectoryFiles(res_dir, {".jpg"});
    print_files(files);

    cout << "INFO filter" << endl;
    files = GetDirectoryFiles(res_dir, {".info", ".jpg"});
    print_files(files);

    cout << "Without filters" << endl;
    files = GetDirectoryFiles(res_dir, {});
    print_files(files);
}

void GetFile() 
{
    auto permission = [] (fs::perms aPerm) 
    {
        cout
            << ((aPerm & fs::perms::owner_read   ) != fs::perms::none ? "r" : "-")
            << ((aPerm & fs::perms::owner_write  ) != fs::perms::none ? "w" : "-")
            << ((aPerm & fs::perms::owner_exec   ) != fs::perms::none ? "x" : "-")
            << ((aPerm & fs::perms::group_read   ) != fs::perms::none ? "r" : "-")
            << ((aPerm & fs::perms::group_write  ) != fs::perms::none ? "w" : "-")
            << ((aPerm & fs::perms::group_exec   ) != fs::perms::none ? "x" : "-")
            << ((aPerm & fs::perms::others_read  ) != fs::perms::none ? "r" : "-")
            << ((aPerm & fs::perms::others_write ) != fs::perms::none ? "w" : "-")
            << ((aPerm & fs::perms::others_exec  ) != fs::perms::none ? "x" : "-")
            << endl;       
    };

    ofstream("file_test");

    cout << "Initial file permission for a file: ";
    permission(fs::status("file_test").permissions());

    fs::permissions("file_test",
                        fs::perms::remove_perms
                    |   fs::perms::owner_write
                    |   fs::perms::group_all);

    cout << "Adding all bits to owner and goup: ";
    permission(fs::status("file_test").permissions());

    fs::permissions("file_test",
                        fs::perms::remove_perms
                    |   fs::perms::owner_write
                    |   fs::perms::group_write
                    |   fs::perms::others_write);

    cout << "Removing the white bits for all: ";
    permission(fs::status("file_test").permissions());
    fs::remove("file_test");
}