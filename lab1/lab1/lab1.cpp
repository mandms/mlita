//1.4.Заповедная роща(6)
//В заповеднике растет роща редких деревьев.Для их защиты требуется обнести рощу забором.Но для обеспечения доступа к
//остальной территории заповедника площадь участка, окруженного забором, должна быть минимальной.Деревья растут точно
//в узлах координатной сетки на расстоянии одного метра друг от друга.Любое из деревьев имеет хотя бы одного 
//соседа(с юга, севера, востока или запада).Забор состоит из блоков длиной в один метр.Чтобы огородить одно дерево необходимо 4 блока забора
//По заданной конфигурации рощи найти минимально необходимое число блоков для забора.
//Ввод.В первой строке записаны через пробел два числа N и K(1 ≤ N, K ≤ 300)– количество строк и 
//столбцов данных.В следующих N строках содержатся последовательности из K символов(единиц или нулей).
//Единицей обозначается расположение дерева, а нулем – его отсутствие в узле координатной сетки.
//Вывод.В единственной строке выводится число блоков забора, необходимое для огораживания.
//Юдин ПС-22


#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> Stack;
typedef vector<vector<char>> Field;

struct St
{
    int h;
    int w;
    St* next;
};

void border(Field& field, int w, int h)
{
    fill(field[0].begin(), field[0].end(), '*');
    fill(field.back().begin(), field.back().end(), '*');
    // Заполняем левую и правую границы
    for (auto& row : field) {
        row[0] = '*';
        row.back() = '*';
    }
}

//void border(Field& field, int w, int h) //забор
//{
//    for (int i = 0; i < h + 2; i++)
//    {
//        for (int j = 0; j < w + 2; j++)
//        {
//            field[i][j] = '*';
//        }
//    }
//}

void read(ifstream& input, Field& field)
{
    int h, w;
    input >> h;
    input >> w;

    field.resize(h + 2, vector<char>(w + 2));
    border(field, w, h);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            char ch;
            input >> ch;
            field[i + 1][j + 1] = ch;
        }
    }
}

void write(Field field)
{
    for (int i = 0; i < field.size(); i++)
    {
        for (int j = 0; j < field[i].size(); j++)
        {
            cout << field[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void Push(int i, int j, Field& field, St*& p, int& count)
{
    if (field[i][j] == '1')
    {
        St* t = new St;
        t->h = i;
        t->w = j;
        t->next = p;
        p = t;

        int v = 0;
        if ((field[i + 1][j] == '#'))
            v += 2; //+=2 потому что сторону текущего и соседа
        if ((field[i - 1][j] == '#'))
            v += 2;
        if ((field[i][j + 1] == '#'))
            v += 2;
        if ((field[i][j - 1] == '#'))
            v += 2;
        field[i][j] = '#';
        count += 4 - v;
    }
}

void Pop(int& i, int& j, St*& p)
{
    i = p->h;
    j = p->w;
    St* t = p;
    p = p->next;
    delete t;
}

void Mark(int i, int j, Field& field, int& count)
{
    St* top = 0;
    Push(i, j, field, top, count);

    while (top)
    {
        Pop(i, j, top);
        Push(i + 1, j, field, top, count);
        Push(i, j + 1, field, top, count);
        Push(i - 1, j, field, top, count);
        Push(i, j - 1, field, top, count);
    }
}
//if (field[i][j] == '1')
//{
//    int v = 0;
//    if ((field[i + 1][j] == '#'))
//        v += 2; //+=2 потому что сторону текущего и соседа
//    if ((field[i - 1][j] == '#'))
//        v += 2;
//    if ((field[i][j + 1] == '#'))
//        v += 2;
//    if ((field[i][j - 1] == '#'))
//        v += 2;
//    count += 4 - v;
//    field[i][j] = '#';
//    Mark(i + 1, j, field, count);
//    Mark(i - 1, j, field, count);
//    Mark(i, j + 1, field, count);
//    Mark(i, j - 1, field, count);
//} 

void PushHole(int i, int j, Field& field, St*& p, bool& isBoundary)
{
    if (field[i][j] == '0')
    {
        St* t = new St;
        t->h = i;
        t->w = j;
        t->next = p;
        p = t;
        if ((i == 1) || (j == 1) || (i == field.size() - 2) || (j == field[i].size() - 2))
        {
            isBoundary = true;
        }
        field[i][j] = '-';
    }
}

void checkHole(int i, int j, Field& field, bool& isBoundary)
{
    St* top = 0;
    PushHole(i, j, field, top, isBoundary);

    while (field[top->h][top->w + 1] == '0' || field[top->h][top->w - 1] == '0' || field[top->h + 1][top->w] == '0' || field[top->h - 1][top->w] == '0')
    {
        PushHole(top->h + 1, top->w, field, top, isBoundary);
        PushHole(top->h, top->w + 1, field, top, isBoundary);
        PushHole(top->h - 1, top->w, field, top, isBoundary);
        PushHole(top->h, top->w - 1, field, top, isBoundary);
    }
    while (top)
    {
        Pop(i, j, top);
        if (field[i][j] == '-' && !isBoundary) {
            field[i][j] = '1';
        }
    }
    isBoundary = false;
}

int countForests(Field& field) //поиск рощи
{
    int count = 0;
    bool isBoundary = false;
    for (int i = 0; i < field.size(); i++)
    {
        for (int j = 0; j < field[i].size(); j++)
        {
            if (field[i][j] == '0')
            {
                checkHole(i, j, field, isBoundary);
            }
        }
    }
    //write(field);
    for (int i = 0; i < field.size(); i++)
     {
         for (int j = 0; j < field[i].size(); j++)
         {
             if (field[i][j] == '1')
             {
                 Mark(i, j, field, count);
             }
         }
     }
    return count;
}

int main()
{
    auto start_time = std::chrono::steady_clock::now();

    std::ifstream input;
    input.open("input1.txt");

    std::ofstream output;
    output.open("output.txt");

    Field field;

    read(input, field);

    output << countForests(field) << endl;

    auto end_time = std::chrono::steady_clock::now();
    double elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << elapsed_ns * 1e-9 << "sec \n";
    return 0;
}