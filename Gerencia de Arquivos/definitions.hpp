/*
 * definitions.hpp
 *
 *  Created on: 26 de jun de 2017
 *      Author: vinicius
 */

#ifndef DEFINITIONS_HPP_
#define DEFINITIONS_HPP_
//! Arquivo de definições e includes unicos para organização

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <thread>

//! Define os nomes dos arquivos a serem criados
#define manPD "manpage.dat"
#define ind1 "manPageIndex.dat"
#define ind2 "inverted.dat"
#define ind21 "invertedIndex.dat"
#define lex "lexical.dat"

//! Define variaveis para o uso interno
#define commandSize 50
#define contentSize 139900
#define lexicalIgnoredSize 1200
#define wordSize 50
#define occurrencesSize 5642

//! Variaveis globais
char lexicalIgnored[lexicalIgnoredSize];
char wordsManPage[contentSize];
std::vector<std::string> ignoredStrings = std::vector<std::string>();

//!  Struct do elemento comando com manpage.
/*!  Struct que possui o nome do comando e
 *   conteúdo da manpage do comando.
 */
typedef struct {
	char command[commandSize];
	char content[contentSize];
} ManPage;

//!  Struct do elemento word com ocorrências.
/*!  Struct que possuí a palavra e todas as
 *	 manpages no qual ela existe.
 */
typedef struct {
	char word[wordSize];
	int occurrences[occurrencesSize];
	int occurrenceIndex = -1;
} Word;



#endif /* DEFINITIONS_HPP_ */
