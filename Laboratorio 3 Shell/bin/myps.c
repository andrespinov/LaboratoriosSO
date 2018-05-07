#include <dirent.h>	
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>

struct linux_dirent {
	long   d_ino;
	off_t  d_off;
	unsigned short d_reclen;
	char   d_name[];
};

int esNumero(char *);

int main(int argc, char *argv[])
{
	int fd, lectura;
	char buf[1024], ruta[20];
	struct linux_dirent *d;
	int bpos;

	char nombre[1024];

  strcpy(ruta, "/proc/");

	fd = open(ruta, O_RDONLY | O_DIRECTORY);
	if (fd == -1){
		printf("No se pudo abrir la ruta /proc/\n");
  }
	for ( ; ; ) {
		lectura = syscall(SYS_getdents, fd, buf, 1024);
		if (lectura == -1){
      printf("No es posible usar la función getdents\n");
    }

		if (lectura == 0){
      break;
    }

		for (bpos = 0; bpos < lectura;) {
			d = (struct linux_dirent *) (buf + bpos);
			strcpy(nombre, d->d_name);
      if(esNumero(nombre) == 1){
        printf("%s\n", nombre);
      }
			bpos += d->d_reclen;
		}
	}
	return 0;
}

int esNumero(char *cadena) {
  for(int i = 0; i < strlen( cadena ); i ++) {
    if (cadena[i] < 48 || cadena[i] > 57)
      return 0;
  }
   return 1;
}
