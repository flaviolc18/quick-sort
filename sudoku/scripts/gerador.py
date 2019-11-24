import random, copy, sys

"""
Randomly arrange numbers in a grid while making all rows, columns and
squares (sub-grids) contain the numbers 1 through 9.
"""
def construct_puzzle_solution(N=9, R=3, C=3):

    # Loop until we're able to fill all 81 cells with numbers, while
    # satisfying the constraints above.
    while True:
        try:
            puzzle  = [[0]*N for i in range(N)] # start with blank puzzle
            rows    = [set(range(1,N+1)) for i in range(N)] # set of available
            columns = [set(range(1,N+1)) for i in range(N)] #   numbers for each
            squares = [set(range(1,N+1)) for i in range(N)] #   row, column and square

            for i in range(N):
                for j in range(N):
                    # pick a number for cell (i,j) from the set of remaining available numbers
                    choices = rows[i].intersection(columns[j]).intersection(squares[(i/R)*R + j/C])
                    choice  = random.choice(list(choices))
        
                    puzzle[i][j] = choice
        
                    rows[i].discard(choice)
                    columns[j].discard(choice)
                    squares[(i/R)*R + j/C].discard(choice)

            # success! every cell is filled.
            return puzzle
            
        except IndexError:
            # if there is an IndexError, we have worked ourselves in a corner (we just start over)
            pass

"""
Randomly pluck out cells (numbers) from the solved puzzle grid, ensuring that any
plucked number can still be deduced from the remaining cells.

For deduction to be possible, each other cell in the plucked number's row, column,
or square must not be able to contain that number. """
def pluck(puzzle, n=0, N=9, R=3, C=3):

    """
    Answers the question: can the cell (i,j) in the puzzle "puz" contain the number
    in cell "c"? """
    def canBeA(puz, i, j, c, N, R, C):
        v = puz[c/N][c%N]
        if puz[i][j] == v: return True
        if puz[i][j] in range(1,N+1): return False

        for m in range(N): # test row, col, square
            # if it's not the cell itself, and the mth cell of the group contains the value v, then "no"
            if not (m==c/N and j==c%N) and puz[m][j] == v: return False
            if not (i==c/N and m==c%N) and puz[i][m] == v: return False
            if not ((i/R)*R + m/R==c/N and (j/C)*C + m%C==c%N) and puz[(i/R)*R + m/R][(j/C)*C + m%C] == v:
                return False

        return True


    """
    starts with a set of all 81 cells, and tries to remove one (randomly) at a time
    but not before checking that the cell can still be deduced from the remaining cells. """
    cells     = set(range(N*N))
    cellsleft = cells.copy()
    while len(cells) > n and len(cellsleft):
        cell = random.choice(list(cellsleft)) # choose a cell from ones we haven't tried
        cellsleft.discard(cell) # record that we are trying this cell

        # row, col and square record whether another cell in those groups could also take
        # on the value we are trying to pluck. (If another cell can, then we can't use the
        # group to deduce this value.) If all three groups are True, then we cannot pluck
        # this cell and must try another one.
        row = col = square = False

        for i in range(N):
            if i != cell/N:
                if canBeA(puzzle, i, cell%N, cell, N, R, C): row = True
            if i != cell%N:
                if canBeA(puzzle, cell/N, i, cell, N, R, C): col = True
            if not (((cell/N)/R)*R + i/R == cell/N and ((cell/N)%C)*C + i%C == cell%N):
                if canBeA(puzzle, ((cell/N)/R)*R + i/R, ((cell/N)%C)*C + i%C, cell, N, R, C): square = True

        if row and col and square:
            continue # could not pluck this cell, try again.
        else:
            # this is a pluckable cell!
            puzzle[cell/N][cell%N] = 0 # 0 denotes a blank cell
            cells.discard(cell) # remove from the set of visible cells (pluck it)
            # we don't need to reset "cellsleft" because if a cell was not pluckable
            # earlier, then it will still not be pluckable now (with less information
            # on the board).

    # This is the puzzle we found, in all its glory.
    return (puzzle, len(cells))
    
    
"""
That's it.

If we want to make a puzzle we can do this:
    pluck(construct_puzzle_solution())
    
The following functions are convenience functions for doing just that...
"""

"""
This uses the above functions to create a new puzzle. It attempts to
create one with 28 (by default) given cells, but if it can't, it returns
one with as few givens as it is able to find.

This function actually tries making 100 puzzles (by default) and returns
all of them. The "best" function that follows this one selects the best
one of those.
"""
def run(n = 28, iter=100, N=9, R=3, C=3):
    all_results = {}
    # print "Constructing a sudoku puzzle."
    # print "* creating the solution..."
    a_puzzle_solution = construct_puzzle_solution(N=N, R=R, C=C)

    # print "* constructing a puzzle..."
    for i in range(iter):
        puzzle = copy.deepcopy(a_puzzle_solution)
        (result, number_of_cells) = pluck(puzzle, n, N=N, R=R, C=C)
        all_results.setdefault(number_of_cells, []).append(result)
        if number_of_cells <= n: break

    return all_results

def best(set_of_puzzles):
    # Could run some evaluation function here. For now just pick
    # the one with the fewest "givens".
    return set_of_puzzles[max(set_of_puzzles.keys())][0]

def display(puzzle):
    for row in puzzle:
        print ' '.join([str(n or '0') for n in row])


""" Controls starts here """
if len(sys.argv) > 3:
    try:
        N = int(sys.argv[1])
        R = int(sys.argv[2])
        C = int(sys.argv[3])
        if(R*C != N or R<C): raise Exception()

        print N, R, C

        results = run(n=0, N=N, R=R, C=C)       # find puzzles with as few givens as possible.
        puzzle  = best(results)  # use the best one of those puzzles.
        display(puzzle)          # display that puzzle.
    except:
        print "invalid numbers, N, R, C must be integer so that R * C = N and R >= C"
        exit()
else:
    print "usage: python {} N R C".format(sys.argv[0])
