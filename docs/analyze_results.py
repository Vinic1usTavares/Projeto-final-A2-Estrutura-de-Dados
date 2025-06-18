import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("estatisticas.csv")
n_docs = np.array(data[data["arvore"] == 'RBT']["num_docs"])
print(data[data["arvore"] == 'RBT']["segundos_insercao"])


def plot_fts_comparison(data):

    for key in data.keys():
        rbt = np.array(data[data["arvore"] == 'RBT'][key])
        avl = np.array(data[data["arvore"] == 'AVL'][key])
        bst = np.array(data[data["arvore"] == 'BST'][key])


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

#plot_fts_comparison(data)