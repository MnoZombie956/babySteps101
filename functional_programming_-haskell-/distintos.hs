primeiroLista [] = 0
--primeiroLista [_] = 0
primeiroLista (x:resto) = x --head

repeated [] _ = False
repeated (x1:resto1) (n) = n == x1 || repeated (resto1) (n)

distintos [] = True
distintos (x1:resto1) = distintos (resto1) && not (repeated (resto1) (x1))


main = do
    let lista1 = [1,6,3,6] 
    print(distintos lista1)
