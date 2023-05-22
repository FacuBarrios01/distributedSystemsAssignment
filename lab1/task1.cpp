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

    void addLink(int i, int j)
    {
        adjMatrix[i][j] = true;
    }

    void removeEdge(int i, int j)
    {
        adjMatrix[i][j] = false;
        adjMatrix[j][i] = false;
    }
    bool** getAdjMatrix(){
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

    ~Graph()
    {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }
};

int main()
{
    int numVertices = 5;
    Graph g(numVertices);

    g.addLink(0, 3);
    g.addLink(0, 2);
    g.addLink(0, 4);

    g.addLink(1, 3);

    g.addLink(2, 1);
    g.addLink(2, 3);

    g.addLink(3, 1);

    g.addLink(4, 1);
    g.addLink(4, 0);

    g.toString();
    g.memMatrixPrint();

    bool** adjMatrix = g.getAdjMatrix();
    set<int> nodesCoveredSet;

    nodesCoveredSet.insert(0);

    bool newNodeFound = true;
    while (newNodeFound && nodesCoveredSet.size() < numVertices )
    {
        newNodeFound = false;
        set<int> newNodes;

        for(int node : nodesCoveredSet){
            for (int i = 0; i < numVertices; i++)
            {
                if( adjMatrix[node][i] && (nodesCoveredSet.count(i) == 0))
                {
                    newNodes.insert(i);
                    newNodeFound = true;
                }
            }
        }
        nodesCoveredSet.insert(newNodes.begin(), newNodes.end());
    }

    if(nodesCoveredSet.size() == numVertices)
    {
        cout << "Node A is a good initiator.\n";
    } else {
        cout << "Node A is not a good initiator.\n";
    }
}