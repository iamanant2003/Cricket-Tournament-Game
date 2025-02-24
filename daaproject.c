#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define PASSWORD_LENGTH 20
#define CREDENTIALS_FILE "credentials.txt"
#define MAX_TEAM_CHOICES MAX_TEAMS
#define MAX_TEAMS 4
#define MAX_PLAYERS 15
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 10

typedef struct
{
    char name[50];
    int id;
    int age;
    char role[20];
    float strike_rate;
    float economy;
    int fours;
    int sixes;
    int hundreds;
    int fifties;
} Player;

typedef struct
{
    char name[50];
    Player players[MAX_PLAYERS];
    int points;
} Team;

Team teams[MAX_TEAMS] =
    {
        {
            "Chennai Super Kings",
            {{"MS Dhoni (Captain)", 7, 42, "Wicketkeeper", 126.13, 7.50, 45, 25, 0, 24},
             {"Ravindra Jadeja", 5, 34, "All-rounder", 128.00, 7.80, 50, 30, 1, 15},
             {"Deepak Chahar", 3, 31, "Bowler", 130.00, 8.00, 20, 10, 0, 5},
             {"Shardul Thakur", 4, 31, "Bowler", 140.00, 8.50, 25, 15, 0, 3},
             {"Faf du Plessis", 6, 39, "Batsman", 130.00, 0.00, 60, 30, 2, 25},
             {"Ruturaj Gaikwad", 2, 27, "Batsman", 145.00, 0.00, 55, 20, 1, 10},
             {"Dwayne Bravo", 1, 39, "All-rounder", 120.00, 8.00, 40, 25, 0, 15},
             {"Moeen Ali", 8, 36, "All-rounder", 137.00, 7.50, 30, 20, 1, 5},
             {"Ambati Rayudu", 9, 38, "Batsman", 130.00, 0.00, 40, 15, 1, 10},
             {"Tushar Deshpande", 10, 29, "Bowler", 125.00, 8.20, 15, 5, 0, 2},
             {"Prashant Solanki", 11, 24, "Bowler", 110.00, 7.00, 10, 3, 0, 1},
             {"Simarjeet Singh", 13, 25, "Bowler", 120.00, 8.00, 12, 4, 0, 0},
             {"Devon Conway", 12, 32, "Batsman", 135.00, 0.00, 50, 15, 1, 8},
             {"Lasith Malinga", 59, 37, "Bowler", 140.00, 8.50, 14, 6, 1, 3},
             {"Nishant Sindhu", 14, 26, "Batsman", 125.00, 0.00, 20, 5, 0, 2}},
        },

        {
            "Royal Challengers Bangalore",
            {{"Virat Kohli (Captain)", 15, 34, "Batsman", 130.00, 0.00, 70, 40, 6, 50},
             {"Faf du Plessis", 17, 39, "Batsman", 135.00, 0.00, 60, 30, 2, 25},
             {"Dinesh Karthik", 15, 38, "Wicketkeeper", 125.00, 0.00, 40, 20, 0, 15},
             {"Mohammed Siraj", 18, 29, "Bowler", 0.00, 8.50, 10, 0, 0, 5},
             {"Harshal Patel", 19, 32, "Bowler", 140.00, 9.00, 30, 15, 0, 3},
             {"Glenn Maxwell", 20, 34, "All-rounder", 145.00, 7.50, 50, 25, 1, 10},
             {"Wanindu Hasaranga", 21, 26, "All -rounder", 130.00, 6.50, 40, 20, 0, 10},
             {"Wanindu Hasaranga", 21, 26, "All-rounder", 130.00, 6.50, 40, 20, 0, 10},
             {"Shahbaz Ahmed", 25, 28, "All-rounder", 120.00, 7.80, 30, 15, 0, 5},
             {"Devdutt Padikkal", 23, 27, "Batsman", 135.00, 0.00, 50, 20, 1, 10},
             {"Kedar Jadhav", 24, 38, "Batsman", 125.00, 0.00, 40, 15, 0, 5},
             {"Josh Hazlewood", 22, 32, "Bowler", 0.00, 7.00, 20, 5, 0, 2},
             {"Rajat Patidar", 26, 29, "Batsman", 130.00, 0.00, 30, 10, 0, 3},
             {"Anuj Rawat", 27, 23, "Wicketkeeper", 120.00, 0.00, 20, 5, 0, 1},
             {"Vikram Singh", 28, 24, "Batsman", 130.00, 0.00, 10, 2, 0, 0}},
        },

        {
            "Kolkata Knight Riders",
            {{"Shubman Gill (Captain)", 30, 24, "Batsman", 130.00, 0.00, 60, 30, 1, 15},
             {"Andre Russell", 31, 35, "All-rounder", 140.00, 8.00, 50, 25, 2, 20},
             {"Sunil Narine", 35, 34, "All-rounder", 125.00, 7.50, 40, 20, 0, 10},
             {"Eoin Morgan", 34, 37, "Batsman", 135.00, 0.00, 50, 15, 1, 5},
             {"Nitish Rana", 31, 29, "Batsman", 130.00, 0.00, 45, 20, 0, 10},
             {"Lockie Ferguson", 32, 32, "Bowler", 0.00, 8.50, 20, 5, 0, 2},
             {"Pat Cummins", 36, 30, "Bowler", 0.00, 7.00, 25, 10, 0, 3},
             {"Venkatesh Iyer", 39, 28, "Batsman", 135.00, 0.00, 55, 15, 1, 8},
             {"Rinku Singh", 38, 26, "Batsman", 120.00, 0.00, 30, 10, 0, 5},
             {"Kuldeep Yadav", 37, 28, "Bowler", 0.00, 8.00, 15, 4, 0, 1},
             {"Shivam Mavi", 40, 24, "Bowler", 0.00, 8.50, 10, 3, 0, 0},
             {"Suyash Prabhudessai", 2, 27, "Batsman", 125.00, 0.00, 15, 3, 0, 0},
             {"Ajinkya Rahane", 43, 35, "Batsman", 125.00, 0.00, 40, 15, 0, 5},
             {"Kamlesh Nagarkoti", 41, 23, "Bowler", 0.00, 9.00, 5, 1, 0, 0},
             {"Prasidh Krishna", 42, 27, "Bowler", 0.00, 8.00, 20, 5, 0, 2}},
        },
        {
            "Mumbai Indians",
            {{"Rohit Sharma (Captain)", 58, 36, "Batsman", 130.00, 0.00, 70, 40, 5, 50},
             {"Jasprit Bumrah", 57, 29, "Bowler", 0.00, 7.50, 20, 5, 0, 10},
             {"Kieron Pollard", 56, 35, "All-rounder", 140.00, 8.00, 50, 25, 2, 20},
             {"Ishan Kishan", 55, 25, "Wicketkeeper", 135.00, 0.00, 60, 30, 1, 15},
             {"Hardik Pandya", 54, 30, "All-rounder", 145.00, 7.00, 40, 20, 1, 10},
             {"Quinton de Kock", 53, 30, "Wicketkeeper", 130.00, 0.00, 50, 25, 1, 15},
             {"Trent Boult", 52, 34, "Bowler", 0.00, 8.00, 30, 10, 0, 5},
             {"Rahul Chahar", 51, 27, "Bowler", 0.00, 7.50, 25, 5, 0, 3},
             {"Suryakumar Yadav", 50, 32, "Batsman", 135.00, 0.00, 55, 20, 1, 10},
             {"Anmolpreet Singh", 49, 25, "Batsman", 120.00, 0.00, 20, 5, 0, 2},
             {"Jayant Yadav", 48, 33, "All-rounder", 125.00, 7.00, 15, 3, 0, 1},
             {"Mohammed Nabi", 47, 34, "All-rounder", 130.00, 7.50, 20, 5, 0, 2},
             {"Dinesh Karthik", 46, 38, "Wicketkeeper", 125.00, 0.00, 40, 15, 0, 5},
             {"Chris Lynn", 45, 32, "Batsman", 135.00, 0.00, 50, 20, 1, 10},
             {"Ben Stokes", 44, 32, "All-rounder", 140.00, 8.00, 60, 30, 2, 20}},
        }};

typedef struct BSTNode
{
    Player player;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef struct
{
    char matches[MAX_STACK_SIZE][100];
    int top;
} Stack;

typedef struct
{
    Team teams[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

BSTNode *create_bst_node(Player player)
{
    BSTNode *new_node = (BSTNode *)malloc(sizeof(BSTNode));
    new_node->player = player;
    new_node->left = new_node->right = NULL;
    return new_node;
}

BSTNode *insert_bst(BSTNode *root, Player player)
{
    if (root == NULL)
    {
        return create_bst_node(player);
    }
    if (player.id < root->player.id)
    {
        root->left = insert_bst(root->left, player);
    }
    else
    {
        root->right = insert_bst(root->right, player);
    }
    return root;
}

Player *search_bst(BSTNode *root, int id)
{
    if (root == NULL || root->player.id == id)
    {
        return (root != NULL) ? &root->player : NULL;
    }
    if (id < root->player.id)
    {
        return search_bst(root->left, id);
    }
    return search_bst(root->right, id);
}
void display_points_table(void);
void push(Stack *stack, const char *match)
{
    if (stack->top < MAX_STACK_SIZE)
    {
        strcpy(stack->matches[stack->top++], match);
    }
    else
    {
        printf("Stack is full!\n");
    }
}

void pop(Stack *stack)
{
    if (stack->top > 0)
    {
        stack->top--;
    }
    else
    {
        printf("Stack is empty!\n");
    }
}

void display_stack(Stack *stack)
{
    printf("Match History:\n");
    for (int i = 0; i < stack->top; i++)
    {
        printf("%s\n", stack->matches[i]);
    }
}

void enqueue(Queue *queue, Team team)
{
    if ((queue->rear + 1) % MAX_QUEUE_SIZE != queue->front)
    {
        queue->teams[queue->rear] = team;
        queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    }
    else
    {
        printf("Queue is full!\n");
    }
}

Team dequeue(Queue *queue)
{
    if (queue->front != queue->rear)
    {
        Team team = queue->teams[queue->front];
        queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
        return team;
    }
    else
    {
        printf("Queue is empty!\n");
        Team empty_team = {"", {{""}}, 0};
        return empty_team;
    }
}

void display_queue(Queue *queue)
{
    printf("Teams in Queue:\n");
    for (int i = queue->front; i != queue->rear; i = (i + 1) % MAX_QUEUE_SIZE)
    {
        printf("%s\n", queue->teams[i].name);
    }
}

void display_teams_and_players()
{
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        printf("Team: %s\n", teams[i].name);
        printf("Players:\n");

        for (int j = 0; j < MAX_PLAYERS; j++)
        {
            Player *player = &teams[i].players[j]; // Pointer for easier access
            if (player->name[0] != '\0')
            { // Check if the player name is not empty
                printf("%d. %s (ID: %d, Age: %d, Role: %s, SR: %.2f, Economy: %.2f, Fours: %d, Sixes: %d, Hundreds: %d, Fifties: %d)\n",
                       j + 1, player->name, player->id, player->age,
                       player->role, player->strike_rate, player->economy,
                       player->fours, player->sixes, player->hundreds,
                       player->fifties);
            }
        }
        printf("\n");
    }
}

void sort_players_by_id(Team *team)
{
    // Comparator function
    int compare_players(const void *a, const void *b)
    {
        const Player *playerA = (const Player *)a; // Cast a to Player*
        const Player *playerB = (const Player *)b; // Cast b to Player*
        return playerA->id - playerB->id;          // Sort by ID
    }

    // Sort the players
    qsort(team->players, MAX_PLAYERS, sizeof(Player), compare_players);

    // Print sorted players
    printf("Sorted Players for Team: %s\n", team->name);
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (strlen(team->players[i].name) > 0)
        {
            printf("%s\n", team->players[i].name);
        }
    }
    printf("\n");
}

void trim_spaces(char *str)
{
    // Remove leading spaces
    while (isspace((unsigned char)*str))
        str++;

    // Remove trailing spaces
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Null-terminate the string after the last non-space character
    *(end + 1) = '\0';
}

void search_player_by_name(Team *team, const char *name)
{
    int found = 0;

    // Check if the name is empty
    if (name == NULL || strlen(name) == 0)
    {
        printf("Player name cannot be empty.\n");
        return;
    }

    // Create a lowercase copy of the search name
    char lower_search_name[50];
    strcpy(lower_search_name, name);
    for (int i = 0; lower_search_name[i]; i++)
    {
        lower_search_name[i] = tolower(lower_search_name[i]);
    }

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (strlen(team->players[i].name) == 0)
            continue; // Skip empty player names

        // Create a lowercase copy of the player's name
        char lower_player_name[50];
        strcpy(lower_player_name, team->players[i].name);
        for (int j = 0; lower_player_name[j]; j++)
        {
            lower_player_name[j] = tolower(lower_player_name[j]);
        }

        // Check if the search string is a substring of the player's name
        if (strstr(lower_player_name, lower_search_name) != NULL)
        {
            printf("Found Player: ID: %d, Name: %s, Role: %s, Strike Rate: %.2f, Economy: %.2f\n",
                   team->players[i].id, team->players[i].name, team->players[i].role,
                   team->players[i].strike_rate, team->players[i].economy);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Player with name '%s' not found in team %s.\n", name, team->name);
    }
}

void handle_team_choice(int *team_choice)
{
    printf("Select a team (1-%d): ", MAX_TEAMS);
    scanf("%d", team_choice);

    if (*team_choice < 1 || *team_choice > MAX_TEAMS)
    {
        printf("Invalid team choice! Please select a valid team.\n");
        *team_choice = -1; // Set to -1 for invalid choice
    }
}

void select_playing_eleven(Team *team)
{
    int selected_players[11];
    bool is_selected[MAX_PLAYERS] = {false}; // Track selected players
    int num_selected = 0;

    printf("Available Players:\n");
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (strlen(team->players[i].name) > 0)
        {
            printf("%d. %s (ID: %d, Role: %s)\n", i + 1, team->players[i].name, team->players[i].id, team->players[i].role);
        }
    }

    printf("Select up to 11 players for the playing eleven:\n");
    while (num_selected < 11)
    {
        printf("Select player %d (1-%d): ", num_selected + 1, MAX_PLAYERS);
        int choice;
        scanf("%d", &choice);

        if (choice > 0 && choice <= MAX_PLAYERS)
        {
            int player_index = choice - 1;

            // Check if the player has already been selected
            if (!is_selected[player_index] && strlen(team->players[player_index].name) > 0)
            {
                selected_players[num_selected] = player_index;
                is_selected[player_index] = true; // Mark player as selected
                num_selected++;
            }
            else
            {
                printf("Invalid choice or player already selected, please select again.\n");
            }
        }
        else
        {
            printf("Invalid choice, please select again.\n");
        }
    }

    printf("Playing eleven:\n");
    for (int i = 0; i < num_selected; i++)
    {
        printf("%s (ID: %d, Role: %s)\n", team->players[selected_players[i]].name, team->players[selected_players[i]].id, team->players[selected_players[i]].role);
    }
}

void fixtures(Queue *queue, Stack *match_history)
{
    Team team1, team2;
    int team1_runs, team2_runs;
    char venue[50];
    queue->front = queue->rear = 0;
    printf("Select Team 1 (1-%d): ", MAX_TEAMS);
    int team1_choice;
    scanf("%d", &team1_choice);

    if (team1_choice > 0 && team1_choice <= MAX_TEAMS)
    {
        team1 = teams[team1_choice - 1];
        for (int i = 0; i < MAX_TEAMS; i++)
        {
            if (i != team1_choice - 1)
            {
                enqueue(queue, teams[i]);
            }
        }
        if (queue->front != queue->rear)
        {
            printf("Enter runs for %s: ", team1.name);
            scanf("%d", &team1_runs);
            team2 = dequeue(queue);
            team2_runs = rand() % 200 + 100;
            printf("Team 2: %s\n", team2.name);
            printf("Team 2 runs: %d\n", team2_runs);
            printf("Enter venue: ");
            scanf("%49s", venue);
            printf("Match result: %s vs %s at %s\n", team1.name, team2.name, venue);
            if (team1_runs > team2_runs)
            {
                printf("%s wins by %d runs\n", team1.name, team1_runs - team2_runs);
                for (int i = 0; i < MAX_TEAMS; i++)
                {
                    if (strcmp(teams[i].name, team1.name) == 0)
                    {
                        teams[i].points += 2;
                        break;
                    }
                }
            }
            else if (team1_runs < team2_runs)
            {
                printf("%s wins by %d runs\n", team2.name, team2_runs - team1_runs);
                for (int i = 0; i < MAX_TEAMS; i++)
                {
                    if (strcmp(teams[i].name, team2.name) == 0)
                    {
                        teams[i].points += 2;
                        break;
                    }
                }
            }
            else
            {
                printf("The match is a tie\n");
                for (int i = 0; i < MAX_TEAMS; i++)
                {
                    if (strcmp(teams[i].name, team1.name) == 0)
                    {
                        teams[i].points += 1;
                    }
                    if (strcmp(teams[i].name, team2.name) == 0)
                    {
                        teams[i].points += 1;
                    }
                }
            }
            char match_result[100];
            if (team1_runs == team2_runs)
            {
                sprintf(match_result, "%s vs %s: Match is a tie", team1.name, team2.name);
            }
            else
            {
                sprintf(match_result, "%s vs %s: %s wins by %d runs",
                        team1.name, team2.name,
                        (team1_runs > team2_runs) ? team1.name : team2.name,
                        abs(team1_runs - team2_runs));
            }
            push(match_history, match_result);
            display_points_table();
        }
        else
        {
            printf("No teams left in the queue for fixtures.\n");
        }
    }
    else
    {
        printf("Invalid team selection!\n");
    }
}
void ask_for_credentials(char *username, char *password)
{
    printf("Please set your username: ");
    fgets(username, PASSWORD_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Please set your password (max %d characters): ", PASSWORD_LENGTH - 1);
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;
    FILE *file = fopen(CREDENTIALS_FILE, "w");
    if (file)
    {
        fprintf(file, "%s\n%s\n", username, password);
        fclose(file);
        printf("Credentials saved successfully!\n");
    }
    else
    {
        printf("Error saving credentials.\n");
    }
}
bool load_credentials(char *username, char *password)
{
    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (file)
    {
        fgets(username, PASSWORD_LENGTH, file);
        username[strcspn(username, "\n")] = 0; // Remove newline character
        fgets(password, PASSWORD_LENGTH, file);
        password[strcspn(password, "\n")] = 0; // Remove newline character
        fclose(file);
        return true;
    }
    return false;
}

bool login_user(char *username, char *password)
{
    char stored_username[PASSWORD_LENGTH] = {0};
    char stored_password[PASSWORD_LENGTH] = {0};

    if (load_credentials(stored_username, stored_password))
    {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0)
        {
            return true;
        }
    }
    return false;
}
void display_points_table()
{
    printf("\n===========================================\n");
    printf("                Points Table               \n");
    printf("===========================================\n");
    printf("| %-3s | %-27s | %-6s |\n", "No", "Team Name", "Points");
    printf("-------------------------------------------\n");
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        printf("| %-3d | %-27s | %-6d |\n", i + 1, teams[i].name, teams[i].points);
    }
    printf("===========================================\n\n");
}
int main()
{
    printf("Champions League T20 2025\n");
    char username[50] = {0};
    char user_password[PASSWORD_LENGTH] = {0};
    if (!load_credentials(username, user_password))
    {
        printf("Please create your account.\n");
        ask_for_credentials(username, user_password);
    }
    else
    {
        printf("Welcome back, %s!\n", username);
    }
    Stack match_history = {.top = 0};
    Queue team_queue = {.front = 0, .rear = 0};
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        enqueue(&team_queue, teams[i]);
    }
    int choice;
    while (1)
    {
        printf("1. Create account or Login\n");
        printf("2. Display Teams and Players\n");
        printf("3. Sort Players by ID\n");
        printf("4. Search Player by Name\n");
        printf("5. Select Playing Eleven\n");
        printf("6. Fixtures\n");
        printf("7. Display Match History\n");
        printf("8. Display Points Table\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            printf("1. Create Account\n");
            printf("2. Login\n");
            printf("Enter your choice: ");
            int account_choice;
            scanf("%d", &account_choice);
            getchar();
            if (account_choice == 1)
            {
                ask_for_credentials(username, user_password);
            }
            else if (account_choice == 2)
            {
                printf("Username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0;
                printf("Password: ");
                fgets(user_password, sizeof(user_password), stdin);
                user_password[strcspn(user_password, "\n")] = 0;

                if (login_user(username, user_password))
                {
                    printf("Login successful! Welcome back, %s!\n", username);
                }
                else
                {
                    printf("Invalid username or password. Try again!\n");
                }
            }
            else
            {
                printf("Invalid choice! Please try again.\n");
            }
            break;
        case 2:
            display_teams_and_players();
            break;
        case 3:
        {
            int team_choice;
            handle_team_choice(&team_choice);
            if (team_choice != -1)
            {
                sort_players_by_id(&teams[team_choice - 1]);
            }
            break;
        }
        case 4:
        {
            int team_choice;
            handle_team_choice(&team_choice);
            if (team_choice != -1)
            {
                char name_to_search[50];
                printf("Enter player name to search: ");
                getchar();
                fgets(name_to_search, sizeof(name_to_search), stdin);
                name_to_search[strcspn(name_to_search, "\n")] = 0;
                search_player_by_name(&teams[team_choice - 1], name_to_search);
            }
            else
            {
                printf("Invalid team choice. Please select a valid team.\n");
            }
            break;
        }
        case 5:
        {
            int team_choice;
            handle_team_choice(&team_choice);
            if (team_choice != -1)
            {
                select_playing_eleven(&teams[team_choice - 1]);
            }
            break;
        }
        case 6:
            fixtures(&team_queue, &match_history);
            break;
        case 7:
            display_stack(&match_history);
            break;
        case 8:
            display_points_table();
            break;
        case 9:
            printf("Exiting program...\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
            break;
        }
    }
    return 0;
}
