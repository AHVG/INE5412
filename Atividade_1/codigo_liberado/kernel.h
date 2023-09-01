
// TODO Colocar as diretivas para evitar import circular
// TOOD Colocar os imports

class Kernel {

    private:

    CPU cpu;
    Scheduler scheduler;

    public:

    Kernel();
    ~Kernel();

    void initialize();  // Criará os processos e etc
    int run();          // Executa os processo
    void close();       // Destrói tudo que foi criado

}
