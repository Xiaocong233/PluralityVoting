#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // if name matches any of the candidates', update his/her vote count, then returning true, else return false
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Initializing the number of winners to be 1
    int numberOfWinner = 1;
    // Declaring an array to store potential winners
    string winner[candidate_count];
    // Initializing the highest number of votes to be the first candidate's
    int highVote = candidates[0].votes;
    // Initializing the winner to be the first candidate
    winner[numberOfWinner - 1] = candidates[0].name;

    // Iterating through all candidates, comparing their vote counts to the highVote and do corresponding operation
    for (int i = 1; i < candidate_count; i++)
    {
        // If the ith candidate has a higher vote count than high vote, update the winner and highVote
        if (candidates[i].votes > highVote)
        {
            winner[0] = candidates[i].name;
            highVote = candidates[i].votes;
        }
        // If the ith candidate has the same vote count as high vote, increase the number of winners and store that candidate's name into the next place in the winner array
        else if (candidates[i].votes == highVote)
        {
            numberOfWinner++;
            winner[numberOfWinner - 1] = candidates[i].name;
        }
    }
    // If there is only one winner, print out his/her name
    if (numberOfWinner == 1)
    {
        printf("%s\n", winner[0]);
    }
    else
    {
        // Else print out all winners' names
        for (int i = 0; i < numberOfWinner; i++)
        {
            printf("%s\n", winner[i]);
        }
    }
    return;
}
