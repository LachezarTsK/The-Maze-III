
#include <array>
#include <queue>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {

    struct Point {
        int row{};
        int column{};
        string path{};
        int distanceFromStart{};

        Point(int row, int column) : row{row}, column{ column}{}
        Point() = default;
        virtual ~Point() = default;
    };

    struct CompareDistance {
        bool operator()(const Point& p1, const Point& p2) {
            return p1.distanceFromStart > p2.distanceFromStart;
        }
    };

    inline static const string m_INFINITY{ "z"};
    inline static const string GOAL_CAN_NOT_BE_REACHED = "impossible";
    inline static const array<array<int, 2>, 4> moves{ {{-1, 0}, {1, 0}, {0, -1}, {0, 1}} };
    inline static unordered_map<string, char> Direction{ {"UP", 'u'}, {"DOWN", 'd'}, {"LEFT", 'l'}, {"RIGHT", 'r'} };

    array<int, 2> start;
    array<int, 2> goal;
    size_t rows;
    size_t columns;
    int distanceForRolledOverPoints;

public:
    string findShortestWay(vector<vector<int>>&maze, vector<int>& ball, vector<int>& hole) {
        rows = maze.size();
        columns = maze[0].size();
        copy(ball.begin(), ball.end(), start.begin());
        copy(hole.begin(), hole.end(), goal.begin());
        return dijkstraSearch(maze);
    }

private:
    string dijkstraSearch(const vector<vector<int>>& maze) {
        priority_queue<Point, vector<Point>, CompareDistance> minHeap;
        minHeap.push(Point(start[0], start[1]));

        vector<vector<int>> minDistance(rows, vector<int>(columns, INT_MAX));
        minDistance[start[0]][start[1]] = 0;
        string shortestWay = m_INFINITY;

        while (!minHeap.empty()) {
            Point point = minHeap.top();
            minHeap.pop();

            if (point.row == goal[0] && point.column == goal[1]) {
                if (point.path < shortestWay) {
                    shortestWay = point.path;
                }
                continue;
            }

            for (const auto& move : moves) {

                int nextRow = point.row + move[0];
                int nextColumn = point.column + move[1];
                if (!isInMaze(nextRow, nextColumn) || maze[nextRow][nextColumn] != 0) {
                    continue;
                }
                rollOverEmptyPoints(nextRow, nextColumn, maze, move);

                nextRow = point.row + (move[0] * distanceForRolledOverPoints);
                nextColumn = point.column + (move[1] * distanceForRolledOverPoints);

                if (minDistance[nextRow][nextColumn] >= point.distanceFromStart + distanceForRolledOverPoints) {

                    Point nextPoint(nextRow, nextColumn);
                    nextPoint.path.append(point.path).push_back(getDirectionLetter(move));
                    nextPoint.distanceFromStart = point.distanceFromStart + distanceForRolledOverPoints;

                    minDistance[nextRow][nextColumn] = nextPoint.distanceFromStart;
                    minHeap.push(nextPoint);
                }
            }
        }
        return shortestWay != m_INFINITY ? shortestWay : GOAL_CAN_NOT_BE_REACHED;
    }

    void rollOverEmptyPoints(int nextRow, int nextColumn, const vector<vector<int>>& maze, const array<int, 2>& move) {
        distanceForRolledOverPoints = 0;
        while (isInMaze(nextRow, nextColumn) && maze[nextRow][nextColumn] == 0) {
            ++distanceForRolledOverPoints;
            if (nextRow == goal[0] && nextColumn == goal[1]) {
                break;
            }
            nextRow += move[0];
            nextColumn += move[1];
        }
    }

    char getDirectionLetter(const array<int, 2>& move) {
        if (move[0] == -1) {
            return Direction["UP"];
        }
        if (move[0] == 1) {
            return Direction["DOWN"];
        }
        if (move[1] == -1) {
            return Direction["LEFT"];
        }
        return Direction["RIGHT"];
    }

    bool isInMaze(int row, int column) {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }
};
