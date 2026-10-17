import matplotlib.pyplot as plt
import networkx as nx
import pandas as pd

nodes = pd.read_csv("./simulation_logs/nodes_0.csv", sep=";")
belief_dict = dict(zip(nodes["id"], nodes["belief"]))

edges = pd.read_csv("./simulation_logs/edges_0.csv", sep=";")
G = nx.from_pandas_edgelist(edges, "src_id", "destination_id", create_using=nx.DiGraph())

node_beliefs = [belief_dict.get(node, 0.5) for node in G.nodes()]

fix, ax = plt.subplots(figsize=(8,8))
pos = nx.spring_layout(G, seed=13)

nx.draw(G, pos, ax=ax, with_labels=False, node_color=node_beliefs, cmap=plt.cm.coolwarm, vmin=0, vmax=1, node_size=50, edge_color="#434343", width=0.4, arrows=True, arrowsize=4)


sm = plt.cm.ScalarMappable(cmap=plt.cm.coolwarm, norm=plt.Normalize(vmin=0, vmax=1))
sm.set_array([])
cbar = plt.colorbar(sm, ax=ax, shrink=0.65)
cbar.set_label("Belief", fontsize=12, fontweight="bold")

ax.set_title("Hupeyaszih Polarization Simulation - Analysis", fontsize=14, fontweight="bold")
plt.show()
