// RUN: %clang_cc1 -triple x86_64-apple-macos10.7.0 -verify -fopenmp -ferror-limit 100 -o - %s

void foo() {
}

bool foobool(int argc) {
  return argc;
}

struct S1; // expected-note {{declared here}}

int main(int argc, char **argv) {
  #pragma omp parallel if // expected-error {{expected '(' after 'if'}} expected-error {{expected expression}}
  #pragma omp parallel if ( // expected-error {{expected expression}} expected-error {{expected ')'}} expected-note {{to match this '('}}
  #pragma omp parallel if () // expected-error {{expected expression}}
  #pragma omp parallel if (argc // expected-error {{expected ')'}} expected-note {{to match this '('}}
  #pragma omp parallel if (argc)) // expected-warning {{extra tokens at the end of '#pragma omp parallel' are ignored}}
  #pragma omp parallel if (argc > 0 ? argv[1] : argv[2])
  #pragma omp parallel if (foobool(argc)), if (true) // expected-error {{directive '#pragma omp parallel' cannot contain more than one 'if' clause}}
  #pragma omp parallel if (S1) // expected-error {{'S1' does not refer to a value}}
  #pragma omp parallel if (argv[1]=2) // expected-error {{expected ')'}} expected-note {{to match this '('}}
  foo();

  return 0;
}
