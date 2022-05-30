#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern int errno;

int main(int argc, char **argv) {
  int type;
  char *name;
  FILE *currentfile;

  if (argc < 3) {
    printf("Projup - A tool to quickly generate c projects"
           "\n\nusage: projup [<type>] [<name>]"
           "\n\nTypes: bin/lib"
           "\nbin - Creates a project that compiles to a runnable binay"
           "\nlib - Create a project that compiles to a library"
           "\n\nName: String"
           "\nThe name of the project\n");
    return 1;
  } else if (strcmp(argv[1], "bin") == 0) {
    type = 0;
    name = argv[2];
  } else if (strcmp(argv[1], "lib") == 0) {
    type = 1;
    name = argv[2];
  } else {
    printf("Type must be \"bin\" or \"lib\"\n");
    return 1;
  }

  char header[256];
  strcpy(header, name);
  strcat(header, ".h");
  char *files[] = {"Makefile", "main.c", "test.c", header};

  // checks if files already exists
  for (int i = 0; files[i] != NULL; i++) {
    if (access(files[i], F_OK) == 0) {
      printf("The file \"%s\" already exists\n", files[i]);
      exit(1);
    }
  }

  for (int i = 0; currentfile != NULL; i++) {
    currentfile = fopen(files[i], "w");
    if (currentfile == NULL) {
      printf("%s\n", strerror(errno));
      exit(1);
    }
    if (i == 0 && type == 0) {
      fprintf(currentfile,
              "NAME=%s\n\n"
              "CFLAGS= -Wall -Wextra -ggdb -O3 -std=gnu11\n\n"
              "${NAME}: "
              "main.c\n"
              "\tcc main.c -o ${NAME} ${CFLAGS}\n\n"
              "install: ${NAME}\n"
              "\tinstall -D projup /usr/bin\n\n"
              "uninstall:\n"
              "\trm /usr/bin/projup\n\n"
              "clean:\n"
              "\trm projup",
              name);
    } else if (i == 0 && type == 1) {
      fprintf(currentfile,
              "NAME=%s\n\n"
              "CFLAGS= -Wall -Wextra -ggdb -O3 -std=gnu11\n"
              "TESTFLAGS= -I. -L. -l${NAME}\n\n"
              ".PHONY: test\n\n"
              "${NAME}.o: "
              "main.c\n"
              "\tcc main.c -o ${NAME}.o ${CFLAGS} -c -DLOG\n"
              "\tar ruv lib${NAME}.a ${NAME}.o\n"
              "\tranlib lib${NAME}.a\n\n"
              "test: test.c\n\tcc "
              "test.c -o test ${CFLAGS} ${TESTFLAGS}\n\n"
              "install: ${NAME}\n"
              "\tinstall -D lib${NAME}.a /usr/lib/\n\n"
              "\tinstall -D ${NAME}.h /usr/include/"
              "uninstall:\n"
              "\trm /usr/lib/lib${NAME}.a /usr/include/${NAME}/${NAME}.h\n\n"
              "clean:\n"
              "\trm lib${NAME}.a ${NAME}.o test test.o",
              name);
    } else if (i == 1) {
      fprintf(currentfile, "#include <stdio.h>\n\n"
                           "int main(void) {\n"
                           "\tprintf(\"Hello World\");\n"
                           "\treturn 0;\n"
                           "}");
      if (type == 0) {
        i = i + 2;
      }
    } else if (i == 2 && type == 1) {
      fprintf(currentfile, "#include <stdio.h>\n\n"
                           "int main(void) {\n"
                           "\treturn 0;\n"
                           "}");
    } else if (i == 3 && type == 1) {
      fprintf(currentfile, "#prama once");
    }
    fclose(currentfile);
  }
  return 0;
}
