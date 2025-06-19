import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("estatisticas.csv")
print(data)
n_docs = np.array(data[data["arvore"] == 'rbt']["num_docs"])
print(data[data["arvore"] == 'RBT']["segundos_insercao"])


def plot_fts_comparison(data):

    for key in data.keys():
        if key in ['arvore', 'num_docs', 'pior_busca_ms']:
            continue

        rbt = np.array(data[data["arvore"] == 'rbt'][key])
        avl = np.array(data[data["arvore"] == 'avl'][key])
        bst = np.array(data[data["arvore"] == 'bst'][key])


        plt.figure(figsize = (8,6))
        plt.plot(n_docs,rbt, label= "RBT")
        plt.plot(n_docs,avl, label= "AVL")
        plt.plot(n_docs,bst, label= "BST")
        plt.title(f"{key} nas árvores por número de documentos")
        plt.xlabel("Número de documentos")
        plt.ylabel(f"{key}")
        plt.legend()
        plt.show()

    return None

#Obs: Gráfico do pior tempo inutilizável devido a variação durante a execução
# E o arredondamento para 0 devido a ser um tempo muito pequeno
#plot_fts_comparison(data)
