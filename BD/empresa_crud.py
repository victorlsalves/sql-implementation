import os
import json

# Utilitários
def carregar_arquivo(nome):
    if not os.path.exists(nome):
        return []
    with open(nome, "r") as f:
        return [json.loads(linha) for linha in f.readlines()]

def salvar_arquivo(nome, dados):
    with open(nome, "w") as f:
        for item in dados:
            f.write(json.dumps(item) + "\n")

# CRUD Funcionário
def criar_funcionario():
    funcionario = {
        "cpf": input("CPF: "),
        "primeiro_nome": input("Primeiro nome: "),
        "inicial_meio": input("Inicial do meio: "),
        "ultimo_nome": input("Último nome: "),
        "endereco": input("Endereço: "),
        "salario": float(input("Salário: ")),
        "genero": input("Gênero: "),
        "data_nasc": input("Data de nascimento: "),
        "departamento": input("Número do departamento: "),
        "projetos": input("Projetos (números separados por vírgula): ").split(",")
    }

    funcionarios = carregar_arquivo("funcionarios.txt")
    funcionarios.append(funcionario)
    salvar_arquivo("funcionarios.txt", funcionarios)
    print("Funcionário criado com sucesso!")

def listar_funcionarios():
    funcionarios = carregar_arquivo("funcionarios.txt")
    for f in funcionarios:
        print(f)

def atualizar_funcionario():
    cpf = input("CPF do funcionário a atualizar: ")
    funcionarios = carregar_arquivo("funcionarios.txt")
    for f in funcionarios:
        if f["cpf"] == cpf:
            f["endereco"] = input("Novo endereço: ")
            f["salario"] = float(input("Novo salário: "))
            salvar_arquivo("funcionarios.txt", funcionarios)
            print("Funcionário atualizado.")
            return
    print("Funcionário não encontrado.")

def deletar_funcionario():
    cpf = input("CPF do funcionário a remover: ")
    funcionarios = carregar_arquivo("funcionarios.txt")
    novos = [f for f in funcionarios if f["cpf"] != cpf]
    salvar_arquivo("funcionarios.txt", novos)
    print("Funcionário removido.")

# Funções similares podem ser feitas para Departamento e Projeto

# Exemplo de menu principal
def menu():
    while True:
        print("\n1. Criar Funcionário")
        print("2. Listar Funcionários")
        print("3. Atualizar Funcionário")
        print("4. Deletar Funcionário")
        print("0. Sair")
        opcao = input("Escolha uma opção: ")

        if opcao == "1":
            criar_funcionario()
        elif opcao == "2":
            listar_funcionarios()
        elif opcao == "3":
            atualizar_funcionario()
        elif opcao == "4":
            deletar_funcionario()
        elif opcao == "0":
            break
        else:
            print("Opção inválida.")

if __name__ == "__main__":
    menu()
