#include <fstream>
#include <experimental/filesystem>
#include "jsonParser.cpp"

using namespace std;
namespace fs = std::experimental::filesystem;


bool Filter(fs::v1::path path) 
{
   vector<string> param { "icon", ".png" };
   
   for (size_t i = 0; i < param.size(); i++)
   {
      switch (i)
      {
         case 0:
            //cout << path.stem() << " " << param[0] << endl;
            if (path.stem().string() != param[0])
               return false;
            break;
         case 1:
            //cout << path.extension() << " " << param[1] << endl;
            if (path.extension().string() != param[1])
               return false;
            break;
         default:
            break;
      }
   }
   return true;
}

void GetDirectoryFiles()
{
   int count = 0;

   for (auto &&item : fs::recursive_directory_iterator("d:/Program Files/ZealPotable/docsets/HTML.docset"))
   {
      if (Filter(item.path()))
         cout << item << endl;         
      count++;
   }

   std::cout << "Total: " << count << endl;
}

int main()
{
   //watcher::GetDirectoryFiles();
   // ParseJson parseJson;
   // parseJson.InterapOverElements();
   
   return 0;
}