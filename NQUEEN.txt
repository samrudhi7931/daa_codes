# Function to check if a queen can be placed on the board
def is_safe(board, row, col):
    # Check this column on upper side
    for i in range(row):
        if board[i][col] == 1:
            return False

    # Check upper diagonal on left side
    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False

    # Check upper diagonal on right side
    for i, j in zip(range(row, -1, -1), range(col, len(board))):
        if board[i][j] == 1:
            return False

    return True


# Backtracking function to place remaining queens
def solve_queen(board, row):
    n = len(board)

    # Base case: If all queens are placed
    if row >= n:
        return True

    # Try placing queen in all columns for the current row
    for col in range(n):
        if is_safe(board, row, col):
            # Place queen
            board[row][col] = 1

            # Recur to place the rest of the queens
            if solve_queen(board, row + 1):
                return True

            # Backtrack (remove the queen if placing it here leads to a failure)
            board[row][col] = 0

    # If no column could be found, return False (backtrack)
    return False


# Function to print the board
def print_board(board):
    for row in board:
        print(" ".join("Q" if x == 1 else "." for x in row))
    print("\n")


# Function to solve the N-Queen problem
def solve_n_queen(n):
    # Initialize the NxN chessboard
    board = [[0 for _ in range(n)] for _ in range(n)]

    # Start solving from row 0 (placing first queen here)
    if solve_queen(board, 0):
        print("Final {}-Queen Matrix:".format(n))
        print_board(board)
    else:
        print("Solution does not exist for {} queens.".format(n))


# Example usage:
n = int(input("Enter the number of queens (n): "))
solve_n_queen(n)
