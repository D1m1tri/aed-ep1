ep1 de aed

Sobre o projeto:
  Se trata de um buscador de palavras presentes em um arquivo de texto predefinido. 
  A organização utilizada pelo programa é selecionada no momento de sua execução, podendo ser escolhido entre
Árvore binária e Lista ligada, ambos implementados do zero. Este projeto foi realizado entre estudantes do 
segundo semestre de Sistemas de Informação da USP, para a disciplina de Análise e Estrutura de Dados.

Como compilar o projeto:
  - tenha certeza que os seguintes arquivos estejam no mesmo diretório:
        -> ep1.c
        -> arvore.h
        -> funcoes.h
        -> lista.h
        
  - uma vez confirmado a presença dos arquivos anteriores no mesmo diretório, execute nesse mesmo diretório:
        -> gcc -o exec ep1.c
        
  - isso irá gerar um executável de nome exec que irá ser chamado no momento de executar o programa.

Como executar o projeto:
  Supondo que você tenha seguido os passos anteriores, agora você possui um arquivo executável de nome exec.
  - No diretório onde se encontra o executável, coloque o arquivo de texto que se deseja realizar a busca.
  
  - execute o seguinte comando:
        -> ./exec <NomeDoArquivo> <TipoDeOrganização>
  No qual exec é o nome do executável, <NomeDoArquivo> se trata do nome do arquivo de texto (sendo necessário 
colocar também a extensão) e <TipoDeOrganização> se refere a qual organização se deve ser utilizada pelo programa,
podendo ser "lista" ou "arvore"
  
  - Dentro do programa, após a leitura do arquivo, o usuário será recebido com um prompt ">". Nesse momento o 
usuário poserá tanto digitar "busca <PalavraASerBuscada>" quanto "fim". O primeiro busca no arquivo a palavra
<PalavraASerBuscada>, enquanto o segundo encerra a operação.

Espero ter ajudado :)
