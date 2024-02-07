#include<iostream>
#include<fstream>
#include<vector>
//#include<algorithm>
using namespace std;
string inputFileName;
string outputFilePath = "output";

void coutContent(const vector<struct Data> V);//Test; print content vector 

void readContent();
void quickSort(vector<struct Data> &V, int low, int high);
int partition(vector<struct Data> &V, int low, int high);
void binarySearch(vector<struct Data> V);
void foutContent(vector<struct Data> &V);

vector<struct Data> inputContent;

struct Data
{
    string Name;
    int Value;
};
static bool comparing(Data a, Data b)
{
    return a.Value < b.Value;
}
ifstream fin;
ofstream fout;


int main(void)
{
    cout << "Enter the file name: ";
    cin >> inputFileName;

    //open the required file
    fin.open("res\\" + inputFileName);
    if (!fin.is_open()) {
        cout << "Failed to open intput file.\n";
        return 1; // EXIT_FAILURE
    }


    readContent();//read input content 

    quickSort(inputContent, 0, inputContent.size()-1);//quick sort

    



    outputFilePath += inputFileName[5];
    //open the output file 
    fout.open("res\\" + outputFilePath + ".txt");
    if (fout.fail()) { 
        cout << "Failed to open output file.\n";
        return 1;
    }
    binarySearch(inputContent);//binary search
    fout << "****************" << endl;

    foutContent(inputContent);
    fout.close();
}


void readContent()
{
    string name;
    int value;

    while (fin >> name >> value)
    {
        inputContent.push_back({ name,value });
    }
    //printcontent(inputContent);
    fin.close();//close the input file
}
void foutContent(vector<struct Data> &V)
{
    for (int i = 0; i < V.size(); i++)
    {
        fout << V[i].Name << " " << V[i].Value << endl;
    }

}

void quickSort(vector<struct Data> &V, int low, int high)
{
    if (low < high) {
        int pivotIndex = partition(V, low, high);

        quickSort(V, low, pivotIndex - 1);//the part less than pivot
        quickSort(V, pivotIndex + 1, high);//the part larger than pivot
    }
}
int partition(vector<struct Data> &V, int low, int high)
{
    Data pivot = V[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (V[j].Value < pivot.Value) {
            swap(V[++i], V[j]);
        }
    }

    swap(V[i + 1], V[high]);
    return i + 1;
}

void binarySearch(vector<struct Data> V)
{
    int targetNumber;
    cout << "Enter the target number: ";
    cin >> targetNumber;
    cout << endl;

    //binary searching
    int left = 0;
    int right = V.size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (V[mid].Value < targetNumber)
        {
            left = mid + 1;
        }
        else if (V[mid].Value > targetNumber)
        {
            right = mid - 1;
        }
        else
        {
            if (mid == left)
            {
                cout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                fout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                while (mid != right && V[++mid].Value == targetNumber)//search forward
                {
                    cout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                    fout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                }
            }
            else if (mid == right)
            {
                cout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                fout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                while (mid != left && V[--mid].Value == targetNumber)//search backward
                {
                    cout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                    fout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                }
            }
            else
            {
                cout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                fout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                while (mid != right && V[++mid].Value == targetNumber)//search forward
                {
                    cout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                    fout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                }
                mid = (left + right) / 2;
                while (mid != 0 && V[--mid].Value == targetNumber)//search backward
                {
                    cout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                    fout << "Find" << " " << V[mid].Name << " " << V[mid].Value << endl;
                }
            }break;
        }
    }
    if (left > right)
    {
        cout << "Cannot Find" << " " << targetNumber << endl;
        fout << "Cannot Find" << " " << targetNumber << endl;
    }
}
void coutContent(vector<struct Data> V)
{
    for (int i = 0; i < V.size(); i++)
    {
        cout << V[i].Name << " " << V[i].Value << endl;
    }
}
