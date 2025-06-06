#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Structure to store coordinates and distance
struct Cell {
    int x, y, dist;
};

// Check if the cell is within the board
bool isValid(int x, int y) {
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

// Possible knight moves
int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

// Implementation using array
int knightMovesArray(char start[], char end[]) {
    int startX = start[0] - 'A';
    int startY = start[1] - '1';
    int endX = end[0] - 'A';
    int endY = end[1] - '1';

    // Array to keep track of visited cells
    bool visited[8][8] = {false};
    // Queue implemented via array
    Cell queue[64];
    int front = 0, rear = 0;

    queue[rear++] = {startX, startY, 0};
    visited[startX][startY] = true;

    while (front != rear) {
        Cell current = queue[front++];
        if (current.x == endX && current.y == endY) {
            return current.dist;
        }

        for (int i = 0; i < 8; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY)) {
                if (!visited[newX][newY]) {
                    visited[newX][newY] = true;
                    queue[rear++] = {newX, newY, current.dist + 1};
                }
            }
        }
    }
    return -1;
}

// Implementation using linked list
struct Node {
    Cell data;
    Node* next;
};

class LinkedListQueue {
private:
    Node* front;
    Node* rear;
public:
    LinkedListQueue() : front(nullptr), rear(nullptr) {}
    void enqueue(Cell data) {
        Node* newNode = new Node{data, nullptr};
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    Cell dequeue() {
        if (front == nullptr) {
            return {-1, -1, -1};
        }
        Node* temp = front;
        Cell data = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return data;
    }
    bool isEmpty() {
        return front == nullptr;
    }
};

int knightMovesLinkedList(char start[], char end[]) {
    int startX = start[0] - 'A';
    int startY = start[1] - '1';
    int endX = end[0] - 'A';
    int endY = end[1] - '1';

    bool visited[8][8] = {false};
    LinkedListQueue queue;

    queue.enqueue({startX, startY, 0});
    visited[startX][startY] = true;

    while (!queue.isEmpty()) {
        Cell current = queue.dequeue();
        if (current.x == endX && current.y == endY) {
            return current.dist;
        }

        for (int i = 0; i < 8; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY)) {
                if (!visited[newX][newY]) {
                    visited[newX][newY] = true;
                    queue.enqueue({newX, newY, current.dist + 1});
                }
            }
        }
    }
    return -1;
}

// Implementation using STL queue
int knightMovesSTL(char start[], char end[]) {
    int startX = start[0] - 'A';
    int startY = start[1] - '1';
    int endX = end[0] - 'A';
    int endY = end[1] - '1';

    bool visited[8][8] = {false};
    queue<Cell> q;

    q.push({startX, startY, 0});
    visited[startX][startY] = true;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();
        if (current.x == endX && current.y == endY) {
            return current.dist;
        }

        for (int i = 0; i < 8; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY)) {
                if (!visited[newX][newY]) {
                    visited[newX][newY] = true;
                    q.push({newX, newY, current.dist + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    char start[] = "A1";
    char end[] = "H8";

    // Timing for array implementation
    auto startTime = high_resolution_clock::now();
    int resultArray = knightMovesArray(start, end);
    auto stopTime = high_resolution_clock::now();
    auto durationArray = duration_cast<microseconds>(stopTime - startTime);

    // Timing for linked list implementation
    startTime = high_resolution_clock::now();
    int resultLinkedList = knightMovesLinkedList(start, end);
    stopTime = high_resolution_clock::now();
    auto durationLinkedList = duration_cast<microseconds>(stopTime - startTime);

    // Timing for STL implementation
    startTime = high_resolution_clock::now();
    int resultSTL = knightMovesSTL(start, end);
    stopTime = high_resolution_clock::now();
    auto durationSTL = duration_cast<microseconds>(stopTime - startTime);

    // Output results
    cout << "Minimum number of moves (array): " << resultArray << endl;
    cout << "Execution time (array): " << durationArray.count() << " microseconds" << endl;

    cout << "Minimum number of moves (linked list): " << resultLinkedList << endl;
    cout << "Execution time (linked list): " << durationLinkedList.count() << " microseconds" << endl;

    cout << "Minimum number of moves (STL): " << resultSTL << endl;
    cout << "Execution time (STL): " << durationSTL.count() << " microseconds" << endl;

    // Performance comparison
    cout << "\nPerformance comparison:" << endl;
    cout << "1. STL queue: " << durationSTL.count() << " microseconds" << endl;
    cout << "2. Array: " << durationArray.count() << " microseconds" << endl;
    cout << "3. Linked list: " << durationLinkedList.count() << " microseconds" << endl;

    return 0;
}
