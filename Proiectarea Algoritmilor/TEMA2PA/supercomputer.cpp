#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// Structură ce reprezintă un nod de adiacență într-o listă de adiacență.
struct AdjListNode {
    int dest;
    struct AdjListNode *next;
};

// Structură ce reprezintă o listă de adiacență pentru un nod din graf.
struct AdjList {
    struct AdjListNode *head;
};

// Structura pentru graf.
struct Graph {
    int V;
    struct AdjList *array;
    vector<int> data;  // Seturile de date pentru fiecare nod
};

// Funcție pentru crearea unui nou nod de adiacență.
struct AdjListNode *newAdjListNode(int dest) {
    struct AdjListNode *newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->next = nullptr;
    return newNode;
}

// Funcție pentru adăugarea unei muchii în graf.
void addEdge(struct Graph *graph, int src, int dest) {
    // Adăugăm o muchie de la src la dest.
    struct AdjListNode *newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Funcție pentru citirea datelor de intrare.
void readInput(struct Graph *graph) {
    ifstream inputFile("supercomputer.in");
    if (!inputFile) {
        cerr << "Eroare la deschiderea fisierului de intrare." << endl;
        exit(1);
    }

    int N, M;
    inputFile >> N >> M;

    graph->V = N;
    graph->array = new AdjList[N];

    // Citim seturile de date pentru fiecare nod.
    for (int i = 0; i < N; i++) {
        int data;
        inputFile >> data;
        graph->data.push_back(data);
    }

    // Citim dependențele între noduri și adăugăm muchiile în graf.
    for (int i = 0; i < M; i++) {
        int u, v;
        inputFile >> u >> v;
        addEdge(graph, u - 1, v - 1);
        // Scădem 1 pentru a obține indexarea corectă a nodurilor în graf.
    }

    inputFile.close();
}

// Funcție pentru sortarea topologică a grafului.
vector<int> topologicalSort(struct Graph *graph, int data) {
    vector<int> result;  // Rezultatul sortării topologice

    // Inițializăm un vector pentru a număra numărul
    // de dependențe către fiecare nod.
    vector<int> inDegree(graph->V, 0);

    // Calculăm numărul de dependențe pentru fiecare nod.
    for (int i = 0; i < graph->V; i++) {
        struct AdjListNode *curr = graph->array[i].head;
        while (curr != nullptr) {
            inDegree[curr->dest]++;
            curr = curr->next;
        }
    }

    // Cream o coadă pentru a stoca nodurile fără dependențe.
    queue<int> q1;
    for (int i = 0; i < graph->V; i++) {
        if (inDegree[i] == 0 && graph->data[i] == 1) {
            q1.push(i);
        }
    }

    queue<int> q2;
    for (int i = 0; i < graph->V; i++) {
        if (inDegree[i] == 0 && graph->data[i] == 2) {
            q2.push(i);
        }
    }

    // Parcurgem nodurile și eliminăm dependențele acestora.
    while (!q1.empty() || !q2.empty()) {
        if (!q1.empty() && data == 1) {
            int k;
            k = q1.front();
            q1.pop();
            result.push_back(k);
            // Parcurgem vecinii nodului curent.
            struct AdjListNode *temp = graph->array[k].head;
            while (temp != nullptr) {
                inDegree[temp->dest]--;
                if (inDegree[temp->dest] == 0 && graph->data[temp->dest] == 1) {
                    q1.push(temp->dest);
                } else if (inDegree[temp->dest] == 0 &&
                graph->data[temp->dest] == 2) {
                    q2.push(temp->dest);
                }
                temp = temp->next;
            }
            continue;
        } else {
            if (q1.empty())
            data = 2;
        }
        if (!q2.empty() && data == 2) {
            int k;
            k = q2.front();
            q2.pop();
            result.push_back(k);
            // Parcurgem vecinii nodului curent.
            struct AdjListNode *temp = graph->array[k].head;
            while (temp != nullptr) {
                inDegree[temp->dest]--;
                if (inDegree[temp->dest] == 0 && graph->data[temp->dest] == 1) {
                    q1.push(temp->dest);
                } else if (inDegree[temp->dest] == 0 &&
                graph->data[temp->dest] == 2) {
                    q2.push(temp->dest);
                }
                temp = temp->next;
            }
        } else {
            if (q2.empty())
            data = 1;
        }
    }

    // Verificăm dacă există dependențe nesatisfăcute pentru anumite noduri.
    for (int i = 0; i < graph->V; i++) {
        if (inDegree[i] > 0) {
            // Nodul i are dependențe nesatisfăcute, deci nu putem obține
            // o sortare topologică validă.
            result.clear();  // Golește rezultatul sortării topologice
            break;
        }
    }

    return result;
}

// Funcție pentru determinarea numărului minim de context switch-uri.
int countContextSwitches(struct Graph *graph, vector<int> &sorted) {
    int numContextSwitches = 0;
    int prevData = -1;  // Setul de date al task-ului precedent

    for (int i = 0; i < sorted.size(); i++) {
        int currTask = sorted[i];
        int currData = graph->data[currTask];
        // Obține setul de date pentru task-ul curent

        if (currData != prevData) {
            numContextSwitches++;
        }

        prevData = currData;
    }

    return numContextSwitches - 1;
    // Scădem 1 pentru a obține numărul minim de context switch-uri
}

int main() {
    struct Graph graph;
    readInput(&graph);

    vector<int> sorted = topologicalSort(&graph, 1);
    vector<int> sorted2 = topologicalSort(&graph, 2);
    int numContextSwitches = countContextSwitches(&graph, sorted);
    int numContextSwitches2 = countContextSwitches(&graph, sorted);

    ofstream outputFile("supercomputer.out");
    if (!outputFile) {
        cerr << "Eroare la deschiderea fisierului de iesire." << endl;
        exit(1);
    }

    if (numContextSwitches < numContextSwitches2)
        outputFile << numContextSwitches;
    else
        outputFile << numContextSwitches2;

    outputFile.close();

    return 0;
}
