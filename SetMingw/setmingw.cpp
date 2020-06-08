#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int msg[6] {1, 2, 3, 4, 5, 6};

    for (const int& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}