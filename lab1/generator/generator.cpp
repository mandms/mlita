
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef vector<vector<char>> Field;

vector<string> Templates = {
    "11111", "01111", "00111", "00011", "00001", "00000", "10001", "11011", "10011", "11001"
};

void generate(int w, int h, Field& field)
{
    field.resize(h);
    for (int i = 0; i < h; i++)
    {
        field[i].resize(w);
        for (int j = 0; j < w; j++)
        {
            field[i][j] = '1';
        }
    }

    //int rw = 0 + rand() % w;
    //int rh = 0 + rand() % h;

    //for (int i = 0; i < h; i++)
    //{
    //    field[i].resize(w);
    //    for (int j = 0; j < w; j++)
    //    {
    //        if ((i == rw) && (j == rh))
    //            field[i][j] = '1';
    //    }
    //}
}

void figure(int i, int j, Field& field, int quantity = 0)
{
    if (field[i][j] != '1' && quantity < 5)
    {
        field[i][j] = '1';
        quantity++;
        figure(i + 1, j, field, quantity);

    }
}

void write(int w, int h, Field field)
{
    std::ofstream output;
    output.open("output.txt");
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int r = rand() % 4 + 0;
            output << Templates[r];
        }
        output << endl;
    }
}

int main()
{
    int w, h;
    cin >> w >> h;

    Field field;

    //generate(w, h, field);
    write(w, h, field);
    
}
