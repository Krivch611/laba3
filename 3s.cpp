#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <chrono>
#include <locale>
using namespace std;
using namespace std::chrono;

// ��������� ��� �������� ��������� � ����������
struct Cell {
    int x, y, dist;
};

// ��������, ��������� �� ������ � �������� �����
bool isValid(int x, int y) {
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

// ��������� ���� ����
int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

// ���������� ����� ������
int knightMovesArray(char start[], char end[]) {
    int startX = start[0] - 'A';
    int startY = start[1] - '1';
    int endX = end[0] - 'A';
    int endY = end[1] - '1';

    // ������ ��� �������� ���������� ������
    bool visited[8][8] = {false};
    // ������� ����������� ����� ������
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

// ���������� ����� ��������� ������
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

// ���������� ����� STL (�������)
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
    setlocale(LC_ALL, "Russian");
    char start[] = "A1";
    char end[] = "H8";

    // ������������ � ����� ������� ��� �������
    auto startTime = high_resolution_clock::now();
    int resultArray = knightMovesArray(start, end);
    auto stopTime = high_resolution_clock::now();
    auto durationArray = duration_cast<microseconds>(stopTime - startTime);

    // ������������ � ����� ������� ��� ���������� ������
    startTime = high_resolution_clock::now();
    int resultLinkedList = knightMovesLinkedList(start, end);
    stopTime = high_resolution_clock::now();
    auto durationLinkedList = duration_cast<microseconds>(stopTime - startTime);

    // ������������ � ����� ������� ��� STL
    startTime = high_resolution_clock::now();
    int resultSTL = knightMovesSTL(start, end);
    stopTime = high_resolution_clock::now();
    auto durationSTL = duration_cast<microseconds>(stopTime - startTime);

    // ����� �����������
    cout << "����������� ����� ����� (������): " << resultArray << endl;
    cout << "����� ���������� (������): " << durationArray.count() << " ���" << endl;

    cout << "����������� ����� ����� (��������� ������): " << resultLinkedList << endl;
    cout << "����� ���������� (��������� ������): " << durationLinkedList.count() << " ���" << endl;

    cout << "����������� ����� ����� (STL): " << resultSTL << endl;
    cout << "����� ���������� (STL): " << durationSTL.count() << " ���" << endl;

    // ��������� ������������������
    cout << "\n��������� ������������������:" << endl;
    cout << "1. STL �������: " << durationSTL.count() << " ���" << endl;
    cout << "2. ������: " << durationArray.count() << " ���" << endl;
    cout << "3. ��������� ������: " << durationLinkedList.count() << " ���" << endl;

    return 0;
}