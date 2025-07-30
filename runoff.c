#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] é o j-ésimo candidato preferido do eleitor i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

// Funções
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Uso: runoff [candidato ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Máximo de candidatos é %i\n", MAX_CANDIDATES);
        return 2;
    }

    // Inicializa candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Número de eleitores: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Máximo de eleitores é %i\n", MAX_VOTERS);
        return 3;
    }

    // Lê todas as preferências
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Voto %i de %i: ", j + 1, candidate_count);

            if (!vote(i, j, name))
            {
                printf("Voto inválido.\n");
                return 4;
            }
        }
    }

    // Loop da eleição
    while (true)
    {
        tabulate();

        if (print_winner())
        {
            break;
        }

        int min = find_min();
        if (is_tie(min))
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        eliminate(min);

        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
}

// Registra a preferência do eleitor
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Conta votos para o candidato mais preferido não eliminado
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int idx = preferences[i][j];
            if (!candidates[idx].eliminated)
            {
                candidates[idx].votes++;
                break;
            }
        }
    }
}

// Imprime o vencedor se alguém tiver maioria
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Retorna o menor número de votos entre os candidatos restantes
int find_min(void)
{
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Verifica se todos os candidatos restantes estão empatados
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Elimina candidatos com o menor número de votos
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
