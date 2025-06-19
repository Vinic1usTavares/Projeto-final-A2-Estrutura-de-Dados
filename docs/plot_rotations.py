import pandas as pd
import matplotlib.pyplot as plt
import os

# Caminho para o CSV
csv_path = "docs/benchmark_rotations.csv"
df = pd.read_csv(csv_path)

# Filtra dados por tipo de árvore
avl = df[df['arvore'] == 'avl']
rbt = df[df['arvore'] == 'rbt']

# Cria o gráfico
plt.figure(figsize=(10, 6))
plt.plot(avl['num_docs'], avl['rotacoes_totais'], label='AVL', linewidth=2)
plt.plot(rbt['num_docs'], rbt['rotacoes_totais'], label='RBT', linewidth=2)

# Títulos e rótulos
plt.title('Quantidade de Documentos vs Total de Rotações')
plt.xlabel('Número de Documentos')
plt.ylabel('Total de Rotações')
plt.legend()
plt.grid(True)
plt.tight_layout()

# Cria diretório de saída se não existir
output_dir = "docs/graficos"
os.makedirs(output_dir, exist_ok=True)

# Salva o gráfico
plt.savefig(os.path.join(output_dir, "grafico_rotacoes.png"), dpi=300)

