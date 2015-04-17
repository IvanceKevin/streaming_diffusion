#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>

#define LENGTH 35    /* Combien de secondes du signal à stocker */
#define RATE 44100  /* Taux d'échantillonnage par défaut  */
#define SIZE 16     /* taille en bits d'un échantillon: 8 or 16 bits */
#define CHANNELS 1  /* 1 = mono 2 = stereo */

/* Ce buffer gère les données vidéo */
unsigned char buf[LENGTH*RATE*SIZE*CHANNELS/8];

float a,b;

float LittleEndianIntRead(int num_bytes, FILE* pfile,unsigned char *aby,unsigned char *bby) {
int i;int a;
long long int s=0;
for (i=0;i<num_bytes;i++){
    
    a=getc(pfile);
    s+=a << (i*8);
    /* Les données sont codées ici en 16 bits par échantillon : i=0 8 bits de poids faibles i=1 les 8
    autres : il s'agit ici de créer le flux envoyé au HP ou BIEN AU PROGRAMME CLIENT */  
    if(i==0) *aby=(unsigned char) a;
    if(i==1) *bby=(unsigned char) a;
    }

    /* Pour visulaisation avec gnuplot : données formats float */
    
   if (s > (1<<(num_bytes*8-1))) {
        return (float)(s-(1<<(num_bytes*8)));
   }
   else{
        return(float)(s);
   }
   }
   
void main_wave(){
    char pszFileName[]="bbc.wav";  /* NOM du fichier audio : celui-ci doit correspondre à la requête */
    FILE* pFile=NULL;
    char pbType[4];
    int nSampleRate;
    short nChannels;
    short nBitsPerSample;
    int nSamples;
    int nTotalChunkSize;
    char found;
    int nRead;
    float** ppfData;
    int ch;
    int bin;
    unsigned char aby,bby;
    
    pFile=fopen(pszFileName,"rb");
    if(pFile==NULL) {
        printf("Impossible d'ouvrir le fichier : \"%s\"",pszFileName);
	return;
    }
     rewind(pFile);
     fseek(pFile,4,SEEK_CUR);
     fseek(pFile,4,SEEK_CUR);
     fseek(pFile,4,SEEK_CUR);
     fseek(pFile,4,SEEK_CUR);
     fseek(pFile,4,SEEK_CUR);
     fseek(pFile,2,SEEK_CUR);
     
     fread(&nChannels,2,1,pFile);
     fread(&nSampleRate,4,1,pFile);
     fseek(pFile,4,SEEK_CUR);
     fseek(pFile,2,SEEK_CUR);
     
     fread(&nBitsPerSample,2,1,pFile);
     
     nTotalChunkSize=0;
     found=0;
     
     do{
         nRead = fread(pbType,4,1,pFile);
	 nRead = fread(&(nTotalChunkSize),4,1,pFile);
	  if((pbType[0]=='d') && (pbType[1]=='a') && (pbType[2]=='t') && (pbType[3]=='a')){
	  found=1;
	  break;
	  }
	  fseek(pFile,nTotalChunkSize,SEEK_CUR);
     }while(nRead);
     
     if(found){
         nSamples=(nTotalChunkSize)/(nBitsPerSample/8*nChannels);
	 
	 ppfData=malloc(sizeof(float*)*nChannels);
	 for (ch=0; ch<nChannels;ch++) {
	   ppfData[ch]=malloc(sizeof(float)*nSamples);
	 }
	 
	 switch(nBitsPerSample) {
	   case 8 :
	   case 16 :
	   case 24 :
	   case 32 :
	   	     printf("Ce format est pris en charge !\n");

	             for (bin=0;bin<nSamples;bin++) {
		     for (ch=0;ch<nChannels;ch++) {
		         ppfData[ch][bin]=LittleEndianIntRead(nBitsPerSample/8,pFile,&aby,&bby);
		     
		     /* On remplit le buffer avec les données : 8 bits de poids faibles suivis des 8
		     autres : buf sera ensuite envoyé au HP ou sur le flux à destination du client */
		     
		     buf[2*bin]=aby;
		     buf[2*bin+1]=bby;
		   
		        }
		     } 
		     break;
            default:
	             printf("Ce format n'est pas prise en charge");
		     break;
		     }
   }
   for(ch=0;ch<nChannels;ch++) {
       free(ppfData[ch]);
    }
    free(ppfData);
    fclose(pFile);
    
    }   
     

int main()
{
  int fd;	/* Descripteur du fichier son */
  int arg;	/* Argument pour l'appler à ioctl */
  int status;   /* retourne du statut du système */
  int i;
  FILE *fdd;

  /* Lecture du fichier wav : et création du flux dans buffer */
  main_wave();

  /* Gestion de l'interface son : dans le projet streaming, cette partie doit se trouver chez le client */
  /* Ouverture du Device audio */
  fd = open("/dev/dsp", O_RDWR);
  if (fd < 0) {
    perror("Erreur lors de l'ouverture de /dev/dsp");
    exit(1);
  }

  /* Ensemble des paramètres de l'échantillonnage : ce fichier a en effet été échantillonné */
  arg = SIZE;	   /* taille des échantillons */
  status = ioctl(fd, SOUND_PCM_WRITE_BITS, &arg);
  if (status == -1)
    perror("SOUND_PCM_WRITE_BITS ioctl failed");
  if (arg != SIZE)
    perror("Impossible de fixer la valeur de l'éachantillonage");

  arg = CHANNELS;  /* mono ou stereo */
  status = ioctl(fd, SOUND_PCM_WRITE_CHANNELS, &arg);
  if (status == -1)
    perror("SOUND_PCM_WRITE_CHANNELS ioctl failed");
  if (arg != CHANNELS)
    perror("uImpossible de fixer le nombre de canaux");

  arg = RATE;	   /* sampling rate */
  status = ioctl(fd, SOUND_PCM_WRITE_RATE, &arg);
  if (status == -1)
    perror("SOUND_PCM_WRITE_WRITE ioctl failed");
    
     

  while (1) { /* loop until Control-C */
   
      
    printf("Vous devez entendre quelque chose .... : 3 secondes du fichier:\n");

   /* Envoie d'un signal carré pour test */    
   /*    for(i=0;i<4000;i++) {
    	buf[4*i]=0x80;
	buf[4*i+1]=0x80;
	buf[4*i+2]=0xFF;
	buf[4*i+3]=0xFF;
	}*/
	
    /* Autre mise en forme du signal pour test */    
   /*    a=(int) 128.0;b=(int) 256.0;
    for(i=0;i<4000;i++) {
        buf[4*i]=(unsigned char) a;
	buf[4*i+2]=(unsigned char) b;    
	}*/
	
    
    status = write(fd, buf, sizeof(buf)); /* On rejout la même chose pendant 3s */
    if (status != sizeof(buf))
      perror("Mauvais nombre d'octets");
    
    status = ioctl(fd, SOUND_PCM_SYNC, 0); 
  if (status == -1)
    perror("SOUND_PCM_SYNC ioctl failed");
    
 
  }
}	
	 
