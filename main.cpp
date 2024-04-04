
#include "bin_tree.h"


void findInRangeTest(BinTree<int> btree)
{
    for (int i = 0; i < 10; i++)
        std::cout << i << " ";
    std::cout << std::endl;
    for (int i = 0; i < 10; i++)
    {
        if (btree.find(i) == btree.end())
        {
            std::cout << "- ";
            continue;
        }
        std::cout << *btree.find(i) << " ";
    }
    std::cout << std::endl;
}


int main()
{
    BinTree<int> btree(4);
    btree.insert(5);
    btree.insert(3);
    btree.insert(2);
    btree.insert(4);
    btree.insert(7);
    btree.insert(7);
    // for (auto i = btree.begin(); i != btree.end(); ++i)
    // {
    //     std::cout << *i << ' ';
    // }
    findInRangeTest(btree);
}
