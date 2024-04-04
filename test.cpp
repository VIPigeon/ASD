
#include "bin_tree.h"


void test1()
{
    std::cout << "1. Добавление элемента в дерево" << std::endl;
    BinTree<int> btree(4);
    // btree.printInQueue("_ ");
    // std::cout << std::endl;
    btree.insert(5);
    // btree.printInQueue("_ ");
    // std::cout << std::endl;
    btree.insert(3);
    // btree.printInQueue("_ ");
    // std::cout << std::endl;
    btree.insert(2);
    // btree.printInQueue("_ ");
    // std::cout << std::endl;
    btree.insert(4);
    // btree.printInQueue("_ ");
    std::cout << "Тест пройден" << std::endl;
}


void test2()
{
    std::cout << "2. Поиск элемента" << std::endl;
    BinTree<int> btree(4);
    btree.insert(5);
    btree.insert(3);
    btree.insert(2);
    btree.insert(4);
    btree.insert(7);
    btree.insert(7);

    bool answers[10] = {0, 0, 1, 1, 1, 1, 0, 1, 0, 0};

    for (int i = 0; i < 10; i++)
        if (btree.find(i) != answers[i])
            throw std::invalid_argument("Ошибка в тесте 2");
    std::cout << "Тест пройден" << std::endl;
}


void test3()
{
    std::cout << "3. Поиск минимального и максимального элементов" << std::endl;
    BinTree<int> btree(4);
    btree.insert(5);
    btree.insert(3);
    btree.insert(2);
    btree.insert(4);
    btree.insert(7);
    btree.insert(7);
    if (btree.min() != 2 || btree.max() != 7)
        throw std::invalid_argument("Ошибка в тесте 3");

    btree.insert(6);
    btree.insert(4);
    btree.insert(18);
    btree.insert(3);
    btree.insert(5);
    btree.insert(1);
    if (btree.min() != 1 || btree.max() != 18)
        throw std::invalid_argument("Ошибка в тесте 3");
    std::cout << "Тест пройден" << std::endl;
}


void test4()
{
    std::cout << "4. Поиск первого элемента, больше (меньше) или равного заданного" << std::endl;
    BinTree<int> btree(4);
    btree.insert(5);
    btree.insert(3);
    btree.insert(2);
    btree.insert(4);
    btree.insert(7);
    btree.insert(7);
    if (btree.lowerFind(3) != 3 || btree.upperFind(6) != 7 || btree.upperFind(5) != 5 || btree.lowerFind(6) != 4)
        throw std::invalid_argument("Ошибка в тесте 4");
    std::cout << "Тест пройден" << std::endl;
}

void test5()
{
    std::cout << "5. Удаление элемента" << std::endl;
    BinTree<int> btree(4);
    btree.insert(5);
    btree.insert(3);
    btree.insert(2);
    btree.insert(4);
    btree.insert(7);
    btree.insert(7);

    btree.remove(4);
    btree.remove(7);
    btree.remove(3);
    btree.remove(7);

    if (btree.find(7) || !btree.find(4) || btree.find(3) || !btree.find(5))
        throw std::invalid_argument("Ошибка в тесте 5");
    std::cout << "Тест пройден" << std::endl;
}


void test6()
{
    std::cout << "6. Вывод на экран – рекурсивный обход (ЛКП)" << std::endl;
    BinTree<int> btree(4);
    btree.insert(7);
    btree.insert(5);
    btree.insert(3);
    btree.insert(2);
    btree.insert(4);
    btree.insert(7);
    btree.printInRecursion();
    std::cout << "Тест пройден" << std::endl;
}


void test7()
{
    std::cout << "7. Вывод на экран – с использованием стека (ПКЛ) и без использования рекурсии" << std::endl;
    BinTree<int> btree(4);
    btree.insert(7);
    btree.insert(5);
    btree.insert(3);
    btree.insert(2);
    btree.insert(4);
    btree.insert(7);
    btree.printInStack();
    std::cout << "Тест пройден" << std::endl;
}


void test8()
{
    std::cout << "8. Вывод на экран «по слоям» – с использованием очереди" << std::endl;
    BinTree<int> btree(4);
    btree.insert(7);
    btree.insert(5);
    btree.insert(3);
    btree.insert(2);
    btree.insert(4);
    btree.insert(7);
    btree.printInQueue();
    std::cout << "Тест пройден" << std::endl;
}
void test9()
{
    std::cout << "9. Сравнение двух деревьев на равенство (идентичность полностью, по элементам и структуре, рекурсивно)." << std::endl;
    BinTree<int> btree(4);
    btree.insert(5);
    btree.insert(3);
    btree.insert(2);
    btree.insert(4);
    btree.insert(7);
    btree.insert(7);

    BinTree<int> btree2(3);
    btree2.insert(7);
    btree2.insert(5);
    btree2.insert(2);
    btree2.insert(4);
    btree2.insert(4);

    if (btree.dataCompare(btree2))
        throw std::invalid_argument("Ошибка в тесте 9");

    BinTree<int> btree3(5);
    btree3.insert(6);
    btree3.insert(4);
    btree3.insert(3);
    btree3.insert(5);
    btree3.insert(8);
    btree3.insert(8);
    if (!btree.structureCompare(btree3))
        throw std::invalid_argument("Ошибка в тесте 9");

    BinTree<int> btree4(4);
    btree4.insert(5);
    btree4.insert(3);
    btree4.insert(2);
    btree4.insert(4);
    btree4.insert(7);
    btree4.insert(7);
    // btree.printInQueue();
    // btree4.printInQueue();
    if (!btree.strictCompare(btree4))
        throw std::invalid_argument("Ошибка в тесте 9");
    // std::cout << std::endl;
    // btree4.printInQueue();
    std::cout << "Тест пройден" << std::endl;
}
void test10()
{
    std::cout << "10. Поиск для заданного (в виде указателя или итератора) элемента следующего и предыдущего элементов." << std::endl;
    BinTree<int> btree4(4);
    btree4.insert(5);
    btree4.insert(3);
    btree4.insert(2);
    btree4.insert(4);
    btree4.insert(7);
    btree4.insert(7);
    if (btree4.next(btree4.next(btree4.root))->data != 7 ||
        btree4.prev(btree4.prev(btree4.root))->data != 2)
    {
        throw std::invalid_argument("Ошибка в тесте 10");
    }
    std::cout << "Тест пройден" << std::endl;
}


int main()
{
    test1();
    std::cout << std::endl;
    test2();
    std::cout << std::endl;
    test3();
    std::cout << std::endl;
    test4();
    std::cout << std::endl;
    test5();
    std::cout << std::endl;
    test6();
    std::cout << std::endl;
    test7();
    std::cout << std::endl;
    test8();
    std::cout << std::endl;
    test9();
    std::cout << std::endl;
    test10();
}
