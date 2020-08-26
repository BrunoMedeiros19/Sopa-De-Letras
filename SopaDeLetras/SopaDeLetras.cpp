#pragma once
/*
Ficheiro: SopaDeLetras.cpp
Título: Sopa de Letras
Autor: Bruno Miguel Barrigas Medeiros 71337
Obs: 
Data: 14/06/2020
Revisões:
......
*/
#include <iostream>
#include "Ponto.h"
#include "Char.h"
#include "Word.h"
#include "Game.h"
#include "Player.h"
#include <time.h>
#include "Master.h"
#include "Rookie.h"
#include <chrono>
#include <fstream>

using namespace std;
#define BOARD_W 25
#define BOARD_H 25


int main()
{
    srand((int)time(NULL));
    int bw = BOARD_W;
    int bh = BOARD_H;
    string name;
    char choose, choose_dif;

    cout <<"\n\n\tDATA : " << __DATE__;
    cout <<"\n\n\t HORA: " << __TIME__;
    cout <<"\n\n   $$ Seja Bem-Vindo ao jogo Sopa de Letras $$ \n\n\n";
    cout <<"   Escreva uma das seguintes opcoes: \n\n\n\n\n";
    cout << "\tA-->   NOVO JOGO \n\n\n\n\n";
    cout << "\tB-->   RETOMAR A PARTIDA GUARDADA \n\n\n\n\n";
    cout << "\tC-->   SAIR DO JOGO \n\n\n\n\n";
    cout << "\tEscreva o seu nome: ";
    cin >> name;
    cout << "\n\n\tEscolha: ";
    cin >> choose;

    switch(choose)
    {
        /*Opcao para jogar a sopa de letras*/
        case 'A':
        case 'a':
        {
            cout << "\n\n\tEscolha a dificuldade do jogo: Rookie -> r ; Master -> m: ";
            cin >> choose_dif;

            /*• O jogador Rooky deve poder jogar uma partida com menos palavras para descobrir e as
            palavras que se encontram na matriz devem ser apresentadas no ecrã*/
            if( choose_dif == 'r')
            {
                system("cls");
                Rookie player;
                player.SetName(name);
                cout << "Difficulty: Rookie\n";
                cout << "Player: " << player.View() << endl;
                cout << "Board Size = " << bw << " Wide X " << bh << " High" << endl;
                
                
                Game MyGame(BOARD_W, BOARD_H, name,0);
                
                MyGame.Run();

                cout << "Parabens "<< player.View() <<", esta foi facil, tenta jogar agora o modo Master!" << endl;
                cout << "Pontuacao: " << MyGame.Get_PlayBoard().Get_Numwords() << " pontos" << endl;
                system("pause");
                exit(0);
                
            }
            /*O jogador Master deve jogar uma partida com, pelo menos, 8 palavras para descobrir e
            as palavras, que se encontram na matriz, não devem ser apresentadas no ecrã. Neste
            tipo de jogador deve ser contabilizado o tempo de jogo e devem ser atribuídos pontos
            ao jogador, tendo em conta o tempo que demorou a terminar um jogo.*/
            else
            {
                system("cls");
                Master player;
                player.SetName(name);
                cout << "Difficulty: Master\n";
                cout << "Player: " << player.View() << endl;
                cout << "Board Size = " << bw << " Wide X " << bh << " High" << endl;;
                
                Game MyGame(BOARD_W, BOARD_H, name,1);//inicializar a matriz

                chrono::steady_clock sc;//função da library chrono que serve para medir intervalos de tempos
                auto start = sc.now();//definicao do inicio do tempo
                MyGame.Run();
                auto end = sc.now();//definicao do fim do tempo       
                auto time_span = static_cast<chrono::duration<double>>(end - start);   //É medido o tempo que passou com a subtracao do tempo final - inicial
                int tempo = (int)time_span.count() / 60; //este tempo vai nos arrendondar uma vez que está int ou seja 0,3min = 0min
                float aux_tempo =(int) time_span.count() / 60;//tempo auxiliar para calcular os segundos que nos da 0,3min certos e nao 0min
                int tempo_s = (int)aux_tempo * 6;
                /*Aqui a pontuacao vai ser dividida em 3 partes bom , normal , mau*/
                /*É DADA A PONTUACAO MAXIMA*/
                if(tempo < 3)
                {
                    cout << "Como acabou o jogo antes de 3min recebeste a pontuacao maxima!" << endl;
                    cout << "Parabens " << player.View() << " pelo teu tempo incrivel!" << endl;
                    cout << "Pontuacao: " << MyGame.Get_PlayBoard().Get_Numwords() << " pontos" << endl;
                    cout << "Tempo Jogado:" << tempo << " min e " <<tempo_s << "segundos" << endl;
                    system("pause");
                    exit(0);
                }
                /*É DADA 50% DA PONTUACAO MAXIMA*/
                else if(tempo <5)
                {
                    cout << "Como acabou o jogo antes de 5min recebeste a pontuacao media!" << endl;
                    cout << "Nao esta mau " << player.View() << " mas ainda podes melhorar!" << endl;
                    cout << "Pontuacao: " << (MyGame.Get_PlayBoard().Get_Numwords()*0.5) << " pontos" << endl;
                    cout << "Tempo Jogado:" << tempo << " min e " << tempo_s << "segundos" << endl;
                    system("pause");
                    exit(0);
                }
                /*É DADA 25% DA PONTUACAO MAXIMA*/
                else if(tempo <7)
                {
                    cout << "Como acabou o jogo antes de 7min recebeste a pontuacao baixa!" << endl;
                    cout << "Joga novamente " << player.View() << " para melhorar o teu tempo." << endl;
                    cout << "Pontuacao: " << (MyGame.Get_PlayBoard().Get_Numwords() * 0.25) << " pontos" << endl;
                    cout << "Tempo Jogado:" << tempo << " min e " << tempo_s << "segundos" << endl;
                    system("pause");
                    exit(0);
                }
            }
        }
           
        /*Opcao para retomar a partida guardada*/
        case 'B':
        case 'b':
        {
            system("cls");
            ifstream is("save-game.txt");
            string line;
            if(is.is_open())
            {
                Game My_Game;             
                My_Game.Read(is);
                cout << "BEM-VINDO DE VOLTA!" << endl;
                ////tamanho da matriz
                //cout << My_Game.Get_PlayBoard().Get_BoardHeight() << ";" << My_Game.Get_PlayBoard().Get_BoardWidth() << endl;
                //My_Game.Get_PlayBoard().View();
                //cout << endl;
                ////nº de palavras
                //cout << My_Game.Get_PlayBoard().Get_Numwords() << endl;
                //cout << endl;

                ////palavras que existem na matriz
                //for(int i=0; i < My_Game.Get_PlayBoard().Get_Numwords(); i++)
                //{
                //    cout << My_Game.Get_PlayBoard().Get_Word(i) << ",";
                //}
                //cout << endl;
                ////palavras descobertas
                //for (int i = 0; i < My_Game.Get_PlayBoard().Get_Numwords(); i++)
                //{
                //    cout << My_Game.Get_Wordstxt(i) << ",";
                //}
                //cout << "\n" << My_Game.Get_Name() << ",score: "<< My_Game.Get_Score() << "|Dificuldade: " << My_Game.Get_Difficulty();
                My_Game.Run();
                system("pause");
                exit(0);
            }
        }
        /*Opcao para sair do jogo*/
        case 'C':
        case 'c':
        {
            exit(0);
        }
    }

}
