#include"common.h"

int main(int argc,char* argv[]){
  
  if(argc<3){
    printf("[# CLIENT #]:Erreur Nombre d argument  insuffissants\n");
    return 0;
  }
  int socketClient;
  socketClient=socket(AF_INET,SOCK_STREAM,0);
  if(socketClient==-1){
    printf("[# CLIENT #]: Erreur de la création du socket()");
    return 0;
  }

  struct sockaddr_in addrServeur;
  memset(&addrServeur,0,sizeof(struct sockaddr_in));
  addrServeur.sin_family=AF_INET;
  addrServeur.sin_port=htons(atoi(argv[2]));
 addrServeur.sin_addr.s_addr=inet_addr(argv[1]);

  int conect=connect(socketClient,(struct sockaddr *)&addrServeur, sizeof(addrServeur));
  if(conect==-1){
    printf("[# CLIENT #]:Erreur du demande de connexion \n");
    close(socketClient);
    return 0;
  }

  int nbrecieve;
    while (1)
  {
    //memset(buffrecieve,0,10*sizeof(char));
    nbrecieve= recv(socketClient,&compteur,sizeof(int),0);
     if(nbrecieve>0)
      {
        printf("[# CLIENT #]:Recu : %d\n",compteur);
      }
    sleep(10);
    compteur++;
    send(socketClient,&compteur, sizeof(int),0);
  }
  close(socketClient);

  return 0;
}