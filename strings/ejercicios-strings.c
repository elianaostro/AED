#define _GNU_SOURCE 
// ERROR: el compilador no ha encontrado una declaración explícita de la función getline. 
// Esto puede ocurrir porque el compilador no reconoce la función o porque no se ha incluido la cabecera adecuada.
#include <stdio.h>
#include <stdlib.h>

void ejercicio(const char *buffer, unsigned long len){
  // TODO
    printf("%s",buffer);
}

int main(int argc, char **argv) {
  char *buffer = NULL;
  size_t len;
  size_t read = getline(&buffer, &len, stdin);
  if (read != -1) {
    ejercicio(buffer, len);
  } else {
    printf("No se leyó ninguna línea\n");
  }

  free(buffer);
  return 0;
}
