#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "hacking.h"
#include "hacking-network.h"


#include <memory.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>


#define LINELENGTH 88200   /* Longueur des paquets recues */

#define RATE 88200  /* Taux d'�chantillonnage par d�faut  */
#define SIZE 16     /* taille en bits d'un �chantillon: 8 or 16 bits */
#define CHANNELS 1  /* 1 = mono 2 = stereo */


int main(int argc, char *argv[]) {
	int sockfd;
	struct hostent *host_info;
	struct sockaddr_in target_addr;
	
	FILE *fdesc;    /* pour le buffer de r�ception */
	FILE *fd;       /* pour le buffer de r�ception */
	size_t n;       /* pour le buffer de r�ception */
	unsigned char buf[LINELENGTH];  /* pour les donn�es */
	unsigned char bufHP[LINELENGTH];  /* pour les donn�es � envoyer dans le HP */
	unsigned char buf1[256];  /* pour les informations */
	int longueur;

        int fdson;	/* Descripteur du fichier son */
        int arg;	/* Argument pour l'appler � ioctl */
        int status;   /* retourne du statut du syst�me */
     
	
	if(argc < 2) {
		printf("Usage: %s <hostname>\n", argv[0]);
		exit(1);
	}
/*-----------------------------------------------------------------------*/
/* Partie GESTION DU SON � mettre dans une fonction : version d�finitive */
/*-----------------------------------------------------------------------*/

  /* Ouverture du Device audio */
  fdson = open("/dev/dsp", O_RDWR);
  if (fdson < 0) {
    perror("Erreur lors de l'ouverture de /dev/dsp");
    exit(1);
  }

  /* Ensemble des param�tres de l'�chantillonnage : ce fichier a en effet �t� �chantillonn� */
  arg = SIZE;	   /* taille des �chantillons */
  status = ioctl(fdson, SOUND_PCM_WRITE_BITS, &arg);
  if (status == -1)
    perror("SOUND_PCM_WRITE_BITS ioctl failed");
  if (arg != SIZE)
    perror("Impossible de fixer la valeur de l'�achantillonage");

  arg = CHANNELS;  /* mono ou stereo */
  status = ioctl(fdson, SOUND_PCM_WRITE_CHANNELS, &arg);
  if (status == -1)
    perror("SOUND_PCM_WRITE_CHANNELS ioctl failed");
  if (arg != CHANNELS)
    perror("uImpossible de fixer le nombre de canaux");

  arg = RATE;	   /* sampling rate */
  status = ioctl(fdson, SOUND_PCM_WRITE_RATE, &arg);
  if (status == -1)
    perror("SOUND_PCM_WRITE_WRITE ioctl failed");
    
/*--------------------------------------------------------*/
/* Partie INITIALISATION de la communication              */
/*--------------------------------------------------------*/

	if((host_info = gethostbyname(argv[1])) == NULL)
		fatal("looking up hostname");

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		fatal("in socket");

	target_addr.sin_family = AF_INET;
	target_addr.sin_port = htons(7890);	
	target_addr.sin_addr = *((struct in_addr *)host_info->h_addr);
	memset(&(target_addr.sin_zero), '\0', 8); // zero the rest of the struct

	if (connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1)
		fatal("connecting to target server");

/*---------------------------------------------------------------*/
/* Cr�ation du Tampon : �vite de perdre des donn�es              */
/*---------------------------------------------------------------*/
       
	
	fdesc=fdopen(sockfd,"r");
	fd=fopen("filecontrole","w");
	if (fd==NULL) 
	    printf("Impossible d'ouvrir le fichier"); 
	
	longueur=0;   /* Attention : longueur doit �tre initialis�e */
	while(longueur==0)
	  longueur=recv_line(sockfd,buf1);
	  	
	buf1[54]='\0';  /* On doit pouvoir g�rer cela autrement ...*/
	fprintf(stdout,"Le client est connecte au serveur !!! %s\n",buf1);
	
        /*************************************************************/
		/*  VOUS INTERVENEZ ICI                                                           */
		/*  Cette partie du programme doit                                                   */
		/*     - Placer dans le tableau buf le contenu d�un paquet re�u dans le  */
		/*       tampon de la socket fdesc.                                                     */
        /*     - Ecrire sur le flux fdson le contenu de buf pour l�envoie aux      */
		/*       haut-parleurs.                                                                        */
		/**************************************************************/
		
	
	send_string(sockfd, strcat(argv[2], "\r\n"));
	while((n=fread(buf, sizeof(char), LINELENGTH, fdesc)))
	{
		status = write(fdson, buf, LINELENGTH);
		if (status == -1)
			perror("SOUND_PCM_SYNC ioctl failed");
	}
	fclose(fd);
	printf("Arret du serveur\n");
	exit(1);
}
