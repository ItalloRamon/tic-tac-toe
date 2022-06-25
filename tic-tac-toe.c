#include <stdio.h>
#include <math.h>

void print_campo(char board[][3]){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c", board[i][j]);
            if (j != 2)
            {
                printf("  |");
            }
        }
        printf("\n");
        printf("---|---|---\n");
    }
}
int acabou_jogo(char board[][3]){
    //Verificar linhas
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) //Linha está preencihda
        {
            if (board[i][0] == 'X')
            {
                return 10;
            }
            else if (board[i][0] == 'O')
            {
                return -10;
            }
        }
    }
    //Verificar colunas
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j])
        {
            if (board[0][j] == 'X')
            {
                return 10;
            }
            else if (board[0][j] == 'O')
            {
                return -10;
            }
        }
    }
    //Verificar diagonais
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'X')
        {
            return 10;
        }
        else if (board[0][0] == 'O')
        {
            return -10;
        }
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == 'X')
        {
            return 10;
        }
        else if (board[0][2] == 'O')
        {
            return -10;
        }
    }
    
    //Se ngm ganhou, nem empatou retorna 0
    int moves_left = isMovesLeft(board);
    if (moves_left == 0)
    {
        return 2; //Empate
    }
    return 0;
}
int isMovesLeft(char board[][3]){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return 1;
            }
        }
    }
    return 0;
}
int minimax(char board[][3], int isMax){
    int score, moves_left;
    moves_left = isMovesLeft(board);
    score = acabou_jogo(board);
    if (score == 10 || score == -10)
    {
        return score;
    }
    if (moves_left == 0)
    {
        return score;
    }
    
    if (isMax == 1)
    {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    score = minimax(board, 0);
                    board[i][j] = ' ';
                    if (score > bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    score = minimax(board, 1);
                    board[i][j] = ' ';
                    if (score < bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    
}
void find_best_move(char board[][3], char marca_player, char marca_pc, int key){
    int x, y, bestScore, score;
    if (key == 1) //PC é o 1 jogador
    {
        bestScore = -1000;
    }
    else
    {
        bestScore = 1000;
    }
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = marca_pc;
                if (key == 1)
                {
                    score = minimax(board, 0);
                }
                else
                {
                    score = minimax(board, 1);
                }
                board[i][j] = ' ';
                if (score < bestScore && key == 0)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
                else if (score > bestScore && key == 1)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
            int moves_left = isMovesLeft(board);
            if (moves_left == 0)
            {
                return;
            }
        }
    }
    board[x][y] = marca_pc;
}
int jogada(char board[3][3], char marca, int x, int y){
    if ((x < 0 || x > 2) || (y < 0 || y > 2))
    {
        return 0;
    }
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == x && j == y)
            {
                if (board[i][j] == ' ')
                {
                    return 200;
                }
                else
                {
                    //printf("Posição inválida\n");
                    return 0;
                }
            }
        }
    }
}

int main(){
    int jogadas_pc = 0;
    char board[3][3];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }

    int jogador, key;
    char marca_player, marca_pc;
    while(1)
    {
        printf("Digite 1 para ser o Jogador 1 (X) ou digite 2 para ser Jogador 2 (O): ");
        scanf("%d", &jogador);
        if (jogador == 1)
        {
            marca_player = 'X';
            marca_pc = 'O';
            key = 0;
            break;
        }
        else if (jogador == 2)
        {
            marca_player = 'O';
            marca_pc = 'X';
            key = 1;
            break;
        }
        else
        {
            printf("Digite uma opção válida.\n");
        }
    }

    int should_continue = 0;
    while (should_continue == 0)
    {
        if (key == 1)
        {
            find_best_move(board, marca_player, marca_pc, key);
            print_campo(board);
            should_continue = acabou_jogo(board);
        }
        if (should_continue == 0)
        {
            int x, y, eh_valida = 0;
            while (eh_valida == 0)
            {
                printf("Digite um posição para jogar: ");
                scanf("%d %d", &x, &y);
                x--;
                y--;
                eh_valida = jogada(board, marca_player, x, y);
            }
            board[x][y] = marca_player;
        }
        if (key == 0)
        {
            find_best_move(board, marca_player, marca_pc, key);
            print_campo(board);
        }
        should_continue = acabou_jogo(board);
    }
    if (should_continue == 10 || should_continue == -10)
    {
        printf("Você perdeu :(\n");
    }
    else
    {
        printf("Parabéns, você empatou!\n");
    }
    return 0;
}
