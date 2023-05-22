#include <fstream>
#include <iostream>
#include <set>

using namespace std;

class Graph
{
private:
    bool **adjMatrix;
    int numVertices;

public:
    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        adjMatrix = new bool *[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            adjMatrix[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++)
            {
                adjMatrix[i][j] = false;
            }
        }
    }

    void setAdjMatrix(bool **adjMatrix)
    {
        this->adjMatrix = adjMatrix;
    }

    void addLink(int i, int j)
    {
        adjMatrix[i][j] = true;
    }

    void removeEdge(int i, int j)
    {
        adjMatrix[i][j] = false;
    }
    bool **getAdjMatrix()
    {
        return adjMatrix;
    }

    void memMatrixPrint()
    {
        for (int i = 0; i < numVertices; i++)
        {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++)
            {
                cout << &adjMatrix[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    void toString()
    {
        char pChar = 'A';
        cout << "-> : A B C D E \n";
        for (int i = 0; i < numVertices; i++)
        {
            cout << pChar << "  : ";
            for (int j = 0; j < numVertices; j++)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << "\n";
            pChar++;
        }
        cout << "\n";
    }
    int size()
    {
        return numVertices;
    }
};

bool IsGoodInitiator(int node, Graph g)
{
    int numVertices = g.size();
    bool **adjMatrix = g.getAdjMatrix();
    set<int> nodesCoveredSet;

    nodesCoveredSet.insert(node);

    bool newNodeFound = true;
    while (newNodeFound && nodesCoveredSet.size() < numVertices)
    {
        newNodeFound = false;
        set<int> newNodes;

        for (int node : nodesCoveredSet)
        {
            for (int i = 0; i < numVertices; i++)
            {
                if (adjMatrix[node][i] && (nodesCoveredSet.count(i) == 0))
                {
                    newNodes.insert(i);
                    newNodeFound = true;
                }
            }
        }
        nodesCoveredSet.insert(newNodes.begin(), newNodes.end());
    }

    if (nodesCoveredSet.size() == numVertices)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char *argv[])
{
    // First we check out inputs and create our bolean matrix for our dataset
    // we assume the structure of the dataset is correct
    if (argc == 2)
    {
        std::ifstream inputFile;
        inputFile.open(argv[1]);

        bool **adjMatrix;
        if (inputFile.is_open())
        {
            // We ingest the first line of the file separetly in order to alocate the memory of our arrays
            string line;
            string auxLine = "";
            std::getline(inputFile, line);
            for (int j = 0; j < line.size(); j++)
            {
                if (line[j] == '0' || line[j] == '1')
                    auxLine += line[j];
            }

            int graphSize = auxLine.size();

            adjMatrix = new bool *[graphSize];
            adjMatrix[0] = new bool[graphSize];

            for (int j = 0; j < graphSize; j++)
            {
                if (auxLine[j] == '0')
                    adjMatrix[0][j] = false;
                else if (auxLine[j] == '1')
                    adjMatrix[0][j] = true;
            }

            // Here we process the rest of the file lines
            int rowIndex;
            for (int i = 1; i < graphSize; i++)
            {
                std::getline(inputFile, line);

                rowIndex = 0;
                adjMatrix[i] = new bool[graphSize];
                for (int j = 0; j < line.size(); j++)
                {
                    if (line[j] == '0')
                    {
                        adjMatrix[i][rowIndex] = false;
                        rowIndex++;
                    }
                    else if (line[j] == '1')
                    {
                        adjMatrix[i][rowIndex] = true;
                        rowIndex++;
                    }
                }
            }
            // Print the matrix
            for (int i = 0; i < graphSize; i++)
            {
                for (int j = 0; j < graphSize; j++)
                {
                    cout << adjMatrix[i][j];
                }
                std::cout << "\n";
            }
            std::cout << "\n";

            // Now we create a graph and set its adjMatrix
            Graph g(graphSize);
            g.setAdjMatrix(adjMatrix);
            bool **graphMatrix = g.getAdjMatrix();

            // And check if it is a valid initializer node
            if (IsGoodInitiator(0, g))
            {
                cout << "Node A is a valid initializer node \n";
            }
        }
        else
        {
            std::cout << "Error while opening file \n " << std::endl;
            return 0;
        }
    }
    else if (argc > 2)
    {
        std::cout << "Too many arguments" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "No dataset provided" << std::endl;
        return 0;
    }
}