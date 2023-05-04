class arvore:
    def __init__(self, cpf):
        self.cpf = cpf
        self.esquerda = None
        self.direita = None
    
    def remove_node(self, cpf):
        if self is None:
            return self

        if cpf < self.cpf:
            self.esquerda = self.remove_node(self.esquerda, cpf)
        elif cpf > self.cpf:
            self.direita = self.remove_node(self.direita, cpf)
        else:
            if self.esquerda is None:
                temp = self.direita
                self = None
                return temp
            elif self.direita is None:
                temp = self.esquerda
                self = None
                return temp

            temp = self.remove_node(self.direita)
            self.cpf = temp.cpf
            self.direita = self.remove_node(self.direita, temp.cpf)
        return self

    def inserir(self, cpf):
        if cpf==self.cpf:
            print("O CPF ja se encontra cadastado! favor inserir dados validos!")
            return
        if cpf < self.cpf:
            if self.esquerda is None: 
                self.esquerda = arvore(cpf)
            else:
                self.esquerda.inserir(cpf)
        else:
            if self.direita is None:
                self.direita = arvore(cpf)
            else:
                self.direita.inserir(cpf)

    def mostraOrdem(self):
        if self.esquerda:
            self.esquerda.mostraOrdem()
        print(self.cpf)
        if self.direita:
            self.direita.mostraOrdem()

    def procura(self, cpf):
        if cpf < self.cpf:
            if self.esquerda is None:
                return False
            else:
                return self.esquerda.procura(cpf)
        elif cpf > self.cpf:
            if self.direita is None:
                return False
            else:
                return self.direita.procura(cpf)
        else:
            print(self.cpf)
            return True
    
    def main(self, alternativa):
        while True:
            if alternativa == 1:
                self.inserir(int(input("Digite o CPF do funcionario para cadastro: ")))
                return
            if alternativa == 2:
                if self.procura(int(input("Digite o CPF do funcionario para busca: "))):
                    print("Localizado e exibindo dados do funcionario")
                else:
                    print("Nao foi possivel localizar nenhum dado compativel!")
                return
            if alternativa == 3:
                self.remove_node(int(input("Digite o CPF do funcionario para remover: ")))
                return
            if alternativa == 4:
                self.mostraOrdem()
                return
            if alternativa == 5:
                return 5

def menu():
    print("******************************")
    print("*1.Cadastro de Funcionarios  *")
    print("*2.Busca de Funcionario      *")
    print("*3.Remocao de Funcionario    *")
    print("*4.Mostra Todos Funcionarios *")
    print("*5.Fechar programa           *")
    print("******************************")
    return int(input("Digite o numero referente: "))

if __name__ == "__main__":
    aux = arvore(10)
    while True:
        if aux.main(menu()) == 5:
            break
        
    aux.mostraOrdem()
    print("ola")