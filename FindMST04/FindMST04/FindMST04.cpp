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
void split(string& s);
void findMST();
bool isInVisited(string targetNode);

double sum = 0;
string fileNumber;
string inputFileName;
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
vector<node> nodelist;//to store the attribution of the each nodes
vector<edge> lengthlist;//to store the attribution of the each edges
vector<edge> MST;//to store the edges that satisfying the properties to form the minimum spanning tree 
vector<string> visited;//to record the node those which has been visited

ifstream fin;
ofstream fout;

//define a comparing method
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
    cout << "OK !" << endl;
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
        fout << "(" << MST[i].node1 << "," << MST[i].node2 << ")Length = " << MST[i].distance << endl;
    }
    fout << "****************************" << endl;
    fout << "Total Wire Length = " << sum << endl;
    fout.close();
}

void split(string& str)
{
    string temp;
    string nodename;
    int x_pos = 0;
    int y_pos = 0;
    int begin = 0;
    for (int i = 0; i <= str.size(); i++)
    {
        if (str[i] == '(')
        {
            nodename += str.substr(begin, i);
            begin = i + 1;
        }
        if (str[i] == ',')
        {
            temp = str.substr(begin, i);
            x_pos = stoi(temp);
            begin = i + 1;
            temp = {};
        }
        if (str[i] == ')')
        {
            temp = str.substr(begin, i);
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
        for (int i = 0; i < nodelist.size(); i++)
        {
            if (nodelist[i].nodeName == nodelist[j].nodeName) { continue; }
            lengthlist.push_back({ nodelist[j].nodeName, nodelist[i].nodeName, findDistance(nodelist[j], nodelist[i]) });
        }
    }
    //sort the lengthlist in ascending form
    sort(lengthlist.begin(), lengthlist.end(), compareDistance);
    //the algorithm of finding MST 
    int current = 0;
    visited.push_back(lengthlist[current].node1);//the initial node 
    while (MST.size() < nodelist.size() - 1)
    {
        bool node1State = false;
        bool node2State = false;

        //node1 is in visited list and node2 is not
        if (isInVisited(lengthlist[current].node1) != node1State and isInVisited(lengthlist[current].node2) == node2State)
        {
            MST.push_back(lengthlist[current]);
            visited.push_back(lengthlist[current].node2);
            current = 0;
        }
        //node2 is in visited list and node1 is not 
        else if (isInVisited(lengthlist[current].node1) == node1State and isInVisited(lengthlist[current].node2) != node2State)
        {
            MST.push_back(lengthlist[current]);
            visited.push_back(lengthlist[current].node1);
            current = 0;
        }
        //node1 and node2 are both in visited list or both not
        else
        {
            current++;
            continue;
        }
        current++;
    }

    //calculate the total weight
    for (int i = 0; i < MST.size(); i++)
    {
        sum += MST[i].distance;
    }
}

bool isInVisited(string targetNode)
{
    for (int i = 0; i < visited.size(); i++)
    {
        if (targetNode == visited[i])
        {
            return true;
        }
    }
    return false;
}


