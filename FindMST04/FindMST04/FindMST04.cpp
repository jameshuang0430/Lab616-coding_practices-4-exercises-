#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

//                                                   __----~~~~~~~~~~~------___
//                                     .  .   ~~//====......          __--~ ~~
//                     -.            \_|//     |||\\  ~~~~~~::::... /~
//                  ___-==_       _-~o~  \/    |||  \\            _/~~-
//          __---~~~.==~||\=_    -_--~/_-~|-   |\\   \\        _/~
//      _-~~     .=~    |  \\-_    '-~7  /-   /  ||    \      /
//    .~       .~       |   \\ -_    /  /-   /   ||      \   /
//   /  ____  /         |     \\ ~-_/  /|- _/   .||       \ /
//   |~~    ~~|--~~~~--_ \     ~==-/   | \~--===~~        .\
//            '         ~-|      /|    |-~\~~       __--~~
//                        |-~~-_/ |    |   ~\_   _-~            /\
//                             /  \     \__   \/~                \__
//                         _--~ _/ | .-~~____--~-/                  ~~==.
//                        ((->/~   '.|||' -_|    ~~-/ ,              . _||
//                                   -_     ~\      ~~---l__i__i__i--~~_/
//                                   _-~-__   ~)  \--______________--~~
//                                 //.-~~~-~_--~- |-------~~~~~~~~
//                                        //.-~~~--\
//                                 神獸保佑，程式碼沒Bug!


int readFileData(string fileName);
int writeFileData(string fileName);
double findDistance(struct node a, struct node b);
bool isCycle(string name2);
void split(string& s);
void coutVectorData(vector<struct node>& v);
void findMST();

double sum = 0;
string inputFileName;
string fileNumber;
string outputFileName = "mst";

struct node {
    string nodeName;
    int x;
    int y;
};
struct edge {
    string node1;
    string node2;
    double distance;
};

vector<node> nodelist;
vector<edge> lengthlist;
vector<edge> MST;

ifstream fin;
ofstream fout;

static bool compareDistance(const edge& a, const edge& b) {
    return a.distance < b.distance;
}

int main()
{
    cout << "Enter the file name: ";
    cin >> inputFileName;

    readFileData(inputFileName);
    findMST();

    outputFileName += fileNumber;
    writeFileData(outputFileName);
}

int readFileData(string fileName)
{
    //get file number 
    for (int i = 0; i < inputFileName.size(); i++)
    {
        if (inputFileName[i] == '_')
        {
            fileNumber += inputFileName[i];
        }
        if (isdigit(inputFileName[i]))
        {
            fileNumber += inputFileName[i];
        }
    }
    //open the required file
    fin.open("res\\" + inputFileName);
    if (!fin.is_open()) {
        cout << "Failed to open intput file.\n";
        return 1; // EXIT_FAILURE
    }

    //split data
    string line;
    while (getline(fin, line)) {
        split(line);
    }
    fin.close();
}
int writeFileData(string fileName)
{
    fout.open("res\\" + fileName + ".txt");
    if (fout.fail()) {
        cout << "Failed to open output file.\n";
        return 1;
    }

    for (int i = 0; i < MST.size(); i++)
    {
        fout << "(" << MST[i].node1 << "," << MST[i].node2 <<")Length = " << MST[i].distance << endl;
    }
    fout << "****************************" << endl;
    fout << "Total Wire Length = " << sum << endl;
}
void coutVectorData(vector<node>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].nodeName << " " << v[i].x << " " << v[i].y << endl;
    }

    cout << "***************" << endl;
}
void split(string& s)
{
    string temp;
    string nodename;
    int x_pos = 0;
    int y_pos = 0;
    int begin = 0;
    for (int i = 0; i <= s.size(); i++)
    {
        if (s[i] == '(')
        {
            nodename += s.substr(begin, i);
            begin = i + 1;
        }
        if (s[i] == ',')
        {
            temp = s.substr(begin, i);
            x_pos = stoi(temp);
            begin = i + 1;
            temp = {};
        }
        if (s[i] == ')')
        {
            temp = s.substr(begin, i);
            y_pos = stoi(temp);
            begin = 0;
            temp = {};
        }
    }
    nodelist.push_back({ nodename, x_pos, y_pos });
}
double findDistance(struct node a, struct node b)
{
    double distance = 0;
    distance = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    return distance;
}
void findMST()
{
    for (int j = 0; j < nodelist.size(); j++)
    {
        for (int i = j + 1; i < nodelist.size(); i++)
        {
            lengthlist.push_back({ nodelist[j].nodeName, nodelist[i].nodeName, findDistance(nodelist[j], nodelist[i]) });
        }
    }
    sort(lengthlist.begin(), lengthlist.end(), compareDistance);

    /*
    //cout legthlist
    for (int i = 0; i < lengthlist.size(); i++)
    {
        cout << lengthlist[i].node1 << " " << lengthlist[i].node2 << " " << lengthlist[i].distance << endl;
    }
    cout << "***************" << endl;
    */
    while (!lengthlist.empty() || MST.size() < nodelist.size() - 1)
    {
        if (!isCycle(lengthlist[0].node2))
        {
            MST.push_back(lengthlist[0]);
        }
        else
        {
            lengthlist.erase(lengthlist.begin());
        }
    }
    
    for (int i = 0; i < MST.size(); i++)
    {
        sum += MST[i].distance;
    }
    /*
    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < MST.size(); i++)
    {
        cout << MST[i].node1 << " " << MST[i].node2 << " " << MST[i].distance << endl;
    }
    cout << "***************" << endl;
    cout << "Total Wire Length = " << sum << endl;
    */
}
bool isCycle(string name2)
{
    if (MST.empty())
    {
        return false;
    }
    for (int i = 0; i < MST.size(); i++)
    {
        if (name2 == MST[i].node2)
        {
            return true;
        }
    }
    return false;
}