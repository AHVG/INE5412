# Variáveis
CXX = g++
CXXFLAGS = -Wall -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Lista de arquivos fonte (.cpp) e cabeçalhos (.h)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
HDRS = $(wildcard $(SRC_DIR)/*.h)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/meu_programa

# Regra para construir o programa
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para construir os objetos a partir dos arquivos fonte
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Regra para limpar os objetos e o executável
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

# Informa ao Make quais regras não são arquivos
.PHONY: all clean

all: $(TARGET)

# Diretório de destino
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))
