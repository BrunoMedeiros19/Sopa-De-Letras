#pragma once
#include "Board.h"
#include "Char.h"
#include "Word.h"
#include <vector>


Board::Board(void)
{
	/*Método para inicializar as variaveis e objetos*/
	Set_BoardWidth(0); Set_BoardWidth(0);
	Chars = NULL;
	Words = NULL;
	NumWords = 0;
}

void Board::Init(int Sx, int Sy, int dif)
{
	ifstream is;
	string word;
	Ponto p;
	Set_BoardWidth(Sx); Set_BoardHeight(Sy);

	
	//Alocação dinamica de memoria onde cada entrada da matriz
	//é uma classe que pertence a char.
	if ((Chars = (Char**) new Char * [Sy]) == NULL)
	{
		cout << "Nao foi possivel alocar memoria" << endl;
		exit(0);
	}

	//caso crie um vetor y vamos criar para cada entrada 
	//vamos criar um vetor x
	for (int i = 0; i < Sy; i++)
	{
		if ((Chars[i] = (Char*) new Char[Sx]) == NULL)
		{
			cout << "Nao foi possivel alocar memoria" << endl;	//aqui cada entrada dessa 
			exit(0);											//array criada anteriormente
		}															//vai criar uma array criando assim uma matriz

	}
	for (int i = 0; i < Sy; i++)
	{
		for (int j = 0; j < Sx; j++)
		{
			Chars[i][j].Rand();//colocacao random de um caracter
			p.SetX(i);
			p.SetY(j);
			Chars[i][j].Set_ChPosition(p);
			//como todas as coordenas sao aleatorias vamos definir o free para 0
			Chars[i][j].set_free(0);
			//fica 0 aqui
		}
	}
	/*DIFICULDADE ROOKIE*/
	if(dif == 0)
	{
		is.open("lista_palavras.txt");
		if (!is)
		{
			cout << "Nao foi possivel ler o ficheiro de texto lista_palavras.txt" << endl;
			exit(1);
		}
		/*primeira linha do ficheiro de texto vai corresponder
		ao numero de palavras que existem*/
		is >> NumWords;
		NumWords = (int)(NumWords * 0.5);
		/*Criação do vetor Words onde vai ter as palavras
		que foram lidas do ficheiro de texto*/
		if ((Words = new Word[NumWords]) == NULL)
		{
			cout << "Nao foi possivel alocar memoria" << endl;
			exit(0);
		}
		/*Atribuição das palavras do ficheiro no vetor Words*/
		for (int i = 0; i < NumWords; i++)
		{
			is >> word;
			Words[i].Set_Letters(word);
		}
		is.close();
		/*O numero de palavras tem de ser par uma vez que defini que quando fosse
		ROOKIE a dificuldade ,iria ser so usadas 50% das palavras portanto tem de
		existir um numero par para assim ser inteiro quando dividr por 2*/
		if (NumWords % 2 == 0)
		{
			/*ESCREVE AS PALAVRAS NA SOPA DE LETRAS*/
			Insert_Words(Sx, Sy);
			//cout << "\n\n###NUMERO TOTAL DE PALAVRAS: " << NumWords;
			Verify_Coord(Sx, Sy);
			//system("pause");
		}
		else
		{
			cout << "Coloque um nº par de palavras no ficheito lista_palavras.txt!" << endl;
			cout << "Caso contrário o programa não vai funcionar";
			exit(0);
		}
	}
	/*NIVEL MASTER*/
	if(dif ==1)
	{
		is.open("lista_palavras.txt");
		if (!is)
		{
			cout << "Nao foi possivel ler o ficheiro de texto lista_palavras.txt" << endl;
			exit(1);
		}
		/*primeira linha do ficheiro de texto vai corresponder
		ao numero de palavras que existem*/
		is >> NumWords;

		/*Tem de ser pelo menos 8 palavras segundo o protocolo portanto caso nao seja avisamos*/
		if(NumWords<8)
		{
			cout << "ERRO, MINIMO DE PALAVRAS PARA SER JOGADO MODO MASTER E 8!!" << endl;
			exit(0);
		}

		/*Criação do vetor Words onde vai ter as palavras
		que foram lidas do ficheiro de texto*/
		if ((Words = new Word[NumWords]) == NULL)
		{
			cout << "Nao foi possivel alocar memoria" << endl;
			exit(0);
		}
		/*Atribuição das palavras do ficheiro no vetor Words*/
		for (int i = 0; i < NumWords; i++)
		{
			is >> word;
			Words[i].Set_Letters(word);
		}
		is.close();
		
		/*ESCREVE AS PALAVRAS NA SOPA DE LETRAS*/
		Insert_Words(Sx, Sy);
		//cout << "\n\n###NUMERO TOTAL DE PALAVRAS: " << NumWords;
		Verify_Coord(Sx, Sy);
		//system("pause");
		
	}
	
}

void Board::View()
{
	/*Mostra a SOPA DE LETRAS*/
	cout << endl;
	for (int i = 0; i < Get_BoardHeight(); i++)
	{
		for (int j = 0; j <Get_BoardWidth() ; j++)
		{
			Chars[i][j].View();
			cout << " ";
		}
		cout <<"|"<< i << "|"<<endl;
	}
	cout << "\n\n*matriz das posicoes ocupadas* (so funciona no modo novo jogo) ";
	cout << "\n";
	//tabela com posicoes disponiveis
	for (int i = 0; i < Get_BoardHeight(); i++)
	{
		for (int j = 0; j < Get_BoardWidth(); j++)
		{
			Chars[i][j].View_availbpos();
			cout << " ";
		}
		cout << "|" << i << "|" << endl;
	}
	
}

Board::~Board()
{
}

void Board::Save(ofstream &os)
{
	/*GUARDA OS CARACTERES E TAMANHO DA MATRIZ*/
	os << BoardHeight << ";" << BoardWidth << endl;

	for(int i = 0; i < BoardHeight; i++)
	{
		for(int j= 0 ; j < BoardWidth; j++)
		{
			Chars[i][j].Save(os);
		}
	}
	os << endl;
	os << NumWords;
	os << endl;

	/*As palavras que existem para serem encontradas*/
	for (int i = 0; i < NumWords; i++)
	{
		Words[i].Save(os);
	}
}
/*Este metodo lê as dimensoes da matriz que estao no ficheito de txt e 
cria uma matriz com essas dimensoes e coloca as letras com esse valor*/
void Board::Read(ifstream& is)
{
	string l1,l2,l3,l4,l5;//posso so ter 1 variavel
	
		getline(is, l1, ';');//procura a primeira coisa ate encontrar o ;
		BoardHeight = stoi(l1);//conversao de string para int
		getline(is, l2, '\n');
		BoardWidth = stoi(l2);

		if ((Chars = (Char**) new Char * [BoardHeight]) == NULL)
		{
			cout << "Nao foi possivel alocar memoria" << endl;
			exit(0);
		}

		for (int i = 0; i < BoardHeight; i++)
		{
			if ((Chars[i] = (Char*) new Char[BoardWidth]) == NULL)
			{
				cout << "Nao foi possivel alocar memoria" << endl;
				exit(0);											
			}														

		}
		for(int i=0; i < BoardHeight; i++)
		{
			for(int j=0; j < BoardWidth; j++)
			{
				Chars[i][j].Read(is);
				getline(is, l3, ';');
				
			}
		}
		getline(is, l3, '\n');
		getline(is, l4, '\n');
		NumWords = stoi(l4);

		if ((Words = new Word[NumWords]) == NULL)
		{
			cout << "Nao foi possivel alocar memoria" << endl;
			exit(0);
		}
		//criação de um vector que aloca as palavras
		vector<string> result;
		int i = 0;
		while (i<NumWords)
		{
			string substr;
			getline(is, substr, ',');
			result.push_back(substr);
			Words[i].Set_Letters(substr);
			i++;
		}		
		
		getline(is, l3, '\n');
}

void Board::Insert_Words(int Sy, int Sx)
{
	char ch;
	for (int i = 0; i < NumWords; i++)
	{
		Ponto P;
		//cria as coordernadas aleatorias para a primeira letra e assegura que vai estar sempre dos limites da matriz
		P.SetX(int (rand() % (Sy - Words[i].Lenght())));
		P.SetY(int (rand() % (Sx - Words[i].Lenght())));
		//coordenadas da primeira letra da palavra
		int x = P.GetX();
		int y = P.GetY();
		Words[i].Set_Position(P);

		//este set vai definir a orientacao que tem a palavra que é aleatoria
		Words[i].Set_Orient();
		
		//VERTICAL
		if(Words[i].Get_Orient() == 1)
		{
			//cout << endl;
			//cout << Words[i].Get_Letters() << "|Coordenadas: (" << x << " ate " << x + Words[i].Lenght()-1 << "," << y << ") --> ";		
			/*Ciclo para colocar as letras na VERTICAL*/
			for (int j = 0; j < Words[i].Lenght(); j++)
			{
				ch = (Words[i].Get_Ch(j));
				//cout << ch << "(";
				//so funciona quando o y < 25
				//verificar se a posicao do chars tem free ativo ou nao
				Chars[(x + j)][y].Set_Ch(ch);
				Chars[(x + j)][y].set_free(1);

				/*Atribuicao de coordenadas a cada letra*/
				P.SetX(x + j);
				P.SetY(y);
				
				Chars[(x + j)][y].Set_ChPosition(P);
				//cout << Chars[(x + j)][y].Get_ChPosition().GetX() << ","<< Chars[(x + j)][y].Get_ChPosition().GetY() << ") ";			
			}
		}
		/*Ciclo para colocar as letras na HORIZONTAL*/
		else if(Words[i].Get_Orient()==2)
		{
			/*cout << endl;
			cout << Words[i].Get_Letters() << "|Coordenadas: (" << x << "," << y <<" ate "<< y+ Words[i].Lenght()-1 << ") --> ";*/
			for (int j = 0; j < Words[i].Lenght(); j++)
			{
				ch = (Words[i].Get_Ch(j));
				//cout << ch << "(";
				//so funciona quando o y + comprimento da palavra for < Board
				Chars[x][y + j].Set_Ch(ch);
				Chars[x][y+j].set_free(1);
				//cout << Chars[(x)][y+j].Get_ChPosition().GetX() << "," << Chars[x][y+j].Get_ChPosition().GetY() << ") ";
			}
		}
		/*Ciclo para colocar as letras na DIAGONAL*/
		else
		{
			/*cout << endl;
			cout << Words[i].Get_Letters() << "|Coordenadas: (" << x << " ate " << x + Words[i].Lenght()-1<< "," << y << " ate " << y + Words[i].Lenght()-1 << ") --> ";*/
			for (int j = 0; j < Words[i].Lenght(); j++)
			{
				ch = (Words[i].Get_Ch(j));
				//cout << ch << "(";
				Chars[(x + j)][(y + j)].Set_Ch(ch);
				Chars[(x + j)][(y+j)].set_free(1);
				//cout << Chars[(x + j)][y+j].Get_ChPosition().GetX() << "," << Chars[(x + j)][y+j].Get_ChPosition().GetY() << ") ";
			}
		}
			
	}

}

/*VERIFICACAO DE PALAVRAS*/
void Board::Verify_Coord(int Sy, int Sx) 
{			
		/*ESTE CICLO SERVE PARA CADA LETRA DE CADA PALAVRA COM DETERMINADAS COORDENADAS
		SER COMPARADA COM TODAS AS OUTRAS LETRAS EXISTENTES*/

		/*CICLO DE PALAVRAS QUE COMEÇA COM A PRIMEIRA QUE ESTA NO VECTOR WORDS[I]*/
		for(int i=0; i < NumWords; i++)
		{
			//cout << "\n ### " << Words[i].Get_Letters() << " ###\n";
			/*Este ciclo vai servir para  a segunda palavra a ser comparada que tem de ser uma posicao
			a mais que a palavra inicial*/
			for (int c = (1+i); c < NumWords ; c++)//0 1 2 3 4
			{
				//cout << "\nCOORDENADAS INICIAS ATUALIZADAS" << endl;
				//for (int i = 0; i < NumWords; i++)
				//{
				//	cout << "\n" << Words[i].Get_Letters() << "--> (" << Words[i].Get_Position().GetX() << "," << Words[i].Get_Position().GetY() << ") /Orientation: " <<Words[i].Get_Orient();			
				//}				
				//cout << "\n\n##" << Words[i].Get_Letters() << " a comparar com " << Words[c].Get_Letters() << "--> " << "\n\n";
				//cout << "\nVALOR DE I:" << i << "\n\n";
				//cout << "VALOR DE C:" << c << "\n\n";
				/*Significa que a primeira palavra é VERTICAL e a segunda palavra VERTICAL*/
				if ((Words[i].Get_Orient() == 1) && (Words[c].Get_Orient() == 1))
				{

					/*CICLO PARA A PALAVRA QUE VAMOS COMPARAR QUE É SEMPRE A PROXIMA
						DA PALAVRA INICIAL*/
					for (int b = 0; b < Words[i].Lenght(); b++)//PORTUGAL-> 8 letras
					{
						for (int j = 0; j < Words[c].Lenght(); j++)//ESPANHA-> 7 letras
						{
							//coordenadas da n letra da primeira palavra 
							int x = (Words[i].Get_Position().GetX() + b);
							int y = Words[i].Get_Position().GetY();
							Ponto P(x, y);
							//cout << "\nCOMPARANDO..."; //estamos a comparar a coordenada da primeira palavra c
							//P.Show();
							//coordenadas da n letra da segunda palavra
							int x2 = (Words[c].Get_Position().GetX() + j);
							int y2 = Words[c].Get_Position().GetY();

							Ponto P2(x2, y2);
							//P2.Show();
							if (P == P2)
							{
								//cout << "COORDENADAS IGUAS! ->" << Words[i].Get_Letters() << "igual a " << Words[c].Get_Letters() << endl;
								/*Neste caso quando existem duas palavras que tem a mesma orientação e uma coordenada em comum, nao 
								e necessario saber se tem uma letra em comum pois o desfecho é sempre o msm vamos ter de inserir noutro lugar
								uma vez que é impossivel cruzar palavras com a mesma orientação.*/
								Ponto new_c;
								new_c = Insert_freeSpace(Words[c], Words[i], Words[c].Get_Orient(), Words[i].Get_Orient());
								Words[c].Set_Position(new_c);
								Update_Matrix(Sy, Sx);
								/*Se a palavra foi mudada de posicao colocamos um fim a estes dois ciclos 
								para assim passar-mos para outra palavra para ser comparada as pos*/
								j = (int)Words[c].Lenght();
								b = (int)Words[i].Lenght();
								
							}
							//mudança de letra ou seja de coordenadas
						}
					}
					//posicao pretendida
				}
				//VERTICAL COMPARADA -> HORIZONTAL
				if ((Words[i].Get_Orient() == 1) && (Words[c].Get_Orient() == 2))
				{
					/*CICLO PARA A PALAVRA QUE VAMOS COMPARAR QUE É SEMPRE A PROXIMA
						DA PALAVRA INICIAL*/
					for (int b = 0; b < Words[i].Lenght(); b++)
					{
						for (int j = 0; j < Words[c].Lenght(); j++)
						{
							//coordenadas da primeira letra da primeira palavra
							int x = Words[i].Get_Position().GetX() + b;
							int y = Words[i].Get_Position().GetY();
							Ponto P(x, y);
							/*cout << "\nCOMPARANDO...";
							P.Show();*/
							//coordenadas da primeira letra da segunda palavra
							int x2 = Words[c].Get_Position().GetX();
							int y2 = (Words[c].Get_Position().GetY() + j);
							Ponto P2(x2, y2);
							//P2.Show();

							if (P == P2)
							{
								//cout << "COORDENADAS IGUAS! ->" << Words[i].Get_Letters() << " igual a " << Words[c].Get_Letters() << endl;
								char equal_ch = Verify_Char(Words[i].Get_Letters(), Words[c].Get_Letters());
								/*caso exista um caracter em comum faz isto caso contrario aloca num espaco livre a palavra*/
								if (equal_ch != NULL)
								{
									//cout << "letra em comum: " << equal_ch << endl;
									Ponto NewCoord;//ponto que vai guardar as coordenadas atualizadas
									/*Realocacao da letra na matriz de modo a que se cruzem*/
									NewCoord = Reallocate_Words(Words[i], Words[c], equal_ch);
									//return da posicao do palavra que cruzamos e atualizamos as coordenadas;										
									Words[c].Set_Position(NewCoord);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
								else
								{
									//cout << "nao tem letra em comum" << endl;
									//metodo que encontra coordenadas livres onde nao haja palavras
									Ponto new_c;
									new_c = Insert_freeSpace(Words[c], Words[i], Words[c].Get_Orient(), Words[i].Get_Orient());
									Words[c].Set_Position(new_c);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
							}
						}
					}
				}
				if ((Words[i].Get_Orient() == 1) && (Words[c].Get_Orient() == 3))
				{
					/*CICLO PARA A PALAVRA QUE VAMOS COMPARAR QUE É SEMPRE A PROXIMA
						DA PALAVRA INICIAL ou seja +1 no vetor Words*/
					for (int b = 0; b < Words[i].Lenght(); b++)
					{
						for (int j = 0; j < Words[c].Lenght(); j++)
						{
							//coordenadas da primeira letra da primeira palavra
							int x = (Words[i].Get_Position().GetX() + b);
							int y = Words[i].Get_Position().GetY();
							Ponto P(x, y);
							/*cout << "\nCOMPARANDO...";
							P.Show();*/
							//coordenadas da primeira letra da segunda palavra
							int x2 = (Words[c].Get_Position().GetX() + j);
							int y2 = (Words[c].Get_Position().GetY() + j);
							Ponto P2(x2, y2);
							//P2.Show();
							if (P == P2)
							{
								//cout << "COORDENADAS IGUAS! ->" << Words[i].Get_Letters() << " igual a " << Words[c].Get_Letters() << endl;
								char equal_ch = Verify_Char(Words[i].Get_Letters(), Words[c].Get_Letters());
								/*caso exista um caracter em comum faz isto caso contrario aloca num espaco livre a palavra*/
								if (equal_ch != NULL)
								{
									//cout << "letra em comum: " << equal_ch << endl;
									Ponto NewCoord;
									/*Realocacao da letra na matriz de modo a que se cruzem*/
									NewCoord = Reallocate_Words(Words[i], Words[c], equal_ch);
									//return da posicao do palavra que cruzamos e atualizamos as coordenadas;										
									Words[c].Set_Position(NewCoord);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
								else
								{
									//cout << "nao tem letra em comum" << endl;
									//metodo que encontra coordenadas livres onde nao haja palavras
									Ponto new_c;
									new_c = Insert_freeSpace(Words[c], Words[i], Words[c].Get_Orient(), Words[i].Get_Orient());
									Words[c].Set_Position(new_c);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
							}

						}

					}

				}
				/*Significa que a primeira palavra é HORIZONTAL e a segunda palavra VERTICAL*/
				if ((Words[i].Get_Orient() == 2) && (Words[c].Get_Orient() == 1))
				{
					/*CICLO PARA A PALAVRA QUE VAMOS COMPARAR QUE É SEMPRE A PROXIMA
						DA PALAVRA INICIAL*/
					for (int b = 0; b < Words[i].Lenght(); b++)
					{
						for (int j = 0; j < Words[c].Lenght(); j++)
						{
							//coordenadas da primeira letra da primeira palavra
							int x = Words[i].Get_Position().GetX();
							int y = (Words[i].Get_Position().GetY() + b);
							Ponto P(x, y);
							/*cout << "\nCOMPARANDO...";
							P.Show();*/
							//coordenadas da primeira letra da segunda palavra
							int x2 = (Words[c].Get_Position().GetX() + j);
							int y2 = Words[c].Get_Position().GetY();
							Ponto P2(x2, y2);
							//P2.Show();
							if (P == P2)
							{
								//cout << "COORDENADAS IGUAS! ->" << Words[i].Get_Letters() << " igual a " << Words[c].Get_Letters() << endl;
								char equal_ch = Verify_Char(Words[i].Get_Letters(), Words[c].Get_Letters());
								/*caso exista um caracter em comum faz isto caso contrario aloca num espaco livre a palavra*/
								if (equal_ch != NULL)
								{
									//cout << " letra em comum: " << equal_ch << endl;
									Ponto NewCoord;
									/*Realocacao da letra na matriz de modo a que se cruzem*/
									NewCoord = Reallocate_Words(Words[i], Words[c], equal_ch);
									//return da posicao do palavra que cruzamos e atualizamos as coordenadas;										
									Words[c].Set_Position(NewCoord);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
								else
								{
									//cout << "nao tem letra em comum" << endl;
									//metodo que encontra coordenadas livres onde nao haja palavras
									Ponto new_c;
									new_c = Insert_freeSpace(Words[c], Words[i], Words[c].Get_Orient(), Words[i].Get_Orient());
									Words[c].Set_Position(new_c);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
							}
						}

					}


				}

				if ((Words[i].Get_Orient() == 2) && (Words[c].Get_Orient() == 2))
				{
					/*CICLO PARA A PALAVRA QUE VAMOS COMPARAR QUE É SEMPRE A PROXIMA
					DA PALAVRA INICIAL*/
					for (int b = 0; b < Words[i].Lenght(); b++)
					{
						for (int j = 0; j < Words[c].Lenght(); j++)
						{
							//coordenadas da primeira letra da primeira palavra
							int x = Words[i].Get_Position().GetX();
							int y = Words[i].Get_Position().GetY() + b;
							Ponto P(x, y);
							/*cout << "\nCOMPARANDO...";
							P.Show();*/
							//coordenadas da primeira letra da segunda palavra
							int x2 = (Words[c].Get_Position().GetX());
							int y2 = Words[c].Get_Position().GetY() + j;
							Ponto P2(x2, y2);
							//P2.Show();
							if (P == P2)
							{
								//cout << "COORDENADAS IGUAS! ->" << Words[i].Get_Letters() << " igual a " << Words[c].Get_Letters() << endl;
								/*Neste caso quando existem duas palavras que tem a mesma orientação e uma coordenada em comum, nao
								e necessario saber se tem uma letra em comum pois o desfecho é sempre o msm vamos ter de inserir noutro lugar
								uma vez que é impossivel cruzar palavras com a mesma orientação.*/
								Ponto new_c;
								new_c = Insert_freeSpace(Words[c], Words[i], Words[c].Get_Orient(), Words[i].Get_Orient());
								Words[c].Set_Position(new_c);
								Update_Matrix(Sy, Sx);
								j = (int)Words[c].Lenght();
								b = (int)Words[i].Lenght();
							}
						}
					}
				}

				if ((Words[i].Get_Orient() == 2) && (Words[c].Get_Orient() == 3))
				{
					/*CICLO PARA A PALAVRA QUE VAMOS COMPARAR QUE É SEMPRE A PROXIMA
						DA PALAVRA INICIAL*/
					for (int b = 0; b < Words[i].Lenght(); b++)
					{
						for (int j = 0; j < Words[c].Lenght(); j++)
						{
							//coordenadas da primeira letra da primeira palavra
							int x = Words[i].Get_Position().GetX();
							int y = Words[i].Get_Position().GetY() + b;
							Ponto P(x, y);
							/*cout << "\nCOMPARANDO...";
							P.Show();*/
							//coordenadas da primeira letra da segunda palavra
							int x2 = (Words[c].Get_Position().GetX() + j);
							int y2 = Words[c].Get_Position().GetY() + j;
							Ponto P2(x2, y2);
							//P2.Show();
							if (P == P2)
							{
								//cout << "COORDENADAS IGUAS! ->" << Words[i].Get_Letters() << " igual a " << Words[c].Get_Letters() << endl;
								char equal_ch = Verify_Char(Words[i].Get_Letters(), Words[c].Get_Letters());
								/*caso exista um caracter em comum faz isto caso contrario aloca num espaco livre a palavra*/
								if (equal_ch != NULL)
								{
									//cout << "letra em comum: " << equal_ch << endl;
									Ponto NewCoord;
									/*Realocacao da letra na matriz de modo a que se cruzem*/
									NewCoord = Reallocate_Words(Words[i], Words[c], equal_ch);
									//return da posicao do palavra que cruzamos e atualizamos as coordenadas;										
									Words[c].Set_Position(NewCoord);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
								else
								{
									//cout << "nao tem letra em comum" << endl;
									//metodo que encontra coordenadas livres onde nao haja palavras
									Ponto new_c;
									new_c = Insert_freeSpace(Words[c], Words[i], Words[c].Get_Orient(), Words[i].Get_Orient());
									Words[c].Set_Position(new_c);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
							}
						}
					}
				}

				if ((Words[i].Get_Orient() == 3) && (Words[c].Get_Orient() == 1))
				{			
					/*CICLO PARA A PALAVRA QUE VAMOS COMPARAR QUE É SEMPRE A PROXIMA
						DA PALAVRA INICIAL*/
					for (int b = 0; b < Words[i].Lenght(); b++)
					{
						for (int j = 0; j < Words[c].Lenght(); j++)
						{
							//coordenadas da primeira letra da primeira palavra
							int x = Words[i].Get_Position().GetX() + b;
							int y = Words[i].Get_Position().GetY() + b;
							Ponto P(x, y);
							/*cout << "\nCOMPARANDO...";
							P.Show();*/
							//coordenadas da primeira letra da segunda palavra
							int x2 = (Words[c].Get_Position().GetX() + j);
							int y2 = (Words[c].Get_Position().GetY());
							Ponto P2(x2, y2);
							//P2.Show();

							if (P == P2)
							{
								//cout << "COORDENADAS IGUAS! ->" << Words[i].Get_Letters() << " igual a " << Words[c].Get_Letters() << endl;
								char equal_ch = Verify_Char(Words[i].Get_Letters(), Words[c].Get_Letters());
								/*caso exista um caracter em comum faz isto caso contrario aloca num espaco livre a palavra*/
								if (equal_ch != NULL)
								{
									//cout << "letra em comum: " << equal_ch << endl;

									Ponto NewCoord;
									/*Realocacao da letra na matriz de modo a que se cruzem*/
									NewCoord = Reallocate_Words(Words[i], Words[c], equal_ch);
									//return da posicao do palavra que cruzamos e atualizamos as coordenadas;										
									Words[c].Set_Position(NewCoord);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();									
								}
								else
								{
									//cout << "nao tem letra em comum" << endl;
									//metodo que encontra coordenadas livres onde nao haja palavras
									Ponto new_c;
									new_c = Insert_freeSpace(Words[c], Words[i], Words[c].Get_Orient(), Words[i].Get_Orient());
									Words[c].Set_Position(new_c);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
							}
						}
					}
				}
				if ((Words[i].Get_Orient() == 3) && (Words[c].Get_Orient() == 2))
				{
					/*CICLO PARA A PALAVRA QUE VAMOS COMPARAR QUE É SEMPRE A PROXIMA
						DA PALAVRA INICIAL*/
					for (int b = 0; b < Words[i].Lenght(); b++)
					{
						for (int j = 0; j < Words[c].Lenght(); j++)
						{
							//coordenadas da primeira letra da primeira palavra
							int x = (Words[i].Get_Position().GetX() + b);
							int y = (Words[i].Get_Position().GetY() + b);
							Ponto P(x, y);
							//cout << "\nCOMPARANDO...";
							//P.Show();
							//coordenadas da primeira letra da segunda palavra
							int x2 = (Words[c].Get_Position().GetX());
							int y2 = (Words[c].Get_Position().GetY() + j);
							Ponto P2(x2, y2);
							//P2.Show();

							if (P == P2)
							{
								//cout << "COORDENADAS IGUAS! ->" << Words[i].Get_Letters() << " igual a " << Words[c].Get_Letters() << endl;
								char equal_ch = Verify_Char(Words[i].Get_Letters(), Words[c].Get_Letters());
								/*caso exista um caracter em comum faz isto caso contrario aloca num espaco livre a palavra*/
								if (equal_ch != NULL)
								{
									//cout << "letra em comum: " << equal_ch << endl;

									Ponto NewCoord;
									/*Realocacao da letra na matriz de modo a que se cruzem*/
									NewCoord = Reallocate_Words(Words[i], Words[c], equal_ch);
									//return da posicao do palavra que cruzamos e atualizamos as coordenadas;										
									Words[c].Set_Position(NewCoord);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
								else
								{
									//cout << "nao tem letra em comum" << endl;
									//metodo que encontra coordenadas livres onde nao haja palavras
									Ponto new_c;
									new_c = Insert_freeSpace(Words[c], Words[i], Words[c].Get_Orient(), Words[i].Get_Orient());
									Words[c].Set_Position(new_c);
									Update_Matrix(Sy, Sx);
									j = (int)Words[c].Lenght();
									b = (int)Words[i].Lenght();
								}
							}
						}
					}
				}

				if ((Words[i].Get_Orient() == 3) && (Words[c].Get_Orient() == 3))
				{
					/*CICLO PARA A PALAVRA QUE VAMOS COMPARAR QUE É SEMPRE A PROXIMA
						DA PALAVRA INICIAL*/
					for (int b = 0; b < Words[i].Lenght(); b++)
					{
						for (int j = 0; j < Words[c].Lenght(); j++)
						{
							//coordenadas da primeira letra da primeira palavra
							int x = Words[i].Get_Position().GetX() + b;
							int y = Words[i].Get_Position().GetY() + b;
							Ponto P(x, y);
							//cout << "\nCOMPARANDO...";
							//P.Show();
							//coordenadas da primeira letra da segunda palavra
							int x2 = (Words[c].Get_Position().GetX() + j);
							int y2 = (Words[c].Get_Position().GetY() + j);
							Ponto P2(x2, y2);
							//P2.Show();

							if (P == P2)
							{
								//cout << "COORDENADAS IGUAS! ->" << Words[i].Get_Letters() << " igual a " << Words[c].Get_Letters() << endl;
								/*Neste caso quando existem duas palavras que tem a mesma orientação e uma coordenada em comum, nao
								e necessario saber se tem uma letra em comum pois o desfecho é sempre o msm vamos ter de inserir noutro lugar
								uma vez que é impossivel cruzar palavras com a mesma orientação.*/
								Ponto new_c;
								new_c = Insert_freeSpace(Words[c], Words[i], Words[c].Get_Orient(), Words[i].Get_Orient());
								Words[c].Set_Position(new_c);
								Update_Matrix(Sy, Sx);
								j = (int)Words[c].Lenght();
								b = (int)Words[i].Lenght();
							}
						}
					}
				}
			}	
		}
		
}

/*Metodo que verifica se existe alguma letra em comum, neste caso sera a primeira
letra em comum entre duas palavras que vai ser devolvida mesmo que existam mais*/
char Board::Verify_Char(string s1, string s2)
{
	for(int i=0; i < s1.length(); i++)
	{
		for(int j=0;j<s2.length();j++)
		{
			if(s1[i] == s2[j])
			{
				//cout << "a letra " << s1[i] << " e igual a " << s2[j];
				return s1[i];
			}
		}
	}
return NULL;
}

/*Este método é responsavel por averiguar se é possível cruzar duas palavras quando as mesmas
possuem uma letra em comum, aqui irá ser testado se é possível esse cruzamento mesmo com letra em comum
através da verificação dos limites da matriz e se a palavra respeita esses limites , caso não seja possível
o cruzamento da 2º palavra com a primeira teremos de chamar o método insert_freespace para que este nos 
coloque a palavra num espaço livre dentro dos limites da matriz devolvendo sempre as coordenadas atualizadas
da primeira letra dessa palavra que foi alterada*/
Ponto Board::Reallocate_Words(Word w1, Word w2, char ch)
{
	Ponto new_c;//ponto que vai guardar as coordenadas caso siga pelo metodo insert_freespace
	Ponto new_coord;//ponto que vai guardar as coordenadas caso siga pelo metodo realoc ou seja a flag = 1

	int flag = 1;//esta flag vai ser usada para saber se atualizamos as coordenadas da palavra cruzada ou se já foi feito no metodo insert_freespace
	Ponto coord_letracomum_1;//este ponto vai guardar as coordenadas da palavra w1(primeira palavra) onde tem a letra em comum
	
	int pos_letracomum_2 = 0;//posição da letra na segunda palavra onde tem a letra em comum com a primeira
	//coordenadas da primeira palavra
	int x = w1.Get_Position().GetX();
	int y = w1.Get_Position().GetY();

	//coordenadas da segunda palavra
	int x_2 = w2.Get_Position().GetX();
	int y_2 = w2.Get_Position().GetY();
	int cont = 0;
	/*NOTEMOS QUE CADA PALAVRA TEM UMA ORIENTACAO PORTANTO TEMOS DE TER
	ISSO EM CONTA AO VOLTARMOS A REALOCAR A PALAVRA NA MATRIZ DE MODO A QUE
	NENHUMA PALAVRA FIQUE "TAPADA*/
	/*NOTEMOS TAMBEM QUE QUANDO AS DUAS PALAVRAS TEM A MESMA ORIENTAÇÃO É IMPOSSIVEL
	CRUZA-LAS COM QUE ENTAO CHAMAMOS O METODO INSERT_FREESPACE*/

	if(w1.Get_Orient()==1 && w2.Get_Orient() == 1)
	{
		//aloca a palavra num sitio na matriz que esteja livre
		new_c = Insert_freeSpace(w2, w1, w2.Get_Orient(), w1.Get_Orient());
		return new_c;
	}
	/*1º PALAVRA -> VERTICAL; 2ºPALAVRA-> HORIZONTAL*/
	else if(w1.Get_Orient()==1 && w2.Get_Orient() == 2)
	{
		//cenarios possiveis para verificacao
		/*verificar que ao colocar a palavra nao vá bater nas extremidades da matriz*/

		//encontrar a coordenada da palavra principal onde tem a letra em comum
		for(int i=0; i < w1.Lenght();i++)
		{
			if(Chars[x+i][y].Get_Ch() == ch)
			{
				coord_letracomum_1.SetX(x+i);
				coord_letracomum_1.SetY(y);
				//assim que encontra a primeira sai do ciclo
				i = (int)w1.Lenght();
			}
		}
		/*cout << "Coord. da primeira palavra onde tem letra comum -> ";
		coord_letracomum_1.Show();
		cout << endl;*/

		//encontrar a posicao da letra da segunda palavra que tem a letra em comum com a primeira palavra
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (w2.Get_Ch(i) == ch)
			{
				pos_letracomum_2 = i;
				i = (int)w2.Lenght();
			}
		}

		//cout << "Posicao da letra da segunda palavra que tem a letra em comum:" << pos_letracomum_2;
		//ciclo para destruir a antiga palavra uma vez que vai ser substituida de lugar
		for (int i = 0; i < w2.Lenght(); i++)
		{
			Chars[x_2][y_2+i].Set_Ch('A' + rand() % 26);
			Chars[x_2][y_2 + i].set_free(0);
		}
		
		//ciclo para saber se vai só cruzar com 1 letra ou com mais
		for(int i=0; i < w2.Lenght();i++)
		{
			if(Chars[coord_letracomum_1.GetX()][(coord_letracomum_1.GetY() - pos_letracomum_2) + i].get_free() == 1)
			{
				cont++;
			}
		}
		//ciclo para cruzarmos a 2 palavra com a primeira
		for(int j=0; j < w2.Lenght(); j++)
		{
			/*condicao para testar se a palavra cruzada vai caber na matriz ao cruzarmos com a 1º palavra
			, houver as mesmas condições partimos entao para o cruzamemnto da mesma caso contrario chamamos o método
			insert_freespace e colocamos a flag=0 para assim devolver as coordenadas do metodo insert_freespace e nao deste*/
			if ((coord_letracomum_1.GetY() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetY() + w2.Lenght()) <= BoardHeight) && (coord_letracomum_1.GetX() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetX() + w2.Lenght()) <= BoardWidth) && (cont == 1))
			{			
				Chars[coord_letracomum_1.GetX()][(coord_letracomum_1.GetY() - pos_letracomum_2) + j].Set_Ch(w2.Get_Ch(j));
				Chars[coord_letracomum_1.GetX()][(coord_letracomum_1.GetY() - pos_letracomum_2) + j].set_free(1);
			}
			else
			{	
				new_c = Insert_freeSpace(w2, w1, w2.Get_Orient(), w1.Get_Orient());
				//como as coordenadas ja foram alteradas no metodo anterior nao precisamos de mudar novamente entao colocamos a flag a 0
				flag = 0;
				//para terminar o ciclo e sair do mesmo
				j = (int)w2.Lenght();
			}
		}
		//volta a escrever a primeira palavra de modo a certificar nao há lapsos
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x + i][y].Set_Ch(w1.Get_Ch(i));
			Chars[x + i][y].set_free(1);
		}

		/*Tal como foi dito anteriormente se a flag=1 devolve as coordenadas do metodo realloc(este) caso seja flag=0 devolve as coordenadas
		do metodo insert_freespace*/
		if (flag == 1)
		{
			//Definicao das coordenadas da primeira letra 2º palavra(palavra cruzada)
			new_coord.SetX(coord_letracomum_1.GetX());
			new_coord.SetY(coord_letracomum_1.GetY() - pos_letracomum_2);
			return  new_coord;//devolvemos essas mesmas coordenadas
		}
		else
		{
			/*Caso a flag=0 significa que usou o metodo insert_freespace e devolvemos essas coordenadas atualizadas*/
			return new_c;
		}
		
	}
	/*O MESMO SE APLICA ÀS RESTANTES CONDICOES A UNICA COISA QUE MUDA É A ORIENTAÇÃO E A MANEIRA COMO AS CRUZAMOS
	MAS O RACIOCINIO É O MESMO*/
	else if(w1.Get_Orient() == 1 && w2.Get_Orient() == 3)
	{
		for (int i = 0; i < w1.Lenght(); i++)
		{
			if (Chars[x + i][y].Get_Ch() == ch)
			{
				coord_letracomum_1.SetX(x + i);
				coord_letracomum_1.SetY(y);
				i = (int)w1.Lenght();
			}
		}
		/*cout << "Coord. da primeira palavra onde tem letra comum -> ";
		coord_letracomum_1.Show();
		cout << endl;*/

		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (w2.Get_Ch(i) == ch)
			{
				pos_letracomum_2 = i;
				i = (int)w2.Lenght();
			}
		}
		//cout << "Posicao da letra da segunda palavra que tem a letra em comum:" << pos_letracomum_2;
		for (int i = 0; i < w2.Lenght(); i++)
		{
			Chars[x_2 + i][y_2+i].Set_Ch('A' + rand() % 26);
			Chars[x_2 + i][y_2+i].set_free(0);
		}

		//ciclo para saber se vai só cruzar com 1 letra ou com mais
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + i][(coord_letracomum_1.GetY() - pos_letracomum_2) + i].get_free() == 1)
			{
				cont++;
			}
		}
		for (int j = 0; j < w2.Lenght(); j++)
		{
			/*Se couber na matriz a palavra cruzada, cruzamo-la caso contrario usamos o insert_freespace*/
			if ((coord_letracomum_1.GetY() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetY() + w2.Lenght()) <= BoardHeight) && (coord_letracomum_1.GetX() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetX() + w2.Lenght()) <= BoardWidth) && (cont ==1))
			{
				Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + j][(coord_letracomum_1.GetY() - pos_letracomum_2) + j].Set_Ch(w2.Get_Ch(j));
				Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + j][(coord_letracomum_1.GetY() - pos_letracomum_2) + j].set_free(1);			
			}
			else
			{
				new_c = Insert_freeSpace(w2, w1, w2.Get_Orient(), w1.Get_Orient());
				flag = 0;
				j = (int)w2.Lenght();
			}
		}
		//volta a escrever a primeira palavra de modo a certificar nao há lapsos
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x + i][y].Set_Ch(w1.Get_Ch(i));
			Chars[x + i][y].set_free(1);
		}

		if (flag == 1)
		{
			
			new_coord.SetX(coord_letracomum_1.GetX() - pos_letracomum_2);
			new_coord.SetY(coord_letracomum_1.GetY() - pos_letracomum_2);
			return  new_coord;
		}
		else
		{
			return new_c;
		}
	}
	//1 PALAVRA- HORIZONTAL; 2 PALAVRA -> VERTICAL
	else if (w1.Get_Orient() == 2 && w2.Get_Orient() == 1)
	{
		//encontrar a coordenada da palavra principal onde tem a letra em comum
		for (int i = 0; i < w1.Lenght(); i++)
		{
			if (Chars[x][y+i].Get_Ch() == ch)
			{
				coord_letracomum_1.SetX(x);
				coord_letracomum_1.SetY(y+i);
				i = (int)w1.Lenght();
			}
		}
		/*cout << "Coord. da primeira palavra onde tem letra comum -> ";
		coord_letracomum_1.Show();
		cout << endl;*/

		//encontrar a posicao da letra da segunda palavra que tem a letra em comum com a primeira palavra
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (w2.Get_Ch(i) == ch)
			{
				pos_letracomum_2 = i;
				i = (int)w2.Lenght();
			}
		}		
		//cout << "Posicao da letra da segunda palavra que tem a letra em comum:" << pos_letracomum_2;
		//ciclo para destruir a antiga palavra uma vez que vai ser substituida de lugar
		for(int i = 0; i < w2.Lenght(); i++)
		{
			Chars[x_2 + i][y_2].Set_Ch('A' + rand() % 26);
			Chars[x_2 + i][y_2].set_free(0);
		}

		//ciclo para saber se vai só cruzar com 1 letra ou com mais
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + i][coord_letracomum_1.GetY()].get_free() == 1)
			{
				cont++;
			}
		}
		//ciclo para cruzarmos a 2 palavra com a primeira
		for (int j = 0; j < w2.Lenght(); j++)
		{
			if ((coord_letracomum_1.GetY() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetY() + w2.Lenght()) <= BoardHeight) && (coord_letracomum_1.GetX() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetX() + w2.Lenght()) <= BoardWidth)&& (cont ==1))
			{
				Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + j][coord_letracomum_1.GetY()].Set_Ch(w2.Get_Ch(j));
				Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + j][coord_letracomum_1.GetY()].set_free(1);
			}
			else
			{
				new_c = Insert_freeSpace(w2, w1, w2.Get_Orient(), w1.Get_Orient());
				flag = 0;
				j = (int)w2.Lenght();
			}
		}
		//volta a escrever a primeira palavra de modo a certificar nao há lapsos
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x][y + i].Set_Ch(w1.Get_Ch(i));
			Chars[x][y + i].set_free(1);
		}
		if (flag == 1)
		{		
			new_coord.SetX(coord_letracomum_1.GetX()-pos_letracomum_2);
			new_coord.SetY(coord_letracomum_1.GetY());
			return  new_coord;
		}
		else
		{
			return new_c;
		}
	}
	else if (w1.Get_Orient() == 2 && w2.Get_Orient() == 2)
	{
		
		new_c = Insert_freeSpace(w2, w1, w2.Get_Orient(), w1.Get_Orient());
		return new_c;
	}
	else if (w1.Get_Orient() == 2 && w2.Get_Orient() == 3)
	{    
		//encontrar a coordenada da palavra principal onde tem a letra em comum
		for (int i = 0; i < w1.Lenght(); i++)
		{
			if (Chars[x][y + i].Get_Ch() == ch)
			{
				coord_letracomum_1.SetX(x);
				coord_letracomum_1.SetY(y + i);
				i = (int)w1.Lenght();
			}
		}
		//cout << "Coord. da primeira palavra onde tem letra comum -> ";
		//coord_letracomum_1.Show();
		//cout << endl;

		//encontrar a posicao da letra da segunda palavra que tem a letra em comum com a primeira palavra
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (w2.Get_Ch(i) == ch)
			{
				pos_letracomum_2 = i;
				i = (int)w2.Lenght();
			}
		}
		//cout << "Posicao da letra da segunda palavra que tem a letra em comum:" << pos_letracomum_2;

		//ciclo para destruir a antiga palavra uma vez que vai ser substituida de lugar
		for (int i = 0; i < w2.Lenght(); i++)
		{
			Chars[x_2 + i][y_2+i].Set_Ch('A' + rand() % 26);
			Chars[x_2 + i][y_2+i].set_free(0);
		}
		//ciclo para saber se vai só cruzar com 1 letra ou com mais
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + i][((coord_letracomum_1.GetY() - pos_letracomum_2) + i)].get_free() == 1)
			{
				cont++;
			}
		}
		//ciclo para cruzarmos a 2 palavra com a primeira
		for (int j = 0; j < w2.Lenght(); j++)
		{
			if ((coord_letracomum_1.GetY() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetY() + w2.Lenght()) <= BoardHeight) && (coord_letracomum_1.GetX() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetX() + w2.Lenght()) <= BoardWidth) && (cont == 1))
			{
				Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + j][((coord_letracomum_1.GetY() - pos_letracomum_2) + j)].Set_Ch(w2.Get_Ch(j));
				Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + j][((coord_letracomum_1.GetY() - pos_letracomum_2) + j)].set_free(1);				
			}
			else
			{
				new_c = Insert_freeSpace(w2, w1, w2.Get_Orient(), w1.Get_Orient());
				j = (int)w2.Lenght();
				flag = 0;
			}
		}
		//volta a escrever a primeira palavra de modo a certificar nao há lapsos
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x][y + i].Set_Ch(w1.Get_Ch(i));
			Chars[x][y + i].set_free(1);
		}

		if (flag == 1)
		{
			
			new_coord.SetX(coord_letracomum_1.GetX() - pos_letracomum_2);
			new_coord.SetY(coord_letracomum_1.GetY() - pos_letracomum_2);
			return  new_coord;			
		}
		else 
		{
			return new_c;
		}		
	}

	else if (w1.Get_Orient() == 3 && w2.Get_Orient() == 1)
	{
		//encontrar a coordenada da palavra principal onde tem a letra em comum
		for (int i = 0; i < w1.Lenght(); i++)
		{
			if (Chars[x+i][y+i].Get_Ch() == ch)
			{
				coord_letracomum_1.SetX(x+i);
				coord_letracomum_1.SetY(y + i);
				i = (int)w1.Lenght();
			}
		}
		/*cout << "Coord. da primeira palavra onde tem letra comum -> ";
		coord_letracomum_1.Show();
		cout << endl;*/

		//encontrar a posicao da letra da segunda palavra que tem a letra em comum com a primeira palavra
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (w2.Get_Ch(i) == ch)
			{
				pos_letracomum_2 = i;
				i = (int)w2.Lenght();
			}
		}
		//cout << "Posicao da letra da segunda palavra que tem a letra em comum:" << pos_letracomum_2;
		//ciclo para destruir a antiga palavra uma vez que vai ser substituida de lugar
		for (int i = 0; i < w2.Lenght(); i++)
		{
			Chars[x_2 + i][y_2].Set_Ch('A' + rand() % 26);
			Chars[x_2 + i][y_2].set_free(0);
		}

		//ciclo para saber se vai só cruzar com 1 letra ou com mais
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + i][coord_letracomum_1.GetY()].get_free() == 1)
			{
				cont++;
			}
		}
		//ciclo para cruzarmos a 2 palavra com a primeira
		for (int j = 0; j < w2.Lenght(); j++)
		{
			if ((coord_letracomum_1.GetY() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetY() + w2.Lenght()) <= BoardHeight) && (coord_letracomum_1.GetX() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetX() + w2.Lenght()) <= BoardWidth) && (cont==1))
			{		
				Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + j][coord_letracomum_1.GetY()].Set_Ch(w2.Get_Ch(j));
				Chars[(coord_letracomum_1.GetX() - pos_letracomum_2) + j][coord_letracomum_1.GetY()].set_free(1);				
			}
			else
			{
				new_c = Insert_freeSpace(w2, w1, w2.Get_Orient(), w1.Get_Orient());
				j = (int)w2.Lenght();
				flag = 0;
			}
		}
		//volta a escrever a primeira palavra de modo a certificar nao há lapsos
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x + i][y + i].Set_Ch(w1.Get_Ch(i));
			Chars[x + i][y + i].set_free(1);
		}

		if (flag == 1)
		{		
			new_coord.SetX(coord_letracomum_1.GetX()- pos_letracomum_2);
			new_coord.SetY(coord_letracomum_1.GetY());
			return  new_coord;
		}
		else 
		{
			return new_c;
		}
	}
	else if (w1.Get_Orient() == 3 && w2.Get_Orient() == 2)
	{
		//encontrar a coordenada da palavra principal onde tem a letra em comum
		for (int i = 0; i < w1.Lenght(); i++)
		{
			if (Chars[x + i][y + i].Get_Ch() == ch)
			{
				coord_letracomum_1.SetX(x + i);
				coord_letracomum_1.SetY(y + i);
				i = (int)w1.Lenght();
			}
		}
		/*cout << "Coord. da primeira palavra onde tem letra comum -> ";
		coord_letracomum_1.Show();
		cout << endl;*/

		//encontrar a posicao da letra da segunda palavra que tem a letra em comum com a primeira palavra
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (w2.Get_Ch(i) == ch)
			{
				pos_letracomum_2 = i;
				i = (int)w2.Lenght();
			}
		}
		//cout << "Posicao da letra da segunda palavra que tem a letra em comum:" << pos_letracomum_2;

		//ciclo para destruir a antiga palavra uma vez que vai ser substituida de lugar
		for (int i = 0; i < w2.Lenght(); i++)
		{
			Chars[x_2][y_2+i].Set_Ch('A' + rand() % 26);
			Chars[x_2][y_2+i].set_free(0);
		}
		//ciclo para saber se vai só cruzar com 1 letra ou com mais
		for (int i = 0; i < w2.Lenght(); i++)
		{
			if (Chars[(coord_letracomum_1.GetX())][((coord_letracomum_1.GetY() - pos_letracomum_2) + i)].get_free() == 1)
			{
				cont++;
			}
		}
		//ciclo para cruzarmos a 2 palavra com a primeira
		for (int j = 0; j < w2.Lenght(); j++)
		{
			if ((coord_letracomum_1.GetY() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetY() + w2.Lenght()) <= BoardHeight) && (coord_letracomum_1.GetX() - pos_letracomum_2) >= 0 && ((coord_letracomum_1.GetX() + w2.Lenght()) <= BoardWidth) && (cont==1))
			{
				Chars[(coord_letracomum_1.GetX())][((coord_letracomum_1.GetY() - pos_letracomum_2) + j)].Set_Ch(w2.Get_Ch(j));
				Chars[(coord_letracomum_1.GetX())][((coord_letracomum_1.GetY() - pos_letracomum_2) + j)].set_free(1);
			}
			else
			{ 
				new_c = Insert_freeSpace(w2, w1, w2.Get_Orient(), w1.Get_Orient());
				j = (int)w2.Lenght();
				flag = 0;
			}
		}
		//volta a escrever a primeira palavra de modo a certificar nao há lapsos
		for(int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x + i][y + i].Set_Ch(w1.Get_Ch(i));
			Chars[x + i][y + i].set_free(1);
		}
		if(flag == 1)
		{
			
			new_coord.SetX(coord_letracomum_1.GetX());
			new_coord.SetY(coord_letracomum_1.GetY() - pos_letracomum_2);
			return  new_coord;
		}
		else 
		{
			return new_c;
		}
	}
	else if (w1.Get_Orient() == 3 && w2.Get_Orient() == 3)
	{
		new_c = Insert_freeSpace(w2,w1, w2.Get_Orient(), w1.Get_Orient());
		return new_c;
	}
return new_c;//esta situação nunca se vai verificar pois as palavras tem sempre uma orientação este return é so para evitar que o compilador de um warning
}

/*Este método é chamado quando as palavras possuem a mesma orientação ou quando é impossivel cruza-las pois uma das palavras
nao iria caber nos limites da matriz. Quando isso acontece este método entra em ação , tem o papel de procurar coordenadas
onde não estejam ocupadas por nenhuma palavra e que tenha o comprimento da mesma palavra, quando isto é feito e verificado
devidamente colocamos essa palavra nessas coordenadas geradas e atualizamos as coordenadas da palavra através do valor que devolvemos
no fim que é um Ponto onde tem as coordenadas da primeira letra da palavra alterada.*/
/*Possui também 4 parâmetros que são as palavras que estao a ser comparadas onde w1 será a segunda palavra ou seja aquela
que vamos mudar de posição e w2 será a fixa. Ori_1 corresponde à orientação de w1 e o mesmo com ori_2.*/
Ponto Board::Insert_freeSpace(Word w1,Word w2, int ori_1, int ori_2)
{
	int x = 0, y = 0, cont = 0, x_1 = 0,y_1 = 0, x_2 = 0, y_2 = 0;//inicialização das variáveis
	//coordenadas iniciais da palavra w1, ou seja aquela que vai ser mudada de sitio
	x_1 = w1.Get_Position().GetX();
	y_1 = w1.Get_Position().GetY();
	//coordenadas inicias da palavra w2, ou seja aquela que é fixa 
	x_2 = w2.Get_Position().GetX();
	y_2 = w2.Get_Position().GetY();
	Ponto coord;

	/*TEMOS DE VERIFICAR PARA TODO O TIPO DE ORIENTAÇÕES QUE ESSAS DUAS PALAVRAS POSSAM TER*/
	/*VERTICAL*/
	if(ori_1 == 1)
	{
		/*Ciclo que encontra nao encontrar um conjunto coordenadas livres
		do tamanho da palavra não para!*/
		do
		{
			//gera numeros aleatorios
			x = rand() % (BoardHeight - w1.Lenght());
			y = rand() % BoardWidth;
			//cout << "\nCOORDENADAS GERADAS: (" << x << "," << y << ")";

			// **PESQUISA DE UM CONJUNTO DE COORDENADAS LIVRES**
			/*Cada vez que encontra uma posicao livre o conta aumenta mais 1
			se o cont tiver o msm numero que o numero de letras significa
			que existem x posicoes livres do tamanho da palavra onde podemos colocar*/
			for(int i= 0; i < w1.Lenght(); i++)
			{
				if(Chars[x+i][y].get_free() == 0)
				{
					cont++;
				}
				else
				{
					//logo fica descartada aquela hipotese
					cont = 0;
				}
			}
		} while (cont < w1.Lenght());

		//temos de destruir onde a palavra se encontrava antes e colocar como livres as coordenadas antigas 
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[(x_1+i)][(y_1)].Set_Ch('A' + rand() % 26);
			Chars[(x_1+i)][(y_1)].set_free(0);
		}
		/*Se saiu do ciclo é pq encontrou coordenadas que estao disponiveis usando essas mesmo para
		transferirmos e colocarmos a palavra*/
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x + i][y].Set_Ch(w1.Get_Ch(i));
			Chars[x + i][y].set_free(1);
		}

		/*Temos de voltar a escrever a palavra que estava em primeiro lugar
		para deste modo nao ficar sobreposta com a que mudamos para isso precisamos
		de saber a orientacao da palavra que estava lá primeiro depois disso é
		so configurar como ira ser reescrita essa mesma palavra com base nessa orientacao*/
		if (ori_2 == 1)
		{
			for (int i = 0; i < w2.Lenght(); i++)
			{
				Chars[(x_2 + i)][(y_2)].Set_Ch(w2.Get_Ch(i));
				Chars[(x_2 + i)][(y_2)].set_free(1);
			}
		}
		else if (ori_2 == 2)
		{
			for (int i = 0; i < w2.Lenght(); i++)
			{
				Chars[(x_2)][(y_2 + i)].Set_Ch(w2.Get_Ch(i));
				Chars[(x_2)][(y_2 + i)].set_free(1);
			}
		}
		else if (ori_2 == 3)
		{
			for (int i = 0; i < w2.Lenght(); i++)
			{
				Chars[(x_2 + i)][(y_2 + i)].Set_Ch(w2.Get_Ch(i));
				Chars[(x_2 + i)][(y_2 + i)].set_free(1);
			}
		}
		//View();
		/*Definimos as coordenadas inicias atualizadas da palavra transferida e devolvemos as mesmas*/
		coord.SetX(x);
		coord.SetY(y);
		return coord;
	}
	/*HORIZONTAL*/
	if(ori_1 ==2)
	{
		do
		{
			//gera numeros aleatorios
			x = rand() % (BoardHeight);
			y = rand() % (BoardWidth - w1.Lenght());
			//cout << "\nCOORDENADAS GERADAS: (" << x << "," << y << ")";
			/*Cada vez que encontra uma posicao livre o conta aumenta mais 1
			se o cont tiver o msm numero que o numero de letras significa
			que existem x posicoes livres do tamanho da palavra onde podemos colocar*/
			for (int i = 0; i < w1.Lenght(); i++)
			{
				if (Chars[x][y+i].get_free() == 0)
				{
					cont++;
				}
				else
				{
					cont = 0;
				}
			}

		} while (cont < w1.Lenght());

		//temos de destruir onde a palavra se encontrava antes 
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x_1][(y_1+i)].Set_Ch('A' + rand() % 26);
			Chars[x_1][(y_1+i)].set_free(0);
		}

		/*Se saiu do ciclo é pq encontrou coordenadas que estao disponiveis*/
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x][y + i].Set_Ch(w1.Get_Ch(i));
			Chars[x][y + i].set_free(1);
		}

		//reescrevemos a palavra que nao foi mudada novamente para evitar qualquer falha.
		if (ori_2 == 1)
		{
			for (int i = 0; i < w2.Lenght(); i++)
			{
				Chars[(x_2 + i)][(y_2)].Set_Ch(w2.Get_Ch(i));
				Chars[(x_2 + i)][(y_2)].set_free(1);
			}
		}
		else if (ori_2 == 2)
		{
			for (int i = 0; i < w2.Lenght(); i++)
			{
				Chars[(x_2)][(y_2 + i)].Set_Ch(w2.Get_Ch(i));
				Chars[(x_2)][(y_2 + i)].set_free(1);
			}
		}
		else if (ori_2 == 3)
		{
			for (int i = 0; i < w2.Lenght(); i++)
			{
				Chars[(x_2 + i)][(y_2 + i)].Set_Ch(w2.Get_Ch(i));
				Chars[(x_2 + i)][(y_2 + i)].set_free(1);
			}
		}
		//View();
		coord.SetX(x);
		coord.SetY(y);
		return coord;
	}
	/*DIAGONAL*/
	if(ori_1 ==3)
	{
		do
		{
			//gera numeros aleatorios
			x = rand() % (BoardHeight -w1.Lenght());
			y = rand() % (BoardWidth - w1.Lenght());
			//cout << "\nCOORDENADAS GERADAS: (" << x << "," << y << ")";
			/*Cada vez que encontra uma posicao livre o conta aumenta mais 1
			se o cont tiver o msm numero que o numero de letras significa
			que existem x posicoes livres do tamanho da palavra onde podemos colocar*/
			for (int i = 0; i < w1.Lenght(); i++)
			{
				if (Chars[x+i][y + i].get_free() == 0)
				{
					cont++;
				}
				else
				{
					cont = 0;
				}
			}

		} while (cont < w1.Lenght());

		//temos de destruir onde a palavra se encontrava antes 
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[(x_1+i)][(y_1 + i)].Set_Ch('A' + rand() % 26);
			Chars[(x_1+i)][(y_1 + i)].set_free(0);
		}
		/*Se saiu do ciclo é pq encontrou coordenadas que estao disponiveis*/
		for (int i = 0; i < w1.Lenght(); i++)
		{
			Chars[x + i][y + i].Set_Ch(w1.Get_Ch(i));
			Chars[x + i][y + i].set_free(1);
		}

		//reescrevemos a palavra que nao foi mudada novamente para evitar qualquer falha.
		if (ori_2 == 1)
		{
			for (int i = 0; i < w2.Lenght(); i++)
			{
				Chars[(x_2 + i)][(y_2)].Set_Ch(w2.Get_Ch(i));
				Chars[(x_2 + i)][(y_2)].set_free(1);
			}
		}
		else if (ori_2 == 2)
		{
			for (int i = 0; i < w2.Lenght(); i++)
			{
				Chars[(x_2)][(y_2 + i)].Set_Ch(w2.Get_Ch(i));
				Chars[(x_2)][(y_2 + i)].set_free(1);
			}
		}
		else if (ori_2 == 3)
		{
			for (int i = 0; i < w2.Lenght(); i++)
			{
				Chars[(x_2 + i)][(y_2 + i)].Set_Ch(w2.Get_Ch(i));
				Chars[(x_2 + i)][(y_2 + i)].set_free(1);
			}
		}
		coord.SetX(x);
		coord.SetY(y);
		//View();
		return coord;
	}
 return coord;
}

void Board::Update_Matrix(int Sy, int Sx)
{
	Ponto aux;
	int x, y;

	for(int a = 0; a< NumWords; a++)
	{
		/*Coordenadas da palavra*/
		x = Words[a].Get_Position().GetX();
		y = Words[a].Get_Position().GetY();
		/*VERTICAL*/
		if(Words[a].Get_Orient() == 1)
		{
			for(int i = 0; i < (int)Words[a].Lenght(); i++ )
			{
				Chars[x + i][y].Set_Ch(Words[a].Get_Ch(i));
				Chars[x + i][y].set_free(1);
			}
		}
		/*HORIZONTAL*/
		else if(Words[a].Get_Orient() == 2)
		{
			for (int i = 0; i < (int)Words[a].Lenght(); i++)
			{
				Chars[x][y+i].Set_Ch(Words[a].Get_Ch(i));
				Chars[x][y+i].set_free(1);
			}
		}
		/*DIAGONAL*/
		else
		{
			for (int i = 0; i < (int)Words[a].Lenght(); i++)
			{
				Chars[x + i][y + i].Set_Ch(Words[a].Get_Ch(i));
				Chars[x + i][y + i].set_free(1);
			}
		}
	}
	//cout << "#####As palavras foram reescritas com sucesso!####" << endl;
	//View();
}