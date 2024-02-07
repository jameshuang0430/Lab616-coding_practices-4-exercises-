#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
int whichMode();
int MODE = 0;// switch function variable to tell which mode 
int row1 = 0;
int row2 = 0;
int col1 = 0;
int col2 = 0;
void getArray1();
void getArray2();
void split1(string&s);
void split2(string& s);

// asked function for the question 
void transpose();
void multiplication();
void inverse();
ifstream ifs;
string mode;//get first line content of the file 
string fileName;
string name1;
string name2;
string case1 = "Matrix_Transpose";
string case2 = "Matrix_Multiplication";
string case3 = "Matrix_Inverse";
std::vector<std::vector<double>> T_array;
std::vector<std::vector<double>> M_array1;
std::vector<std::vector<double>> M_array2;
std::vector<std::vector<double>> I_array;
vector<string> splitResult1;
vector<string> splitResult2;

int main()
{
    cout << "Enter file name: ";
    cin >> fileName;
    ifs.open("res\\" + fileName);//target file

    //check if file is opened correctly
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
        return 1; 
    }
    getline(ifs, mode);
    cout << mode << endl;//first line
    getline(ifs, name1);
    cout << name1 << endl;//second line

    MODE = whichMode();

    switch (MODE)
    {   
        case 1:
            getArray1();
            transpose();
            cout << "End_Matrix_Transpose" << endl;
            break;
        case 2:
            getArray1();
            getArray2();
            multiplication();
            cout << "End_Matrix_Multiplication" << endl;
            break;
        case 3:
            cout << "invalid file path." << endl;
            break;
    }
    ifs.close();
}

int whichMode()
{
    //transpose
    if (mode[7] == case1[7])
    {
        MODE = 1;
    }
    //multiplication
    else if (mode[7] == case2[7])
    {
        MODE = 2;
    }
    //inverse
    else if(mode[7] == case3[7])
    {
        MODE = 3;
    }
    return MODE;
}
void getArray1()
{
    string content = {};
    while (getline(ifs, content)) {
        cout << content << endl;
        if (content[0] == 'E' || content[0] == 'N') { break; }//keyword: 'End' or 'Name'
        else { split1(content); }
    }
}
//split with ' ' and end with ';'
void split1(string &content) 
{
    int begin = 0;
    int current=0;
    string temp;
    while (1)
    {
        if (content[current] == ' ')
        {
            for (begin; begin <= current; begin++)
            {
                temp += content[begin];
            }
            splitResult1.push_back(temp);
            begin = current + 1;
            temp = {};
        }
        else if (content[current] == ';') { row1++; break; }
        current++;
    }
}

void getArray2()
{
    string content = {};
    while (getline(ifs, content)) {
        cout << content << endl;
        if (content[0] == 'E') { break; }//keyword: End or Name
        else { split2(content); }
    }
}

void split2(string& content)
{
    int begin = 0;
    int current = 0;
    string temp;
    while (1)
    {
        if (content[current] == ' ')
        {
            for (begin; begin <= current; begin++)
            {
                temp += content[begin];
            }
            splitResult2.push_back(temp);
            begin = current + 1;
            temp = {};
        }
        else if (content[current] == ';') { row2++; break; }
        current++;
    }
}
void transpose()
{
    col1 = (splitResult1.size()) / row1;

     //assign value to T_array
    T_array.resize(row1);
    for (int i = 0; i<row1; i++)
    {
        T_array[i].resize(col1);
        for (int j=0; j<col1;j++)
        {
            T_array[i][j] = stod(splitResult1[j + i*col1]);
        }
    }
    //transpose T_array
    cout << "\nTransposed result" << endl;
    vector<vector<double>> transposed;
    transposed.resize(col1);
    for (int i= 0; i<col1;i++)
    {
        transposed[i].resize(row1);
        for (int j=0; j<row1;j++)
        {
            transposed[i][j] = T_array[j][i];
            cout << transposed[i][j] << " ";
        }
        std::cout << ";" << std::endl;
    }
    
}
void multiplication()
{
    col1 = (splitResult1.size()) / row1;
    col2 = (splitResult2.size()) / row2;

    //assign value to M_array1
    M_array1.resize(row1);
    for (int i = 0; i < row1; i++)
    {
        M_array1[i].resize(col1);
        for (int j = 0; j < col1; j++)
        {
            M_array1[i][j] = stod(splitResult1[j + i * col1]);
        }
    }
    //assign value to M_array2
    M_array2.resize(row2);
    for (int i = 0; i < row2; i++)
    {
        M_array2[i].resize(col2);
        for (int j = 0; j < col2; j++)
        {
            M_array2[i][j] = stod(splitResult2[j + i * col2]);
        }
    }

    //multiplication 
    cout << "\nMultiplicated result" << endl;
    vector<vector<double>> multiplicated;

    multiplicated.resize(row1);
    for (int i=0;i<row1; i++)
    {
        multiplicated[i].resize(col2);
        for (int j = 0; j < col2; j++)
        {
            for (int k = 0;k < col1; k++)
            {
                multiplicated[i][j] += M_array1[i][k] * M_array2[k][j];
            }
            cout << multiplicated[i][j] << " ";
        }
        std::cout << ";" << std::endl;
    }
}
//void inverse(){}