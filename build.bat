@echo off
gcc main.c ^
clientes/clientes.c ^
medicamentos/medicamentos.c ^
estoque/estoque.c ^
vendas/vendas.c ^
-Iclientes ^
-Imedicamentos ^
-Iestoque ^
-Ivendas ^
-o farmacia

pause