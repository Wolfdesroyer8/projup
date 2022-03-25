#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Check for inputed name if not the main is the name
  char *name;
  if (argc == 1) {
    name = "main";
  } else {
    name = argv[1];
  }

  // Adds Makefile
  FILE *cfile;
  cfile = fopen("Makefile", "a");
  fprintf(cfile, "%s: main.c\n", name);
  fprintf(cfile, "\tclang main.c -o %s -g -O3 -std=gnu11", name);
  fclose(cfile);

  // Adds the main.c file
  cfile = fopen("main.c", "a");
  fprintf(cfile, "#include <stdio.h>\n");
  fprintf(cfile, "\n");
  fprintf(cfile, "int main(void)\n");
  fprintf(cfile, "{\n");
  fprintf(cfile, "return 0;\n");
  fprintf(cfile, "}");
  fclose(cfile);

  // Adds .gitignore file for the binary
  cfile = fopen(".gitignore", "a");
  fprintf(cfile, "%s", name);
  fclose(cfile);
  // Selects license
  system("set-license");
  return 0;
}
