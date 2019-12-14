# Graph Designer

## Introduction

## Commands

The parameters between {} are mandatory.
The parameters between [] are optional.

### Graph commands

***add_link*** *{i} {j} [X]*: add a link from node i to node j, and, from node j to node i if you add X.

***add_path*** *{n1 n2 ... nN} [X]*: create a path through the nodes "n1,...nN". With X the path is created with double connections.

***clean***: remove all links of the graph.

***delete_link*** *{i} {j} [X]*: delete the existing link from node i to node j, and, from node j to node i if you add X.

***delete_path** {n1 n2 ... nN} [X]*: delete a path through the nodes "n1,...nN". With X the path is deleted with double connections.

***is_link** {i} {j}*: return if the link from i to j exists.

***resize** {N}*: change the size of the graph to N and remove all the links.


### Utility commands

***eigenvalues** {A/L/T}*: calculate the eigenvalues of the adjacency matrix (A), normalized laplacian (L) or laplacian (T).

***info***: show the number of nodes and links of the graph.

***line_graph** {A} {B}*: create a line graph of A and saves it in B.

***list_labels** {file_name}*: show the list of labels (graphs) in the "file_name".

***load** {file_name} {label}*: load the graph "label" from the file "file_name".

***matrix***: show the adjacency matrix.

***save** {file_name} {label}*: save the actual graph in the file "file_name" with the name "label".

***show***: show the graph using feh and dot softwares. It creates the files name.png and name.dot.


### System commands

***copy** {A} {B}*: copy the graph A in B.

***delete_graph** {name}*: delete the graph "name".

***exit***: end the current session.

***help***: show this help.

***ls***: show the list of graphs in the current session.

***new_graph** {name}*: it creates new graph "name" or change the current graph to it.

***system** {command}*: execute the command.
