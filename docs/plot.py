import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

# Lê o caminho do CSV (ou usa padrão)
csv_file = "docs/tempo_indexacao.csv"

# Carrega os dados
df = pd.read_csv(csv_file)

# Agrupa por tipo de árvore
trees = df['arvore'].unique()

plt.figure(figsize=(12, 6))

# Plot
for tree in trees:
    subset = df[df['arvore'] == tree]
    plt.plot(subset['num_docs'], subset['segundos_indexacao'], label=f"{tree.upper()}", linewidth=2)

plt.xlabel("Número de documentos")
plt.ylabel("Tempo de indexação (segundos)")
plt.title("Tempo de Indexação por Estrutura de Dados")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("grafico_indexacao.png")
plt.show()
