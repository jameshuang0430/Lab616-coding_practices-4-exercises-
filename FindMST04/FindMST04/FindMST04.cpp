#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

int readFileData(string fileName);
int writeFileData(string fileName);
double findDistance(struct node a, struct node b);
void split(string& s);
void coutVectorData(vector<struct node>& v);
void findMST();
bool isInVisited(string targetNode);


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
vector<string> visited;

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
        fout << "(" << MST[i].node1 << "," << MST[i].node2 << ")Length = " << MST[i].distance << endl;
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
        for (int i = 0; i < nodelist.size(); i++)
        {
            if (nodelist[i].nodeName == nodelist[j].nodeName) { continue; }
            lengthlist.push_back({ nodelist[j].nodeName, nodelist[i].nodeName, findDistance(nodelist[j], nodelist[i]) });
        }
    }
    cout << "***************" << endl;
    sort(lengthlist.begin(), lengthlist.end(), compareDistance);

    //cout legthlist
    for (int i = 0; i < lengthlist.size(); i++)
    {
        cout << lengthlist[i].node1 << " " << lengthlist[i].node2 << " " << lengthlist[i].distance << endl;
    }
    cout << "***************" << endl;

    

    //the algorithm of finding MST 
    int current = 0;
    visited.push_back(lengthlist[current].node1);

    while (MST.size() < nodelist.size() - 1)
    {
        bool node1State = false;
        bool node2State = false;

        if (isInVisited(lengthlist[current].node1) != node1State and  isInVisited(lengthlist[current].node2) == node2State)
        {
            MST.push_back(lengthlist[current]);
            visited.push_back(lengthlist[current].node2);
            current = 0;
        }
        else if (isInVisited(lengthlist[current].node1) == node1State and isInVisited(lengthlist[current].node2) != node2State)
        {
            MST.push_back(lengthlist[current]);
            visited.push_back(lengthlist[current].node1);
            current = 0;
        }
        else
        {
            current++;
            continue;
        }
        current++;
    }

    for (int i = 0; i < MST.size(); i++)
    {
        sum += MST[i].distance;
    }

    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < MST.size(); i++)
    {
        cout << MST[i].node1 << " " << MST[i].node2 << " " << MST[i].distance << endl;
    }
    cout << "***************" << endl;
    cout << "Total Wire Length = " << sum << endl;
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


