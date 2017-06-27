#include "FileNoAVL.hpp"
#include "definitions.hpp"

using namespace std;

//! Função ignoredWords.
/*! Inicializa a lista de palavras ignoradas,
 *	encontradas no arquivo lexicalIgnored.txt
 */
void ignoredWords() {
	// Abre o arquivo para leitura
	FILE* lexicalIgnoredTxt = fopen(lex, "r");
	for (int j = 0; j < lexicalIgnoredSize; j++) {
		lexicalIgnored[j] = ' ';
	}

	// Adiciona todos os caracteres a um array
	int i;
	for (i = 0; !feof(lexicalIgnoredTxt); i++) {
		lexicalIgnored[i] = fgetc(lexicalIgnoredTxt);
	}

	// Seta o char de término do conteúdo
	lexicalIgnored[i - 1] = '\0';

	// Corta o array de char na ocorrência de espacos
	char *pch;
	pch = strtok(lexicalIgnored,
			" ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");

	// Realiza os cortes até o fim do array e adiciona as palavras em um vetor
	while (pch != NULL) {
		ignoredStrings.push_back(pch);
		pch = strtok(NULL,
				" ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
	}
	fclose(lexicalIgnoredTxt);
}

//! Função createManpageDat.
/*! Responsável por gerar o arquivo manpage.dat
 *  \param argc número de arquivos.txt que serão lidos
 *  \param argv array com os nomes dos arquivos.txt a serem lidos
 */
void createManpageDat(int argc, char* argv[]) {
	// Cria o arquivo manpage.dat (guarda as manpages)
	FILE* manPageDat = fopen(manPD, "w");

	for (int i = 1; i < argc; i++) {
		///////////////
		//MANPAGE.DAT//
		///////////////
		// Abre manpage.txt
		FILE* manPageTxt = fopen(argv[i], "r");

		// Verifica se ocorreu erro ao abrir o arquivo
		if (manPageTxt == NULL) {
			perror("Erro ao abrir manpage.txt");
		}

		ManPage manPage;

		// Preenche o comando com espaço em branco
		for (int j = 0; j < commandSize; j++) {
			manPage.command[j] = ' ';
		}

		// Altera a ultima ocorrencia do '.' para o char de término '\0'
		*strrchr(argv[i], '.') = '\0';

		// Copia o nome do comando
		strcpy(manPage.command, argv[i]);

		// Retorna o argv[i] ao nome original
		*strchr(argv[i], '\0') = '.';

		// Preenche o conteudo com espaços em branco e as palavras
		for (int j = 0; j < contentSize; j++) {
			manPage.content[j] = ' ';
		}

		// Copia o conteudo e as palavras do txt
		int k;
		for (k = 0; !feof(manPageTxt); k++) {
			char c = fgetc(manPageTxt);
			manPage.content[k] = c;
		}

		// Seta o char de término do conteúdo
		manPage.content[k - 1] = '\0';
		wordsManPage[k - 1] = '\0';

		// Fecha o arquivo txt
		fclose(manPageTxt);
		fwrite(&manPage, sizeof(ManPage), 1, manPageDat);
	}
	fclose(manPageDat);

}
//! Função create1Index.
/*! Responsável por gerar o arquivo manPageIndex.dat
 */
void create1Index() {
	FILE* manPageDat = fopen(manPD, "r");

	FILE* manPageIndexDat = fopen(ind1, "w+");
	int manPageIndexRoot = 0;
	fwrite(&manPageIndexRoot, sizeof(int), 1, manPageIndexDat);

	ManPage manPage;

	int manpagePosition = ftell(manPageDat);

	while (fread(&manPage, sizeof(manPage), 1, manPageDat) == 1) {
		FileNoAVL *avlNode = new FileNoAVL(manpagePosition, manPage.command,
				fopen(ind1, "r+"));
		rewind(manPageIndexDat);
		// Lê a raiz
		fread(&manPageIndexRoot, sizeof(int), 1, manPageIndexDat);
		// Insere o nó na árvore
		manPageIndexRoot = avlNode->insert(avlNode->getNode(),
				manPageIndexRoot);
		rewind(manPageIndexDat);
		// Atualiza a raiz
		fwrite(&manPageIndexRoot, sizeof(int), 1, manPageIndexDat);
		delete avlNode;

		manpagePosition = ftell(manPageDat);
	}

	fclose(manPageIndexDat);
	fclose(manPageDat);
}
//! Função create2Index.
/*! Responsável por gerar os arquivos:
 *  inverted.dat e invertedIndex.dat
 */
void create2Index() {
	// Cria o arquivo manpage.dat (guarda as manpages)
	FILE* manPageDat = fopen(manPD, "r");

	// Cria o arquivo inverted.dat (guarda o arquivo invertido, chaves secundarias)
	FILE* invertedDat = fopen(ind2, "w+");

	// Cria o arquivo invertedIndex.dat (guarda a arvore de chave secundaria)
	FILE* invertedIndexDat = fopen(ind21, "w+");
	int invertedIndexRoot = 0;
	fwrite(&invertedIndexRoot, sizeof(int), 1, invertedIndexDat);

	ManPage manPage;

	int manpagePosition = ftell(manPageDat);

	while (fread(&manPage, sizeof(manPage), 1, manPageDat) == 1) {
		// Preenche o conteudo com espaços em branco e as palavras
		for (int j = 0; j < contentSize; j++)
			wordsManPage[j] = ' ';

		// Copia o conteudo e as palavras do txt
		int k;
		for (k = 0; manPage.content[k]; k++)
			wordsManPage[k] = tolower(manPage.content[k]);

		// Seta o char de término do conteúdo
		wordsManPage[k - 1] = '\0';

		// Corta o array de char na ocorrência dos delimitadores
		char *pch;
		pch = strtok(wordsManPage,
				" ',.-+:<>[]()=;|_%*&$#@!?}{/^\"0123456789\t\r\n\f\v");

		// Realiza os cortes até o fim do array e também compara com a lista de
		// palavras ignoradas
		while (pch != NULL) {
			const char *c;
			bool accepted = true;
			for (unsigned int i = 0; i < ignoredStrings.size(); i++) {
				c = ignoredStrings[i].c_str();
				if (strcmp(pch, c) == 0) {
					accepted = false;
					break;
				}
			}
			if (accepted == true) {
				char pchTmp[100];
				for (int i = 0; i < commandSize; i++) {
					pchTmp[i] = ' ';
				}
				strcpy(pchTmp, pch);
				FileNoAVL *avlNode = new FileNoAVL(0, pchTmp,
						fopen(ind21, "r+"));
				int wordAddress = avlNode->search(avlNode->getNode());
				delete avlNode;
				if (wordAddress == -1) {
					Word wordTmp;
					wordTmp.occurrenceIndex = 0;
					wordTmp.occurrences[wordTmp.occurrenceIndex] =
							manpagePosition;
					for (int j = 0; j < wordSize; j++) {
						wordTmp.word[j] = ' ';
					}
					strcpy(wordTmp.word, pch);
					fseek(invertedDat, 0, SEEK_END);
					int invertedPosition = ftell(invertedDat);
					fwrite(&wordTmp, sizeof(Word), 1, invertedDat);

					FileNoAVL *avlNode = new FileNoAVL(invertedPosition,
							wordTmp.word, fopen(ind21, "r+"));
					rewind(invertedIndexDat);
					// Lê a raiz
					fread(&invertedIndexRoot, sizeof(int), 1, invertedIndexDat);
					// Insere o nó na árvore
					invertedIndexRoot = avlNode->insert(avlNode->getNode(),
							invertedIndexRoot);
					rewind(invertedIndexDat);
					// Atualiza a raiz
					fwrite(&invertedIndexRoot, sizeof(int), 1,
							invertedIndexDat);
					delete avlNode;
				} else {
					fseek(invertedDat, wordAddress, SEEK_SET);
					Word wordTmp;
					fread(&wordTmp, sizeof(Word), 1, invertedDat);
					if (wordTmp.occurrences[wordTmp.occurrenceIndex]
							!= manpagePosition) {
						wordTmp.occurrenceIndex++;
						wordTmp.occurrences[wordTmp.occurrenceIndex] =
								manpagePosition;
						fseek(invertedDat, wordAddress, SEEK_SET);
						fwrite(&wordTmp, sizeof(Word), 1, invertedDat);
						fflush(invertedDat);
					}
				}
			}

			pch = strtok(NULL,
					" ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
		}

		manpagePosition = ftell(manPageDat);
	}

	fclose(manPageDat);
	fclose(invertedDat);
	fclose(invertedIndexDat);
}
//! Função createDatFiles.
/*! Responsável por chamar as funções para gerar arquivos
 *  Usa threads para agilizar o processo
 *  \param argc número de arquivos.txt que serão lidos
 *  \param argv array com os nomes dos arquivos.txt a serem lidos
 */
void createDatFiles(int argc, char *argv[]) {
	thread t0(ignoredWords);
	createManpageDat(argc, argv);
	t0.join();
	cout << "Arquivo principal gerado" << endl;
	thread t1(create1Index);
	thread t2(create2Index);
	t1.join();
	cout << "Indexagem primaria concluida" << endl;
	t2.join();
	cout << "Indexagem secundaria concluida" << endl << endl;
}
//! Função searchByCommand.
/*! Realiza a busca da manpage de um comando, pela sua chave primária.
 */
void searchByCommand() {
	printf("\nInforme o nome do comando a ser procurado:\n");
	char command[100] = "ManPages/";
	for (int i = 9; i < commandSize; i++) {
		command[i] = ' ';
	}
	scanf("%s", &command[9]);

	FileNoAVL *avlNode = new FileNoAVL(0, command, fopen(ind1, "r+"));
	int commandAddress = avlNode->search(avlNode->getNode());
	if (commandAddress == -1) {
		printf("Comando inexistente\n");
		return;
	}
	ManPage manPage;
	FILE* manPageDat = fopen(manPD, "r");
	fseek(manPageDat, commandAddress, SEEK_SET);
	fread(&manPage, sizeof(ManPage), 1, manPageDat);
	printf("COMANDO: %s\n", manPage.command);
	printf("CONTEÚDO: %s\n", manPage.content);
	delete avlNode;
	fclose(manPageDat);
}
//! Função searchBySingleWord
/*! Realiza a busca de manpages que contém a
 * 	chave secundária definida pelo usuário
 */
Word searchBySingleWord(char *c) {
	char word[100];
	Word wordTmp;
	bool valid = true;
	if (c == NULL) {
		printf("\nInforme a palavra a ser procurada:\n");
		for (int i = 0; i < commandSize; i++) {
			word[i] = ' ';
		}
		scanf("%s", word);
	} else {
		strcpy(word, c);
	}

	FileNoAVL *avlNode = new FileNoAVL(0, word, fopen(ind21, "r+"));
	int wordAddress = avlNode->search(avlNode->getNode());
	delete avlNode;
	if (wordAddress == -1) {
		printf("Palavra inexistente\n");
		valid = false;
	}

	if(valid == true) {
	FILE* invertedDat = fopen(ind2, "r");
	fseek(invertedDat, wordAddress, SEEK_SET);
	fread(&wordTmp, sizeof(Word), 1, invertedDat);
	fclose(invertedDat);

	ManPage manPage;
	FILE* manPageDat = fopen(manPD, "r");
	for (int i = 0; i <= wordTmp.occurrenceIndex; i++) {
		fseek(manPageDat, wordTmp.occurrences[i], SEEK_SET);
		fread(&manPage, sizeof(ManPage), 1, manPageDat);
		if (c == NULL)
			printf("%s\n", manPage.command);
	}
	fclose(manPageDat);
	}
	return wordTmp;
}
//! Função searchByTwoWord
/*! Realiza a busca de manpages que contém as duas
 * 	chaves secundárias definidas pelo usuário
 */
void searchByTwoWords() {
	printf("\nInforme a primeira palavra a ser procurada:\n");
	char word[100];
	for (int i = 0; i < commandSize; i++) {
		word[i] = ' ';
	}
	scanf("%s", word);

	Word wordTmp = searchBySingleWord(word);
	if (wordTmp.occurrenceIndex == -1)
		return;

	printf("\nInforme a segunda palavra a ser procurada:\n");
	char word2[100];
	for (int i = 0; i < commandSize; i++) {
		word2[i] = ' ';
	}
	scanf("%s", word2);

	Word wordTmp2 = searchBySingleWord(word2);
	if (wordTmp2.occurrenceIndex == -1)
		return;

	std::vector<int> wordOccurrences = std::vector<int>();
	for (int i = 0; i <= wordTmp.occurrenceIndex; i++)
		wordOccurrences.push_back(wordTmp.occurrences[i]);
	sort(wordOccurrences.begin(), wordOccurrences.end());

	std::vector<int> wordOccurrences2 = std::vector<int>();
	for (int i = 0; i <= wordTmp2.occurrenceIndex; i++)
		wordOccurrences2.push_back(wordTmp2.occurrences[i]);
	sort(wordOccurrences2.begin(), wordOccurrences2.end());

	std::vector<int> intersection;
	set_intersection(wordOccurrences.begin(), wordOccurrences.end(),
			wordOccurrences2.begin(), wordOccurrences2.end(),
			back_inserter(intersection));

	if (intersection.size() == 0) {
		printf(
				"\nNão existe a ocorrência destas duas palavras em um única manpage\n");
		return;
	}

	FILE* manPageDat = fopen(manPD, "r");
	for (int i = 0; i < (int) intersection.size(); i++) {
		ManPage manPage;
		fseek(manPageDat, intersection[i], SEEK_SET);
		fread(&manPage, sizeof(ManPage), 1, manPageDat);
		printf("%s\n", manPage.command);
	}
	fclose(manPageDat);
}

int main(int argc, char* argv[]) {
	// INICIA O MENU DO PROGRAMA
	int input;
	system("clear");
	do {
		cout << "Escolha 1 numero abaixo" << endl << endl;
		cout << "1 para gerar arquivos indexados" << endl;
		cout << "2 para buscar conteudo de um comando" << endl;
		cout << "3 para buscar as manpages que possuem uma palavra" << endl;
		cout << "4 para buscar as manpages que possuem 2 palavras" << endl;
		cout << "0 para sair" << endl << endl;
		cin >> input;
		switch (input) {
		case 0:
			exit(0);
		case 1:
			createDatFiles(argc, argv);
			break;
		case 2:
			searchByCommand();
			break;
		case 3:
			searchBySingleWord(NULL);
			break;
		case 4:
			searchByTwoWords();
			break;
		default:
			printf("Opção inválida\n");
		}
	} while (input != 0);
	return 0;
}
