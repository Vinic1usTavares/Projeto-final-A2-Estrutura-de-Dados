import pandas as pd
import matplotlib.pyplot as plt

# Caminho para o seu CSV
csv_path = "benchmark_rotations.csv"  # ajuste se o nome for outro

# Carrega o CSV
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

# Mostra o gráfico
plt.show()
