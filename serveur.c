#include"common.h"
int compteur=0;
int  main(int argc,char* argv[]){

    if(argc<2)
      {
        printf("Nombre d arguments insuffissants \n");
        return 0;
      }
    int socketServeur=socket(AF_INET,SOCK_STREAM,0);
    if(socketServeur==-1)
      {
        printf("\n [# SERVEUR #]:Erreur de creation du socket()\n");
        return 0;
      }
    struct sockaddr_in addrServeur,addrClient;
    memset(&addrServeur,0,sizeof(addrServeur));
    addrServeur.sin_family=AF_INET;
    addrServeur.sin_port=htons(atoi(argv[1]));
    addrServeur.sin_addr.s_addr=inet_addr("0.0.0.0");//ou bien INADDR_ANY pour désigner tous 
    int bind=bind(socketServeur,(struct sockaddr *)&addrServeur,sizeof(addrServeur));
    if(bind==-1){
       printf("\n [# SERVEUR #]:Erreur de lancement de bind() \n");
       close(socketServeur);
       return 0;
    }
    int list=listen(socketServeur,3);
    if(list==-1){
      printf("\n [# SERVEUR #]:Erreur Lors d'établissement de la file d'attente\n ");
      close(socketServeur);
      return 0;
    }
    int sokClient;
    int tab;
    int taille=sizeof(struct sockaddr_in);
    while(1){ 
    int sokClient=accept(socketServeur,(struct sockaddr *)&addrClient,&taille);
    if(sokClient==-1)
      {
        printf("\n [# SERVEUR #]:Erreur de l acceptation de connexion  au Client :");
        printf("%d | %s \n",htons(addrClient.sin_port),inet_ntoa(addrClient.sin_addr));
        return 0;
      }
    int sed=send(sokClient,&compteur,sizeof(int),0);
    if(sed==-1)
     {
        printf("\n [# SERVEUR #]: Erreur lors de l 'envoie au Client:");
        printf("%d | %s \n",htons(addrClient.sin_port),inet_ntoa(addrClient.sin_addr));
        close(sokClient);
        return 0;
     }
    int rcv=recv(sokClient,&compteur,sizeof(int),0);
    if(rcv<=0)
     {
        printf("\n [# SERVEUR #]: Erreur lors de reception de l'envoie du Client:");
        printf("%d | %s \n",htons(addrClient.sin_port),inet_ntoa(addrClient.sin_addr));
        close(sokClient);
        return 0;  
     }
    printf("\n [# SERVEUR #]: La nouvelle valeur du compteur recu:<< %d >>",compteur);
    sleep(10);
    compteur++;
    }
    close(socketServeur);
    close(sokClient);
  return 0;  
}