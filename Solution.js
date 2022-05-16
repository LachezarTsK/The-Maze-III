
/**
 * @param {number[][]} maze
 * @param {number[]} ball
 * @param {number[]} hole
 * @return {string}
 */
var findShortestWay = function (maze, ball, hole) {
    this.INFINITY = "z";
    this.GOAL_CAN_NOT_BE_REACHED = "impossible";
    this.moves = [[-1, 0], [1, 0], [0, -1], [0, 1]];
    this.Direction = {UP: "u", DOWN: "d", LEFT: "l", RIGHT: "r"};

    this.start = ball;
    this.goal = hole;
    this.rows = maze.length;
    this.columns = maze[0].length;
    this.distanceForRolledOverPoints = 0;
    return dijkstraSearch(maze);

};

/**
 * @param {number[][]} maze
 * @return {string}
 */
function dijkstraSearch(maze) {
    const {PriorityQueue} = require('@datastructures-js/priority-queue');
    const minHeap = new MinPriorityQueue({compare: (p1, p2) => p1.distanceFromStart - p2.distanceFromStart});
    minHeap.enqueue(new Point(this.start[0], this.start[1]));

    const minDistance = Array.from(new Array(this.rows), () => new Array(this.columns).fill(Number.MAX_SAFE_INTEGER));
    minDistance[start[0]][start[1]] = 0;
    let shortestWay = this.INFINITY;

    while (!minHeap.isEmpty()) {
        let point = minHeap.dequeue();

        if (point.row === this.goal[0] && point.column === this.goal[1]) {
            if (point.path.localeCompare(shortestWay) < 0) {
                shortestWay = point.path;
            }
            continue;
        }

        for (let move of this.moves) {

            let nextRow = point.row + move[0];
            let nextColumn = point.column + move[1];
            if (!isInMaze(nextRow, nextColumn) || maze[nextRow][nextColumn] !== 0) {
                continue;
            }
            rollOverEmptyPoints(nextRow, nextColumn, maze, move);

            nextRow = point.row + (move[0] * this.distanceForRolledOverPoints);
            nextColumn = point.column + (move[1] * this.distanceForRolledOverPoints);

            if (minDistance[nextRow][nextColumn] >= point.distanceFromStart + distanceForRolledOverPoints) {

                let nextPoint = new Point(nextRow, nextColumn);
                nextPoint.path = point.path + getDirectionLetter(move);
                nextPoint.distanceFromStart = point.distanceFromStart + distanceForRolledOverPoints;
                
                minDistance[nextRow][nextColumn] = nextPoint.distanceFromStart;
                minHeap.enqueue(nextPoint);
            }
        }
    }
    return shortestWay !== this.INFINITY ? shortestWay : this.GOAL_CAN_NOT_BE_REACHED;
}

/**
 * @param {number} nextRow
 * @param {number} nextColumn
 * @param {number[][]} maze
 * @param {number[]} move
 * @return {void}
 */
function rollOverEmptyPoints(nextRow, nextColumn, maze, move) {
    this.distanceForRolledOverPoints = 0;
    while (isInMaze(nextRow, nextColumn) && maze[nextRow][nextColumn] === 0) {
        ++this.distanceForRolledOverPoints;
        if (nextRow === this.goal[0] && nextColumn === this.goal[1]) {
            break;
        }
        nextRow += move[0];
        nextColumn += move[1];
    }
}

/**
 * @param {number[]} move
 * @return {string}
 */
function getDirectionLetter(move) {
    if (move[0] === -1) {
        return this.Direction.UP;
    }
    if (move[0] === 1) {
        return this.Direction.DOWN;
    }
    if (move[1] === -1) {
        return this.Direction.LEFT;
    }
    return this.Direction.RIGHT;
}

/**
 * @param {number} row
 * @param {number} column
 * @return {boolean}
 */
function isInMaze(row, column) {
    return row >= 0 && row < this.rows && column >= 0 && column < this.columns;
}

/**
 * @param {number} row
 * @param {number} column
 */
function Point(row, column) {
    this.row = row;
    this.column = column;
    this.path = "";
    this.distanceFromStart = 0;
}
