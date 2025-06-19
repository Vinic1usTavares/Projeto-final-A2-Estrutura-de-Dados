import pandas as pd
import matplotlib.pyplot as plt
import sys

# Lê o caminho do CSV (ou usa padrão)
csv_file =  "docs/estrutura.csv"

# Carrega os dados
df = pd.read_csv(csv_file)

# Lista de métricas para plotar
metricas = {
    "comparacoes_por_operacao": "Média de Comparações por Operação",
    "altura": "Altura da Árvore",
    "menor_caminho": "Menor Caminho (profundidade mínima)"
}

for coluna, titulo in metricas.items():
    plt.figure(figsize=(10, 5))
    for arv in df["arvore"].unique():
        subset = df[df["arvore"] == arv]
        plt.plot(subset["num_docs"], subset[coluna], label=arv.upper(), linewidth=2)
    
    plt.title(f"{titulo} vs Número de Documentos")
    plt.xlabel("Número de Documentos")
    plt.ylabel(titulo)
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    nome_arquivo = f"docs/graficos/grafico_{coluna}.png"
    plt.savefig(nome_arquivo)
    print(f"Gráfico salvo em: {nome_arquivo}")
    plt.show()