# Atividade 1
## Simulador de algoritmos de escalonamento

### Como rodar?
#### 1o método
Digite na pasta raiz ./run.sh que automaticamente será feito a compilação do programa e a execução.
#### 2o método
Se o objetivo é testar o programa, digite o ./test.sh para o valgrind executar os testes na memória.
Caso você não possua o valgrind, basta digitar

``` sudo apt-get install valgrind ```

#### 3o método
Se o desejo é compilar e rodar por si mesmo, faça make all e em seguida ./bin/atividade_1

### Como funciona?
Após executar algum dos métodos acima, aparece no terminal uma tela de seleção. Nesse momento, o usuário
deve colocar um valor inteiro de 1 a 5 para indicar qual dos algoritmos rodar e 6 para rodar todos e -1 para sair.

### Saída do programa
Após selecionar algumas das opções de algoritmos, aparecerá como foi a execução do algoritmo por meio de um diagrama
de tempo e as suas métricas (as que foram pedidas). Em seguida, novamente aparecerá o menu perguntando mais uma vez
qual algoritmo se deseja rodar.
