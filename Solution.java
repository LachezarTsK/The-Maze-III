
import java.util.Arrays;
import java.util.PriorityQueue;

public class Solution {

    private static final String INFINITY = "z";
    private static final String GOAL_CAN_NOT_BE_REACHED = "impossible";
    private static final int[][] moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    private static enum Direction {
        UP('u'), DOWN('d'), LEFT('l'), RIGHT('r');
        char letter;

        Direction(char letter) {
            this.letter = letter;
        }
    }

    private int[] start;
    private int[] goal;
    private int rows;
    private int columns;
    private int distanceForRolledOverPoints;

    public String findShortestWay(int[][] maze, int[] ball, int[] hole) {
        rows = maze.length;
        columns = maze[0].length;
        start = ball;
        goal = hole;
        return dijkstraSearch(maze);
    }

    private String dijkstraSearch(int[][] maze) {
        PriorityQueue<Point> minHeap = new PriorityQueue<>((p1, p2) -> p1.distanceFromStart - p2.distanceFromStart);
        minHeap.add(new Point(start[0], start[1]));

        int[][] minDistance = new int[rows][columns];
        for (int[] nums : minDistance) {
            Arrays.fill(nums, Integer.MAX_VALUE);
        }
        minDistance[start[0]][start[1]] = 0;
        String shortestWay = INFINITY;

        while (!minHeap.isEmpty()) {
            Point point = minHeap.poll();

            if (point.row == goal[0] && point.column == goal[1]) {
                if (point.path.toString().compareTo(shortestWay) < 0) {
                    shortestWay = point.path.toString();
                }
                continue;
            }

            for (int[] move : moves) {

                int nextRow = point.row + move[0];
                int nextColumn = point.column + move[1];
                if (!isInMaze(nextRow, nextColumn) || maze[nextRow][nextColumn] != 0) {
                    continue;
                }
                rollOverEmptyPoints(nextRow, nextColumn, maze, move);

                nextRow = point.row + (move[0] * distanceForRolledOverPoints);
                nextColumn = point.column + (move[1] * distanceForRolledOverPoints);

                if (minDistance[nextRow][nextColumn] >= point.distanceFromStart + distanceForRolledOverPoints) {

                    Point nextPoint = new Point(nextRow, nextColumn);
                    nextPoint.path.append(point.path).append(getDirectionLetter(move));
                    nextPoint.distanceFromStart = point.distanceFromStart + distanceForRolledOverPoints;
                    minDistance[nextRow][nextColumn] = nextPoint.distanceFromStart;
                    minHeap.add(nextPoint);
                }
            }
        }
        return !shortestWay.equals(INFINITY) ? shortestWay : GOAL_CAN_NOT_BE_REACHED;
    }

    private void rollOverEmptyPoints(int nextRow, int nextColumn, int[][] maze, int[] move) {
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

    private char getDirectionLetter(int[] move) {
        if (move[0] == -1) {
            return Direction.UP.letter;
        }
        if (move[0] == 1) {
            return Direction.DOWN.letter;
        }
        if (move[1] == -1) {
            return Direction.LEFT.letter;
        }
        return Direction.RIGHT.letter;
    }

    private boolean isInMaze(int row, int column) {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }
}

class Point {

    int row;
    int column;
    StringBuilder path;
    int distanceFromStart;

    public Point(int row, int column) {
        this.row = row;
        this.column = column;
        path = new StringBuilder();
    }
}
