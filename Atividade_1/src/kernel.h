#ifndef _H_KERNEL
#define _H_KERNEL
// TOOD Colocar os imports

class Kernel {

private:
public:
  Kernel() {}
  ~Kernel() {}

  void initialize() {}    // Criará os processos e etc
  int run() { return 1; } // Executa os processo
  void close() {}         // Destrói tudo que foi criado
};

#endif
