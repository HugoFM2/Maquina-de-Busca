#include <iostream> //cin e cout
#include <fstream>  //lidar com arquivos
#include <string>   //cadeia de caracteres
#include <regex>    //ferramente para procurar o padrão de palavras
#include <stdio.h>  //necessário para tornar letras minúsculas
#include <ctype.h>  //idem
#include <set>      //container que armazena apenas uma cópia, não tem repetição
#include <map>      //container do tipo key:value

using namespace std;

int main(){

	int i = 0;
	string filename,line, a, palavra;
	set <string> words;
	smatch m;
	map <string,string> summary;
	regex pattern ("[a-zA-Z0-9]+-?[a-zA-Z0-9]*"); //esse é o padrão para detectar números e letras e possivelmente um hífen no meio (palavras)

    cout<<"*** MAQUINA DE BUSCAS - THALLYS FELIPE GONCALVES BARBOSA - 2018080622 - PDS2 - TF1 ***\n\n\n";
    cout<<"-> DIGITE EM SEQUENCIA O NOME DOS ARQUIVOS QUE DESEJA INCLUIR, EM SEGUIDA DIGITE 0:\n\n";
	while (cin>>filename and filename != "0"){    //funciona enquanto nomes de arquivos estiverem sendo inseridos
		fstream file (filename);
		if (file.is_open()){                      //testa se o arquivo foi aberto com sucesso
 	   		while (getline(file,line)){           //pega cada linha do arquivo
				while (regex_search(line,m,pattern)){  //testa o padrão de palavras com cada linha do arquivo
					for (string x : m) {               //passa cada palavra encontrada pelo padrão para a variável x
					while(x[i]){                       //pega cada caractere da palavra separadamente
						x[i] = tolower(x[i]);          //transforma os caracteres em letra minúscula, se possível
						if (isalnum(x[i]) == 0){       //testa se o caractere é uma letra minúscula, uma letra maiúscula ou número. Se não for:
							x.erase(x.begin()+i);      //apaga o caractere (no caso só pode ser um hífen, devido ao padrão de palavra)
							i--;                       //volta uma unidade no iterator porque o caractere retirado diminuiu a string
						}
						i++;                           //avança para o próximo caractere
					}
					i = 0;                             //volta o iterator para o primeiro caractere da próxima palavra que vier
					words.insert(x);                   //insere a palavra, agora apenas com números e letras minúsculas, no set "words"
					line = m.suffix().str();           /*faz com que a próxima vez que a linha for lida a procura de uma palavra
													   a leitura comece logo após a palavra anterior. Caso contrário, daria um infinite loop
													   com a mesma palavra */
					}
				}
			}
 	    }
  	    file.close();
  	    set<string>::iterator iter;                          //define um iterator para deslocar pelo set "words"
		for(iter=words.begin(); iter!=words.end(); iter++){  //faz com que o iterator comece no início do set e avance uma unidade por vez, até o final
			if (summary.count(*iter) == 0){                  //teste se já existe cada palavra do set como uma key no map "summary"
				summary[*iter] = filename;                   //se não houver, cria uma key com a palvra, tendo o valor como o nome do arquivo
			}
			else {
				summary[*iter] += "\n";                     //se houver, pega o valor e adiciona um "endl"
				summary[*iter] += filename;                 //e adiciona o nome do outro arquivo que também tem a palavra
			}
		}
		words.clear();                                      //limpa o set "words" para que não confunda as palavras de um arquivo com de outro
 	}

    cout<<"\n-> DIGITE A PALAVRA QUE DESEJA BUSCAR: \n\n";
 	while(cin>>palavra){                           //funciona enquanto palavras a serem buscadas forem inseridas
 		cout<<summary[palavra]<<endl;              //retorna os valores a partir da key "palavra", no dicionario "summary
	 }
	return 0;
}
