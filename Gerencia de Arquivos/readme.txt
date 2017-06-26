Alunos: Vinícius Schwinden Berkenbrock e Thiago Martendal Salvador

Os arquivos abaixo:
	-FileNoAVL.hpp
	-definitions.hpp
	-lexical.dat
	-main.cpp

Devem estar localizados todos no mesmo diretório.
Além disso, os arquivos com extensão "txt" que possuem os conteúdos das manpages, devem estar dentro de um diretório nomeado "ManPages" junto com os arquivos acima.

LINHA DE COMANDO PARA COMPILAÇÃO:

g++ -o main *.cpp -g -lm -lutil -lpthread -std=c++11 -Wall -Werror

LINHA DE COMANDO PARA EXECUÇÃO:

./main ManPages/*.txt