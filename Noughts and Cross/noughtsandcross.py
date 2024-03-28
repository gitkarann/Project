def draw_board(board):
    """Code to draw the board"""
    print("\n".join([" | ".join(row) for row in board]))

def welcome(board):
    """Code to display welcome messages"""
    print("Welcome to the 'Unbeatable Noughts and Crosses' game. The board is shown below:")
    draw_board(board)
    print("When prompted, enter the number corresponding to the square you want.")

def initialise_board(board):
    """initialising the board"""
    for i in range(3):
        for j in range(3):
            board[i][j] = ' '
    return board

def get_player_move(board):
    """To get the player board"""
    while True:
        print("Choose your square:")
        move = input().strip()
        if move in ['1', '2', '3', '4', '5', '6', '7', '8', '9']:
            row, col = (int(move) - 1) // 3, (int(move) - 1) % 3
            if board[row][col] == ' ':
                return row, col
        print("Invalid move, try again.")

def choose_computer_move(board):
    """function to choose the computer move"""
    # Randomly choose a cell for the computer's move
    import random
    while True:
        row, col = random.randint(0, 2), random.randint(0, 2)
        if board[row][col] == ' ':
            return row, col

def check_for_win(board, mark):
    """Function to check the win"""
    # Check rows
    for i in range(3):
        if board[i][0] == mark and board[i][1] == mark and board[i][2] == mark:
            return True
    # Check columns
    for i in range(3):
        if board[0][i] == mark and board[1][i] == mark and board[2][i] == mark:
            return True
    # Check diagonals
    if board[0][0] == mark and board[1][1] == mark and board[2][2] == mark:
        return True
    if board[0][2] == mark and board[1][1] == mark and board[2][0] == mark:
        return True
    return False

def check_for_draw(board):
    """Function to check the draw"""
    for i in range(3):
        for j in range(3):
            if board[i][j] == ' ':
                return False
    return True

def play_game(board):
    """Function of game playing"""
    initialise_board(board)
    draw_board(board)
    player_mark = 'X'
    computer_mark = 'O'
    while True:
        # Player move
        row, col = get_player_move(board)
        board[row][col] = player_mark
        draw_board(board)
        if check_for_win(board, player_mark):
            return 1
        if check_for_draw(board):
            return 0
        # Computer move
        row, col = choose_computer_move(board)
        board[row][col] = computer_mark
        draw_board(board)
        if check_for_win(board, computer_mark):
            return
def menu():
    """Function for options of the code"""
    option = input("Enter one of the following options:\n1-Play the game\n2-Save your score in the leaderboard\n3-Load and display the leaderboard\nQ-End the program\n1, 2, 3 or q?\n")
    return option

def load_scores():
    """Function for displaying leaderboard including names and scores"""
    leaders = {}
    try:
        with open("leaderboard.txt", "r") as f:
            for line in f:
                name, score = line.strip().split(",")
                leaders[name] = int(score)
    except:
        pass
    return leaders

def save_score(score):
    """This function saves the scores with the player's name"""
    name = input("Enter your name: ")
    with open("leaderboard.txt", "a") as f:
        f.write("{},{}\n".format(name, score))
    return

def display_leaderboard(leaders):
    """For displaying the leaderboard"""
    print("Name\tScore")
    for name, score in sorted(leaders.items(), key=lambda x: x[1], reverse=True):
        print("{}\t{}".format(name, score))
    return


    
def main():
    """The main function of the code"""
    board = [ ['1','2','3'],\
              ['4','5','6'],\
              ['7','8','9']]

    welcome(board)
    total_score = 0
    while True:
        choice = menu()
        if choice == '1':
            score = play_game(board)
            total_score += score
            print('Your current score is:',total_score)
        if choice == '2':
            save_score(total_score)
        if choice == '3':
            leader_board = load_scores()
            display_leaderboard(leader_board)
        if choice == 'q':
            print('Thank you for playing the "Unbeatable Noughts and Crosses" game.')
            print('Good bye')
            return


    
# Program execution begins here
if __name__ == '__main__':
    main()